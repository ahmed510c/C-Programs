#include <stdio.h>
#include <stdlib.h>

// Function to write hardcoded points to a binary file
void write_hardcoded_shape_to_file(const char* file_name);

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Write hardcoded points to the specified file
    write_hardcoded_shape_to_file(argv[1]);
    return 0;
}

/**
 * Writes 3 hardcoded points to a binary file.
 * @param file_name The name of the binary file to write.
 */
void write_hardcoded_shape_to_file(const char* file_name) {
    FILE* file = fopen(file_name, "wb");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", file_name);
        return;
    }

    // Write the number of points (3 hardcoded points)
    int num_points = 3;
    fwrite(&num_points, sizeof(int), 1, file);

    // Hardcoded points
    int points[][2] = {
        {287, 422},
        {283, -981},
        {781, 647}
    };

    // Write the hardcoded points to the binary file
    for (int i = 0; i < num_points; ++i) {
        fwrite(&points[i][0], sizeof(int), 1, file); // Write x-coordinate
        fwrite(&points[i][1], sizeof(int), 1, file); // Write y-coordinate
    }

    fclose(file);
    printf("Binary file %s created with %d hardcoded points.\n", file_name, num_points);
}
*
This program generates a file of random binary points.

Usage: ./create_binary_shape.out file_path [num_points] [min_value] [max_value]
@file_path: the path to the file to write the shape to
@num_points: the number of points to put in the file. Defaults to 10 if not given
@min_value: the smallest value for an x/y coordinate. Defaults to -100 if not given
@min_value: the largest value for an x/y coordinate. Defaults to 100 if not given
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_int(int min_value, int max_value);
void write_random_shape_to_file(const char* file_name, int num_points, int min_value, int max_value);
int process_command_line_parameter(const char* parameter_value, const char* parameter_name,
                                   bool has_minimum, int min_value,
                                   int default_value);

int main(int argc, char** argv){
    srand(time(NULL));


    int num_points = 10;
    int default_min = -100, default_max = 100;
    int min_value = default_min, max_value = default_max;
    if(argc < 2 || argc > 5){
        printf("Improper usage.\n"
               "Correct usage: %s file_path [num_points] [min_value] [max_value]\n", argv[0]
               );
    }else{

        if(argc >= 3){
          num_points = process_command_line_parameter(argv[2], "num_points", true, 3, 3);
        }

        if(argc >= 4){
            min_value = process_command_line_parameter(argv[3], "min_value", false, default_min, default_min);
        }

        if(argc >= 5){
            max_value = process_command_line_parameter(argv[4], "max_value", false, default_max, default_max);
        }

        if(max_value <= min_value){
            min_value = default_min;
            max_value = default_max;
            printf("max_value is below min_value. Using %d for min_value and %d for max_value\n", default_min, default_max);
        }

        write_random_shape_to_file(argv[1], num_points, min_value, max_value);
    }
return 0;
}



int rand_int(int min_value, int max_value){
    /*
      Generate a random int between [min_value, max_value]
      @min_value: the lowest value that can be generated
      @max_value: the highest value that can be generated
    */
    const int range = max_value - min_value + 1;
    return min_value + rand() % range;
}

void write_random_shape_to_file(const char* file_name, int num_points, int min_value, int max_value){
    /*
    Create and write a random shape to the specified file
    @file_name: the path to the file to write to
    @num_points: the number of vertices in the shape
    @min_value: the minimum value for an x/y coordinate
    @max_value: the maximum value for an x/y coordinate
    */
    FILE* file = fopen(file_name, "w");

    if(file == NULL){
        printf("Failed to open %s. Ending program\n", file_name);
        exit(1);
    }

    fwrite(&num_points, sizeof(int), 1, file);
    for(int i = 0 ; i < num_points; ++i){
        int x_coord = rand_int(min_value, max_value), y_coord = rand_int(min_value, max_value);
        fwrite(&x_coord, sizeof(int), 1, file);
        fwrite(&y_coord, sizeof(int), 1, file);
    }
    fclose(file);

}

int process_command_line_parameter(const char* parameter_value, const char* parameter_name,
                                   bool has_minimum, int min_value,
                                   int default_value){


    char should_be_blank;
    int value;

    int num_args_read = sscanf(parameter_value, "%d %c", &value, &should_be_blank);
    if(num_args_read == 1){
        if(has_minimum && value >= min_value){
            return value;
        }else{
            printf("Invalid value for %s: %s. Value must be at least %d.\nDefaulting to %d\n",
                    parameter_name, parameter_value, min_value, default_value);
            return default_value;
        }
    }else{
        printf("Invalid value for %s: %s. Defaulting to %d\n",
                parameter_name, parameter_value, default_value);
        return default_value;
    }

}
