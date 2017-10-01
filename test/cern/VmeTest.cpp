/*
 * VmeTest.cpp
 *
 *  Created on: Sep 29, 2017
 *      Author: fean9r
 */
#include <boost/test/auto_unit_test.hpp>

#include <cern/vme/VMESensorsManager.h>
#include <typeinfo>
#include <fstream>
#include <iostream>

using namespace cern;

struct VMEFixture
{
	VMEFixture()
	{
	}
	VMESensorsManager sensor_manager;
};

BOOST_FIXTURE_TEST_SUITE (cern_VmeTest, VMEFixture)

BOOST_AUTO_TEST_CASE(addSensor_test)
{
	sensor_manager.addSensor(0xAAAA, true );
	sensor_manager.addSensor(0xBBBB, true );
	sensor_manager.addSensor(0xCCCC, true );
	sensor_manager.addSensor(0xDDDD, true );
}
BOOST_AUTO_TEST_CASE(setConversionFactors_test)
{
	sensor_manager.addSensor(0xAAAA, true );
	sensor_manager.setConversionFactors(0xAAAA,2.5,70);

}
BOOST_AUTO_TEST_CASE(getSensorList_test)
{
	sensor_manager.addSensor(0xAAAA, true );
	sensor_manager.addSensor(0xBBBB, true );
	sensor_manager.addSensor(0xCCCC, true );
	sensor_manager.addSensor(0xDDDD, true );

	for(auto sen : sensor_manager.getSensorList())
	{
		std::cout << sen << std::endl;
		BOOST_CHECK_EQUAL(10, 10);

	}
}
BOOST_AUTO_TEST_CASE(setOutStream_test)
{
	sensor_manager.setOutStream(std::cout);

}

BOOST_AUTO_TEST_CASE(stop_test)
{
	sensor_manager.stop();
}

BOOST_AUTO_TEST_CASE(removeSensor_test)
{

	BOOST_CHECK_EQUAL(10, 10);
}

BOOST_AUTO_TEST_CASE(full_test)
{
	sensor_manager.setOutStream(std::cout);

	// after this xml formatted data should be printed each second
	// one for each sensor
	sensor_manager.addSensor(0xAAAA, true );
	sensor_manager.setConversionFactors(0xAAAA,2.5,70);

	sensor_manager.addSensor(0xBBBB, true );
	sensor_manager.setConversionFactors(0xBBBB,3.5,-50);

	sensor_manager.addSensor(0xCCCC, true );
	sensor_manager.setConversionFactors(0xCCCC,-2.5,20);

	sensor_manager.addSensor(0xDDDD, true );
	// what happens if there is no conversion factor?

	for(auto sen : sensor_manager.getSensorList())
	{
		std::cout << sen << std::endl;
	}

	sensor_manager.removeSensor(0xDDDD);

	for(auto sen : sensor_manager.getSensorList())
	{
		std::cout << sen << std::endl;
	}

	// all data should stop now
	sensor_manager.stop();

}

BOOST_AUTO_TEST_SUITE_END()
