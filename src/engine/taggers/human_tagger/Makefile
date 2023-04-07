TARGET_LIBRARY_NAME = libhumantagger.a
PROJDIR := $(realpath $(CURDIR)/../../../..)
BUILDDIR = $(PROJDIR)/build
TARGET_LIBRARY := $(BUILDDIR)/libs/$(TARGET_LIBRARY_NAME)

SOURCEDIR = $(PROJDIR)/src/engine/taggers/human_tagger
OBJECTSDIR = $(BUILDDIR)/objects

COMPONENTS_SOURCEDIRS = $(PROJDIR)/src/engine/components/object_detector
COMPONENTS_SOURCEDIRS += $(PROJDIR)/src/engine/components/roi_filterer

INC_DIRS := $(shell find $(SOURCEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS += -I$(PROJDIR)/src/engine/

LOCAL_LIBS_DIR = $(BUILDDIR)/libs
LOCAL_LIBS = common
LOCAL_LIB_FLAGS = -L$(LOCAL_LIBS_DIR) $(addprefix -l,$(LOCAL_LIBS))

# OpenCV related
OPENCV_INC = /usr/local/include/opencv4
OPENCV_LIB_DIR = /usr/local/lib/
OPENCV_LIBS = opencv_core opencv_imgproc
OPENCV_LIB_FLAGS = -L$(OPENCV_LIB_DIR) $(addprefix -l,$(OPENCV_LIBS))
OPENCV_FLAGS = -I/usr/local/include/opencv4

JSON_INC = $(PROJDIR)/thirdparty/nlohmann/
JSON_FLAGS = -I$(JSON_INC)

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -c
CXXFLAGS += $(INC_FLAGS)
# CXXFLAGS += $(LOCAL_LIB_FLAGS)
CXXFLAGS += $(OPENCV_FLAGS)
CXXFLAGS += $(JSON_FLAGS)
CXXFLAGS += $(COMMON_FLAGS)
CXXFLAGS += -MMD -MP
 
LDFLAGS = $(LOCAL_LIB_FLAGS) $(OPENCV_LIB_FLAGS)

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
SOURCES += $(foreach dir,$(COMPONENTS_SOURCEDIRS), $(shell find $(dir) -name '*.cpp'))
OBJECTS = $(addprefix $(OBJECTSDIR), $(patsubst $(PROJDIR)%.cpp,%.o,$(SOURCES)))
# OBJECTS := $(patsubst $(D)/%.cpp.o,$(D)/%.o,$(SOURCES:%=$(BUILDDIR)/%.o))

all: dir $(TARGET_LIBRARY)

dir:
	mkdir -p $(BUILDDIR)/libs
	mkdir -p $(OBJECTSDIR)

$(TARGET_LIBRARY): $(OBJECTS)
	ar ru $@ $^
	ranlib $@

# $(TARGET_EXECUTABLE): $(OBJECTS)
# 	$(CXX) $^ -o $@

$(OBJECTS): $(OBJECTSDIR)/%.o : $(PROJDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -r $(TARGET_LIBRARY)