/*
 * XmlEncoder.cpp
 *
 *      Author: Iacopo Breschi
 */

#include "XmlEncoder.h"

#include <sstream>
#include <iostream>

namespace cern
{

XmlEncoder::XmlEncoder(std::ostream& stream) :
				out_stream_(stream)
{

}

XmlEncoder::~XmlEncoder()
{
}

void XmlEncoder::addElement(Event & elem, std::stringstream & stream)
{
	stream << "\t<Sensor>\n";
	stream << "\t\t<address>" << elem.address << "</address>\n";
	stream << "\t\t<max_temp>" << elem.max_temp << "</max_temp>\n";
	stream << "\t\t<min_temp>" << elem.min_temp << "</min_temp>\n";
	stream << "\t\t<current_temp>" << elem.current_temp << "</current_temp>\n";
	stream << "\t</Sensor>\n";
}

void XmlEncoder::encode(std::vector<Event> events)
{
	std::stringstream ss("", std::ios_base::out);
	ss << "<Sensors>\n";
	for (auto & ev : events)
		addElement(ev, ss);
	ss << "</Sensors>\n";
	out_stream_ << ss.str() << std::endl;
}

} /* namespace cern */
