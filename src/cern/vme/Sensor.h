/*
 * Sensor.h
 *
 *      Author: Iacopo Breschi
 */

#ifndef cern_vme_Sensor_h_INCLUDED
#define cern_vme_Sensor_h_INCLUDED

#include "SafeQueue.hpp"
#include "Event.h"
#include <cern/ext/vmod.h>
#include <thread>
#include <condition_variable>

namespace cern
{

class Sensor
{
public:
	Sensor(uint16_t address, SafeQueue<Event> & queue,std::mutex& mut, std::condition_variable& cond, bool & ready, bool & work_done);

	virtual ~Sensor();

	void runThread();
	uint16_t getAddress() const;
	void setCalibrator(double scalingFactor, double offset);
	void read();

private:
	double applyCalibration(double analog_val);

	uint16_t sensor_address_;
	double scalingFactor_;
	double offset_;
	Event state_;
	SafeQueue<Event> & queue_;
	std::thread thread_;
	std::condition_variable& cv_;
	std::mutex& cv_m_;
	bool & ready_;
	bool & work_done_;

};

} // namespace cern

#endif /* cern_vme_Sensor_h_INCLUDED */
