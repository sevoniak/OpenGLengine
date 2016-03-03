#pragma once
#include "Defs.h"

class Texture
{
private:
	GLuint buffer;
public:
	Texture(void);
	~Texture(void);

	GLuint getBuffer();
};

