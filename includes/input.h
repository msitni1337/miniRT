#ifndef INPUT_H
#define INPUT_H
#include "Renderer.h"
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

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17


int key_hook_up(int key, t_renderer *renderer);
int key_hook_down(int key, t_renderer *renderer);
int mouse_hook_up(int button, int x, int y, t_renderer *renderer);
int mouse_hook_down(int button, int x, int y, t_renderer *renderer);

#endif // INPUT_H