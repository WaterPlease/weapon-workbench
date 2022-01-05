#ifndef __RENDERER__
#define __RENDERER__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "parameter.h"
#include "Shader.h"
#include "Model.h"

class Renderer
{
private:
	GLFWwindow* window;
public:
	void InitRenderer();
	void draw_prepare();
	void run();

	void SetOnResize(GLFWframebuffersizefun ResizeCallback) {
		glfwSetFramebufferSizeCallback(window, ResizeCallback);
	}
};

#endif