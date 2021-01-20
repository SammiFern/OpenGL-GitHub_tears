#pragma once
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include<fstream>
#include<string>

#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>

#include<SOIL2.h>

class Shader {
private:
	//draw program name (core_program as an example), 
	GLuint id;
	const int versionMajor;
	const int versionMinor;

	//load shader filename.glsl return string containing source code
	std::string loadShaderSource(char* fileName) {
		std::string temp = "";
		std::string src = "";
		std::ifstream in_file;
		in_file.open(fileName);

		if (in_file.is_open()) {
			while (std::getline(in_file, temp)) {
				src += temp + "\n";
			}
		}
		else {
			std::cout << "Couldn't open shader file "<<fileName<<"\n";
		}
		in_file.close();
		std::string versionNr = std::to_string(this->versionMajor) + std::to_string(this->versionMinor) + "0";
		src.replace(src.find("#version "), 12, ("#version "+versionNr));

		return src;
	}
	//vertex, fragment or geometry shader
	GLuint loadShader(GLenum type, char* fileName) {
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Couldn't compile shader"<<fileName<<"\n";
			std::cout << infoLog << "\n";
		}
		return shader;
	}
	//link shaders
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		//glUseProgram(this->id);
		glAttachShader(this->id, vertexShader);
		if (geometryShader!=0) {
			glAttachShader(this->id, geometryShader);
		}
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "Couldn't link program\n";
			std::cout << infoLog << "\n";
		}
		glUseProgram(0);

	}

public:
	//constructor & destructor
	Shader(const int versionMajor, const int versionMinor,
		char * vertexFile, char* geometryFile, char* fragmentFile )
		:versionMajor(versionMajor), versionMinor(versionMinor) {
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

		if (geometryFile != "") {
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		glUseProgram(0);
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	~Shader() {
		glDeleteProgram(this->id);
	}

	//set uniform funcs
	void use(){
		glUseProgram(this->id);
	}

	void unuse() {
		glUseProgram(0);
	}

	//texture
	void set1i(GLint value, const GLchar* name) {
		this->use();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void set1f(GLfloat value, const GLchar* name) {
		this->use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name) {
		this->use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}


	void setVec3f(glm::fvec3 value, const GLchar* name) {
		this->use();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name) {
		this->use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE) {
		this->use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE) {
		this->use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}
};