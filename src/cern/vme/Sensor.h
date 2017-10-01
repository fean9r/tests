/*
 * Sensor.h
 *
 *      Author: Iacopo Breschi
 */

#ifndef cern_vme_Sensor_h_INCLUDED
#define cern_vme_Sensor_h_INCLUDED

#include "SafeQueue.hpp"
#include <cern/ext/vmod.h>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "SensorState.h"

namespace cern
{

class Sensor
{
public:
	Sensor(uint16_t address, SafeQueue<SensorState> & queue,std::mutex& mut, std::condition_variable& cond, bool & ready, bool & work_done);

	virtual ~Sensor();

	void runThread();
	uint16_t getAddress() const;
	void setCalibrator(double scalingFactor, double offset);

private:
	void read();
	double applyCalibration(double analog_val);

	uint16_t sensor_address_;
	double scalingFactor_;
	double offset_;
	SensorState state_;
	SafeQueue<SensorState> & queue_;
	std::thread producer_thread_;
	std::condition_variable& cond_var_;
	std::mutex& cv_mutex_;
	std::atomic_int read_counter_;
	bool & ready_for_next_;
	bool & work_done_;
};

} // namespace cern

#endif /* cern_vme_Sensor_h_INCLUDED */
