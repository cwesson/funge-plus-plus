##
# @file Makefile
# @author Conlan Wesson
##

FUNGESRC := $(shell find src/ -name \*.cpp)
SRCS := third_party/bigint/src/bigint.cpp $(FUNGESRC)
OBJS := $(addsuffix .o,$(addprefix bin/,$(basename $(SRCS))))
DEPS := $(OBJS:%.o=%.d)

EXEC := bin/funge

INCLUDES := -I src/include -I src/fingerprint/include -I third_party/bigint/include

CPP := g++
CPPARGS := $(INCLUDES) -g -Wall -Wextra -Werror -std=c++2a
LINTARGS := $(INCLUDES) --enable=all --std=c++20

LD := g++
LDARGS := -pthread

.PHONY: all clean realclean build funge test lint doc man ut unittest cpputest smoketest

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
	@$(LD) $(LDARGS) -o $@ $^

bin/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "CPP " $(subst src/,,$<)
	@$(CPP) $(CPPARGS) -MMD -o $@ -c $<

-include $(DEPS)

test: ut smoketest

smoketest: $(EXEC)
	@./test/smoketest.sh

lint:
	@cppcheck $(LINTARGS) $(FUNGESRC)

doc: man
	@echo "DOX "
	@doxygen Doxyfile

man: bin/funge.1

bin/funge.1: doc/man.md
	@mkdir -p $(dir $@)
	@echo "MAN "
	@pandoc $< -s -t man -o $@

CPPUTESTLIB := test/cpputest/src/CppUTest/libCppUTest.a
UTCPPARGS := -I src/include -I test/cpputest/include -lpthread -Wall -Wextra -Werror -std=c++2a
UTSRCS := test/ut/unittest.cpp test/ut/StackTest.cpp src/Stack.cpp test/ut/VectorTest.cpp src/Vector.cpp src/VectorRange.cpp
UTBIN := bin/unittest

ut: unittest

unittest: $(UTBIN)
	@$(UTBIN) -c -v -ojunit

$(UTBIN): $(UTSRCS) $(CPPUTESTLIB)
	@mkdir -p $(dir $@)
	@echo "LD  " $@
	@$(CPP) $(UTCPPARGS) -o $@ $^

cpputest: $(CPPUTESTLIB)

$(CPPUTESTLIB):
	cd test/cpputest; cmake .
	make -C test/cpputest

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS) $(DEPS)

realclean: clean
	@echo REALCLEAN
	@rm -rf bin/
	@rm -rf doc/html/
