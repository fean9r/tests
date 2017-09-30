/*
 * Sensor.cpp
 *
 *  Created on: Sep 29, 2017
 *      Author: fean9r
 */

#include "Sensor.h"

namespace cern
{

void addTemperature(Event state, double temp)
{
	if (state.max_temp < temp) state.max_temp = temp;
	if (state.min_temp > temp) state.min_temp = temp;
	state.current_temp = temp;
}

double Sensor::applyCalibration(double analog_val)
{
	return scalingFactor_ * (analog_val - offset_);
}

void Sensor::read()
{
	double readout = readHardware(sensor_address_);
	addTemperature(state_, applyCalibration(readout));
	queue_.enqueue(state_);
}

//bool Sensor::operator==(const Sensor &s1, const Sensor &s2)
//{
//	return s1.sensor_address_ == s2.sensor_address_;
//}

} // namespace cern
