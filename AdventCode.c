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

	char chunk[128], *hcl_field = NULL, hcl_value[6], *pid_field = NULL, pid_value[9]; 
	int nb_passeports = 0, position;
	bool passeport = true, byr = false, iyr = false, eyr = false, hgt = false, hcl = false, ecl = false, pid = false, cid = false;

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		if ((int)chunk[0] == 10) {
			passeport = false;
			printf("oof\n");
		}

		printf("%s", chunk);

		//Check the fields in the passport
		if (strstr(chunk, "byr") != NULL)
			byr = true;
		if(strstr(chunk, "iyr") != NULL)
			iyr=true;
		if(strstr(chunk, "eyr") != NULL)
			eyr=true;
		if(strstr(chunk, "hgt") != NULL)
			hgt=true;
		if (strstr(chunk, "hcl") != NULL) {
			//check if the hair color is valid 
			hcl = true;
			hcl_field = strstr(chunk, "hcl:");
			hcl_field += 4;
			for (int i = 0; i < 6; i++) {
				hcl_value[i] = hcl_field[i];
			}

			if (hcl_value[0] == '#')
				for (int i = 1; i < 6; i++) {
					if ((hcl_value[i] < '0' || hcl_value[i] > '9') && (hcl_value[i] < 'a' || hcl_value[i] > 'f'))
						hcl = false;
				}
			else
				hcl = false;
		}
		if (strstr(chunk, "ecl") != NULL)
			ecl = true;
		if (strstr(chunk, "pid") != NULL) {
			//Check if pid is valid 
			pid = true;
			pid_field = strstr(chunk, "pid:");
			pid_field += 4;
			for (int i = 0; i < 9; i++) {
				pid_value[i] = pid_field[i];
			}

			for (int i = 1; 9; i++) {
				if (pid_field[i] < '0' || pid_field[i] > '9')
					pid = false;
			}
		}
		if (strstr(chunk, "cid") != NULL)
			cid = true;

		if (!passeport) {
			if ((byr & iyr & eyr & hgt & hcl & ecl & pid) || ((byr & iyr & eyr & hgt & hcl & ecl & pid) & !cid)) {
				nb_passeports++;
			}

			printf("Passport end\n");

			passeport = true; byr = false; iyr = false; eyr = false; hgt = false; hcl = false; ecl = false; pid = false, cid = false;
			}
	}
	printf("Passports : %d\n", nb_passeports);


	fclose(fp);
}