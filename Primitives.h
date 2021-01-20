#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include<vector>
#include"Vertex.h"

class Primitive {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
public:
	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
	Triangle()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2	//Triangle 1
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Quad : public Primitive
{
public:
	Quad()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3		//Triangle 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Pyramid : public Primitive
{
public:
	Pyramid()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			//Triangle front
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

			//Triangle left
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

			//Triangle back
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

			//Triangles right
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

class Cube : public Primitive
{
public:
	Cube()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(0.0f, 0.0f, -1.f), //0
		glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(0.0f, 0.0f, -1.f),//1
		glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 0.0f, 1.f),		glm::vec2(0.0f, 1.f),	glm::vec3(0.0f, 0.0f, -1.f),//2
		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 1.f),		glm::vec2(1.0f, 1.f),	glm::vec3(0.0f, 0.0f, -1.f),//3

		glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 0.0f, 1.f),		glm::vec2(1.0f, 0.f),	glm::vec3(-1.0f, 0.0f, 0.f),//2 4
		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 1.f),		glm::vec2(0.0f, 0.f),	glm::vec3(-1.0f, 0.0f, 0.f),//3 5
		glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 1.f),	glm::vec3(-1.0f, 0.0f, 0.f),//4 6
		glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(0.0f, 1.f),	glm::vec3(-1.0f, 0.0f, 0.f),//5 7

		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 1.f),		glm::vec2(1.0f, 1.f),	glm::vec3(0.0f, 0.0f, -1.f),//3 8
		glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(0.0f, 1.f),	glm::vec3(0.0f, 0.0f, -1.f),//5 9
		glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(0.0f, 0.0f, -1.f), //0 10
		glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(0.0f, 0.0f, -1.f), //6 11

		glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(1.0f, 0.0f, 0.f), //0 12
		glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(1.0f, 0.0f, 0.f), //6 13
		glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(1.0f, 0.0f, 0.f),//1 14
		glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(1.0f, 0.0f, 0.f),//7 15

		glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 0.f),	glm::vec3(0.0f, 0.0f, 1.f), //6 16
		glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(0.0f, 0.0f, 1.f),//7 17
		glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(0.0f, 1.f),	glm::vec3(0.0f, 0.0f, 1.f),//5 18
		glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 1.f),	glm::vec3(0.0f, 0.0f, 1.f),//4 19

		glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(0.0f, 0.0f, 1.f),//7 20
		glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.0f, 1.0f, 0.f),		glm::vec2(0.0f, 0.f),	glm::vec3(0.0f, 0.0f, -1.f),//1 21
		glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.0f, 0.0f, 0.f),		glm::vec2(1.0f, 1.f),	glm::vec3(0.0f, 0.0f, 1.f),//4 22
		glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(0.0f, 0.0f, 1.f),		glm::vec2(0.0f, 1.f),	glm::vec3(0.0f, 0.0f, -1.f)//2 23
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			6, 5, 7,

			8, 9, 10,
			9, 11, 10,

			12, 13, 14,
			13, 15, 14,

			16, 17, 18,
			17, 19, 18,

			20, 21, 22,
			22, 21, 23

		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

