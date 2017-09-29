/*
 * Supervisable.h
 *
 *  Created on: Sep 29, 2017
 *      Author: fean9r
 */

#ifndef cern_vme_Supervisable_h_INCLUDED
#define cern_vme_Supervisable_h_INCLUDED

#include <cstdint>
#include <iostream>

namespace cern
{

class Supervisable
{
public:
	virtual ~Supervisable() = 0;
	virtual void addSensor(uint16_t address, bool type) = 0;
	virtual void removeSensor(uint16_t address) = 0;
	virtual void setConversionFactors(uint16_t address, double scalingFactor, double offset) = 0;
	virtual std::vector<uint16_t> getSensorList() const = 0;
	virtual void setOutStream(std::ostream& stream) = 0;
	virtual void stop() = 0;
};

} // namespace cern
#endif /* cern_vme_Supervisable_h_INCLUDED */
