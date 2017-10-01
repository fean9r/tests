/*
 * Event.h
 *
 *      Author: Iacopo BRESCHI
 */

#ifndef cern_vme_SensorState_h_INCLUDED
#define cern_vme_SensorState_h_INCLUDED
#include <cstdint>

namespace cern
{

struct SensorState
{
	uint16_t address;
	double max_temp;
	double min_temp;
	double current_temp;
};

} // namespace cern

#endif /* cern_vme_SensorState_h_INCLUDED */
