#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC
#include<GL/glew.h>	
#include<GLFW/glfw3.h>


using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;


	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);


	try {
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("open file error");
		}

		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception & ex) {
		printf(ex.what());
	}
}

void Shader::use() {
	glUseProgram(ID);
}
