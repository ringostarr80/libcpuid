/*
 * File:   cpuid_test.hpp
 * Author: ringo
 *
 * Created on 29.05.2013, 10:02:37
 */

#ifndef CPUID_TEST_HPP
#define	CPUID_TEST_HPP

#include <cppunit/extensions/HelperMacros.h>

class cpuid_test : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(cpuid_test);

	CPPUNIT_TEST(cpuidTest);

	CPPUNIT_TEST_SUITE_END();

public:

private:
	void cpuidTest();
};

#endif	/* CPUID_TEST_HPP */

