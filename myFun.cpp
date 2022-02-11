#include "myFun.h"
#include <math.h>

double distance(double x1,double y1,double x2,double y2)
{
	double distance = sqrt((
			(x1 - x2) * (x1 - x2) +
			(y1 - y2) * (y1 - y2)
			));
	return distance;
}

bool SetWindowA(HWND hwnd, int w, int h)
{
	if (hwnd == NULL) { return false; }
	::SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & (~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX)));
	::SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) & (~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME)) | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
	SetWindowPos(hwnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - w) / 2, (GetSystemMetrics(SM_CYSCREEN) - h) / 2, h,h, SWP_SHOWWINDOW
		| SWP_FRAMECHANGED | SWP_DRAWFRAME);
	SetLayeredWindowAttributes(hwnd, 0x000000, 0, LWA_COLORKEY);
	return true;
}

Rander::Rander()
{
	srand(time(NULL));
	seek = time(NULL) % rand();
	seek = GetARand(seek);
}

int Rander::GetARand(int max,int min)
{
	std::uniform_int_distribution<int> u(min, max); // ×ó±ÕÓÒ±ÕÇø¼ä
	std::uniform_int_distribution<int> u1(0, 11000);
	e.seed(seek);
	seek = u1(e);
	return u(e);
}
