/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_gen_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:16:23 by msitni            #+#    #+#             */
/*   Updated: 2024/10/04 11:21:45 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra.h"

void add_other_params(int fd, t_object *obj)
{
    if (obj->checkerboard)
        dprintf(fd, "\t-c");
    if (obj->hidden)
        dprintf(fd, "\t-h"); 
    dprintf(fd, "\n");
}

int get_scene_fd()
{
    char *fname;
    char *tmp;
    int fd;
    struct timeval now;

    gettimeofday(&now, NULL);
    tmp = "scene_gen_";
    fname = itoa(now.tv_sec);
    if (fname == NULL)
        return -1;
    tmp = ft_strjoin(tmp, fname);
    free(fname);
    if (tmp == NULL)
        return -1;
    fname = ft_strjoin(tmp, ".rt");
    free(tmp);
    fd = open(fname, O_CREAT | O_TRUNC);
    free(fname);
    return fd;
}

int gen_scene(t_scene *scene)
{
    int fd;

    fd = get_scene_fd();
    if (fd < 0)
        return log_error("Can't create file to save scene.");
    dprintf(fd, "#Cam:\tPOSITION\tORIENTATION\tFOV\n");
    dprintf(fd, "C\t%f,%f,%f\t%f,%f,%f\t%f\n", scene->camera.origin.x,
            scene->camera.origin.y, scene->camera.origin.z, scene->camera.forward.x,
            scene->camera.forward.y, scene->camera.forward.z, scene->camera.fov);
    dprintf(fd, "#Lights:\tPOSITION\tINTENSITY\tCOLOR\n");
    for (size_t i = 0; i < scene->lights_count; i++)
        dprintf(fd, "L\t%f,%f,%f\t%f\t%f,%f,%f\n", scene->lights[i].position.x,
                scene->lights[i].position.y, scene->lights[i].position.z, scene->lights[i].intensity,
                scene->lights[i].color.x * 255.0f, scene->lights[i].color.y * 255.0f, scene->lights[i].color.z * 255.0f);
    dprintf(fd, "#Ambien Light:\tINTENSITY\tCOLOR\n");
    dprintf(fd, "A\t1.0\t%f,%f,%f\n", scene->ambient_color.x * 255.0f,
            scene->ambient_color.y * 255.0f, scene->ambient_color.z * 255.0f);

    dprintf(fd, "#Objects:[%zu]\n", scene->objects_count);
    for (size_t i = 0; i < scene->objects_count; i++)
    {
        switch (scene->objects[i].type)
        {
        case OBJ_PLANE:
        {
            dprintf(fd, "#plane:\tPOINT\tNORMAL\tCOLOR\n");
            dprintf(fd, "pl\t%f,%f,%f\t%f,%f,%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return 0;
}