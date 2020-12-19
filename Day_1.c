 #include <stdio.h>
 #include <stdlib.h>

int main(void) {
	FILE* fp = fopen("input_one.txt", "r");
	int nb_array[1000];
	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);

	}

	char chunk[128];
	int i = 0, res = 0;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		nb_array[i]  = atoi(chunk);
		i++;
	}

	for (int j = 0; j < i; j++) {
		for (int k = 0; k < i; k++) {
			for (int l = 0; l < i; l++) {
				if (nb_array[j] + nb_array[k] + nb_array[l] == 2020)
					res = nb_array[j] * nb_array[k] * nb_array[l];
			}
		}
	}
	printf("The result is %d", res);

	fclose(fp);
}
