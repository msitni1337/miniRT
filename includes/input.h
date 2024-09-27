/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:14:53 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 11:15:33 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H
#include "Renderer.h"
#include "utils.h"

#ifdef INPUT_MAC
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_RIGHT 124
#define KEY_LEFT 123
#define KEY_Z 122
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_8 91
#define KEY_2 84
#define KEY_6 88
#define KEY_4 86
#define KEY_TAB 48
#define KEY_CTR 259
#define KEY_ESC 53
#define KEY_PLUS_NUM 69
#define KEY_MINUS_NUM 78
#define KEY_PLUS 24
#define KEY_MINUS 27
#define KEY_LPAREN 25
#define KEY_RPAREN 29
#define KEY_H 4
#else
#define KEY_DOWN 65364
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_LEFT 65361
#define KEY_Z 122
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_8 65431
#define KEY_2 65433
#define KEY_6 65432
#define KEY_4 65430
#define KEY_TAB 65289
#define KEY_CTR 65507
#define KEY_ESC 65307
#define KEY_PLUS_NUM 65451
#define KEY_MINUS_NUM 65453
#define KEY_PLUS 61
#define KEY_MINUS 45
#define KEY_LPAREN 57
#define KEY_RPAREN 48
#define KEY_H 104
#endif

#define MOUSE_CLICK 1

#define ON_KEYDOWN 2
#define ON_KEYUP 3
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_MOUSEMOVE 6
#define ON_EXPOSE 12
#define ON_DESTROY 17

#define SENS 2.0f

int key_hook_up(int key, t_renderer *renderer);
int key_hook_down(int key, t_renderer *renderer);
int mouse_hook_up(int button, int x, int y, t_renderer *renderer);
int mouse_hook_down(int button, int x, int y, t_renderer *renderer);
void	hook_input(t_renderer *r);
int	on_destroy(t_renderer *r);

void control_camera(int key, t_camera *cam);
void control_selected_obj(int key, t_object *obj);

#endif // INPUT_H