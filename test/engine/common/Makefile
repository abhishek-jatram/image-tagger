# NOT FUNCTIONAL YET, NEEDS DEBUGGING
TEST_NAME = test_common
PROJDIR := $(realpath $(CURDIR)/../../..)
BUILDDIR = $(PROJDIR)/build
TEST := $(BUILDDIR)/tests/$(TEST_NAME)

SOURCEDIR = .
OBJECTSDIR = $(BUILDDIR)/objects/test


INC_DIRS := $(PROJDIR)/src
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIBS = libcommon.a
LIBS_FLAGS := $(addprefix -l,$(LIBS))

LDFLAGS = -L$(BUILDDIR)/libs $(LIBS_FLAGS)
# LDFLAGS += -static

# SOURCES += test_common.cpp
# SOURCES += test_common.cpp types/test_tensor3d.cpp
SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJECTS = $(addprefix $(OBJECTSDIR)/, $(patsubst %.cpp,%.o,$(SOURCES)))

# GTest related
GTEST_DIR = $(PROJDIR)/thirdparty/googletest-1.13.0

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -c
CXXFLAGS += $(INC_FLAGS)
CXXFLAGS += -I$(GTEST_DIR)/googletest/include
CXXFLAGS += -I$(GTEST_DIR)/googlemock/include
CXXFLAGS += $(LDFLAGS)
# CXXFLAGS += $(GTEST_LIBS)
CXXFLAGS += -L$(GTEST_DIR)/lib -llibgtest.a -llibgmock.a -llibgtest_main.a -llibgmock_main.a
CXXFLAGS += -static


$(info "__________")
$(info $(CXXFLAGS))
$(info "__________")

# gtest:
# 	CURRENT_DIR = $(CURDIR)
# 	cd $(GTEST_DIR)
# 	cmake .
# 	make
# 	cd $(CURRENT_DIR)

all: dir $(TEST)

dir:
	mkdir -p $(OBJECTSDIR)

$(TEST): $(OBJECTS)
	$(CXX) $^ -o $@

$(OBJECTS): $(OBJECTSDIR)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(TEST)