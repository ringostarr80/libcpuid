CC = g++
OBJ = cpuid.o
STD = -std=c++17
CPUID_TEST_OBJ = cpuid_test.o
CPUID_TESTRUNNER_OBJ = cpuid_testrunner.o

build: $(OBJ)
	$(CC) ${STD} -o libcpuid.so $(OBJ) -shared -fPIC

$(OBJ):
	$(CC) ${STD} -c -O3 -fPIC -MMD -MP -MF $(OBJ).d -o $(OBJ) CpuId.cpp

$(CPUID_TESTRUNNER_OBJ):
	$(CC) ${STD}  -c -O3 -fPIC -MMD -MP -MF tests/cpuid_testrunner.o.d -o tests/$(CPUID_TESTRUNNER_OBJ) tests/cpuid_testrunner.cpp

$(CPUID_TEST_OBJ):
	$(CC) ${STD}  -c -O3 -fPIC -MMD -MP -MF tests/cpuid_test.o.d -o tests/$(CPUID_TEST_OBJ) tests/cpuid_test.cpp

test: build $(CPUID_TEST_OBJ) $(CPUID_TESTRUNNER_OBJ)
	$(CC) ${STD}  -o libcpuid_test $(OBJ) tests/$(CPUID_TESTRUNNER_OBJ) tests/$(CPUID_TEST_OBJ) -L/usr/include/cppunit -lcppunit
	./libcpuid_test

clean:
	rm -f *.o *.o.d *.so tests/*.o tests/*.o.d libcpuid_test
