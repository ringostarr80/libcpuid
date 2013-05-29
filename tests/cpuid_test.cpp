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
	CpuRegisters regs = cpuid(0);

	char vendorID[13];
	vendorID[0] = (regs.ebx) & 0xFF;
	vendorID[1] = (regs.ebx >> 8) & 0xFF;
	vendorID[2] = (regs.ebx >> 16) & 0xFF;
	vendorID[3] = (regs.ebx >> 24);
	vendorID[4] = (regs.edx) & 0xFF;
	vendorID[5] = (regs.edx >> 8) & 0xFF;
	vendorID[6] = (regs.edx >> 16) & 0xFF;
	vendorID[7] = (regs.edx >> 24) & 0xFF;
	vendorID[8] = (regs.ecx) & 0xFF;
	vendorID[9] = (regs.ecx >> 8) & 0xFF;
	vendorID[10] = (regs.ecx >> 16) & 0xFF;
	vendorID[11] = (regs.ecx >> 24) & 0xFF;
	vendorID[12] = '\0';

	for(uint8_t i = 0; i < sizeof(vendorID) - 1; i++) {
		if (vendorID[i] < 32 && vendorID[i] > 126) {
			invalidCharFound = true;
			break;
		}
	}

	CPPUNIT_ASSERT(!invalidCharFound);
}
