#include <stdio.h>
#include <stdlib.h>
#include "maze_image_generator.h"

#define MAX_IMAGE_SIZE 500

void generate_maze_image(const char* filename, int row_count, int col_count, char maze[row_count][col_count]) {

    if(row_count > 50 || col_count > 50) {
        fprintf(stderr, "Error: Row and Column of the maze must be less than or equal to 50\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Fatal Error: Could not open file '%s' for writing.\n", filename);
        exit(EXIT_FAILURE);
    }
    
    int larger_dimension = (row_count > col_count) ? row_count : col_count;
    int box_size = MAX_IMAGE_SIZE/larger_dimension;

    int image_height = box_size * row_count;
    int image_width = box_size * col_count;

    fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

    // multiplied by 3 because each pixels need 3 colors: RGB
    int image_row_size = image_width * 3;

    unsigned char row_pixels[image_row_size];
    
    for(int row = 0; row < image_height; row++) {
        for(int col = 0; col < image_width; col++) {
            int maze_row = row/box_size;
            int maze_col = col/box_size;

            int is_maze_border = (row%box_size == box_size - 1) || (col%box_size == box_size-1) || row == 0 || col == 0;
            int image_index = col * 3;
            
            if(is_maze_border) {
                row_pixels[image_index + 0] = 105;
                row_pixels[image_index + 1] = 105;
                row_pixels[image_index + 2] = 105;        
            } else if(maze[maze_row][maze_col] == '#') {
                row_pixels[image_index + 0] = 0;
                row_pixels[image_index + 1] = 0;
                row_pixels[image_index + 2] = 0;
            } else if(maze[maze_row][maze_col] == 's') {
                row_pixels[image_index + 0] = 255;
                row_pixels[image_index + 1] = 0;
                row_pixels[image_index + 2] = 0;
            } else if(maze[maze_row][maze_col] == 'e') {
                row_pixels[image_index + 0] = 0;
                row_pixels[image_index + 1] = 255;
                row_pixels[image_index + 2] = 0;  
            } else if(maze[maze_row][maze_col] == 'p') {
                row_pixels[image_index + 0] = 0;
                row_pixels[image_index + 1] = 0;
                row_pixels[image_index + 2] = 255;  
            } else if(maze[maze_row][maze_col] == 'v') {
                row_pixels[image_index + 0] = 255;
                row_pixels[image_index + 1] = 165;
                row_pixels[image_index + 2] = 0;  
            } else {
                row_pixels[image_index + 0] = 255;
                row_pixels[image_index + 1] = 255;
                row_pixels[image_index + 2] = 255;
            }
        }
        fwrite(row_pixels, sizeof(unsigned char), image_row_size, fp);
    }


    fclose(fp);
    printf("Success! '%s' has been generated.\n", filename);
}

