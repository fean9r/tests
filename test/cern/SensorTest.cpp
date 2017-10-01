/*
 * SensorTest.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: fean9r
 */
#include <boost/test/auto_unit_test.hpp>

#include <cern/vme/Sensor.h>
#include <iostream>

using namespace cern;
struct SensorFixture
{
	SensorFixture()
	{
	}
	SafeQueue<Event> queue;
};

BOOST_FIXTURE_TEST_SUITE (cern_SensorTest, SensorFixture)

BOOST_AUTO_TEST_CASE(getSensorList_test)

{
	Sensor s1(0xAAAA,queue);
	BOOST_CHECK_EQUAL(s1.getAddress(), 0xAAAA);
	s1.read();
	Event e = queue.dequeue();
	BOOST_CHECK_EQUAL(e.address, 0xAAAA);
	BOOST_CHECK_EQUAL(e.current_temp, 0);
	BOOST_CHECK_EQUAL(e.max_temp, 0);
	BOOST_CHECK_EQUAL(e.min_temp, 0);

	s1.setCalibrator(2.2,80.3);
	s1.read();
	e = queue.dequeue();
	// TODO: Find a way to properly set the initial max and min
//	BOOST_CHECK_NE(e.current_temp, 0);
//	BOOST_CHECK_NE(e.max_temp, 0);
//	BOOST_CHECK_NE(e.min_temp, 0);
//	std::cout << std::hex << e.current_temp << std::endl;
//	std::cout << std::hex << e.max_temp << std::endl;
//	std::cout << std::hex << e.min_temp << std::endl;
}


BOOST_AUTO_TEST_SUITE_END()


