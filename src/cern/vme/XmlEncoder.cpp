/*
 * XmlEncoder.cpp
 *
 *      Author: Iacopo Breschi
 */

#include "XmlEncoder.h"

namespace cern
{

XmlEncoder::XmlEncoder(std::ostream& stream) :
				out_stream_(stream)
{

}

XmlEncoder::~XmlEncoder()
{
}

void XmlEncoder::encode()
{
	out_stream_ << "encode this\n";
}

} /* namespace cern */
