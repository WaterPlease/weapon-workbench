#include "Renderer.h"

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

	
	glEnable(GL_DEPTH_TEST);

	// Camera Initiation
	cam.updatePVMat();

	draw_prepare();
}

Shader* shader;
Model* model;
void Renderer::draw_prepare(){
	shader = new Shader("shaders\\vertex.glsl", "shaders\\frag.glsl");
	model = new Model("./models/mp40/mp40.obj",shader);

	model->setPos(glm::vec3(0.0f,0.0f,0.0f));
	model->setRot(glm::vec4(0,0,1,0));
	model->setScale(glm::vec3(0.1,0.1,0.1));
	model->updateTrans();
}
void Renderer::run() {
	while (!glfwWindowShouldClose(window)) {
		// Draw
		glClearColor(0.2f,0.2f,0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model->setRot(glm::vec4(
			(float)glfwGetTime(),
			0.0f,1.0f,0.0f
		));
		model->updateTrans();
		model->draw();

		// loop
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}