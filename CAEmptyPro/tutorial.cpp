#include "stdafx.h"

int screen_width = 600;
int screen_height = 600;

// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x = 0, rotation_x_increment = 0.1;
double rotation_y = 0, rotation_y_increment = 0.05;
double rotation_z = 0, rotation_z_increment = 0.03;

// Flag for rendering as lines or filled polygons
int filling = 1; //0=OFF 1=ON

				 //Now the object is generic, the cube has annoyed us a little bit, or not?
float angel = 0;

obj_type object;
obj_type sky;
obj_type ariship;
obj_type part_airship;

Camera camera;
object_move airship_move;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
	glShadeModel(GL_SMOOTH); // Type of shading for the polygons

							 // Viewport transformation
	glViewport(0, 0, screen_width, screen_height);

	// Projection transformation
	glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
	glLoadIdentity(); // We initialize the projection matrix as identity
	gluPerspective(45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 10.0f, 10000.0f); // We define the "viewing volume"

	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

	glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

	Load3DS(&object, "land13.3ds");
	object.id_texture = LoadBitmap("desert_dn.bmp");
	Load3DS(&ariship, "ship06.3ds");
	ariship.id_texture = LoadBitmap("images.bmp");
	Load3DS(&sky, "sky03.3ds");
	sky.id_texture = LoadBitmap("sky4.bmp");
	Load3DS(&part_airship, "part01.3ds");
	part_airship.id_texture = LoadBitmap("leather.bmp");

	// If the last function returns -1 it means the file was not found so we exit from the program
	printf("the id_texture is %d\n", object.id_texture);
	if (object.id_texture == -1)
	{
		MessageBox(NULL, "Image file: spaceshiptexture.bmp not found", "Zetadeck", MB_OK | MB_ICONERROR);
		exit(0);
	}

	
}

void resize(int width, int height)
{
	screen_width = width; // We obtain the new screen width values and store it
	screen_height = height; // Height value

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
	glViewport(0, 0, screen_width, screen_height); // Viewport transformation

	glMatrixMode(GL_PROJECTION); // Projection transformation
	glLoadIdentity(); // We initialize the projection matrix as identity
	gluPerspective(45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 10.0f, 10000.0f);

	glutPostRedisplay(); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

void keyboard(unsigned char key, int x, int y)
{
	//switch (key)
	//{

	//case ' ':
	//	break;
	//case 'j': case 'J':
	//	pos_x -= speed;
	//	break;
	//case 'k': case 'K':
	//	pos_z -= speed;
	//	break;
	//case 'l': case 'L':
	//	pos_x += speed;
	//	break;
	//case 'i': case 'I':
	//	pos_z += speed;
	//	break;
	//}
}

//void setObjectPos() {
//	if (GetKeyState(74) & 0x80) { //'J'
//		
//	}
//
//	if (GetKeyState(75) & 0x80)
//		pos_z -= speed;
//
//	if (GetKeyState(76) & 0x80)
//		pos_x += speed;
//
//	if (GetKeyState(73) & 0x80)
//		pos_z += speed;
//}

void keyboard_s(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_UP:
		camera.PitchCamera(camera.angle);
		printf("up");
		break;
	case GLUT_KEY_DOWN:
		camera.PitchCamera(-camera.angle);
		printf("down");
		break;
	case GLUT_KEY_LEFT:
		camera.YawCamera(-camera.angle);
		airship_move.left_rotate(airship_move.z_angel);
		break;
	case GLUT_KEY_RIGHT:
		camera.YawCamera(camera.angle);
		airship_move.pitchObject(airship_move.z_angel);
		printf("right");
		break;
	}
}

void display(void)
{
	int l_index;
	bool object_movement = false;

	if (GetKeyState(8) & 0x80) {
		object_movement = true;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
	glMatrixMode(GL_MODELVIEW); // Modeling transformation
	glLoadIdentity(); // Initialize the model matrix as identity

	camera.OperationProc();
	airship_move.setoperation();
	gluLookAt(camera.camera_x, camera.camera_y, camera.camera_z, camera.lookat_x, camera.lookat_y, camera.lookat_z, 0.0f, 1.0f, 0.0f);
	//printf("camera_x: %f camera_y: %f camera_z: %f lookat_x: %f lookat_y: %f lookat_z: %f\n", camera.camera_x, camera.camera_y, camera.camera_z, camera.lookat_x, camera.lookat_y, camera.lookat_z);
	//glTranslatef(0, 0.0, -600); // We move the object forward (the model matrix is multiplied by the translation matrix)

	glutPushWindow();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 
	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	for (l_index = 0; l_index<object.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,
			object.mapcoord[object.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z); //Vertex definition

														 //----------------- SECOND VERTEX -----------------
														 // Texture coordinates of the second vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u,
			object.mapcoord[object.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u,
			object.mapcoord[object.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, sky.id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES);
	for (l_index = 0; l_index<sky.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(sky.mapcoord[sky.polygon[l_index].a].u,
			sky.mapcoord[sky.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(sky.vertex[sky.polygon[l_index].a].x,
			sky.vertex[sky.polygon[l_index].a].y,
			sky.vertex[sky.polygon[l_index].a].z); //Vertex definition

												   //----------------- SECOND VERTEX -----------------
												   // Texture coordinates of the second vertex
		glTexCoord2f(sky.mapcoord[sky.polygon[l_index].b].u,
			sky.mapcoord[sky.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(sky.vertex[sky.polygon[l_index].b].x,
			sky.vertex[sky.polygon[l_index].b].y,
			sky.vertex[sky.polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(sky.mapcoord[sky.polygon[l_index].c].u,
			sky.mapcoord[sky.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(sky.vertex[sky.polygon[l_index].c].x,
			sky.vertex[sky.polygon[l_index].c].y,
			sky.vertex[sky.polygon[l_index].c].z);
	}

	glEnd();

	glutPopWindow();

	//glRotatef(airship_move.z_angel, airship_move.x, airship_move.y, airship_move.z);
	//glRotated(60, 0.0, 0.0, 1.0);
	glTranslatef(airship_move.object_x,airship_move.object_y, airship_move.object_z);
	glBindTexture(GL_TEXTURE_2D, ariship.id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES);
	for (l_index = 0; l_index<ariship.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(ariship.mapcoord[ariship.polygon[l_index].a].u,
			ariship.mapcoord[ariship.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(ariship.vertex[ariship.polygon[l_index].a].x,
			ariship.vertex[ariship.polygon[l_index].a].y,
			ariship.vertex[ariship.polygon[l_index].a].z); //Vertex definition

														 //----------------- SECOND VERTEX -----------------
														 // Texture coordinates of the second vertex
		glTexCoord2f(ariship.mapcoord[ariship.polygon[l_index].b].u,
			ariship.mapcoord[ariship.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(ariship.vertex[ariship.polygon[l_index].b].x,
			ariship.vertex[ariship.polygon[l_index].b].y,
			ariship.vertex[ariship.polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(ariship.mapcoord[ariship.polygon[l_index].c].u,
			ariship.mapcoord[ariship.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(ariship.vertex[ariship.polygon[l_index].c].x,
			ariship.vertex[ariship.polygon[l_index].c].y,
			ariship.vertex[ariship.polygon[l_index].c].z);
	}
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, part_airship.id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	for (l_index = 0; l_index<part_airship.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(part_airship.mapcoord[part_airship.polygon[l_index].a].u,
			part_airship.mapcoord[part_airship.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(part_airship.vertex[part_airship.polygon[l_index].a].x,
			part_airship.vertex[part_airship.polygon[l_index].a].y,
			part_airship.vertex[part_airship.polygon[l_index].a].z); //Vertex definition

														 //----------------- SECOND VERTEX -----------------
														 // Texture coordinates of the second vertex
		glTexCoord2f(part_airship.mapcoord[part_airship.polygon[l_index].b].u,
			part_airship.mapcoord[part_airship.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(part_airship.vertex[part_airship.polygon[l_index].b].x,
			part_airship.vertex[part_airship.polygon[l_index].b].y,
			part_airship.vertex[part_airship.polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(part_airship.mapcoord[part_airship.polygon[l_index].c].u,
			part_airship.mapcoord[part_airship.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(part_airship.vertex[part_airship.polygon[l_index].c].x,
			part_airship.vertex[part_airship.polygon[l_index].c].y,
			part_airship.vertex[part_airship.polygon[l_index].c].z);
	}
	glEnd();

	glFlush(); // This force the execution of OpenGL commands
	glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer

}

int main(int argc, char **argv)
{
	// We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("www.spacesimulator.net - 3d engine tutorials: Tutorial 4");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	//glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_s);
	init();
	glutMainLoop();

	return(0);
}

