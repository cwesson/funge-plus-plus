##
# @file Makefile
# @author Conlan Wesson
##

SRCS := $(shell find src/ -name \*.cpp)
OBJS := $(subst src/,bin/,$(subst .cpp,.o,$(SRCS)))
DEPS := $(OBJS:%.o=%.d)

EXEC := bin/funge

INCLUDES := -I src/include -I src/fingerprint/include

CPP := g++
CPPARGS := $(INCLUDES) -g -Wall -Wextra -Werror

LD := g++
LDARGS := -lpthread

.PHONY: all clean realclean build funge test

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

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "CPP " $(subst src/,,$<)
	@$(CPP) $(CPPARGS) -MMD -o $@ -c $<

-include $(DEPS)

test: build
	@./test/smoketest.sh

lint:
	@cppcheck --enable=all $(INCLUDES) $(SRCS)

CPPUTESTLIB := test/cpputest/src/CppUTest/libCppUTest.a
UTCPPARGS := -I src/include -I test/cpputest/include -lpthread
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
	@rm -f $(OBJS)

realclean:
	@echo REALCLEAN
	@rm -rf bin/
