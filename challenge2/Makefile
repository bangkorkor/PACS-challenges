# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-Wall -std=c++20 -Iinclude

# Directory for built executables and objects
BUILDDIR=build

# Build target executable
TARGET=$(BUILDDIR)/main

# Source files
SRCS=src/matrix.cpp src/main.cpp

# Object files (stored in the build directory)
OBJS=$(SRCS:src/%.cpp=$(BUILDDIR)/%.o)

# Default rule for building the executable
all: $(TARGET)

# Ensure the build directory exists
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Rule for linking the final executable
$(TARGET): $(OBJS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for compiling source files to object files
$(BUILDDIR)/%.o: src/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up by removing files in build directory, but not the directory itself
clean:
	rm -f $(BUILDDIR)/* $(BUILDDIR)/*.o

# Prevent make from doing something with files named like this
.PHONY: all clean
