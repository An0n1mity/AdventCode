#include <stdio.h>
#include <stdlib.h>

int main(void) {

	FILE* fp = fopen("input.txt", "r");

	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);

	}

	char chunk[128], map[32][323];
	int j = 0, x = 0, y = 0, tree = 0;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		for (int i = 0; i < strlen(chunk); i++) {
			map[i][j] = chunk[i];
		}
		j++;
	}

	for (int i = 0; i < 323; i++) {
		x = (x+3) % 31;
		y++;
		if (map[x][y] == '#')
			tree++;
	}

	printf("The answer is %d", tree);

	fclose(fp);
}