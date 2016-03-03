#include "Shader.h"

Shader::Shader(void)
{
	filename = "";
	vertSource = "";
	fragSource = "";
	geomSource = "";
	vertShader = 0;
	fragShader = 0;
	geomShader = 0;
	shaderProgram = 0;
	validated = false;
}

Shader::Shader(string _filename)
{
	filename = _filename;
	vertSource = loadFile("Shaders\\" + filename + ".vert");
	fragSource = loadFile("Shaders\\" + filename + ".frag");
	geomSource = loadFile("Shaders\\" + filename + ".geom");
	vertShader = 0;
	fragShader = 0;
	geomShader = 0;
	shaderProgram = 0;
	linkShaders();
	validated = validateShaders();
}

Shader::~Shader(void)
{
	if (vertShader) glDeleteShader(vertShader);
	if (fragShader) glDeleteShader(fragShader);
	if (geomShader) glDeleteShader(geomShader);
	if (shaderProgram) glDeleteProgram(shaderProgram);

}

string Shader::loadFile(string fName)
{
	if (fName == "")
		return "";

	ifstream file;
	file.open(fName.c_str());
	if (!file.good())
		return "";

	string buffer, line;
	while (getline(file, line))
		buffer += line + "\n";
	file.close();
	return buffer + "\0";
}

void Shader::linkShaders()
{
	shaderProgram = glCreateProgram();

	//compile and attach vertex shader
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vsText = vertSource.c_str();
	GLint vlen = vertSource.length();
	glShaderSource(vertShader, 1, &vsText, &vlen);
	glCompileShader(vertShader);
	glAttachShader(shaderProgram, vertShader);

	//compile and attach fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fsText = fragSource.c_str();
	GLint flen = fragSource.length();
	glShaderSource(fragShader, 1, &fsText, &flen);
	glCompileShader(fragShader);
	glAttachShader(shaderProgram, fragShader);

	//compile and attach geometry shader
	if (geomSource.length() > 1)
	{
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* gsText = geomSource.c_str();
		GLint glen = geomSource.length();
		glShaderSource(geomShader, 1, &gsText, &glen);
		glCompileShader(geomShader);
		glAttachShader(shaderProgram, geomShader);
	}

	glLinkProgram(shaderProgram);
}

GLuint Shader::getProgram() { return shaderProgram; }

bool Shader::validateShaders()
{
	GLint rc = GL_TRUE;
	GLenum err = GL_NO_ERROR;
	do
	{
		err = glGetError();
	} while(err != GL_NO_ERROR);

	if (vertShader)
	{
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &rc);
		if (rc != GL_TRUE)
		{
			const GLsizei maxLen = 256;
			GLsizei len;
			GLchar msg[maxLen];
			glGetShaderInfoLog(vertShader, maxLen, &len, msg);
			cerr << "Shader error: " << filename << ".vert" << endl;
			cerr << msg;
			return false;
		}
	}

	if (fragShader)
	{
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &rc);
		if (rc != GL_TRUE)
		{
			const GLsizei maxLen = 256;
			GLsizei len;
			GLchar msg[maxLen];
			glGetShaderInfoLog(fragShader, maxLen, &len, msg);
			cerr << "Shader error: " << filename << ".frag" << endl;
			cerr << msg;
			return false;
		}
	}

	if (geomShader)
	{
		glGetShaderiv(geomShader, GL_COMPILE_STATUS, &rc);
		if (rc != GL_TRUE)
		{
			const GLsizei maxLen = 256;
			GLsizei len;
			GLchar msg[maxLen];
			glGetShaderInfoLog(geomShader, maxLen, &len, msg);
			cerr << "Shader error: " << filename << ".geom" << endl;
			cerr << msg;
			return false;
		}
	}

	if (shaderProgram)
	{
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &rc);
		if (rc != GL_TRUE)
			return false;
	}

	glUseProgram(shaderProgram);
	err = glGetError();
	const GLubyte* msg = gluErrorString(err);
	if (err != GL_NO_ERROR)
		return false;

	glUseProgram(0);
	return true;
}

bool Shader::isValid() { return validated; }