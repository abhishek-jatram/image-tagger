LIBRARY_NAME = libcommon.a
PROJDIR := $(realpath $(CURDIR)/../../..)
BUILDDIR = $(PROJDIR)/build
LIBRARY := $(BUILDDIR)/libs/$(LIBRARY_NAME)

SOURCEDIR = $(PROJDIR)/src/engine/common
OBJECTSDIR = $(BUILDDIR)/objects

INC_DIRS := $(shell find $(SOURCEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

OPENCV_INC = /usr/local/include/opencv4
OPENCV_LIB_DIR = /usr/local/lib/
OPENCV_LIBS = opencv_core opencv_imgproc
OPENCV_FLAGS = -L$(OPENCV_LIB_DIR) $(addprefix -l,$(OPENCV_LIBS))
OPENCV_FLAGS += -I/usr/local/include/opencv4

JSON_INC = $(PROJDIR)/thirdparty/nlohmann/
JSON_FLAGS = -I$(JSON_INC)

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -c
CXXFLAGS += $(INC_FLAGS)
CXXFLAGS += $(OPENCV_FLAGS)
CXXFLAGS += $(JSON_FLAGS)
CXXFLAGS += -MMD -MP

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