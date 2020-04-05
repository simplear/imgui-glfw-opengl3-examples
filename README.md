# imgui glfw opengl3 Template

- Templates that run with imgui/glfw/opengl3.

## Dependency
- Same as what "https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3" requires.

## Templates
- Each template-source-code is put under src* directory 
- List of templates
    - src0 : the same function as https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3".
    - src1 : show only the main and sub(optional) window.

## How to Build these templates
- common 

```
git clone git@github.com:simplear/imgui-glfw-opengl3-template
mkdir 3rdparty
cd imgui-glfw-opengl3-template/3rdparty
git clone https://github.com/ocornut/imgui.git
```

- for "src0"

```
cd src0
make
```

## How to Run

```
./glfw_opengl3_template
```
