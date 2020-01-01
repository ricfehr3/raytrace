SOURCEDIR = src
BUILDDIR = build

CXXFLAGS = -std=c++17 -O3 -Wall -g -Iinclude
LDFLAGS = -lm
TARGET = ray
SRCS = $(wildcard $(SOURCEDIR)/*.cpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)\

$(TARGET): $(OBJS) 
		$(CXX) -o $(TARGET) $(CXXFLAGS) $(OBJS) $(LDFLAGS)

$(OBJS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
		$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: test clean

test: ray
		echo "No tests. yet ;)"

clean:
		rm -f $(BUILDDIR)/* core *.core $(TARGET)
			
install:
		echo "Installing is not supported"
