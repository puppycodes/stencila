# Include for various STENCILA_XXX variables
include $(dir $(lastword $(MAKEFILE_LIST)))/../variables.make

# Get the Stencila C++ package directory path.
STENCILA_CPP_HOME := $(STENCILA_HOME)/cpp

# Define compiler flags
STENCILA_CPP_FLAGS := -pthread -std=c++0x -Wall -Wno-unused-local-typedefs -DSTENCILA_HOME='"$(STENCILA_HOME)"'

# Define directories for includes
STENCILA_CPP_INCLUDE_DIRS := -I$(STENCILA_CPP_HOME) -I$(STENCILA_CPP_HOME)/requires/include

# Define directories for static libs
STENCILA_CPP_LIB_DIRS := -L$(STENCILA_CPP_HOME)/lib -L$(STENCILA_CPP_HOME)/requires/lib

# Define libraries required
STENCILA_CPP_LIBS := -lstencila
STENCILA_CPP_LIBS += -lboost_filesystem -lboost_system -lboost_regex
STENCILA_CPP_LIBS += -lgit2 -lcrypto -lssl -lrt # libgit2 requires libcrypto, libssl and librt
STENCILA_CPP_LIBS += -lpugixml
STENCILA_CPP_LIBS += -ltidy-html5
ifeq ($(STENCILA_PLATFORM), linux)
STENCILA_CPP_LIBS +=
endif
ifeq ($(STENCILA_PLATFORM), msys)
STENCILA_CPP_LIBS +=
endif