/*
 * File:   cpuidtest.c
 * Author: ringo
 *
 * Created on 28.05.2013, 17:59:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../CpuId.hpp"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
	return 0;
}

int clean_suite(void) {
	return 0;
}

void test1() {
	CU_ASSERT(2 * 2 == 4);
}

void cpuid_test() {
	CU_ASSERT(2 * 2 == 6);
}

int main() {
	CU_pSuite pSuite = NULL;

	/* Initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	} // if (CUE_SUCCESS != CU_initialize_registry())

	/* Add a suite to the registry */
	pSuite = CU_add_suite("cpuidtest", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	} // if (NULL == pSuite)

	/* Add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test1", test1)) || (NULL == CU_add_test(pSuite, "cpuid test", cpuid_test))) {
		CU_cleanup_registry();
		return CU_get_error();
	} // if ((NULL == CU_add_test(pSuite, "test1", test1)) || (NULL == CU_add_test(pSuite, "test2", test2)))

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
