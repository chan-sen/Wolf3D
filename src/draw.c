
#include "./../includes/wolf3d.h"


void		drawbline(t_fdf *map, t_line line, int color)
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
	line.c1 = p1.color;
	line.c2 = p2.color;
	return (line);
}
