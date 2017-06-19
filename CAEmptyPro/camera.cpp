#include "stdafx.h"
#include "camera.h"

Camera::Camera()
{
	PI = 3.1415;

	angle = 3;
	speed = 0.3;
	sight = 100;

	rotate_xy = 0.0f;
	rotate_xz = -90.0f;
	rad_xy = rotate_xy*PI / 180.0f;
	rad_xz = rotate_xz*PI / 180.0f;

	camera_x = 3.0f;
	camera_y = 30.0f;
	camera_z = 414.0f;

	lookat_x = camera_x + sight*cos(rad_xy)*cos(rad_xz);
	lookat_y = camera_y + sight*sin(rad_xy);
	lookat_z = camera_z + sight*cos(rad_xy)*sin(rad_xz);
}

Camera::Camera(float fSpeed, float fAngle)
{
	PI = 3.1415;

	angle = fAngle;
	speed = fSpeed;
	sight = 100;

	rotate_xy = 0.0f;
	rotate_xz = -90.0f;
	rad_xy = rotate_xy*PI / 180.0f;
	rad_xz = rotate_xz*PI / 180.0f;

	camera_x = 0.0f;
	camera_y = 0.0f;
	camera_z = 8.0f;

	lookat_x = camera_x + sight*cos(rad_xy)*cos(rad_xz);
	lookat_y = camera_y + sight*sin(rad_xy);
	lookat_z = camera_z + sight*cos(rad_xy)*sin(rad_xz);
}

void Camera::YawCamera(float fAngle)
{
	rotate_xz = (int)(rotate_xz + fAngle) % 360;
	rad_xz = rotate_xz*PI / 180.0f;

	lookat_x = camera_x + sight*cos(rad_xy)*cos(rad_xz);
	lookat_z = camera_z + sight*cos(rad_xy)*sin(rad_xz);
}

void Camera::PitchCamera(float fAngle)
{
	rotate_xy = (int)(rotate_xy + fAngle) % 360;
	rad_xy = rotate_xy*PI / 180.0f;
	lookat_y = camera_y + sight*sin(rad_xy);
}

void Camera::WalkStraight(float fSpeed)
{
	camera_x += fSpeed*cos(rad_xy)*cos(rad_xz);
	camera_y += fSpeed*sin(rad_xy);
	camera_z += fSpeed*cos(rad_xy)*sin(rad_xz);

	lookat_x = camera_x + sight*cos(rad_xy)*cos(rad_xz);
	lookat_y = camera_y + sight*sin(rad_xy);
	lookat_z = camera_z + sight*cos(rad_xy)*sin(rad_xz);
}

void Camera::WalkTransverse(float fSpeed)
{
	camera_x = camera_x + fSpeed*cos(rad_xy)*sin(rad_xz);
	camera_z = camera_z - fSpeed*cos(rad_xy)*cos(rad_xz);

	lookat_x = camera_x + sight*cos(rad_xy)*cos(rad_xz);
	lookat_y = camera_y + sight*sin(rad_xy);
	lookat_z = camera_z + sight*cos(rad_xy)*sin(rad_xz);
}

void Camera::OperationProc()
{

	/*if (GetKeyState(VK_UP) & 0x80){
		PitchCamera(angle);
		printf("up");
	}
		
		
	if (GetKeyState(VK_DOWN) & 0x80)
		PitchCamera(-angle);

	if (GetKeyState(VK_LEFT) & 0x80)
		YawCamera(-angle);

	if (GetKeyState(VK_RIGHT) & 0x80)
		YawCamera(angle);*/

	if (GetKeyState(87) & 0x80)
		WalkStraight(speed);

	if (GetKeyState(83) & 0x80)
		WalkStraight(-speed);

	if (GetKeyState(65) & 0x80)
		WalkTransverse(speed);

	if (GetKeyState(68) & 0x80)
		WalkTransverse(-speed);
}
//camera::camera()
//{
//}
//
//
//camera::~camera()
//{
//}
