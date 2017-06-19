#ifndef __OBJECTMOVE_H_
#define __OBJECTMOVE_H_

#include <windows.h>
#include <GL/gl.h>
#include <math.h>

#pragma warning(disable:4305)
#pragma warning(disable:4244)
class object_move
{
public:
	float object_x;
	float object_y;
	float object_z;

	float speed;
	float x_angel;
	float z_angel;
	float y_angel;
	float angel_speed;

	float x, y, z;
public:
	object_move();
	void moveStraight(float fspeed);
	void yawObject(float angel);
	void pitchObject(float angel);
	void left_rotate(float angel);
	void moveTranverse(float speed);
	void setoperation();
};
#endif

