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
	stream << "<Sensor>";
	stream << "<address>" << elem.address << "</address>";
	stream << "<max_temp>" << elem.max_temp << "</max_temp>";
	stream << "<min_temp>" << elem.min_temp << "</min_temp>";
	stream << "<current_temp>" << elem.current_temp << "</current_temp>";
	stream << "</Sensor>";
}

void XmlEncoder::encode(std::vector<Event> events)
{
	std::stringstream ss("", std::ios_base::out);
	ss << "<Sensors>";
	for (auto & ev : events)
		addElement(ev, ss);
	ss << "</Sensors>";
	std::cout << ss.str() << std::endl;
	//out_stream_<< ss.str() << std::endl;
}

} /* namespace cern */
