TARGET_TEST_NAME = test_engine
PROJDIR := $(realpath $(CURDIR)/../..)
BUILDDIR = $(PROJDIR)/build
TARGET_TEST := $(BUILDDIR)/bin/$(TARGET_TEST_NAME)

SOURCEDIR = $(PROJDIR)/test/functional
OBJECTSDIR = $(BUILDDIR)/objects

INC_DIRS := $(shell find $(SOURCEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS += -I$(PROJDIR)/src/engine/

LOCAL_LIBS_DIR := $(BUILDDIR)/libs
LOCAL_LIBS := common scenetagger objecttagger humantagger imagetaggerengine
LOCAL_LIB_FLAGS := -L$(LOCAL_LIBS_DIR) $(addprefix -l,$(LOCAL_LIBS))


# OpenCV related
# OPENCV_INC = /usr/local/include/opencv4
OPENCV_LIB_DIR = /usr/local/lib/
OPENCV_LIBS = opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui opencv_videoio opencv_objdetect
OPENCV_LIB_FLAGS = -L$(OPENCV_LIB_DIR) $(addprefix -l,$(OPENCV_LIBS))
OPENCV_FLAGS += -I/usr/local/include/opencv4

# CFLAGS =`pkg-config --cflags opencv`
# LDFLAGS =`pkg-config --libs opencv`
# OPENCV_FLAGS = -I/usr/local/include/opencv4

JSON_INC = $(PROJDIR)/thirdparty/nlohmann/
JSON_FLAGS = -I$(JSON_INC)

CXX = g++
CXXFLAGS = -g -c -std=c++14 -Wall
CXXFLAGS += $(INC_FLAGS)
CXXFLAGS += $(OPENCV_FLAGS)
CXXFLAGS += $(JSON_FLAGS)
CXXFLAGS += -MMD -MP

LDLIBS := $(LOCAL_LIB_FLAGS) $(OPENCV_LIB_FLAGS)

SOURCES := $(SOURCEDIR)/test.cpp
OBJECTS = $(addprefix $(OBJECTSDIR), $(patsubst $(PROJDIR)%.cpp,%.o,$(SOURCES)))
# OBJECTS := $(patsubst $(D)/%.cpp.o,$(D)/%.o,$(SOURCES:%=$(BUILDDIR)/%.o))

all: dir $(TARGET_TEST)

dir:
	mkdir -p $(BUILDDIR)/bin
	mkdir -p $(OBJECTSDIR)

# $(TARGET_LIBRARY): $(OBJECTS)
# 	ar ru $@ $^
# 	ranlib $@

$(TARGET_TEST): $(OBJECTS)
	$(CXX) $(LDLIBS) $^ -o $@

$(OBJECTS): $(OBJECTSDIR)/%.o : $(PROJDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -r $(TARGET_TEST)