# Examples that run with imgui/glfw/opengl3

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
- Refer what "https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3" requires.
- [dear imgui](https://github.com/ocornut/imgui) : for all examples
- [gl3w](https://www.glfw.org) : for all examples
- [stb](https://github.com/nothings/stb) : for src02
- [implot](https://github.com/epezent/implot) : for src07-9
- OpenCV 4.1.0 : for src03-src07

## Examples
- Each template-source-code is put under src* directory 
- Source Code List
    - src00 : the same function as https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3".
    - src01 : show only the main and sub(optional) window.
    - src02 : load and show an image using "stb" library.
    - src03 : load and show an image using "OpenCV 4.1.0".
    - src04 : base on src03, added live video streaming.
    - src05 : base on src04, added average-multi-frame function
    - src06 : base on src03, added image processing using contours
    - src07 : base on src06, added plotter function by implot
    - src08 : run implot minimal-demo for this environment
    - src09 : run implot demo for this environment

## Build and Run
- common

```
git clone git@github.com:simplear/imgui-glfw-opengl3-examples
mkdir 3rdparty
cd 3rdparty
git clone git@github.com/ocornut/imgui.git
git clone git@github.com:nothings/stb.git
git clone git@github.com:epezent/implot.git
cd ..
```

- for "src00"

```
cd src00
make -j`nproc`
./glfw_opengl3_example
```

- for "srcN" (N is a number)

```
cd srcN
make -j`nproc`
./glfw_opengl3_example
```

