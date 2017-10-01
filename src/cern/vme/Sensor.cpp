/*
 * Sensor.cpp
 *
 *      Author: Iacopo Breschi
 */

#include "Sensor.h"

#include <iostream>
#include <atomic>

namespace cern
{
void addTemperature(SensorState& state, double temp)
{
	if (state.max_temp < temp) state.max_temp = temp;
	if (state.min_temp > temp) state.min_temp = temp;
	state.current_temp = temp;
}

Sensor::Sensor(uint16_t address, SafeQueue<SensorState> & queue, std::mutex& mut, std::condition_variable& cond, bool & ready, bool & work_done) :
				sensor_address_(address),
				scalingFactor_(),
				offset_(),
				state_(),
				queue_(queue),
				thread_(),
				cond_var_(cond),
				cv_mutex_(mut),
				ready_for_next_(ready),
				work_done_(work_done),
				read_counter_(0)
{
	state_.address = sensor_address_;
//		state_.max_temp=0;
//		state_.min_temp=0;
}

Sensor::~Sensor()
{
	if (thread_.joinable()) thread_.join();
}

void Sensor::runThread()
{
	thread_ = std::thread(&Sensor::read, this);
}

uint16_t Sensor::getAddress() const
{
	return sensor_address_;
}

void Sensor::setCalibrator(double scalingFactor, double offset)
{
	scalingFactor_ = scalingFactor;
	offset_ = offset;
}

double Sensor::applyCalibration(double analog_val)
{
	return scalingFactor_ * (analog_val - offset_);
}

void Sensor::read()
{
	while (!work_done_)
	{
		{
			std::unique_lock<std::mutex> lck(cv_mutex_);
			cond_var_.wait(lck, [this]
			{	return ready_for_next_ || work_done_;});
			read_counter_++;
		}

		double readout = readHardware(sensor_address_);
		addTemperature(state_, applyCalibration(readout));
		queue_.enqueue(state_);
		if (work_done_) break;

		{
			std::unique_lock<std::mutex> lck(cv_mutex_);
			read_counter_--;
			cond_var_.wait(lck, [this]
			{	return read_counter_ == 0 || work_done_;});
			ready_for_next_ = false;
		}
	}
}

} // namespace cern
