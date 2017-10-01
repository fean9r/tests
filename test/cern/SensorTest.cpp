/*
 * SensorTest.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: fean9r
 */
#include <boost/test/auto_unit_test.hpp>

#include <cern/vme/Sensor.h>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace cern;
struct SensorFixture
{
	SensorFixture() :
					ready_(false),
					work_done_(false)
	{
	}
	SafeQueue<SensorState> queue;
	std::condition_variable cv_;
	std::mutex cv_m_;
	bool ready_;
	bool work_done_;
};

BOOST_FIXTURE_TEST_SUITE (cern_SensorTest, SensorFixture)

BOOST_AUTO_TEST_CASE(one_sensor_one_aquisition_test)
{
	Sensor s1(0xAAAA, queue, cv_m_, cv_, ready_, work_done_);
	s1.runThread();

	BOOST_CHECK_EQUAL(s1.getAddress(), 0xAAAA);
	BOOST_CHECK_EQUAL(0, queue.size());

	{
		std::lock_guard<std::mutex> lk(cv_m_);
		std::cout << "Notifying...\n";
		ready_ = true;
	}
	cv_.notify_all();

	BOOST_CHECK_EQUAL(0, queue.size());
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	BOOST_CHECK_EQUAL(1, queue.size());

	SensorState e = queue.dequeue();
	BOOST_CHECK_EQUAL(e.address, 0xAAAA);
	BOOST_CHECK_EQUAL(e.current_temp, 0);
	BOOST_CHECK_EQUAL(e.max_temp, 0);
	BOOST_CHECK_EQUAL(e.min_temp, 0);

	work_done_ = true;
	cv_.notify_all();
}

BOOST_AUTO_TEST_CASE(one_sensor_n_aquisition_test)
{
	Sensor s1(0xAAAA, queue, cv_m_, cv_, ready_, work_done_);
	s1.runThread();
	BOOST_CHECK_EQUAL(0, queue.size());
	for (size_t i = 0; i < 10; ++i)
	{
		{
			std::lock_guard<std::mutex> lk(cv_m_);
			//std::cout << "Notifying...\n";
			ready_ = true;
		}
		cv_.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		BOOST_CHECK_EQUAL(i + 1, queue.size());
	}
	BOOST_CHECK_EQUAL(10, queue.size());

	work_done_ = true;
	cv_.notify_all();
}

BOOST_AUTO_TEST_CASE(two_sensor_one_aquisition_test)
{
	Sensor s1(0xAAAA, queue, cv_m_, cv_, ready_, work_done_);
	Sensor s2(0xAAAB, queue, cv_m_, cv_, ready_, work_done_);
	s1.runThread();
	s2.runThread();
	BOOST_CHECK_EQUAL(0, queue.size());

	{
		std::lock_guard<std::mutex> lk(cv_m_);
		//std::cout << "Notifying...\n";
		ready_ = true;
	}
	cv_.notify_all();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	BOOST_CHECK_EQUAL(2, queue.size());

	work_done_ = true;
	cv_.notify_all();
}

BOOST_AUTO_TEST_CASE(two_sensor_n_aquisition_test)
{
	Sensor s1(0xAAAA, queue, cv_m_, cv_, ready_, work_done_);
	Sensor s2(0xAAAB, queue, cv_m_, cv_, ready_, work_done_);
	s1.runThread();
	s2.runThread();
	BOOST_CHECK_EQUAL(0, queue.size());
	for (size_t i = 0; i < 10; ++i)
	{
		{
			std::lock_guard<std::mutex> lk(cv_m_);
			//std::cout << "Notifying...\n";
			ready_ = true;
		}
		cv_.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		BOOST_CHECK_EQUAL(2*i + 2, queue.size());
	}
	BOOST_CHECK_EQUAL(20, queue.size());
	work_done_ = true;
	cv_.notify_all();
}
BOOST_AUTO_TEST_CASE(tree_sensor_n_aquisition_test)
{
	Sensor s1(0xAAAA, queue, cv_m_, cv_, ready_, work_done_);
	Sensor s2(0xAAAB, queue, cv_m_, cv_, ready_, work_done_);
	Sensor s3(0xAAAC, queue, cv_m_, cv_, ready_, work_done_);

	s1.runThread();
	s2.runThread();
	s3.runThread();
	BOOST_CHECK_EQUAL(0, queue.size());
	for (size_t i = 0; i < 10; ++i)
	{
		{
			std::lock_guard<std::mutex> lk(cv_m_);
			//std::cout << "Notifying...\n";
			ready_ = true;
		}
		cv_.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		BOOST_CHECK_EQUAL(3*i + 3, queue.size());
	}
	BOOST_CHECK_EQUAL(30, queue.size());
	work_done_ = true;
	cv_.notify_all();
}

BOOST_AUTO_TEST_SUITE_END()

