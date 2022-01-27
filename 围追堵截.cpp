#include "Game.h"
#include <Windows.h>


//SDL2.lib
//SDL2main.lib
//SDL2_ttf.lib
#pragma comment (lib,"SDL2.lib")
#pragma comment (lib,"SDL2main.lib")
#pragma comment (lib,"SDL2_ttf.lib")

#undef main
int main(){

	//Òþ²Øcmd´°¿Ú
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_HIDE);

	class Game game = Game();
	bool isRun = true;
	if (game.OpenGame() > 0) {
		isRun = false;
	}
	if (isRun) {
		game.Updata();
	}
	game.Shutdown();

	ShowWindow(hwnd, SW_SHOW);
	system("pause");
}