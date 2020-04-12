# Example codes that use imgui/glfw/opengl3

Examples that run with imgui/glfw/opengl3.

## Confirmed Environment
- Ubuntu 16.04
- C++
- gcc-version 5.4.0

## Reference
- https://github.com/ocornut/imgui
- https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
- http://siguma-sig.hatenablog.com/entry/2017/04/23/004545
- https://docs.opencv.org/3.4/d8/dfe/classcv_1_1VideoCapture.html

## Dependency
- [dear imgui](https://github.com/ocornut/imgui) : for all examples
- [gl3w](https://www.glfw.org) : for all examples
- [stb](https://github.com/nothings/stb) : for src2
- OpenCV 4.1.0 : for src3, src4
- Refer what "https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3" requires.

## Examples
- Each template-source-code is put under src* directory 
- Source Code List
    - src0 : the same function as https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3".
    - src1 : show only the main and sub(optional) window.
    - src2 : load and show an image using "stb" library.
    - src3 : load and show an image using "OpenCV 4.1.0".
    - src4 : base on src3, add live video streaming using "OpenCV 4.1.0".

## Build and Run
- common

```
git clone git@github.com:simplear/imgui-glfw-opengl3-examples
mkdir 3rdparty
cd 3rdparty
git clone https://github.com/ocornut/imgui.git
git clone git@github.com:nothings/stb.git
cd ..
```

- for "src0"

```
cd src0
make -j`nproc`
./glfw_opengl3_example
```

