#include "CharacterBehaviour.h"
#include "Debug.h"

void CharacterBehaviour::Init() {
	
	player = GameObject();
	BuildPlayerSprite();
}

void CharacterBehaviour::Render() {
	
}

void CharacterBehaviour::Update() {
	
}

void CharacterBehaviour::Attack() {
	Debug::Log("Attack");
}

void CharacterBehaviour::Deffend() {
	Debug::Log("Deffend");
}

void CharacterBehaviour::Run() {
	Debug::Log("Run");
}

void CharacterBehaviour::TakeDamage(int damage) {
	Debug::Log(string("Ouch Take ") + to_string(damage) + string(" hit"));
}

void CharacterBehaviour::UpdateSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;

	if (walk_anim && frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx == NUM_FRAMES - 1) frame_idx = 0;  else frame_idx++;

		// Pass frameIndex to shader
		glUniform1i(glGetUniformLocation(player.GetObjectShaderID(), "frameIndex"), frame_idx);
	}
}

void CharacterBehaviour::DrawPlayerSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Activate shader
	player.Render();

	// Draw sprite
	glBindVertexArray(player.GetVAO());
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void CharacterBehaviour::BuildPlayerSprite()
{
	player.BuildShader("spriteAnim.vert", "spriteAnim.frag", nullptr);

	// Pass n to shader
	GLint location = glGetUniformLocation(player.GetObjectShaderID(), "n");
	player.Render();
	glUniform1f(location, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("homeranim.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES;
	frame_height = (float)height;
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

	player.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(Window::GetScreenWidth()), static_cast<GLfloat>(Window::GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	player.Render();
	glUniformMatrix4fv(glGetUniformLocation(player.GetObjectShaderID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos = (Window::GetScreenWidth() - frame_width) / 2;
	yposGround = Window::GetScreenHeight() - frame_height;
	ypos = yposGround;
	gravity = 0.05f;
	xVelocity = 0.1f;
}