/*
 * File:   cpuid.hpp
 * Author: ringo
 *
 * Created on 29.05.2013, 09:17:33
 */

#ifndef CPUID_HPP
#define	CPUID_HPP

#include <cppunit/extensions/HelperMacros.h>

class cpuid : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(cpuid);

	CPPUNIT_TEST(testMethod);
	CPPUNIT_TEST(testFailedMethod);

	CPPUNIT_TEST_SUITE_END();

public:
	cpuid();
	virtual ~cpuid();
	void setUp();
	void tearDown();

private:
	void testMethod();
	void testFailedMethod();
};

#endif	/* CPUID_HPP */

