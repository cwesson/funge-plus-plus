##
# @file Makefile
# @author Conlan Wesson
##

SRCS := $(wildcard src/*.cpp)
OBJS := $(subst src/,bin/,$(subst .cpp,.o,$(SRCS)))

EXEC := bin/funge

CPP := g++
CPPARGS := -I src/include -g -Wall -Wextra -Werror

LD := g++
LDARGS := -lpthread

.PHONY: all clean realclean

all: test

build: funge

funge: $(EXEC)

$(EXEC): $(OBJS)
	@echo "LD  " $(subst bin/,,$@)
	@$(LD) $(LDARGS) -o $@ $(OBJS)

bin/%.o: src/%.cpp
	@mkdir -p bin/
	@echo "CPP " $(subst src/,,$<)
	@$(CPP) $(CPPARGS) -o $@ -c $<

test: build
	@./test/smoketest.sh

CPPUTESTLIB := ut/cpputest/src/CppUTest/libCppUTest.a
UTCPPARGS := -I src/include -I ut/cpputest/include -lpthread
UTSRCS := ut/unittest.cpp src/Vector.cpp

ut: unittest

unittest: $(UTSRCS) $(CPPUTESTLIB)
	$(CPP) $(UTCPPARGS) -o ./bin/$@ $(UTSRCS) $(CPPUTESTLIB)
	./bin/unittest -c -v

$(CPPUTESTLIB): cpputest

cpputest:
	cd ut/cpputest; cmake .
	make -C ut/cpputest

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS)

realclean:
	@echo REALCLEAN
	@rm -rf bin/
