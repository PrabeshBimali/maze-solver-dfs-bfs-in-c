#ifndef PATH_FINDER_H
#define PATH_FINDER_H

typedef struct {
    int x;
    int y;
} Point;


void solve_maze_dfs(int row, int col, int start_row, int start_col, char maze[row][col]);
void solve_maze_bfs(int row, int col, int start_row, int start_col, char maze[row][col]);

#endif
