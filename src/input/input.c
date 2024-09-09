#include "input.h"

void control_camera(int key, t_renderer *renderer)
{
	switch (key)
	{
	case KEY_UP:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->scene.camera.forward = vec3_normalize(renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_DOWN:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(-10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->scene.camera.forward = vec3_normalize(renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_LEFT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->scene.camera.forward = vec3_normalize(renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_RIGHT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(-10);
		renderer->scene.camera.forward = mat_mul_vec3(&x_rot, &renderer->scene.camera.forward);
		renderer->scene.camera.forward = vec3_normalize(renderer->scene.camera.forward);
		renderer->redraw = TRUE;
		break;
	}
	case KEY_W:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, 2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_S:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.forward, -2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_A:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, -2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_D:
		renderer->scene.camera.origin = vec3_add_vec3(renderer->scene.camera.origin, vec3_scale(renderer->scene.camera.U, 2.0f));
		renderer->redraw = TRUE;
		break;
	case KEY_8:
		renderer->scene.camera.origin.z += 2.0f;
		renderer->redraw = TRUE;
		break;
	case KEY_2:
		renderer->scene.camera.origin.z -= 2.0f;
		renderer->redraw = TRUE;
		break;
	case KEY_4:
	{
		break;
	}
	case KEY_6:
	{
		break;
	}
	default:
		break;
	}
	calculate_camera_uv(&renderer->scene.camera);
}

void control_selected_obj(int key, t_renderer *renderer)
{
	if (renderer->selected_obj == NULL)
		return;
	switch (key)
	{
	case KEY_UP:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(10);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	case KEY_DOWN:
	{
		t_mat4x4 x_rot = get_x_rotation_matrix(-10);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	case KEY_LEFT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(10);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	case KEY_RIGHT:
	{
		t_mat4x4 x_rot = get_z_rotation_matrix(-10);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	case KEY_A:
		renderer->selected_obj->position.x -= 2.0f ;
		break;
	case KEY_D:
		renderer->selected_obj->position.x += 2.0f ;
		break;
	case KEY_S:
		renderer->selected_obj->position.y -= 2.0f ;
		break;
	case KEY_W:
		renderer->selected_obj->position.y += 2.0f ;
		break;
	case KEY_8:
		renderer->selected_obj->position.z += 2.0f ;
		break;
	case KEY_2:
		renderer->selected_obj->position.z -= 2.0f ;
		break;
	case KEY_4:
	{
		t_mat4x4 x_rot = get_y_rotation_matrix(5);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	case KEY_6:
	{
		t_mat4x4 x_rot = get_y_rotation_matrix(-5);
		renderer->selected_obj->normal = mat_mul_vec3(&x_rot, &renderer->selected_obj->normal);
		renderer->selected_obj->normal = vec3_normalize(renderer->selected_obj->normal);
		break;
	}
	default:
		break;
	}
	renderer->selected_obj->recalculate(renderer->selected_obj);
	renderer->redraw = TRUE;
}

int key_hook_up(int key, t_renderer *renderer)
{
	(void)key;
	(void)renderer;
	if (key == KEY_CTR)
		renderer->tab_mode = FALSE; 
	return 0;
}
int key_hook_down(int key, t_renderer *renderer)
{
	printf("key pressed: %d\n", key);

	if (renderer->tab_mode)
		control_camera(key, renderer);
	else
		control_selected_obj(key, renderer);

	if (key == KEY_CTR)
		renderer->tab_mode = TRUE; 

	return 0;
}
int mouse_hook_up(int button, int x, int y, t_renderer *renderer)
{
	t_ray ray;
	t_hit hit;

	ray = get_ray(&renderer->scene.camera, (t_vec3){x, renderer->mlx_texture.height - y},
				  (t_vec3){renderer->mlx_texture.width, renderer->mlx_texture.height});
	hit = get_ray_hit(&(renderer->scene), ray);
	if (hit.is_valid)
		renderer->selected_obj = hit.object;
	return (0);
}
int mouse_hook_down(int button, int x, int y, t_renderer *renderer)
{
	(void)button;
	(void)x;
	(void)y;
	(void)renderer;
	return 0;
}