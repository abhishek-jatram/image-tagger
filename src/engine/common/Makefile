LIBRARY_NAME = libcommon.a
PROJDIR := $(realpath $(CURDIR)/../../..)
BUILDDIR = $(PROJDIR)/build
LIBRARY := $(BUILDDIR)/libs/$(LIBRARY_NAME)

SOURCEDIR = $(PROJDIR)/src/engine/common
OBJECTSDIR = $(BUILDDIR)/objects

INC_DIRS := $(shell find $(SOURCEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -c
CXXFLAGS += $(INC_FLAGS) -MMD -MP

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJECTS = $(addprefix $(OBJECTSDIR), $(patsubst $(PROJDIR)%.cpp,%.o,$(SOURCES)))
# OBJECTS := $(patsubst $(D)/%.cpp.o,$(D)/%.o,$(SOURCES:%=$(BUILDDIR)/%.o))

all: dir $(LIBRARY)

dir:
	mkdir -p $(BUILDDIR)/libs
	mkdir -p $(OBJECTSDIR)

$(LIBRARY): $(OBJECTS)
	ar ru $@ $^
	ranlib $@

# $(EXECUTABLE): $(OBJECTS)
# 	$(CXX) $^ -o $@

$(OBJECTS): $(OBJECTSDIR)/%.o : $(PROJDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -r $(LIBRARY)