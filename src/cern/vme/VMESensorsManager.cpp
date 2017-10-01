/*
 * VMESensorsManager.cpp
 *
 *      Author: Iacopo Breschi
 */

#include "VMESensorsManager.h"
#include "Event.h"
#include "Sensor.h"
#include "XmlEncoder.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <thread>

#include <chrono>

using namespace std::chrono;

namespace cern
{

VMESensorsManager::VMESensorsManager() :
				stop_(false),
				ready_(false)
{
}

VMESensorsManager::~VMESensorsManager()
{
}

void VMESensorsManager::addSensor(uint16_t address, bool type)
{
	// if we have already max num of sensors throw exception
	if (sensors_.size() == 8)
	{
		throw std::out_of_range("Max sensor number reached!");
	}

	// find if there is already a sensor listening at that address
	SensorVectorIterator it = std::find_if(sensors_.begin(), sensors_.end(), [&] (SensorPtr const& s)
	{	return s->getAddress() == address;});
	// if yes throw exception
	if (it != sensors_.end())
	{
		throw std::runtime_error("Sensor already installed!");
	}

	SensorPtr sensor_ptr(new Sensor(address, queue_, cv_m_, cv_, ready_,work_done_));
	sensor_ptr->runThread();
	sensors_.push_back(move(sensor_ptr));
}

void VMESensorsManager::removeSensor(uint16_t address)
{
	sensors_.erase(std::remove_if(sensors_.begin(), sensors_.end(), [&] (SensorPtr const& s)
	{	return s->getAddress() == address;}), sensors_.end());
}

void VMESensorsManager::setOutStream(std::ostream& stream)
{
	encoder_ = std::unique_ptr<Encoder>(new XmlEncoder(stream));
}

std::vector<uint16_t> VMESensorsManager::getSensorList() const
{
	std::vector<uint16_t> result;
	for (auto& s : sensors_)
		result.push_back(s->getAddress());
	return result;
}

void VMESensorsManager::stop()
{
	stop_ = true;
}

void VMESensorsManager::setConversionFactors(uint16_t address, double scalingFactor, double offset)
{
	SensorVectorIterator results = std::find_if(sensors_.begin(), sensors_.end(), [&] (SensorPtr const& s)
	{	return s->getAddress() == address;});

	if (results != sensors_.end())
		(*results)->setCalibrator(scalingFactor, offset);
	else
		std::cout << "Element not found in myvector\n";
}

void VMESensorsManager::notify_all()
{
	std::unique_lock<std::mutex> lck(cv_m_);
	ready_ = true;
	cv_.notify_all();
}

void VMESensorsManager::run()
{
	std::vector<Event> events;
	while (!stop_)
	{
		// Instrumentation
		steady_clock::time_point const timeout = steady_clock::now() + milliseconds(500);
		auto start = std::chrono::high_resolution_clock::now();

		events.clear();
		// 1) Say to all sensors to acquire
		notify_all();

		// either I choose to empty the queue one by one or at once


		// 2) Wait 500 ms. After this I'm pretty sure all sensors have
		// done their job..
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// 3) empty the queue at once
		for (size_t i = 0; i <= queue_.size(); ++i)
		{
			Event state = queue_.dequeue();
			events.push_back(state);
		}

		// 4) Use the encoder to format and stream out the sensor readouts
		if (encoder_)
		{
			encoder_->encode(events);
		}

		// 5) Sleep until timeout
		std::this_thread::sleep_until(timeout);

		// Instrumentation
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		std::cout << "Waited " << elapsed.count() << " ms\n";
	}
	work_done_ = true;
}
} // namespace cern

