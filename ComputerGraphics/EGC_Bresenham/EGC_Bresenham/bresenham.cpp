#include "bresenham.h"
#include "math.h"

//Detects in which octant a line is situated
int getOctant(BresenhamLine line) {

	int deltaY = (line.endY - line.startY);
	int deltaX = (line.endX - line.startX);

	//Slope		
	float m = abs(deltaY) / (float)abs(deltaX);

	if ((m < 1) && (deltaX > 0) && (deltaY <= 0)) //first octant
		return 1;
	else if ((m >= 1) && (deltaX > 0) && (deltaY <= 0)) //second octant
		return 2;
	else if ((m >= 1) && (deltaX <= 0) && (deltaY <= 0)) //third octant
		return 3;
	else if ((m < 1) && (deltaX <= 0) && (deltaY <= 0)) //fourth octant
		return 4;
	else if ((m < 1) && (deltaX <= 0) && (deltaY > 0)) //fifth octant
		return 5;
	else if ((m >= 1) && (deltaX <= 0) && (deltaY > 0)) //sixth octant
		return 6;
	else if ((m >= 1) && (deltaX > 0) && (deltaY > 0)) //seventh octant
		return 7;
	else if ((m < 1) && (deltaX > 0) && (deltaY > 0)) //eighth octant
		return 8;

	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line, SDL_Renderer* renderer) {
	int tmpStartX = 0;
	int tmpStartY = 0;
	int tmpEndX = 0;
	int tmpEndY = 0;
	int tmpCurrentX = 0;
	int tmpCurrentY = 0;

	int dy = abs(line.endY - line.startY);
	int dx = abs(line.endX - line.startX);

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 2:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;
	case 3:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}
		break;
	case 4:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 5:
		tmpStartX = line.startX;
		tmpEndX = tmpCurrentX = line.endX;
		tmpStartY = line.startY;
		tmpEndY = tmpCurrentY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpStartX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 6:
		tmpStartX = line.startX;
		tmpEndX = tmpCurrentX = line.endX;
		tmpStartY = line.startY;
		tmpEndY = tmpCurrentY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpStartY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;
	case 7:
		tmpStartX = line.startX;
		tmpEndX = tmpCurrentX = line.endX;
		tmpStartY = line.startY;
		tmpEndY = tmpCurrentY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpStartY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}
		break;
	case 8:
		tmpStartX = line.startX;
		tmpEndX = tmpCurrentX = line.endX;
		tmpStartY = line.startY;
		tmpEndY = tmpCurrentY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpStartX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;

	default:
		break;
	}
}

//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {
	int X, Y;

	int d = 0;
	Y = circle.radius;

	for (X = 0; X <= float(circle.radius / sqrt(2)); X++)
	{

		SDL_RenderDrawPoint(renderer, circle.centerX + X, circle.centerY + Y);
		SDL_RenderDrawPoint(renderer, circle.centerX - X, circle.centerY + Y);
		SDL_RenderDrawPoint(renderer, circle.centerX - X, circle.centerY - Y);
		SDL_RenderDrawPoint(renderer, circle.centerX + X, circle.centerY - Y);
		SDL_RenderDrawPoint(renderer, circle.centerX + Y, circle.centerY + X);
		SDL_RenderDrawPoint(renderer, circle.centerX - Y, circle.centerY + X);
		SDL_RenderDrawPoint(renderer, circle.centerX - Y, circle.centerY - X);
		SDL_RenderDrawPoint(renderer, circle.centerX + Y, circle.centerY - X);
		d = d + 2 * X + 1;

		if (d > 0)
		{
			d = d + 2 - 2 * Y;
			--Y;
		}


	}
}

