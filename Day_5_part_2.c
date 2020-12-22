#include <stdio.h>
#include <stdlib.h>

void swap(int* xp, int* yp);
void selectionSort(int arr[], int n);

int main(void) {

        FILE* fp = fopen("input.txt", "r");

        if (fp == NULL) {
                perror("Unable to open file!");
                exit(1);

        }
        char chunk[128], last_row, last_column;
        int total_row, total_column, seat_row, seat_column, row_start_index, row_stop_index, column_start_index, column_stop_index;
        int highest_id = 0, minimal_id = 10000, array_id[1000], j = 0;
        while (fgets(chunk, sizeof(chunk), fp) != NULL) {
          total_row = 127; total_column = 7; seat_row = 0; seat_column = 0; row_start_index = 0; row_stop_index = total_row; column_start_index = 0; column_stop_index = total_column;
          for (int i = 0; i < 10; i++) {
            if (chunk[i] == 'F')
              row_stop_index = ((row_start_index + row_stop_index + 1) / 2) - 1;
             
            else if (chunk[i] == 'B')
              row_start_index = (row_start_index + row_stop_index + 1) / 2;
             
            if (chunk[i] == 'R')
              column_start_index = (column_start_index + column_stop_index + 1) / 2;
              
            else if (chunk[i] == 'L')
              column_stop_index = ((column_start_index + column_stop_index + 1) / 2) - 1 ;
             
          }

            seat_row = row_start_index;
            seat_column = column_stop_index;

          if (seat_row * 8 + seat_column > highest_id)
            highest_id = seat_row * 8 + seat_column;
          if (seat_row * 8 + seat_column < minimal_id)
            minimal_id = seat_row * 8 + seat_column;

          array_id[j] = seat_row * 8 + seat_column;

          ++j;
        }


        selectionSort(array_id, j);

        for (int i = 0, k = minimal_id; i < j; i++, k++) {
            if(array_id[i] != k){
              printf("Your seat ID is %d\n", k);
              break;
            }
        }
        fclose(fp);
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
