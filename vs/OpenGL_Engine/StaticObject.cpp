#include "StaticObject.h"

StaticObject::StaticObject() {
	background = GameObject();
	transparentPanel = GameObject();
}

StaticObject::~StaticObject() {

}

void StaticObject::Init() {
	CreateBackground();
	CreateTransparent();
}

void StaticObject::Render() {
	background.Render();
}

void StaticObject::LateRender() {
	transparentPanel.Render();
}

void StaticObject::Update() {

}

void StaticObject::CreateBackground() {
	background.BuildShader("background.vert", "background.frag", nullptr);

	background.ApplyTexture("background/2_game_background.png");

	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	background.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(Window::GetScreenWidth()), static_cast<GLfloat>(Window::GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	background.shader.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(background.GetObjectShaderID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	background.transform.Scale(vec3(Window::GetScreenWidth(), Window::GetScreenHeight(), 1));

}

void StaticObject::CreateTransparent() {
	transparentPanel.BuildShader("background.vert", "background.frag", nullptr);

	transparentPanel.ApplyTexture("background/transparent.png");

	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	transparentPanel.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(Window::GetScreenWidth()), static_cast<GLfloat>(Window::GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	transparentPanel.shader.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(transparentPanel.GetObjectShaderID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform1f(glGetUniformLocation(transparentPanel.GetObjectShaderID(), "alpha"),0.8f);

	transparentPanel.transform.Scale(vec3(Window::GetScreenWidth(), Window::GetScreenHeight(), 1));

	transparentPanel.transform.SetPosition(glm::vec3(transparentPanel.transform.position.x, transparentPanel.transform.position.y, -1));
	transparentPanel.activeSelf = false;
}