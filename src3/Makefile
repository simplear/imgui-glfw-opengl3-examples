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

EXE = glfw_opengl3_template

SOURCES =     main.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_glfw.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += ../3rdparty/imgui/imgui.cpp
SOURCES += ../3rdparty/imgui/imgui_demo.cpp
SOURCES += ../3rdparty/imgui/imgui_draw.cpp
SOURCES += ../3rdparty/imgui/imgui_widgets.cpp
SOURCES += ../3rdparty/imgui/examples/imgui_impl_glfw.cpp ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += ../3rdparty/imgui/examples/libs/gl3w/GL/gl3w.c ## OPENGL LOADER

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -I../3rdparty/imgui/examples -I../3rdparty/imgui -I../3rdparty/stb -I/usr/local/include/opencv4
CXXFLAGS += -g -std=c++11 -Wall -Wformat
CXXFLAGS += -I../3rdparty/imgui/examples/libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W ## OPENGL LOADER
CXXFLAGS += `pkg-config --cflags glfw3` ## BUILD FLAGS PER PLATFORM (Linux)
CXXFLAGS += -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dpm -lopencv_face -lopencv_photo -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core

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
all: $(EXE)
	@echo Build complete for Linux
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
clean:
	rm -f $(EXE) $(OBJS)
