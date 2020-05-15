#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

void GameObject::BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	shader.BuildShader(vertexPath, fragmentPath, geometryPath);
}

void GameObject::BuildObject(GLfloat vertices[], GLuint verticesSize , GLuint indices[], GLuint indicesSize) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void GameObject::Render() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spritesheet.GetTextureID());

	shader.UseShader();
	transform.Execute(shader);
	glUniform1f(glGetUniformLocation(shader.GetShaderID(), "n"), 1.0f / spritesheet.MAX_NUMBER_OF_FRAME_WIDTH);
	glUniform1f(glGetUniformLocation(shader.GetShaderID(), "m"), 1.0f / spritesheet.MAX_NUMBER_OF_FRAME_HEIGHT);

	// Draw sprite
	glBindVertexArray(GetVAO());
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void GameObject::Animate(string animState) {
	spritesheet.Animate(animState);
	Render();
	glUniform1i(glGetUniformLocation(shader.GetShaderID(), "frameIndexX"), spritesheet.frame_idx);
	glUniform1i(glGetUniformLocation(shader.GetShaderID(), "frameIndexY"), spritesheet.frame_idy);
}

GLuint GameObject::GetObjectShaderID() {
	return shader.GetShaderID();
}

GLuint GameObject::GetVAO() {
	return VAO;
}

GLuint GameObject::GetVBO() {
	return VBO;
}

GLuint GameObject::GetEBO() {
	return EBO;
}

void GameObject::ApplyTexture(const char* path, unsigned int count_frame_width, unsigned int count_frame_height) {
	spritesheet = SpriteRender(path, count_frame_width, count_frame_height);
}