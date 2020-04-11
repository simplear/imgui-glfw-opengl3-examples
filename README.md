# Example codes that use imgui/glfw/opengl3

- Examples(templates) that run with imgui/glfw/opengl3.
- Additionally for src2 : "stb"
- Additionally for src3 : "opencv4.1.0"

## Confirmed Environment
- Ubuntu 16.04
- C++
- gcc-version 5.4.0

## Reference
- https://github.com/ocornut/imgui
- https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
- http://siguma-sig.hatenablog.com/entry/2017/04/23/004545

## Dependency
- [dear imgui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)
- [gl3w](https://www.glfw.org)
- Refer what "https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3" requires.

## Examples
- Each template-source-code is put under src* directory 
- List
    - src0 : the same function as https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3".
    - src1 : show only the main and sub(optional) window.
    - src2 : load and show an image using "stb" library.
    - src3 : load and show an image using OpenCV 4.1.0

## Build
- common 

```
git clone git@github.com:simplear/imgui-glfw-opengl3-template
mkdir 3rdparty
cd imgui-glfw-opengl3-template/3rdparty
git clone https://github.com/ocornut/imgui.git
git clone git@github.com:nothings/stb.git
cd ..
```

- for "src0"

```
cd src0
make
```

## Run

```
./glfw_opengl3_template
```
