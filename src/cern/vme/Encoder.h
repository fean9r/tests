/*
 * Encoder.h
 *
 *      Author: Iacopo BRESCHI
 */

#ifndef cern_vme_Encoder_h_INCLUDED
#define cern_vme_Encoder_h_INCLUDED

#include "SensorState.h"
#include <vector>

namespace cern
{

class Encoder
{
public:
	virtual ~Encoder() {}
	virtual void encode(std::vector<SensorState> events) = 0;
};

} /* namespace cern */

#endif /* cern_vme_Encoder_h_INCLUDED */
