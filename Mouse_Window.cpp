#include "Mouse_Window.h"

int Mouse_Window::Updata()
{
	if (flag_mouse_time > 0) {
		flag_mouse_time++;
		if (flag_mouse_time > 3) { flag_mouse_time = 0; }
	}
	else if (flag_mouse_time == 0 && input->GetMouseMove()) {
		if (point_sum.size() > 4) {
			point_sum.erase(point_sum.begin(), point_sum.begin() + 1);//删除多余的元素
		}
		Point* temp = new Point();//创建新的鼠标点
				//获取现在的鼠标位置
		temp->x = input->GetNowPoint()->x;
		temp->y = input->GetNowPoint()->y;
		point_sum.emplace_back(temp);//加入缓冲区
		flag_mouse_time++;//开始计时
	}

	return 0;
}

Mouse_Window::Mouse_Window(Input* input_)
{
	input = input_;
}

vector<Point*> Mouse_Window::Getpoint()
{
	return point_sum;
}
