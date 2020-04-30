#
# Conformed with Ubuntu 16.04
#
# ## prerequisite
#
# - GLFW (http://www.glfw.org):
# - command
#   ```
#   apt-get install libglfw-dev
#   ```

#CXX = g++
#CXX = clang++

EXE = glfw_opengl3_example

#SOURCES =  implot_demo.cpp
SOURCES =  main.cpp
SOURCES += ../3rdparty/implot/implot.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_glfw.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_glfw.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += ../3rdparty/imgui/imgui.cpp
SOURCES += ../3rdparty/imgui/imgui_demo.cpp
SOURCES += ../3rdparty/imgui/imgui_draw.cpp
SOURCES += ../3rdparty/imgui/imgui_widgets.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_glfw.cpp ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += ../3rdparty/imgui/examples/libs/gl3w/GL/gl3w.c ## OPENGL LOADER

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -I../3rdparty/imgui/examples -I../3rdparty/imgui
CXXFLAGS += -I../3rdparty/implot
CXXFLAGS += -g -std=c++11 -Wall -Wformat
CXXFLAGS += -I../3rdparty/imgui/examples/libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W ## OPENGL LOADER
CXXFLAGS += `pkg-config --cflags glfw3` ## BUILD FLAGS PER PLATFORM (Linux)

CFLAGS = $(CXXFLAGS) ## BUILD FLAGS PER PLATFORM (Linux)

LIBS =
LIBS += -lGL `pkg-config --static --libs glfw3` ## BUILD FLAGS PER PLATFORM (Linux)

## BUILD RULES
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o:../3rdparty/imgui/examples/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o:../3rdparty/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o:../3rdparty/imgui/examples/libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o:../3rdparty/imgui/examples/libs/glad/src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o:../3rdparty/implot/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for Linux
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
clean:
	rm -f $(EXE) $(OBJS)
