/*
 * XmlEncoder.h
 *
 *      Author: Iacopo Breschi
 */

#ifndef cern_vme_XmlEncoder_h_INCLUDED
#define cern_vme_XmlEncoder_h_INCLUDED

#include "Encoder.h"
#include <iostream>

namespace cern
{

class XmlEncoder : public Encoder
{
public:
	XmlEncoder(std::ostream& stream);
	virtual ~XmlEncoder();

	void encode(std::vector<SensorState> events);
private:
	void addElement(SensorState& elem, std::stringstream & stream);
	std::ostream& out_stream_;
};

} /* namespace cern */

#endif /* cern_vme_XmlEncoder_h_INCLUDED */
