#include "3d.h"

int map[8][8] =
{
	{1,1,1,0,0,1,1,1},
	{1,0,1,0,1,1,0,1},
	{1,0,1,0,1,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,1,1,1,0,1},
	{1,0,1,0,0,1,0,1},
	{1,0,0,0,0,1,0,1},
	{1,1,1,1,1,1,1,1}

};

int map2[256] =
{
	 1,1,1,0,0,1,1,1
	,1,0,1,0,1,1,0,1
	,1,0,1,0,1,0,0,1
	,1,0,1,0,0,0,0,1
	,1,0,1,1,1,1,0,1
	,1,0,1,0,0,1,0,1
	,1,0,0,0,0,1,0,1
	,1,1,1,1,1,1,1,1
};


int tmp1;
int tmp2;

void	kill(char *string)
{
	if (string)
		fprintf(stderr, "%s", string);
	exit(1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_mlx	*mlxMake(int WIDTH, int HEIGHT, char *title)
{
	t_mlx	*make;

	make = (t_mlx *) malloc(sizeof(t_mlx));
	if (!make)
		kill("func [ makeMlx() ] MALLOC_MLX_FAIL\n");
	make->mlx = mlx_init();
	if (!make->mlx)
		kill("func [ makeMlx() ] MLX_INIT_FAIL\n");
	make->window = mlx_new_window(make->mlx, WIDTH, HEIGHT, title);
	if (!make->window)
		kill("func [ makeMlx() ] MLX_NEW_WINDOW_FAIL\n");
	make->mouse = (t_mouse *) malloc(sizeof(t_mouse));
	if (!make->mouse)
		kill("func [ makeMlx() ] MALLOC_MOUSE_FAIL\n");
	make->mouse->x = 0;
	make->mouse->y = 0;
	make->mouse->keycode = 0;
	make->keyboard = (t_keyboard *) malloc(sizeof(t_keyboard));
	if (!make->keyboard)
		kill("func [ makeMlx() ] MALLOC_KEYBOARD_FAIL\n");
	make->keyboard->keycode = 0;
	make->keyboard->isp = false;
	make->player = (t_player *) malloc(sizeof(t_player));
	if (!make->player)
		kill("func [ makeMlx() ] MALLOC_PLAYER_FAIL\n");
	make->player->pa = 0;
	make->player->px = 160;
	make->player->py = 130;
	make->player->pdx = cos(0)*5;
	make->player->pdy = sin(0)*5;
	make->player->size = 16;
	make->width = WIDTH;
	make->height = HEIGHT;
	return (make);
}

t_data *dataMake(t_mlx *handle, int WIDTH, int HEIGHT) // hieght width
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		kill("func [ dataMake(t_mlx *mlx) ] MALLOC_FAIL\n");
	data->img = mlx_new_image(handle->mlx, WIDTH, HEIGHT);
	if (!data->img)
		kill("func [ dataMake(t_mlx *mlx) ] MLX_NEW_IMAGE_FAIL\n");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (!data->addr)
		kill("func [ dataMake(t_mlx *mlx) ] MLX_GET_DATA_ADDR_FAIL\n");
	return (data);
}

int drawlinew(t_mlx *handle, int bx, int dx, int by, int dy, int color)
{
	double deltaX = dx - bx;
	double deltaY = dy - by;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = bx;
	double pixelY = by;
	while (pixels)
	{
		my_mlx_pixel_put(handle->data, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;

		--pixels;
	}
	return (0);
}

int drawline(t_mlx *handle, int bx, int dx, int by, int dy)
{
	double deltaX = dx;
	double deltaY = dy;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = bx;
	double pixelY = by;
	while (pixels)
	{
		my_mlx_pixel_put(handle->data, pixelX, pixelY, 0x00FF00FF);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}


int drawlined(t_mlx *handle, int bx, int dx, int by, int dy)
{
	double deltaX = dx - bx;
	double deltaY = dy - by;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = bx;
	double pixelY = by;
	while (pixels)
	{
		my_mlx_pixel_put(handle->data, pixelX, pixelY, 0x00FF0000);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

int	windowClose(int keycode, t_mlx	*handle)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(handle->mlx, handle->window);
		kill(NULL);
	}
	if (keycode == A_KEY)
	{
		handle->player->pa-=0.1;
		if (handle->player->pa < 0)
			handle->player->pa += 2 * PI;
		handle->player->pdx = cos(handle->player->pa) * 5;
		tmp1 = cos(handle->player->pa);
		handle->player->pdy = sin(handle->player->pa) * 5;
		tmp2 = sin(handle->player->pa);
	}
	if (keycode == D_KEY)
	{
		handle->player->pa+=0.1;
		if (handle->player->pa > 2 * PI)
			handle->player->pa -= 2 * PI;
		handle->player->pdx = cos(handle->player->pa) * 5;
		tmp1 = cos(handle->player->pa);
		handle->player->pdy = sin(handle->player->pa) * 5;
		tmp2 = sin(handle->player->pa);
	}
	if (keycode == W_KEY)
	{
		handle->player->px += handle->player->pdx;
		handle->player->py += handle->player->pdy;
	}
	if (keycode == S_KEY)
	{
		handle->player->px -= handle->player->pdx;
		handle->player->py -= handle->player->pdy;
	}
	printf("%d\n", keycode);
	return (0);
}

int playerMove(int x, int y, t_mlx *handle)
{
if ((y > 0 && y < 600) && (x > 8 && x < 112))
{
	handle->keyboard->isp = true;
	handle->player->px = x;
	handle->player->py = y;
}

	fprintf(stderr, "%d -> x && %d -> y\n", x, y);
	return (0); 
}

int mouseInput(int keycode, t_mlx *handle)
{
	if (keycode == 1)
	{
		fprintf(stderr, "MOUSE CLICKED!!\n");
	}
	return (0);
}

int **makeMap()
{
	int **arr;

	arr = (int **) malloc(sizeof(int *) * 900);
	for (int i = 0; i < 900; i++)
	{
		arr[i] = (int *) malloc(sizeof(int) * 400);
		for (int j = 0; j < 400; j++)
			arr[i][j] = 0;
	}
	return (arr);
}

//int	frameRenderer(t_mlx	*handle)
//{
//	int j;
//	int i;
//
//	for (int z = 0; z < 900; z++)
//		for (int c = 0; c < 400; c++)
//		{
//			if (handle->map[z][c] == 1)
//				my_mlx_pixel_put(handle->data, z, c, 0x0000FF00);
//			else
//				my_mlx_pixel_put(handle->data, z, c, 0x00FF00FF);
//		}
//	mlx_put_image_to_window(handle->mlx, handle->window, handle->data->img, 0, 0);
//
//	i = (int)(handle->player->x);
//	j = (int)(handle->player->y);
//	if (handle->keyboard->isp == true)
//	{
//		for (int a = i - 8; a < i + handle->player->size - 8; a++)
//		{
//			for (int b = j - 8; b < j + handle->player->size - 8; b++)
//			{
//				handle->map[a][b] = 1;
//			}
//		}
//		handle->keyboard->isp = false;
//	}
//	return (0);
//}

void doWall(int *x, int *y, t_data *data)
{
	int i = *x;
	int j = *y;
	for (; i < (*x)+64; i++)
	{
		j = (*y);
		for(; j < (*y)+64; j++)
		{
			if (i != (*x) + 63 && j != (*y) + 63)
				my_mlx_pixel_put(data, i, j, 0x00FFFFFF);
			else
				my_mlx_pixel_put(data, i, j, 0x00778899); 
		}
	}
	(*x)+=64;
}

void doSpace(int *x, int *y, t_data *data)
{
	int i = *x;
	int j = *y;
	for (; i < (*x)+64; i++)
	{
		j = (*y);
		for(; j < (*y)+64; j++)
		{
			if (i != (*x) + 63 && j != (*y) + 63)
				my_mlx_pixel_put(data, i, j, 0x00000000);
			else
				my_mlx_pixel_put(data, i, j, 0x00778899);
		}
	}
	(*x)+=64;
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax) * (bx-ax) + (by-ay)*(by-ay)));
}

void	drawRay3D(t_mlx *handle)
{
	int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
	ra = handle->player->pa;
	float tpx = handle->player->px;
	float tpy = handle->player->py;
	float disT;
	int color;
	ra=handle->player->pa-DR*30; if(ra < 0) { ra+=2*PI; } if (ra>2*PI) { ra-=2*PI; }
	for (r=0;r<60;r++)
	{
		
		dof = 0;
		float disH = 100000;
		float hx = tpx;
		float hy = tpy;
		float aTan=-1/tan(ra);
		if (ra>PI) { ry = (((int)tpy>>6)<<6) -0.0001; rx=(tpy-ry) * aTan+tpx; yo=-64; xo=-yo*aTan; }
		if (ra<PI) { ry = (((int)tpy>>6)<<6) +64; rx=(tpy-ry) * aTan+tpx; yo= 64; xo=-yo*aTan; }
		if (ra==0 || ra==PI){ rx=tpx; ry=tpy; dof = 8;}
		while (dof < 8)
		{
			mx=(int) (rx)>>6; my=(int) (ry)>>6; mp=my*8+mx;
			if (mp > 0 && mp < 8 * 8 && map2[mp] == 1) { hx = rx; hy = ry; disH = dist(tpx,tpy,hx,hy,ra);dof = 8; }
			else{ rx+=xo; ry+=yo; dof+=1;}
		}
		dof = 0;
		float nTan=-tan(ra);
		float disV = 100000;
		float vx = tpx;
		float vy = tpy;
	if (ra>P2 && ra<P3) { rx = (((int)tpx>>6)<<6) -0.0001; ry=(tpx-rx) * nTan+tpy; xo=-64; yo=-xo*nTan; }
		if (ra<P2 || ra>P3) { rx = (((int)tpx>>6)<<6) +64; ry=(tpx-rx) * nTan+tpy; xo= 64; yo=-xo*nTan; }
		if (ra==0 || ra==PI){ rx=tpx; ry=tpy; dof = 8;}
		while (dof < 8)
		{
			mx=(int) (rx)>>6; my=(int) (ry)>>6; mp=my*8+mx;
			if (mp > 0 && mp < 8 * 8 && map2[mp] == 1) { vx = rx; vy = ry; disV = dist(tpx,tpy,vx,vy,ra);dof = 8; }
			else{ rx+=xo; ry+=yo; dof+=1;}
		}
		int input_1 = 0x00800000;
		int input_2 = 0x00a52a2a;
		if (disV<disH){ rx=vx; ry=vy; disT = disV; color = input_2;}
		else if (disH<disV) { rx=hx; ry=hy; disT = disH; color = input_1;}
		for (int d = 0; d < 5; d++)	
			drawlined(handle, tpx + 6, rx + d, tpy + 6, ry + d);
		float ca=handle->player->pa-ra; if (ca<0) { ca+=2*PI; } if (ca>2*PI) { ca-=2*PI; };
		disT=disT*cos(ca);
		float lineH = (64 * 320)/disT; if (lineH>320) { lineH=320; }
		float lineO = 160-lineH/2;
		for (int thickness = 8; thickness >= 0; thickness--)
		{
				drawlinew(handle, r*8+530 + thickness, r*8+530 + thickness, lineO, lineH + lineO, color);	
		}
		ra+=DR; if(ra < 0) { ra+=2*PI; } if (ra>2*PI) { ra-=2*PI; }
	}
}

int	frameRenderer(t_mlx *handle)
{

	for (int i = 0; i < handle->width; i++)
		for (int j = 0; j < handle->height; j++)
			my_mlx_pixel_put(handle->data, i, j, 0x00A9A9A9);
	mlx_put_image_to_window(handle->mlx, handle->window, handle->data->img, 0, 0);
	int current_x = 0;
	int current_y = 0;

	for (int i = 0; i < 8; i++) // x coord
	{
		for (int j = 0; j < 8; j++) // y coord
		{
			if (map[i][j])
				doWall(&current_x, &current_y, handle->data);
			else
				doSpace(&current_x, &current_y, handle->data);
		}
		current_x = 0;
		current_y += 64;
	}

	mlx_put_image_to_window(handle->mlx, handle->window, handle->data->img, 0, 0);
	int i = handle->player->px;
	int j = handle->player->py;
	drawline(handle, handle->player->px + 6, handle->player->pdx * 5, handle->player->py + 6, handle->player->pdy * 5);
	drawRay3D(handle);
	for (int b = i; b < i + 12; b++)
	{
		for (int a = j; a < j + 12; a++)
		{
				my_mlx_pixel_put(handle->data, b, a, 0x00FFFF00);
		}
	}
	mlx_put_image_to_window(handle->mlx, handle->window, handle->data->img, 0, 0);
	return (0);
}

int inputDrag(int keycode, t_mlx *handle)
{
	//if (keycode == D_KEY)
	//{
	//	handle->player->pa-=0.1;
	//	if (handle->player->pa < 0)
	//		handle->player->pa += 2 * PI;
	//	handle->player->pdx = cos(handle->player->pa) * 5;
	//	tmp1 = cos(handle->player->pa);
	//	handle->player->pdy = sin(handle->player->pa) * 5;
	//	tmp2 = sin(handle->player->pa);
	//}
	//if (keycode == A_KEY)
	//{
	//	handle->player->pa+=0.1;
	//	if (handle->player->pa > 2 * PI)
	//		handle->player->pa -= 2 * PI;
	//	handle->player->pdx = cos(handle->player->pa) * 5;
	//	tmp1 = cos(handle->player->pa);
	//	handle->player->pdy = sin(handle->player->pa) * 5;
	//	tmp2 = sin(handle->player->pa);
	//}
	//if (keycode == W_KEY)
	//{
	//	handle->player->px += handle->player->pdx;
	//	handle->player->py += handle->player->pdy;
	//}
	//if (keycode == S_KEY)
	//{
	//	handle->player->px -= handle->player->pdx;
	//	handle->player->py -= handle->player->pdy;
	//}
	printf("%d- >keycoce\n", keycode);
	return (0);
}
