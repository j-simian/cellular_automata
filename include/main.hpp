#ifndef MAIN_HPP
#define MAIN_HPP

#include <cairo.h>
#include <vector>
using namespace std;

void render_grid(vector<vector<bool>> grid, cairo_t* cr);
vector<vector<bool>> initialise_grid(vector<vector<bool>> grid, int rule);
int main(int argc, char* argv[]);

#endif