#ifndef _TUTORIAL_H
#define _TUTORIAL_H

#define MAX_VERTICES 8000
#define MAX_POLYGONS 8000

typedef struct {
	float x, y, z;
}vertex_type;

typedef struct {
	int a, b, c;
}polygon_type;

typedef struct {
	float u, v;
}mapcoord_type;

typedef struct {
	char name[20];

	int vertices_qty;
	int polygons_qty;

	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];
	int id_texture;
}obj_type, *obj_type_ptr;


#endif // !_TUTORIAL_H


