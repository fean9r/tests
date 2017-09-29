/*
 * VmeTest.cpp
 *
 *  Created on: Sep 29, 2017
 *      Author: fean9r
 */

#include <cern/VMESensorsManager.h>
#include <boost/test/auto_unit_test.hpp>
#include <typeinfo>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE (VmeTest)

BOOST_AUTO_TEST_CASE(first_test)
{
	// We are here in the supervisor
		VMESensorsManager sensor_manager;


		sensor_manager.setOutStream(std::cout);

		// after this xml formatted data should be printed each second
		// one for each sensor
		sensor_manager.addSensor(0xAAAA);
		sensor_manager.setConversionFactors(0xAAAA,2.5,70);

		sensor_manager.addSensor(0xBBBB);
		sensor_manager.setConversionFactors(0xBBBB,3.5,-50);

		sensor_manager.addSensor(0xCCCC);
		sensor_manager.setConversionFactors(0xCCCC,-2.5,20);

		sensor_manager.addSensor(0xDDDD);
		// what happens if there is no conversion factor?

		for(auto sen : sensor_manager.getSensorList())
		{
			std::cout << sen << cout::endl;
		}

		sensor_manager.removeSensor(0xDDDD);

		for(auto sen : sensor_manager.getSensorList())
		{
			std::cout << sen << cout::endl;
		}

		// all data should stop now
		sensor_manager.stop();

	BOOST_CHECK_EQUAL(1, 10);
}

BOOST_AUTO_TEST_SUITE_END()
