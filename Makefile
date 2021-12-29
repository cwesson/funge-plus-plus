##
# @file Makefile
# @author Conlan Wesson
##

SRCS := third_party/bigint/src/bigint.cpp $(shell find src/ -name \*.cpp)
OBJS := $(addsuffix .o,$(addprefix bin/,$(basename $(SRCS))))
DEPS := $(OBJS:%.o=%.d)

EXEC := bin/funge

INCLUDES := -I src/include -I src/fingerprint/include -I third_party/bigint/include

CPP := g++
CPPARGS := $(INCLUDES) -g -Wall -Wextra -Werror -std=c++2a
LINTARGS := $(INCLUDES) --enable=all --std=c++20

LD := g++
LDARGS := -pthread

.PHONY: all clean realclean build funge test lint

GCOV ?= 0
ifneq ($(GCOV),0)
CPPARGS += -fprofile-arcs -ftest-coverage
LDARGS += -fprofile-arcs -ftest-coverage
endif

all: test

build: funge

funge: $(EXEC)

$(EXEC): $(OBJS)
	@echo "LD  " $(subst bin/,,$@)
	@$(LD) $(LDARGS) -o $@ $(OBJS)

bin/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "CPP " $(subst src/,,$<)
	@$(CPP) $(CPPARGS) -MMD -o $@ -c $<

bin/%.o: third_party/%.cpp
	@mkdir -p $(dir $@)
	@echo "CPP " $(subst third_party/,,$<)
	@$(CPP) $(CPPARGS) -MMD -o $@ -c $<

-include $(DEPS)

test: build
	@./test/smoketest.sh

lint:
	@cppcheck $(LINTARGS) $(SRCS)

CPPUTESTLIB := test/cpputest/src/CppUTest/libCppUTest.a
UTCPPARGS := -I src/include -I test/cpputest/include -lpthread -std=c++20
UTSRCS := test/ut/unittest.cpp src/Vector.cpp src/VectorRange.cpp

ut: unittest

unittest: $(UTSRCS) $(CPPUTESTLIB)
	$(CPP) $(UTCPPARGS) -o ./bin/$@ $(UTSRCS) $(CPPUTESTLIB)
	./bin/unittest -c -v

$(CPPUTESTLIB): cpputest

cpputest:
	cd test/cpputest; cmake .
	make -C test/cpputest

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS) $(DEPS)

realclean:
	@echo REALCLEAN
	@rm -rf bin/
