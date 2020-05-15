#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include "Shader.h"
#include "Transform.h"
#include "SpriteRender.h"

class GameObject {
public:
	GameObject();
	~GameObject();
	Transform transform;
	void BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void BuildObject(GLfloat vertices[], GLuint verticesSize, GLuint indices[], GLuint indicesSize);
	void Render();
	Shader shader;
	SpriteRender spritesheet;
	GLuint GetObjectShaderID();
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetEBO();
	void ApplyTexture(const char* path, unsigned int count_frame_width = 1, unsigned int count_frame_height = 1);
	void Animate(string animState);
private:
	GLuint VAO, VBO, EBO;
};

#endif