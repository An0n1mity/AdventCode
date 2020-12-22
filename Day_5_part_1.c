#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void) {

        FILE* fp = fopen("input.txt", "r");

        if (fp == NULL) {
                perror("Unable to open file!");
                exit(1);

        }
        char chunk[128], last_row, last_column;
        int total_row, total_column, seat_row, seat_column, row_start_index, row_stop_index, column_start_index, column_stop_index;
        int highest_id = 0;
        while (fgets(chunk, sizeof(chunk), fp) != NULL) {
          total_row = 128; total_column = 8; seat_row = 0; seat_column = 0; row_start_index = 0; row_stop_index = total_row; column_start_index = 0; column_stop_index = total_column;
          for (int i = 0; i < strlen(chunk); i++) {
            if (chunk[i] == 'F'){
              row_stop_index = ((row_start_index + row_stop_index) / 2) - 1;
              last_row = 'F';
            }
            else if (chunk[i] == 'B'){
              row_start_index = (row_start_index + row_stop_index) / 2;
              last_row = 'B';
            }
            if (chunk[i] == 'R'){
              column_start_index = (column_start_index + column_stop_index) / 2;
              last_column = 'R';
            }
            else if (chunk[i] == 'L'){
              column_stop_index = ((column_start_index + column_stop_index) / 2) - 1 ;
              last_column = 'L';
            }
          }

          if (last_row == 'F')
            seat_row = row_start_index;
          else
            seat_row = row_stop_index;
          if (last_column == 'L')
            seat_column = column_start_index;
          else
            seat_column = column_stop_index;

          printf("row : %d\n", seat_row);
          printf("column : %d\n", seat_column);

          if (seat_row * 8 + seat_column > highest_id)
            highest_id = seat_row * 8 + seat_column;
        }
        printf("Highest seat ID : %d\n", highest_id);


        fclose(fp);
}
