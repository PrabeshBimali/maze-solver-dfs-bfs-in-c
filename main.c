#include <stdio.h>
#include <string.h>
#include "path_finder.h"
#include "maze_image_generator.h"

int main() {
    char maze[10][10] = {
        {'s', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' '},
        {' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#', ' '},
        {' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' '},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', 'e'}
    };
    char maze_copy[10][10];
    memcpy(maze_copy, maze, sizeof(maze));
    
    generate_maze_image("unsolved_maze.ppm", 10, 10, maze);
    solve_maze_bfs(10, 10, 0, 0, maze);
    generate_maze_image("solved_maze_bfs.ppm", 10, 10, maze);
    solve_maze_dfs(10, 10, 0, 0, maze_copy);
    generate_maze_image("solved_maze_dfs.ppm", 10, 10, maze_copy);

    return 0;
}
