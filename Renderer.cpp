#include "Renderer.h"
#include "Shader.h"

void Renderer::InitRenderer() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(iWidth, iHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD" << std::endl;
		exit(-1);
	}
	draw_prepare();
}

Shader* shader;
unsigned int VBO, VAO;
void Renderer::draw_prepare(){
	shader = new Shader("C:\\shaders\\vertex.glsl", "C:\\shaders\\frag.glsl");
}
void Renderer::run() {
	while (!glfwWindowShouldClose(window)) {
		// Draw
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//model->draw();

		// loop
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}