#ifndef MAIN_HPP
#define MAIN_HPP

#include <cairo.h>
#include <vector>

using namespace std;

int calculate_complement_mirror(int rule);
int calculate_complement(int rule);
int calculate_mirror(int rule);

void display_stats(int rule);

void render_grid(vector<vector<bool>> grid, cairo_t* cr);

vector<vector<bool>> initialise_grid(vector<vector<bool>> grid, int rule);

int main(int argc, char* argv[]);

#endif