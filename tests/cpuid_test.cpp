/*
 * File:   cpuid_test.cpp
 * Author: ringo
 *
 * Created on 29.05.2013, 10:02:37
 */

#include <cstdint>

#include "cpuid_test.hpp"
#include "../CpuId.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(cpuid_test);

cpuid_test::cpuid_test() {

}

cpuid_test::~cpuid_test() {

}

void cpuid_test::setUp() {

}

void cpuid_test::tearDown() {

}

void cpuid_test::cpuidTest() {
	bool invalidCharFound = false;
	uint32_t *regs = cpuid(0);

	char vendorID[13];
	vendorID[0] = (regs[1]) & 0xFF;
	vendorID[1] = (regs[1] >> 8) & 0xFF;
	vendorID[2] = (regs[1] >> 16) & 0xFF;
	vendorID[3] = (regs[1] >> 24);
	vendorID[4] = (regs[3]) & 0xFF;
	vendorID[5] = (regs[3] >> 8) & 0xFF;
	vendorID[6] = (regs[3] >> 16) & 0xFF;
	vendorID[7] = (regs[3] >> 24) & 0xFF;
	vendorID[8] = (regs[2]) & 0xFF;
	vendorID[9] = (regs[2] >> 8) & 0xFF;
	vendorID[10] = (regs[2] >> 16) & 0xFF;
	vendorID[11] = (regs[2] >> 24) & 0xFF;
	vendorID[12] = '\0';

	for(uint8_t i = 0; i < sizeof(vendorID) - 1; i++) {
		if (vendorID[i] < 32 && vendorID[i] > 126) {
			invalidCharFound = true;
			break;
		}
	}

	CPPUNIT_ASSERT(!invalidCharFound);
}
