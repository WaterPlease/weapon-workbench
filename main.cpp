#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "parameter.h"

#include "Renderer.h"

void ResizeCallback(GLFWwindow* window, int width, int height) {
	iWidth = width;
	iHeight = height;
	glViewport(0, 0, iWidth, iHeight);
}

int main() {
	Renderer renderer;
	renderer.InitRenderer();
	renderer.SetOnResize(ResizeCallback);

	renderer.run();

	return 0;
}