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

namespace cern
{

VMESensorsManager::VMESensorsManager() :
				stop_(false)
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
	SensorVectorIterator it = std::find_if(sensors_.begin(), sensors_.end(),
			[&] (SensorPtr const& s) { return s->getAddress() == address; });
	// if yes throw exception
	if (it != sensors_.end())
	{
		throw std::runtime_error("Sensor already installed!");
	}

	sensors_.push_back(SensorPtr(new Sensor(address, queue_)));
}

void VMESensorsManager::removeSensor(uint16_t address)
{
	sensors_.erase(
			std::remove_if(sensors_.begin(), sensors_.end(),
					[&] (SensorPtr const& s){ return s->getAddress() == address;}),
			sensors_.end());
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
	//notify all with a signal
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

void VMESensorsManager::run()
{
	while (!stop_)
	{
		// Notify all with a signal
//		for (Sensor s : sensors_)
//		{
//			s.read();
//		}

// where should I put this??
		Event state = queue_.dequeue();
		if (encoder_)
		{
			// how do we pass the state to the encoder ?state
			encoder_->encode();
		}
		//		wait
		//	for 1 second timer arrives
	}
}
} // namespace cern

