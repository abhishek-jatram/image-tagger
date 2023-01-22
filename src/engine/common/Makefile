LIBRARY_NAME = libcommon.a
PROJDIR := $(realpath $(CURDIR)/../../..)
BUILDDIR = $(PROJDIR)/build
LIBRARY := $(BUILDDIR)/libs/$(LIBRARY_NAME)


SOURCEDIR = types#. mapping_info nn_interface types utils
OBJECTSDIR = $(BUILDDIR)/objects

INC_DIRS := $(shell find $(SOURCEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -c
CXXFLAGS += $(INC_FLAGS) -MMD -MP

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
# SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/objects/%.o,$(SOURCES))
# OBJECTS := $(patsubst $(D)/%.cpp.o,$(D)/%.o,$(SOURCES:%=$(BUILDDIR)/%.o))

all: dir $(LIBRARY)

dir:
	mkdir -p $(BUILDDIR)/libs
	mkdir -p $(BUILDDIR)/objects

$(LIBRARY): $(OBJECTS)
	ar ru $@ $^
	ranlib $@

# $(EXECUTABLE): $(OBJECTS)
# 	$(CXX) $^ -o $@

$(OBJECTS): $(BUILDDIR)/objects/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)/*