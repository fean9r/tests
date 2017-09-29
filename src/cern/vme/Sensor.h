#ifndef cern_vme_Sensor_h_INCLUDED
#define cern_vme_Sensor_h_INCLUDED

#include "SafeQueue.hpp"
#include "Event.h"
#include <cern/ext/vmod.h>

namespace cern
{

class Sensor
{
public:
	Sensor(uint16_t address, SafeQueue<Event> & queue) :
					sensor_address_(address),
					scalingFactor_(),
					offset_(),
					state_(),
					queue_(queue)
	{
		state_.address = sensor_address_;
	}

	virtual ~Sensor()
	{
	}

	uint16_t getAddress() const
	{
		return sensor_address_;
	}

	void setCalibrator(double scalingFactor, double offset)
	{
		scalingFactor_ = scalingFactor;
		offset_ = offset;
	}

	void read();

	friend bool operator==(const Sensor &s1, const Sensor &s2);

private:
	double applyCalibration(double analog_val);

	uint16_t sensor_address_;
	double scalingFactor_;
	double offset_;
	Event state_;
	SafeQueue<Event> & queue_;
};

bool operator==(const Sensor &s1, const Sensor &s2)
{
	return s1.sensor_address_ == s2.sensor_address_;
}

} // namespace cern

#endif /* cern_vme_Sensor_h_INCLUDED */
