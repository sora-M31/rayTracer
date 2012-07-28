# Scons-Local Makefile
#
# This allows you to use `make` to build the scons project.
#
# Peter Dodds (http://pddds.com) 2012

SCONSPATH=$(shell python -c 'import os.path; print os.path.normpath("site_scons/local/scons.py")' )
SCONS=python $(SCONSPATH)

all:
	@$(SCONS)

clean:
	@$(SCONS) -c

%:
	@$(SCONS) $@

