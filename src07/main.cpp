#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <implot.h>
#include <math.h>

// Reference
/*
https://github.com/ocornut/imgui
https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
http://siguma-sig.hatenablog.com/entry/2017/04/23/004545
https://docs.opencv.org/4.1.1/df/d5e/samples_2cpp_2tutorial_code_2ImgProc_2Morphology_1_8cpp-example.html#a14
*/

// Desktop OpenGL function loaders
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING)
#define GLFW_INCLUDE_NONE         // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>  // Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>

//using namespace std;
//using namespace gl;
//using namespace cv;

#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// Load an image into a OpenGL texture with common settings
bool LoadTextureFromFileCV(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    cv::Mat image_cv = cv::imread(filename,3);            // read color image
    int image_width =  image_cv.size[1];                  // get image width
    int image_height = image_cv.size[0];                  // get image height
    cv::cvtColor(image_cv, image_cv, cv::COLOR_BGR2RGBA); // convert BGR -> RGBA

    if (image_cv.ptr() == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_cv.ptr());

    // release memory
    image_cv.release();

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool LoadTextureFromMat(cv::Mat image_cv, GLuint* out_texture, int* out_width, int* out_height)
{
    // expect 3ch Mat
    // Load from Mat
    //cv::Mat image_cv = cv::imread(filename,3);          // read color image
    int image_width =  image_cv.size[1];                  // get image width
    int image_height = image_cv.size[0];                  // get image height
    cv::cvtColor(image_cv, image_cv, cv::COLOR_BGR2RGBA); // convert BGR -> RGBA

    if (image_cv.ptr() == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_cv.ptr());

    // release memory
    image_cv.release();

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 template", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
        bool err = gl3wInit() != 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
        bool err = glewInit() != GLEW_OK;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
        bool err = gladLoadGL() == 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING)
        bool err = false;
        glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
    #else
        bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
    #endif

    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Variables
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Added to show image ///////////////////////////////////////////////
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;   // Original
    GLuint my_image_texture_d = 0; // Dilated / Drawn Contours
    GLuint my_image_texture_f = 0; // Filled
    cv::Mat image_cv = cv::imread("../image/contours.png",3);    // read png and texture
    //////////////////////////////////////////////////////////////////////

    cv::Mat image_cv_1ch;
    cv::Mat image_cv_1ch_dilated;
    cv::Mat image_cv_cont;
    cv::Mat image_cv_cont_filled;

    cv::Scalar color( 255, 0, 255 );
    cv::Scalar colorToFill( 255, 0, 0 );

    // contours / hierarchy
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    //uint idx = 0;
    int dilation_size=0;  // how much pixel to dilate
    int RetrievalModes=0; // contour retrieval mode
    int ContourApproximationModes=1;
    std::string RetrievalModes_text;             // for Display
    std::string ContourApproximationModes_text;  // for Display

    /*
    ----- Contour 検出モード
    RETR_EXTERNAL =0 (親子なし。最外側の輪郭のみ。)
    RETR_LIST     =1 (親子なし) 
    RETR_CCOMP    =2 (全輪郭を検出し，2レベルの階層に分類)
    RETR_TREE     =3 (全輪郭を検出し，全階層情報)
    ----- Contour 近似方法
    CHAIN_APPROX_NONE      =0
    CHAIN_APPROX_SIMPLE    =1 -- デフォルト
    CHAIN_APPROX_TC89_L1   =2
    CHAIN_APPROX_TC89_KCOS =3
    */

    //    LoadTextureFromMat(image_cv, &my_image_texture, &my_image_width, &my_image_height);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // main window
        {
            ImGui::Begin("Configuration");
            ImGui::SliderInt("dilation_size", &dilation_size, 0, 5);
            ImGui::SliderInt("RetrievalModes", &RetrievalModes, 0, 3);
            ImGui::SliderInt("ContourApproximationModes", &ContourApproximationModes, 0, 3);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // process image /////////////////////////////////////////////////////
        cv::cvtColor(image_cv,image_cv_1ch, cv::COLOR_BGR2GRAY); // 3ch -> 1ch
        image_cv_cont=image_cv.clone();

        // Dilate (膨張)
        // define kernel
        cv::Mat element = getStructuringElement( cv::MORPH_RECT,
                       cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       cv::Point( dilation_size, dilation_size ) );
        cv::dilate(image_cv_1ch,image_cv_1ch_dilated, element);

        image_cv_cont_filled=image_cv_cont.clone();

        // 輪郭抽出
        cv::findContours( image_cv_1ch_dilated, contours, hierarchy, RetrievalModes, ContourApproximationModes, cv::Point(0, 0) );

        for( uint idx =0; idx<hierarchy.size(); idx++ )
        {
            cv::drawContours( image_cv_cont,        contours, idx, color, cv::LINE_4, 8, hierarchy );
            cv::drawContours( image_cv_cont_filled, contours, idx, color, cv::LINE_4, 8, hierarchy );
            /*
            // when　you want to fill only children
            if(hierarchy[idx][2]!=-1){
                cv::fillConvexPoly( image_cv_cont_filled, contours[hierarchy[idx][2]], colorToFill);
            }
            */
            cv::fillConvexPoly( image_cv_cont_filled, contours[idx], colorToFill);
        }

        // Render and Show image

        // Original
        LoadTextureFromMat(image_cv, &my_image_texture, &my_image_width, &my_image_height);
        ImGui::Begin("Original");
        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
        ImGui::End();

        // Dilated / Drawn Contours
        LoadTextureFromMat(image_cv_cont, &my_image_texture_d, &my_image_width, &my_image_height);
        ImGui::Begin("Dilated / Drawn Contours");
        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image((void*)(intptr_t)my_image_texture_d, ImVec2(my_image_width, my_image_height));

        switch(RetrievalModes){
            case 0:
                RetrievalModes_text = "RETR_EXTERNAL";
                break;
            case 1:
                RetrievalModes_text = "RETR_LIST";
                break;
            case 2:
                RetrievalModes_text = "RETR_CCOMP";
                break;
            case 3:
                RetrievalModes_text = "RETR_TREE";
                break;
        }

        switch(ContourApproximationModes){
            case 0:
                ContourApproximationModes_text = "CHAIN_APPROX_NONE";
                break;
            case 1:
                ContourApproximationModes_text = "CHAIN_APPROX_SIMPLE";
                break;
            case 2:
                ContourApproximationModes_text = "CHAIN_APPROX_TC89_L1";
                break;
            case 3:
                ContourApproximationModes_text = "CHAIN_APPROX_TC89_KCOS";
                break;
        }

        ImGui::Text("RetrievalModes : %s", RetrievalModes_text.c_str());
        ImGui::Text("ContourApproximationModes : %s", ContourApproximationModes_text.c_str());
        ImGui::Text("Hierarchy");
        for (uint j=0;j<hierarchy.size();j++){
                ImGui::Text("%4d %4d %4d %4d", hierarchy[j][0],hierarchy[j][1],hierarchy[j][2],hierarchy[j][3]);
        }

        ImGui::End();

        // Filled
        LoadTextureFromMat(image_cv_cont_filled, &my_image_texture_f, &my_image_width, &my_image_height);
        ImGui::Begin("Filled");
        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image((void*)(intptr_t)my_image_texture_f, ImVec2(my_image_width, my_image_height));
        ImGui::End();

        //////////////////////////////////////////////////////////////////////

        // Plot
        static float xs1[1001], ys1[1001];
        for (int i = 0; i < 1001; ++i) {
            xs1[i] = i * 0.001f;
            ys1[i] = 0.5f + 0.5f * sin(50 * xs1[i]);
        }
        static float xs2[11], ys2[11];
        for (int i = 0; i < 11; ++i) {
            xs2[i] = i * 0.1f;
            ys2[i] = xs2[i] * xs2[i];
        }
        if (ImGui::BeginPlot("Line Plot", "x", "f(x)", {-1,300})) {
            ImGui::Plot("sin(50*x)", xs1, ys1, 1001);
            ImGui::PushPlotStyleVar(ImPlotStyleVar_Marker, ImMarker_Circle);
            ImGui::Plot("x^2", xs2, ys2, 11);
            ImGui::PopPlotStyleVar();
            ImGui::EndPlot();
        }
        //////////////////////////////////////////////////////////////////////


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        // Release Memory
        glDeleteTextures(1 , &my_image_texture);
        glDeleteTextures(1 , &my_image_texture_d);
        glDeleteTextures(1 , &my_image_texture_f);
        contours.clear();

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


