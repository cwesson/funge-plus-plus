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

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS)

realclean:
	@echo REALCLEAN
	@rm -rf bin/
