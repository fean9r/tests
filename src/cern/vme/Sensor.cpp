/*
 * Sensor.cpp
 *
 *      Author: Iacopo Breschi
 */

#include "Sensor.h"
namespace cern
{
void addTemperature(Event& state, double temp)
{
	if (state.max_temp < temp) state.max_temp = temp;
	if (state.min_temp > temp) state.min_temp = temp;
	state.current_temp = temp;
}

Sensor::Sensor(uint16_t address, SafeQueue<Event> & queue, std::mutex& mut, std::condition_variable& cond, bool & ready, bool & work_done) :
				sensor_address_(address),
				scalingFactor_(),
				offset_(),
				state_(),
				queue_(queue),
				thread_(),
				cv_(cond),
				cv_m_(mut),
				ready_(ready),
				work_done_(work_done)
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
		std::unique_lock<std::mutex> lk(cv_m_);
		while (!ready_)
			cv_.wait(lk);

		double readout = readHardware(sensor_address_);
		addTemperature(state_, applyCalibration(readout));
		queue_.enqueue(state_);
	}
}

} // namespace cern
