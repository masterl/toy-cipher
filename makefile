#   =======================
#  ||    ROOT MAKEFILE    ||
#   =======================
#

include .functions.mk

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Compilers:
#--------------------------------------------------------------------------
# Override if needed:
CC := gcc
CXX := g++

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Directories for linking
#--------------------------------------------------------------------------
# ======== GENERAL ========
LIBDIR := -L/usr/lib

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Compilation flags
#--------------------------------------------------------------------------

# Flags for the C compiler.
CFLAGS := -Wall

# Flags for the C++ compiler.
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic
CXXFLAGS += -isystem $(PROJECT_ROOT)/vendor

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Linker flags
#--------------------------------------------------------------------------
# ==== SOME KNOWN FLAGS (might be incomplete) ====
#PGFLAGS = -lpq
#BOOSTFLAGS = -lboost_locale -lpthread -lboost_thread -lboost_filesystem -lboost_system -lboost_regex -lboost_serialization -lboost_random
#MISCFLAGS = -lssl -lcrypto -lz -ldl -lmhash -lcurl
#GOOGLETESTFLAGS = -lgmock_main -lgmock -lgtest
#STACKTRACEFLAGS = -rdynamic
#PTHREADFLAG = -lpthread

#LINKFLAGS := -lboost_filesystem -lboost_system
ifeq ($(MAKECMDGOALS),test)
	CXXFLAGS += -include ./tests/common.hpp
	TESTFLAGS :=
endif

LINKFLAGS += $(TESTFLAGS)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Sources directories
#--------------------------------------------------------------------------
# Specify main source directory (which contains the main source file)
MAINDIR := src
# Name of main file
MAINFILE := $(call get_main_file)

# All source directories (except test files directory)
SOURCEDIRS := $(MAINDIR)

UNPROCESSEDDIRLIST := $(SOURCEDIRS)

ifeq ($(MAKECMDGOALS),test)
	TESTSDIR := tests
	CFLAGS += -iquote $(PROJECT_ROOT)/src
	CXXFLAGS += -iquote $(PROJECT_ROOT)/src
	UNPROCESSEDDIRLIST += $(TESTSDIR)
endif

_ALLSRCDIRLIST := $(call get_processed_directories_trees_list,$(UNPROCESSEDDIRLIST))

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Object directories
#--------------------------------------------------------------------------
OBJDIRLIST := $(call get_objects_directories,$(_ALLSRCDIRLIST))

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Sources list
#--------------------------------------------------------------------------
ALLSRCFILES := $(foreach dir,$(_ALLSRCDIRLIST),$(call get_folder_source_files_list,$(dir)))

# Main file should be removed from list when testing
ifeq ($(MAKECMDGOALS),test)
	ALLSRCFILES := $(filter-out $(MAINFILE),$(ALLSRCFILES))
endif

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Object files list
#--------------------------------------------------------------------------
ALLOBJS := $(call get_objects_from_sources_list,$(ALLSRCFILES))

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Main compiler
#--------------------------------------------------------------------------
MAIN_COMPILER := $(call get_main_compiler)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Main flags
#--------------------------------------------------------------------------
MAIN_FLAGS := $(if $(call is_cpp_project),$(CXXFLAGS),$(CFLAGS))

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Executable definitions
#--------------------------------------------------------------------------
EXEC := toy-cipher
TESTEXEC := test

BINDIR := bin

export CFLAGS
export CXXFLAGS
export OBJDIR

exec: rmexec allobjs FORCE | $(BINDIR)
	$(MAIN_COMPILER) $(ALLOBJS) $(MAIN_FLAGS) -o $(BINDIR)/$(EXEC) $(LINKFLAGS)
	@echo -e '=----------------------------------------------------='
	@echo -e '=           executable generated/updated             ='
	@echo -e '=           Executable: $(BINDIR)/$(EXEC)  \t\t     ='
	@echo -e '=----------------------------------------------------=\n\n'

help:
	@echo -e '\n'
	@echo -e '======================= HELP ========================\n'
	@echo -e '   Options:\n'
	@echo -e '      make exec            [compiles main executable]'
	@echo -e '      make clean         [erases all generated files]'
	@echo -e '=====================================================\n\n'

test: compiletest
	@echo -e 'Executing tests...\n'
	@set -e;./$(BINDIR)/$(TESTEXEC)

compiletest: rmtest allobjs FORCE | $(BINDIR)
	$(MAIN_COMPILER) $(ALLOBJS) $(MAIN_FLAGS) -o $(BINDIR)/$(TESTEXEC) $(LINKFLAGS)
	@echo -e '=----------------------------------------------------='
	@echo -e '=           TESTS generated/updated                  ='
	@echo -e '=           Executable: $(BINDIR)/$(TESTEXEC)  \t\t     ='
	@echo -e '=----------------------------------------------------=\n\n'

allobjs: objdirs $(ALLOBJS)
	@echo -e '------------------------------------------------------'
	@echo -e '\tObjects updated!\n'

$(ALLOBJS): FORCE
	@set -e; $(MAKE) --no-print-directory -f makeobj.mk TARGET=$@

objdirs: | $(OBJDIRLIST)
	@echo -e '------------------------------------------------------'
	@echo -e '\tObjects directories created/checked!\n'

$(OBJDIRLIST) $(BINDIR):
	mkdir $@

clean: rmobjs rmexec FORCE
	rm -rf $(BINDIR)
	@echo -e '------------------------------------------------------'
	@echo -e '\tAll files removed!\n\n'

rmexec:
	rm -f $(BINDIR)/$(EXEC)
	@echo -e '------------------------------------------------------'
	@echo -e '\tExecutables removed!'

rmtest:
	rm -f $(BINDIR)/$(TESTEXEC)
	@echo -e '------------------------------------------------------'
	@echo -e '\tTest executable removed!'

rmobjs: FORCE
	$(foreach dir, $(OBJDIRLIST) tests/$(OBJDIR), $(call execute-command, rm -rf $(dir) ) )

FORCE:

#  ===========================
#  ||    MAKEFILE >END<      ||
#  ===========================
