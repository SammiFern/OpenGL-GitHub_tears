// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include"Game.h"

int main()
{
	
	Game game("Arrow in the knee", 1400, 960, 4, 4, false);
	///////////////////

	//"Игровой цикл". Пока пользователь не закроет окно, ввод будет обрабатываться  
	while (!game.getWindowShouldClose())//проверка инструкций к закрытию
	{
		game.update();
		game.render();

		
	}

	return 0;
}

