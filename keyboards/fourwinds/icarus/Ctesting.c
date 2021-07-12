// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void read_array(char arr[], char str[], float num_elem, int precision) {
    int i;
    int index = 0;
    char output_buffer[precision];
    for ( i = 0; i < num_elem; i++) {
        if (arr[i] == str[0]) {
            output_buffer[index++] = '1';
            printf("CAL_1\n");
        } else if (arr[i] == str[1]) {
            output_buffer[index++] = '.';
            printf("CAL_DOT\n");
        } else if (arr[i] == str[2]) {
            output_buffer[index++] = '3';
            printf("CAL_3\n");
        } else if (arr[i] == str[3]) {
            output_buffer[index++] = 'END';
            printf("CAL_END\n");
        }
    };
    return;
};

int main() {
    // Write C code here
    printf("Hello world\n");
    int precision = 16;
    // int input_index;
    char output_buffer[precision];
    char input_array[5][10];
    strcpy(input_array[0], "CAL_1");
    strcpy(input_array[1], "CAL_DOT");
    strcpy(input_array[2], "CAL_3");
    strcpy(input_array[3], "CAL_END");
    strcpy(input_array[4], "CAL_3");
    size_t num_elem = (sizeof(input_array) / sizeof(input_array[0]));
    read_array(input_array, input_array[4], num_elem, precision);
    return 0;
}