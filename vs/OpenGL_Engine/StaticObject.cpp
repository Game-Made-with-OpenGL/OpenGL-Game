#include "StaticObject.h"

StaticObject::StaticObject() {
	background = GameObject();
}

StaticObject::~StaticObject() {

}

void StaticObject::Init() {
	CreateBackground();
}

void StaticObject::Render() {
	background.Render();
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