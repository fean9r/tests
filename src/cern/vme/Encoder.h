/*
 * Encoder.h
 *
 *  Created on: Sep 29, 2017
 *      Author: Iacopo BRESCHI
 */

#ifndef cern_vme_Encoder_h_INCLUDED
#define cern_vme_Encoder_h_INCLUDED

namespace cern
{

class Encoder
{
public:
	Encoder();
	virtual ~Encoder();
	virtual void encode() = 0;
};

} /* namespace cern */

#endif /* cern_vme_Encoder_h_INCLUDED */
