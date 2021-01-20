#pragma once
#include "Lib.h"
#include "Camera.h"
//#include "OBJLoader.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm.hpp>


enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_PIC = 0, TEX_PIC_SPEC, TEX_CONTAINER, TEX_CONTAINER_SPEC};
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

class Game
{
private:
//vars
	GLFWwindow* window;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	Camera camera;
	
	
	//Matrix
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;


	//Models
	std::vector<Model*> models;


	//light
	std::vector<glm::vec3*> lights;

//priv func
	void initGLFW();
	void initWindow(const char* title,
		bool resizable);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initOBJModels();
	void initModels();
	//void initPointLights();
	void initLights();
	void initUniforms();
	void updateUniforms();
public:
	Game(const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable);
	virtual ~Game();
	
	
	//Accessors
	int getWindowShouldClose();
	
	
	//Mods	
	void setWindowShoulClose();
	
	//Func
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();

	//static func
	
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};

