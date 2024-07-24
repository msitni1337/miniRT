#ifndef SCENE_H
#define SCENE_H
#include "Camera.h"
#include "Object.h"

typedef struct s_scene
{
	t_camera camera;
	size_t objects_count;
	t_object objects;

} t_scene;

#endif // SCENE_H