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

static int count_chars(long n)
{
    int i;

    i = 1;
    if (n < 0)
    {
        n = -n;
        i++;
    }
    while (n > 9)
    {
        n /= 10;
        i++;
    }
    return (i);
}

static int get_first_digit(long n)
{
    while (n > 9)
    {
        n /= 10;
    }
    return ((int)n);
}

static void fill_str_with_nbr(long nbr, char *str, int *i)
{
    if (nbr < 0)
    {
        nbr = -nbr;
        str[*i] = '-';
        (*i)++;
    }
    if (nbr >= 0 && nbr <= 9)
    {
        str[*i] = '0' + get_first_digit(nbr);
        (*i)++;
        return;
    }
    fill_str_with_nbr(nbr / 10, str, i);
    fill_str_with_nbr(nbr % 10, str, i);
}

char *ft_itoa(int n)
{
    char *str;
    int i;

    str = malloc(count_chars(n) + 1);
    if (!str)
        return (NULL);
    i = 0;
    fill_str_with_nbr(n, str, &i);
    str[i] = 0;
    return (str);
}

void add_other_params(int fd, t_object *obj)
{
    if (obj->texture.filename != NULL)
        dprintf(fd, "\t-t\t%s", obj->texture.filename);
    if (obj->normal_map.filename != NULL)
        dprintf(fd, "\t-n\t%s", obj->normal_map.filename);
    if (obj->reflection > 0.0f)
        dprintf(fd, "\t-r\t%f", obj->reflection);
    if (obj->hidden)
        dprintf(fd, "\t-h");
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
    fname = ft_itoa(now.tv_sec);
    if (fname == NULL)
        return -1;
    tmp = ft_strjoin(tmp, fname);
    free(fname);
    if (tmp == NULL)
        return -1;
    fname = ft_strjoin(tmp, ".rt");
    free(tmp);
    fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    free(fname);
    return fd;
}

int gen_scene_rt_file(t_scene *scene)
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

    dprintf(fd, "\n#Objects:[%zu]\n", scene->objects_count);
    for (size_t i = 0; i < scene->objects_count; i++)
    {
        switch (scene->objects[i].type)
        {
        case OBJ_PLANE:
        {
            dprintf(fd, "#Plane:\tPOINT\tNORMAL\tCOLOR\n");
            dprintf(fd, "pl\t%f,%f,%f\t%f,%f,%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        case OBJ_SPHERE:
        {
            dprintf(fd, "#Sphere:\tCENTER\tDIAMETER\tCOLOR\n");
            dprintf(fd, "sp\t%f,%f,%f\t%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].radius * 2.0f,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        case OBJ_CYLINDER:
        {
            dprintf(fd, "#Cylinder:\tCENTER\tAXIS\tHEIGHT\tDIAMETER\tCOLOR\n");
            dprintf(fd, "cy\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].height, scene->objects[i].radius * 2.0f,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        case OBJ_CONE:
        {
            dprintf(fd, "#Cone:\tBASE_CENTER\tAXIS\tHEIGHT\tDIAMETER\tCOLOR\n");
            dprintf(fd, "co\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].height, scene->objects[i].radius * 2.0f,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        case OBJ_CONE_CAP:
        {
            dprintf(fd, "#CapCone:\tBASE_CENTER\tAXIS\tHEIGHT\tDIAMETER\tCOLOR\n");
            dprintf(fd, "cc\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].height, scene->objects[i].radius * 2.0f,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        case OBJ_RECT:
        {
            dprintf(fd, "#Rectangle:\tCENTER\tNORMAL\tWIDTH\tHEIGHT\tCOLOR\n");
            dprintf(fd, "rc\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f",
                    scene->objects[i].position.x, scene->objects[i].position.y, scene->objects[i].position.z,
                    scene->objects[i].normal.x, scene->objects[i].normal.y, scene->objects[i].normal.z,
                    scene->objects[i].width, scene->objects[i].height,
                    scene->objects[i].color.x * 255.0f, scene->objects[i].color.y * 255.0f, scene->objects[i].color.z * 255.0f);
            add_other_params(fd, scene->objects + i);
            break;
        }
        default:
        {
            assert(!"IMPOSSIBLE TO REACH");
            break;
        }
        }
    }
    close(fd);
    return 0;
}