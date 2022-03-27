#include "3d.h"

int main(int argc, char **argv)
{
	t_mlx				*handle;
	t_data			*data;

	handle = mlxMake(1200, 600, "3d");
	data = dataMake(handle, 1200, 600);
	handle->data = data;
	mlx_hook(handle->window, 2, 1L<<0, windowClose, handle);
  //mlx_hook(handle->window, 2, 1L<<0, playerMove, handle);
//	mlx_hook(handle->window, 6, 0L<<0, playerMove, handle);
	mlx_hook(handle->window, 3, 1L<<1, inputDrag, handle);
	mlx_mouse_hook(handle->window, mouseInput, handle);
	mlx_loop_hook(handle->mlx, frameRenderer, handle);
	mlx_loop(handle->mlx);
}
