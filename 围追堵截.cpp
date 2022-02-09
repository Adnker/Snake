#include "Game.h"
#include <Windows.h>


//SDL2.lib
//SDL2main.lib
//SDL2_ttf.lib
#pragma comment (lib,"SDL2.lib")
#pragma comment (lib,"SDL2main.lib")
#pragma comment (lib,"SDL2_ttf.lib")
#pragma comment (lib,"SDL2_image.lib")

#undef main

int main(){

	//隐藏cmd窗口
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_HIDE);

	HANDLE handle;
	handle = CreateMutex(NULL, FALSE, L"Snake");//Release模式下加上一个使用：handle = CreateMutex(NULL, FALSE, L"Snake");
	if (GetLastError() != ERROR_ALREADY_EXISTS) {
		class Game game = Game();
		bool isRun = true;
		if (game.OpenGame() > 0) {
			isRun = false;
		}
		if (isRun) {
			game.Updata();
		}
		game.Shutdown();
		//int i; std::cin >> i;
	}
}