#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {

	FILE* fp = fopen("input.txt", "r");
	int nb_array[1000];

	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);

	}

	char chunk[128], first_index_array[10], second_index_array[10], string[40], letter;
	int nb = 0;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		bool first_index = true, second_index = false, string_bool = false;
		int i = 0;

		memset(first_index_array, 0, 10);
		memset(second_index_array, 0, 10);
		memset(string, 0, 40);

		for (int j = 0; j < strlen(chunk); j++) {
			if (chunk[j] == '-') {
				first_index = false;
				second_index = true;
				i = 0;
				j++;
			}

			if (chunk[j] == ' ') {
				second_index = false;
				string_bool = true;
				j++;
				letter = chunk[j];
				j += 3;
				i = 0;
			}

			if (first_index) 
				first_index_array[i] = chunk[j];
		
			if (second_index) 
				second_index_array[i] = chunk[j];

			if (string_bool) {
				string[i] = chunk[j];

			i++;
		}

		if((letter == string[atoi(first_index_array)-1]) ^ (letter == string[atoi(second_index_array)-1]))
			nb++;
	}

	printf("The answer is %d", nb);

	fclose(fp);
}