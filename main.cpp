#include "main.hpp"
#include <cairo.h>
#include <stdio.h>
#include <vector>
using namespace std;

int rule = 110;
vector<vector<bool>> grid;

const int WIDTH = 300; const int HEIGHT = 100; const int SCALE = 5;

int main(int argc, char* argv[])
{
	cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH * SCALE, HEIGHT * SCALE);
	cairo_t* cr = cairo_create(surface);
	cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);

	grid = initialise_grid(grid, rule);
	render_grid(grid, cr);

	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "hello.png");
	cairo_surface_destroy(surface);
	return 0;
}

void render_grid(vector<vector<bool>> grid, cairo_t* cr) {
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_rectangle(cr, 0, 0, WIDTH * SCALE, HEIGHT * SCALE);
	cairo_fill(cr);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (grid.at(i).at(j)) {
				cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
				cairo_rectangle(cr, j * SCALE, i * SCALE, SCALE, SCALE);
				cairo_fill(cr);
			}
			else {
				// cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
				// cairo_rectangle(cr, j * SCALE, i * SCALE, SCALE, SCALE);
				// cairo_set_line_width(cr, 1.0);
				// cairo_stroke(cr);
			}
		}
	}

}

vector<vector<bool>> initialise_grid(vector<vector<bool>> grid, int rule)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		vector<bool> row;
		for (int j = 0; j < WIDTH; j++)
		{
			bool a, b, c = false;
			if (i == 0 && j == WIDTH / 2)
			{
				row.push_back(true);
				continue;
			}
			else if (i == 0)
			{
				row.push_back(false);
				continue;
			}
			if (j != 0)
			{
				a = grid.at(i - 1).at(j - 1);
			}
			if (j < WIDTH - 1)
			{
				c = grid.at(i - 1).at(j + 1);
			}
			b = grid.at(i - 1).at(j);
			printf("%i", a * 4 + b * 2 + c);
			row.push_back(rule >> (a * 4 + b * 2 + c) & 1);
		}
		grid.push_back(row);
	}
	return grid;
}