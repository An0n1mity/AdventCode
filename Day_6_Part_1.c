#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

	FILE* fp = fopen("input.txt", "r");

	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);

	}

	char chunk[128], answers[27];
	int answer_sum = 0;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		//Check for end of a group
		if ((int)chunk[0] != 10) {

			//Check for one passager answers in the group 
			for (int i = 0; i < strlen(chunk); i++) {
				//Check if it is a valid answer between a - z
				if (chunk[i] <= 'z' && chunk[i] >= 'a')
					// Store answer in an array with alphabetic positionning
					answers[chunk[i] - 'a'] = chunk[i];
			}
		}
		else {
			//Check out how many answers the group had responded
			for (int i = 0; i < 26; i++) {
				if (answers[i] <= 'z' && answers[i] >= 'a')
					answer_sum++;
			}
			//Reset the group answers
			memset(&answers, 0, sizeof(answers));
		}
	}

	//For the last group
	for (int i = 0; i < 26; i++) {
		if (answers[i] <= 'z' && answers[i] >= 'a')
			answer_sum++;
	}

	printf("Sum = %d\n", answer_sum);

	fclose(fp);
}
