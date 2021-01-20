// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "Game.h"

void Game::initGLFW() {
	if (glfwInit()==GLFW_FALSE)
	{
		std::cout << "ERROR INIT GLFW\n";
		glfwTerminate();
	}
}

void Game::initWindow(const char* title,
	bool resizable)
{
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);

	
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//Создание объекта окна
	this-> window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, nullptr, nullptr);

	if (this->window == nullptr) {
		std::cout << "Error init window\n";
		glfwTerminate();

	}
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);
	//Важно для перспективной матрицы glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

	//Контекст окна, который будет основным контекстом в данном потоке
	glfwMakeContextCurrent(this->window);
}

void Game::initGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane);
}

void Game::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"vertex_core.glsl","", "fragment_core.glsl"));
}

void Game::initTextures()
{

	this->textures.push_back(new Texture("image/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("image/container_specular.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("image/Base1.png", GL_TEXTURE_2D));//4 2
	this->textures.push_back(new Texture("image/Diff.png", GL_TEXTURE_2D));//5 3

	this->textures.push_back(new Texture("image/Wall.png", GL_TEXTURE_2D));//6 4
	this->textures.push_back(new Texture("image/WallD.png", GL_TEXTURE_2D));//7 5

	this->textures.push_back(new Texture("image/SMBase.png", GL_TEXTURE_2D));//8  6
	this->textures.push_back(new Texture("image/SMDiff.png", GL_TEXTURE_2D));//9 7

	this->textures.push_back(new Texture("image/CrystalBaseK.png", GL_TEXTURE_2D));//10 8 
	this->textures.push_back(new Texture("image/CrystalDiff.png", GL_TEXTURE_2D));//11 9

	
}

void Game::initMaterials()
{
	// 1ambient 2diffuse 3secular
	this->materials.push_back(new Material(glm::vec3(0.5f), glm::vec3(0.1f), glm::vec3(0.5f),
		0, 1));
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f),
		0, 1));
	this->materials.push_back(new Material(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.714f, 0.4284f, 0.18144f),
		glm::vec3(0.393548f, 0.271906f, 0.166721f),
		0, 1));
	this->materials.push_back(new Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f),
		glm::vec3(0.633f, 0.727811f, 0.633f),
		0, 1));
}

void Game::initOBJModels()
{
	
}


void Game::initModels()
{
	std::vector<Mesh*> meshes;
	std::vector<Mesh*> meshesFloor;
	std::vector<Mesh*> meshesR;
	std::vector<Mesh*> meshesFront;
	std::vector<Mesh*> meshesBack;
	std::vector<Mesh*> meshesLeft;
	std::vector<Mesh*> meshesRight;

	meshes.push_back(new Mesh(&Cube(),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)));
	//where? start, rotation, size 
	meshesFloor.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(-90.f, 0.f, 0.f),
		glm::vec3(1100.f)));

	meshesR.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(90.f, 0.f, 0.f),
		glm::vec3(1000.f)));

	meshesFront.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1200.f)));

	meshesBack.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.f, 180.f, 0.f),
		glm::vec3(1300.f)));

	meshesLeft.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.f, 90.f, 0.f),
		glm::vec3(1100.f)));
	meshesRight.push_back(new Mesh(&Quad(), glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.f, -90.f, 0.f),
		glm::vec3(1100.f)));


	this->models.push_back(new Model(glm::vec3(0.f, -500.f, 0.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesFloor)
	);

	this->models.push_back(new Model(glm::vec3(0.f, 500.f, 0.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesR)
	);

	this->models.push_back(new Model(glm::vec3(0.f, 0.f, -500.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesFront)
	);

	this->models.push_back(new Model(glm::vec3(0.f, 0.f, 500.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesBack));

	this->models.push_back(new Model(glm::vec3(-500.f, 0.f, 0.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesLeft)
	);

	this->models.push_back(new Model(glm::vec3(500.f, 0.f, 0.f),
		this->materials[1],
		this->textures[4],
		this->textures[5],
		meshesRight));

	this->models.push_back(new Model(glm::vec3(20.f, 0.f, 20.f),
		this->materials[0],
		this->textures[2],
		this->textures[3],
		"image/Ssn.obj")//6
	);

	this->models.push_back(new Model(glm::vec3(50.f, 0.f, -100.f),
		this->materials[2],
		this->textures[6],
		this->textures[7],
		"image/SandMet.obj")///7
	);
	this->models.push_back(new Model(glm::vec3(-6.f, 0.f, 0.f),
		this->materials[1],
		this->textures[0],
		this->textures[1],
		"image/Box.obj")//8
	);

	this->models.push_back(new Model(glm::vec3(-26.f, -27.f, -12.f),
		this->materials[3],
		this->textures[8],
		this->textures[9],
		"image/Crystal.obj")//9
	);


	for (auto*& i : meshes)
		delete i;
	for (auto*& i : meshesR)
		delete i;
	for (auto*& i : meshesFloor)
		delete i;
	for (auto*& i : meshesFront)
		delete i;
	for (auto*& i : meshesBack)
		delete i;
	for (auto*& i : meshesLeft)
		delete i;
	for (auto*& i : meshesRight)
		delete i;

	meshes.clear();
	meshesR.clear();
	meshesFloor.clear();
	meshesFront.clear();
	meshesBack.clear();
	meshesLeft.clear();
	meshesRight.clear();

}

void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix", GL_FALSE);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix", GL_FALSE);

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	//this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::updateUniforms()
{

	//for camera
	//this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
}


Game::Game(const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable) : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;
	
	this->initGLFW();

	this->initWindow(title, resizable);

	this->initGLEW();
	this->initOpenGLOptions();

	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	//this->initMeshes();
	this->initOBJModels();
	this->initModels();
	this->initLights();
	this->initUniforms();
	
}

Game::~Game() {
	glfwDestroyWindow(window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (auto*& i : this->models)
		delete i;

	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}



//Acc
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}


//Mod
void Game::setWindowShoulClose()
{
	 glfwSetWindowShouldClose(this->window, GL_TRUE);
}

//Func
void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	//Move light
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		//this->pointLights[0]->setPosition(this->camera.getPosition());
		*this->lights[0] = this->camera.getPosition();
	}
}

void Game::updateKeyboardInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//Camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//this->camPosition.z +=0.001f;
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//this->camPosition.z -= 0.001f;
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//this->camPosition.x += 0.001f;
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//this->camPosition.x -= 0.001f;
		this->camera.move(this->dt, RIGHT);
	}
	
}

void Game::updateInput()
{
	glfwPollEvents();//проверка событий и вызов функций, которые им соответствуют
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}


void Game::update()
{
	this->updateDt();
	this->updateInput();
	this->models[7]->rotate(glm::vec3(0.001f, 0.009f, 0.001f));
	this->models[8]->rotate(glm::vec3(0.001f, 0.000f, 0.01f));
	this->models[9]->rotate(glm::vec3(0.01f, 0.000f, 0.00f));

}

void Game::render()
{
	

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update the uniforms
	
	this->updateUniforms();

	for(auto& i: this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	
	//End Draw
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
};
