#ifndef SETUP_HEADER
#define SETUP_HEADER
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <iostream>

#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/ebo.h"
#include "gfx/shader.h"
#include "gfx/texture.h"

class Render
{
public:
	GLFWwindow* window;

	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader shader;
	Texture texture;

	float vertices[40] =
	{
		//		loc					  colors		 texture
		-0.5f, -0.5f, 0.0f,		0.8f, 0.7f, 0.6f,	0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.5f, 0.4f, 0.3f,	1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		0.8f, 0.7f, 0.6f,	1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.5f, 0.4f, 0.3f,	0.0f, 1.0f,
		 0.0f,  0.0f, 0.8f,		0.2f, 0.1f, 0.2f,   1.0f, 1.0f
	};

	unsigned int indices[50] =
	{
		0, 1, 2,
		0, 3, 2,
		0, 4, 1,
		0, 4, 3,
		1, 4, 2,
		2, 4, 3,
	};

	void Setup()
	{
		vao_create(vao);
		vbo_create(vbo);

		ebo_create(ebo);

		vao_bind(vao);
		vbo_bind(vbo, vertices, sizeof(vertices));

		ebo_bind(ebo);
		ebo_buffer(ebo, indices, sizeof(indices));

		vao_attr(vao, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		vao_attr(vao, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (3 * sizeof(float)));
		vao_attr(vao, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (6 * sizeof(float)));

		stbi_set_flip_vertically_on_load(true);
		texture_create(texture, "include/src/container.jpg");

		program_create(shader, "shaders/default.vert", "shaders/default.frag");
	}


	void Tick()
	{
		float c = glfwGetTime();
		shader_use(shader);

		texture_bind(texture);
		vao_bind(vao);

		ebo_bind(ebo);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(sinf(c*2)*150), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(40.0f), (float)600 / (float)600, 0.1f, 100.0f);

		GLuint modelLoc = glGetUniformLocation(shader.handle, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLuint viewLoc = glGetUniformLocation(shader.handle, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		GLuint projLoc = glGetUniformLocation(shader.handle, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

		glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(window);
	}
	void free()
	{
		vao_delete(vao);
		vbo_delete(vbo);
		ebo_delete(ebo);
		shader_delete(shader);
		texture_delete(texture);
		glfwDestroyWindow(window);
	}
};

#endif