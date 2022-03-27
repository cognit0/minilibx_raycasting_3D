#ifndef _3D_H_
# define _3D_H_

// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../42curses/FdF/include/mlx.h"
#include <OpenGL/opengl.h>
#include <math.h>
#include <stdbool.h>
#include "mlx_int.h"

// KEYCODES
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0173533

// DATATYPES

typedef struct s_mouse
{
	float x;
	float y;
	int keycode;
}	t_mouse;

typedef struct s_keyboard
{
	int keycode;
	bool isp;
}	t_keyboard;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_player
{
	float	px;
	float	py;
	float pdx;
	float pdy;
	float pa;
	int size;
}	t_player;

typedef struct s_3dray
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
}	t_3dray;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
	t_mouse	*mouse;
	t_data	*data;
	t_keyboard	*keyboard;
	t_player		*player;
	t_3dray			*ray;
	int		**map;
} t_mlx;


enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
};

// FUNCTIONS

int	windowClose(int keycode, t_mlx *handle);
int playerMove(int x, int y, t_mlx *handle);
int	frameRenderer(t_mlx *handle);
int mouseInput(int keycode, t_mlx *handle);
int inputDrag(int keycode, t_mlx *handle);

int **makeMap();

void	kill(char *string);
void	drawRay3D(t_mlx *handle);

t_mlx	*mlxMake(int WIDTH, int HEIGHT, char *title);

t_data *dataMake(t_mlx *handle, int WIDTH, int HEIGHT);


#endif
