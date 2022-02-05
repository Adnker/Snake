#include "Main_Window.h"
#include "Game.h"

int Main_Window::DrawMove(const vector<Move_point*>* move_point, SDL_Color* color_)
{
	int jidi_h = 50;
	int quyu_h = 30;
	int index_now = 1;
	int index_before = 0;
	Point* point_before;
	while (index_now < move_point->size()) {
		if (move_point->at(index_now)->flag == NULL) {
			point_before = move_point->at(index_before)->point;
			if (move_point->at(index_before)->flag == QUYU) {
				int i = index_before - 1;
				while (move_point->at(i)->flag == QUYU) {
					i--;
				}
				point_before = move_point->at(i)->point;
			}
			DrawLine(move_point->at(index_now)->point->x * 100 + 50, move_point->at(index_now)->point->y * 100 + 50,
				point_before->x * 100 + 50, point_before->y * 100 + 50);
		}
		else if (move_point->at(index_now)->flag == JIDI) {
			FillRect(move_point->at(index_now)->point->x * 100 + 25, move_point->at(index_now)->point->y * 100 + 25,
				jidi_h, jidi_h, color_);
		}
		else if (move_point->at(index_now)->flag == QUYU) {
			FillRect(move_point->at(index_now)->point->x * 100 + 20, move_point->at(index_now)->point->y * 100 + 20,
				quyu_h, quyu_h, color_);
		}
		index_now++;
		index_before++;
	}
	return 0;
}
