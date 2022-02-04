#include "main.hpp"
#include <cairo.h>
#include <stdio.h>
#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

uint8_t rule = 110;
vector<vector<bool>> grid;

const int WIDTH = 300; const int HEIGHT = 100; const int SCALE = 5;

int main(int argc, char* argv[])
{
	cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH * SCALE, HEIGHT * SCALE);
	cairo_t* cr = cairo_create(surface);
	cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);

	grid = initialise_grid(grid, rule);
	render_grid(grid, cr);
	display_stats(rule);

	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "hello.png");
	cairo_surface_destroy(surface);
	return 0;
}

void display_stats(int rule) {
	printf("Stats: \n");
	printf("Rule: %i\n", rule);
	printf("Mirror rule: %i%s\n", calculate_mirror(rule), calculate_mirror(rule) == rule ? " (antichiral)" : "");
	printf("Complement rule: %i\n", calculate_complement(rule));
	printf("Mirror Complement rule: %i\n", calculate_complement_mirror(rule));
}

int calculate_mirror(int rule) {
	bool a, b, c, d = false;
	a = (rule >> 6) & 1;
	b = (rule >> 4) & 1;
	c = (rule >> 3) & 1;
	d = (rule >> 1) & 1;

	uint8_t mirroredRule = (rule & 0b10100101) + (b << 1) + (a << 3) + (d << 4) + (c << 6);

	return mirroredRule;
}

int calculate_complement(int rule) {
	vector<int> bits;
	for (int i = 0; i < 8; i++) {
		bits.push_back(!(rule >> i & 1));
	}
	reverse(bits.begin(), bits.end());
	uint8_t complementaryRule = 0;
	for (int i = 0; i < 8; i++) {
		if (bits.at(i) == 1) {
			complementaryRule += (1 << i);
		}
	}
	return complementaryRule;
}

int calculate_complement_mirror(int rule) {
	return calculate_mirror(calculate_complement(rule));
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
			row.push_back(rule >> (a * 4 + b * 2 + c) & 1);
		}
		grid.push_back(row);
	}
	return grid;
}