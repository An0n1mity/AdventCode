#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	FILE* fp = fopen("input_two.txt", "r");
	int nb_array[1000];
	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);

	}

	char chunk[128], min_array[10], max_array[10], pass_array[30], letter;
	int nb_pass = 0, nb = 0;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		int i = 0, min = 0, max = 0, nb_letter = 0;
		bool minimal = true, maximal = false, password = false;

		memset(min_array, 0, sizeof(min_array));
		memset(pass_array, 0, sizeof(pass_array));
		memset(max_array, 0, sizeof(max_array));

		for (int j = 0; j < strlen(chunk); j++) {
			
			if (chunk[j] == '-') {
				minimal = false;
				maximal = true;
				i = 0;
				j++;
			}

			if (chunk[j] == ' ') {
				maximal = false;
				j++;
				letter = chunk[j];
				j += 3;
				password = true;
				i = 0;
			}

			if (minimal) {
				min_array[i] = chunk[j];
			}
			if (maximal) {
				max_array[i] = chunk[j];
			}
			if (password) {
				pass_array[i] = chunk[j];
			}
			i++;
		}

		for (int k = 0; k < strlen(pass_array); k++) {
			if (pass_array[k] == letter)
				nb_letter++;
		}

		if ((nb_letter >= atoi(min_array)) && (nb_letter <= atoi(max_array))) {
			nb_pass++;
		}

	}

	printf("%d passwords are correct.", nb_pass);

	fclose(fp);
}