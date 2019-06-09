##
# @file Makefile
# @author Conlan Wesson
##

SRCS := $(wildcard src/*.java)
CLASSES := $(subst src/,bin/,$(subst .java,.class,$(SRCS)))

JAVA := javac
JAVAARGS := -d bin -cp bin -sourcepath src

all: test

java: $(CLASSES)

bin/%.class: src/%.java
	@mkdir -p bin/
	@echo JAVA $(subst src/,,$<)
	@$(JAVA) $(JAVAARGS) $<

test: java
	@./test/smoketest.sh

clean:
	@echo CLEAN bin/
	@rm -f $(CLASSES)

realclean:
	@echo REALCLEAN
	@rm -rf bin/
