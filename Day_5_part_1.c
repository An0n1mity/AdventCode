#include <stdio.h>
#include <stdlib.h>

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
          total_row = 127; total_column = 7; seat_row = 0; seat_column = 0; row_start_index = 0; row_stop_index = total_row; column_start_index = 0; column_stop_index = total_column;
          for (int i = 0; i < strlen(chunk); i++) {
            if (chunk[i] == 'F')
              row_stop_index = ((row_start_index + row_stop_index + 1) / 2) - 1;
            
            else if (chunk[i] == 'B')
              row_start_index = (row_start_index + row_stop_index + 1) / 2;
            
            if (chunk[i] == 'R')
              column_start_index = (column_start_index + column_stop_index + 1) / 2;
            
            else if (chunk[i] == 'L')
              column_stop_index = ((column_start_index + column_stop_index + 1) / 2) - 1;

         seat_row = row_start_index;
         seat_column = column_stop_index;

          if (seat_row * 8 + seat_column > highest_id)
            highest_id = seat_row * 8 + seat_column;
        }
        printf("Highest seat ID : %d\n", highest_id);


        fclose(fp);
}
