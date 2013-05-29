/*
 * File:   cpuid.cpp
 * Author: ringo
 *
 * Created on 29.05.2013, 09:17:34
 */

#include <stdint.h>

#include "cpuid.hpp"
#include "../CpuId.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(cpuid);

cpuid::cpuid() {

}

cpuid::~cpuid() {

}

void cpuid::setUp() {

}

void cpuid::tearDown() {

}

void cpuid::testMethod() {
	uint32_t *regs = cpuid(0);

	CPPUNIT_ASSERT(true);
}

void cpuid::testFailedMethod() {
	CPPUNIT_ASSERT(false);
}

