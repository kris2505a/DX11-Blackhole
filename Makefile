# Project settings
NAME := myprogram
SRCDIR := src
BUILDDIR := obj
BINDIR := bin

# Library directories
GLFWDIR := thirdparty/GLFW
GLADDIR := thirdparty/glad

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -DGLAD_GLAPI_IMPORT \
            -I$(GLFWDIR)/include -I$(GLADDIR)/include -I$(SRCDIR)

# Linker flags
LDFLAGS := -mconsole -L$(GLFWDIR)/lib -L$(GLADDIR)/lib -lglfw3dll -lglad -lopengl32

# Recursively gather source files
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(call rwildcard,$(SRCDIR)/,*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(BINDIR)/$(NAME).exe

# Link executable
$(BINDIR)/$(NAME).exe: $(OBJECTS)
	@echo Linking...
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	$(CXX) $^ -o $@ $(LDFLAGS)
	@copy /Y "$(GLADDIR)\lib\glad.dll" "$(BINDIR)" >nul
	@copy /Y "$(GLFWDIR)\lib\glfw3.dll" "$(BINDIR)" >nul

# Compile source to object
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo Compiling $<
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo Cleaning...
	@if exist "$(BUILDDIR)" rmdir /S /Q "$(BUILDDIR)"
	@if exist "$(BINDIR)\$(NAME).exe" del /Q "$(BINDIR)\$(NAME).exe"
	@if exist "$(BINDIR)\glad.dll" del /Q "$(BINDIR)\glad.dll"
	@if exist "$(BINDIR)\glfw3.dll" del /Q "$(BINDIR)\glfw3.dll"

# Build and run the program
run: all
	@echo Running...
	@$(BINDIR)\$(NAME).exe

.PHONY: all clean run
