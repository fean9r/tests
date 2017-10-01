/*
 * SensorTest.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: fean9r
 */
#include <boost/test/auto_unit_test.hpp>
#include </cern/vme/SensorState.h>
#include <cern/vme/XmlEncoder.h>
#include <iostream>

using namespace cern;
struct EncoderFixture
{
	EncoderFixture() : encoder(std::cout)
	{
	}
	XmlEncoder encoder;
	//SafeQueue<Event> queue;
};

BOOST_FIXTURE_TEST_SUITE (cern_EncoderTest, EncoderFixture)

BOOST_AUTO_TEST_CASE(xml_encoder_test)

{
	SensorState e1;
	e1.address = 0xAAAA;
	e1.current_temp=10.2;
	e1.max_temp=100.3;
	e1.min_temp=-2.0;

	SensorState e2;
	e2.address = 0xBBBB;
	e2.current_temp=91.2;
	e2.max_temp=100.3;
	e2.min_temp=2.0;

	std::vector<SensorState> events;
	events.push_back(e1);

	encoder.encode(events);

	events.push_back(e2);

	encoder.encode(events);

//	BOOST_CHECK_NE(e.current_temp, 0);
//	BOOST_CHECK_NE(e.max_temp, 0);
//	BOOST_CHECK_NE(e.min_temp, 0);
//	std::cout << std::hex << e.current_temp << std::endl;
//	std::cout << std::hex << e.max_temp << std::endl;
//	std::cout << std::hex << e.min_temp << std::endl;
}

BOOST_AUTO_TEST_CASE(getSensorList_test)
{

}
BOOST_AUTO_TEST_SUITE_END()


