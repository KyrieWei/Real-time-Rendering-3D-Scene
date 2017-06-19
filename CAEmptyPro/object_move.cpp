#include "stdafx.h"
#include "object_move.h"


object_move::object_move()
{
	object_x = 0;
	object_y = -100;
	object_z = 20;
	speed = 0.3;
	angel_speed = 30;
	x_angel = 0;
	z_angel = 0;
	y_angel = 0;
	x = 0;
	y = 0;
	z = 0;
}

void object_move::moveStraight(float fspeed) {
	object_y += fspeed;
}

void object_move::moveTranverse(float speed) {
	object_x += speed;
}

void object_move::yawObject(float angel) {
	
}

void object_move::pitchObject(float angel) {
	angel += angel_speed;
	z = 1;
}

void object_move::left_rotate(float angel) {
	angel -= angel_speed;
	z = 1;
}

void object_move::setoperation() {
	if (GetKeyState(87) & 0x80)
		moveStraight(speed);

	if (GetKeyState(83) & 0x80)
		moveStraight(-speed);

	if (GetKeyState(65) & 0x80)
		moveTranverse(-speed);

	if (GetKeyState(68) & 0x80)
		moveTranverse(speed);
}


