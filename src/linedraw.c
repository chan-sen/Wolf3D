
#include "./../includes/wolf3d.h"


void		put_image_pixel(t_img image, int x, int y, int color)
{
	int			b;

	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return ;
	b = (4 * x) + (y * image.sizeline);
	image.data[b++] = color & 0xFF;
	image.data[b++] = (color >> 8) & 0xFF;
	image.data[b] = (color >> 16) & 0xFF;
}

t_point		point(double x, double y)
{
	t_point		a;

	a.x = x;
	a.y = y;
	return (a);
}

t_line		line(t_point p1, t_point p2)
{
	t_line		line;

	line.d = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	if (line.d < 0)
		line.d *= -1;
	line.x1 = p1.x;
	line.y1 = p1.y;
	line.x2 = p2.x;
	line.y2 = p2.y;
	return (line);
}

void		drawline(t_env *map, t_line line, int color)
{
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	line.xi = line.x1 < line.x2 ? 1 : -1;
	line.yi = line.y1 < line.y2 ? 1 : -1;
	line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
	while (!(line.x1 == line.x2 && line.y1 == line.y2))
	{
		put_image_pixel(map->image, line.x1, line.y1, color);
		line.etmp = line.e;
		if (line.etmp > -(line.dx))
		{
			line.e -= line.dy;
			line.x1 += line.xi;
		}
		if (line.etmp < line.dy)
		{
			line.e += line.dx;
			line.y1 += line.yi;
		}
	}
	put_image_pixel(map->image, line.x1, line.y1, color);
}
