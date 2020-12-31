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

	char chunk[128], answers[27], common_answers[27];
	int answer_sum = 0;
	bool first_passenger = true;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		//Check for end of a group
		if ((int)chunk[0] != 10) {

			//Check for one passager answers in the group 
			for (int i = 0; i < strlen(chunk); i++) {
				//Check if it is a valid answer between a - z
				if (chunk[i] <= 'z' && chunk[i] >= 'a') {
					// Store answer in an array with alphabetic positionning
					answers[chunk[i] - 'a'] = chunk[i];
					// Store the answers of the first group passenger
					if (first_passenger)
						common_answers[chunk[i] - 'a'] = chunk[i];
				}
			}

			first_passenger = false;

				// Check if passenger have common answers
				for (int i = 0; i < 27; i++) {
					if (answers[i] != common_answers[i]) {
						common_answers[i] = '0';
					}
				}

				memset(&answers, 0, sizeof(answers));

		}

		//End of a group
		else {

			//Check out how many answers the group had responded
			for (int i = 0; i < 27; i++) {
				if (common_answers[i] <= 'z' && common_answers[i] >= 'a') {
					answer_sum++;
				}
			}

			//Reset the common answers
			memset(&common_answers, 0, sizeof(common_answers));


			first_passenger = true;
		}

	}
	
	for (int i = 0; i < 27; i++) {
		if (common_answers[i] <= 'z' && common_answers[i] >= 'a') {
			answer_sum++;
		}
	}

	printf("Sum = %d\n", answer_sum);

	fclose(fp);
}
