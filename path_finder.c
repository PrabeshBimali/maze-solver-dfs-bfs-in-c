#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "path_finder.h"

/* 
    global variables for storing row and col of given maze so, no need to transfer to functions via parameter
*/
static int maze_row = 0;
static int maze_col = 0;

bool is_point_valid(int r, int c, bool visited[maze_row][maze_col], char maze[maze_row][maze_col]) {
    bool value = (r >= 0 && r < maze_row && c >= 0 && c < maze_col && !visited[r][c] && maze[r][c] != '#');
    return value;
}

void solve_maze_bfs(int row, int col, int start_row, int start_col, char maze[row][col]) {
    maze_row = row;
    maze_col = col;

    bool added_points[maze_row][maze_col];
    memset(added_points, 0, sizeof(added_points));

    bool visited[maze_row][maze_col];
    memset(visited, 0, sizeof(visited));


    Point parent_map[row][col];

    Point queue[row*col];
    int top = -1;
    int bottom = -1;

    Point start = {start_row, start_col};
    queue[++top] = start;
    bottom++;
    parent_map[start_row][start_col] = (Point){-1, -1};
    added_points[start_row][start_col] = true;

    int i_row[] = {1, -1, 0, 0};
    int i_col[] = {0, 0, 1, -1};

    bool is_found = false;
    Point current;

    while(top >= 0) {
        current = queue[top++];
        visited[current.x][current.y] = true;

        if(maze[current.x][current.y] == 'e') {
            is_found = true;
            break;  
        }

        for(int i = 0; i < 4; i++) {
            Point next = {current.x + i_row[i], current.y + i_col[i]};
            
            if(is_point_valid(next.x, next.y, added_points, maze)) {
                queue[++bottom] = next;
                added_points[next.x][next.y] = true;
                parent_map[next.x][next.y] = current;
            }
        }    
            
    }

    // From here we could use different function but it is fine for now.
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(maze[i][j] != 's' && maze[i][j] != 'e' && visited[i][j]) {
                maze[i][j] = 'v';
            }        
        }     
    }

    if(is_found) {
        while(current.x != -1 && current.y != -1) {
            if(maze[current.x][current.y] != 's' && maze[current.x][current.y] != 'e') {
                maze[current.x][current.y] = 'p';
            }
            current = parent_map[current.x][current.y];
        }
    }
}

void solve_maze_dfs(int row, int col, int start_row, int start_col, char maze[row][col]) {

    maze_row = row;
    maze_col = col;

    bool added_points[maze_row][maze_col];
    memset(added_points, 0, sizeof(added_points));

    bool visited[maze_row][maze_col];
    memset(visited, 0, sizeof(visited));


    Point parent_map[row][col];

    Point stack[row*col];
    int top = -1;

    Point start = {start_row, start_col};
    stack[++top] = start;
    parent_map[start_row][start_col] = (Point){-1, -1};
    added_points[start_row][start_col] = true;

    int i_row[] = {1, -1, 0, 0};
    int i_col[] = {0, 0, 1, -1};

    bool is_found = false;
    Point current;

    while(top >= 0) {
        current = stack[top--];
        visited[current.x][current.y] = true;

        if(maze[current.x][current.y] == 'e') {
            is_found = true;
            break;  
        }

        for(int i = 0; i < 4; i++) {
            Point next = {current.x + i_row[i], current.y + i_col[i]};
            
            if(is_point_valid(next.x, next.y, added_points, maze)) {
                stack[++top] = next;
                added_points[next.x][next.y] = true;
                parent_map[next.x][next.y] = current;
            }
        }    
            
    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(maze[i][j] != 's' && maze[i][j] != 'e' && visited[i][j]) {
                maze[i][j] = 'v';
            }        
        }     
    }

    if(is_found) {
        while(current.x != -1 && current.y != -1) {
            if(maze[current.x][current.y] != 's' && maze[current.x][current.y] != 'e') {
                maze[current.x][current.y] = 'p';
            }
            current = parent_map[current.x][current.y];
        }
    }
    
}


