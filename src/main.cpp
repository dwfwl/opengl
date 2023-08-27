#include "setup.h"
#include <iostream>

int b = 1;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		if (b == 1)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			b = 2;
		}
		else if (b == 2)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			b = 1;
		}
	}
}

int main(void)
{
	Render v;
	glfwInit();
	v.window = glfwCreateWindow(600, 600, "opengl", NULL, NULL);
	glfwMakeContextCurrent(v.window);

	gladLoadGL();

	v.Setup();

	glfwSetKeyCallback(v.window, key_callback);

	while (!glfwWindowShouldClose(v.window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		
		glfwPollEvents();

		v.Tick();
	}

	v.free();

	glfwTerminate();
	return 0;
}