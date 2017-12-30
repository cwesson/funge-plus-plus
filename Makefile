##
# @file Makefile
# @author Conlan Wesson
##

SRCS := $(wildcard src/*.java)
CLASSES := $(subst src/,bin/,$(subst .java,.class,$(SRCS)))

JAVA := javac
JAVAARGS := -d bin -cp bin -sourcepath src

all: $(CLASSES)

bin/%.class: src/%.java
	@mkdir -p bin/
	@echo JAVA $(subst src/,,$<)
	@$(JAVA) $(JAVAARGS) $<

clean:
	@echo CLEAN bin/
	@rm -rf bin/*.class

realclean:
	@echo REALCLEAN
	@rm -rf bin/

