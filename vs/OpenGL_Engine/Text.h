#ifndef TEXT_H
#define TEXT_H

#include <map>

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "ScratchEngine.h"

using namespace std;

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text {
public:
	Text();
	~Text();
	void Init();
	void SetText(string _text);
	void SetPosition(glm::vec2 _position);
	void SetSize(float _size);
	void SetColor(glm::vec4 _color);
	int GetShaderID();
	void Render();
	void PreRender();
	glm::vec4 GetColor();
	glm::vec2 GetPosition();
private:
	void BuildTextShader();
	Shader shader;
	string text;
	glm::vec2 position;
	glm::vec4 color;
	float size;
	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO;
};

#endif