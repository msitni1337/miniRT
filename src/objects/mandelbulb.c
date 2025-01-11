/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbulb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simo <simo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:47 by msitni            #+#    #+#             */
/*   Updated: 2025/01/12 00:55:59 by simo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"
#include <stdio.h>

void mandelbulb_recalculate(t_object *object)
{
    (void)object;
}

t_vec4 mandelbulb_map_uv(t_hit hit, t_object *obj)
{
    (void)obj;
    (void)hit;
    return (t_vec4){0};
}

t_hit mandelbulb_intersection(t_object *object, t_ray ray)
{
    /*
    1 - Define a point p⃗ in 3D space as your starting point.
    2 - Initialize z⃗ to p⃗
    ​3 - Iterate the following steps for a specified number of iterations (e.g., nn):
        1 /Convert z⃗z to spherical coordinates:

            r = ∣z⃗∣ (distance from origin)
            θ = arccos⁡(Zy/r) (polar angle)
            ϕ = arctan⁡2(Zx,Zz) (azimuthal angle)

        2 /Apply the fractal power nn (e.g., n=8n=8 for the standard Mandelbulb):

            rnew =r^n
            θnew =n⋅θ
            ϕnew =n⋅ϕ

        3 /Convert back to Cartesian coordinates:

        z⃗new=rnew⋅[sin⁡(θnew)⋅cos⁡(ϕnew),sin⁡(θnew)⋅sin⁡(ϕnew),cos⁡(θnew)]

        4 /Add p⃗ to z⃗new:

        z⃗=z⃗new+p⃗
*/

    t_hit hit;
    hit.is_valid = 0;
    int n = object->iterations;
    ray.target = vec3_scale(ray.target, 0.1f);
    int i = 0;
    for (; i < n && vec3_magnitude(ray.target) < 2.0f; i++)
    {
        double r = vec3_magnitude(ray.target);
        double phi = acos(ray.target.z / r);
        double psi = atan2(sqrt((ray.target.x * ray.target.x) / (ray.target.y * ray.target.y)), ray.target.z);

        double new_r = pow(r, n);
        double new_phi = phi * n;
        double new_psi = n * psi;

        t_vec3 z;
        z.x = new_r * sin(new_phi) * cos(new_psi);
        z.y = new_r * sin(new_phi) * sin(new_psi);
        z.z = new_r * cos(new_phi);
        ray.target = vec3_add_vec3(z, ray.target); // Add the original point p to z
    }

    if (vec3_magnitude(ray.target) < 2.0f)
    {
        hit.is_valid = 1;
        hit.object = object;
        hit.hit_point = ray.target;
        object->color = vec3_scale((t_vec3){1, 1, 1}, 1.0f / i);
    }
    return hit;
}

t_object new_mandelbulb(t_vec3 pos, float iterations, t_vec3 color)
{
    t_object mandelbulb;

    mandelbulb = (t_object){0};
    mandelbulb.type = OBJ_SPHERE;
    mandelbulb.intersection = &mandelbulb_intersection;
    mandelbulb.recalculate = &mandelbulb_recalculate;
    mandelbulb.position = pos;
    mandelbulb.iterations = iterations;
    mandelbulb.color = vec3_scale(color, 1.0f / 255.0f);
    mandelbulb.normal = (t_vec3){0, 0, 1.0f};
    return mandelbulb;
}