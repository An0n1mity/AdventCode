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

								char chunk[128], *hcl_field = NULL, hcl_value[6], *pid_field = NULL, pid_value[9], *byr_field = NULL, byr_value[8], *iyr_field = NULL, iyr_value[8], *eyr_field = NULL, eyr_value[8], *hgt_field = NULL;
								int nb_passeports = 0, position;
								bool passeport = true, byr = false, iyr = false, eyr = false, hgt = false, hcl = false, ecl = false, pid = false, cid = false;

								while (fgets(chunk, sizeof(chunk), fp) != NULL) {
																if ((int)chunk[0] == 13) {
																								passeport = false;
																}

																printf("%s", chunk);

																//Check the fields in the passport
																if (strstr(chunk, "byr") != NULL){
																								byr = true;
																								byr_field = strstr(chunk, "byr");
																								byr_field += 4;
																								for(int i = 0; i < 4; i++){
																									byr_value[i] = byr_field[i];
																								}
																								if (atoi(byr_value) < 1920 || atoi(byr_value) > 2002){
																									byr = false;
																								}
																}
																if(strstr(chunk, "iyr") != NULL){
																								iyr=true;
																								iyr_field = strstr(chunk, "iyr");
																								iyr_field += 4;
																								for(int i = 0; i < 4; i++){
																									iyr_value[i] = iyr_field[i];
																								}
																								if (atoi(iyr_value) < 2010 || atoi(iyr_value) > 2020){
																									iyr = false;
																								}
																}
																if(strstr(chunk, "eyr") != NULL){
																								eyr=true;
																								eyr_field = strstr(chunk, "eyr");
																								eyr_field += 4;
																								for(int i = 0; i < 4; i++){
																									eyr_value[i] = eyr_field[i];
																								}
																								if (atoi(eyr_value) < 2020 || atoi(eyr_value) > 2030){
																									eyr = false;
																								}
																}
																if((strstr(chunk, "hgt") != NULL) && (strstr(chunk, "cm") != NULL || strstr(chunk, "in"))){
																								hgt = true;
																								hgt_field = strstr(chunk, "hgt");
																								hgt_field += 4;

																								// The height is in centimeter
																								if(strstr(chunk, "cm") != NULL){
																									char hgt_value[9];
																									for(int i = 0; i < 3; i++){
																										hgt_value[i] = hgt_field[i];
																									}
																									if (atoi(hgt_value) < 150 || atoi(hgt_value) > 193){
																										hgt = false;
																									}
																								}

																								if(strstr(chunk, "in") != NULL){
																									char hgt_value[8];
																									for(int i = 0; i < 2; i++){
																										hgt_value[i] = hgt_field[i];
																									}
																									if (atoi(hgt_value) < 59 || atoi(hgt_value) > 76){
																										hgt = false;
																									}
																								}
																}
																if (strstr(chunk, "hcl") != NULL) {
																								//check if the hair color is valid
																								hcl = true;
																								hcl_field = strstr(chunk, "hcl");
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
																if ((strstr(chunk, "ecl") != NULL) && (strstr(chunk, "amb") != NULL || strstr(chunk, "blu") != NULL || strstr(chunk, "brn") != NULL || strstr(chunk, "gry") != NULL || strstr(chunk, "grn") != NULL || strstr(chunk, "hzl") != NULL || strstr(chunk, "oth") != NULL))
																								ecl = true;
																if (strstr(chunk, "pid") != NULL) {
																								//Check if pid is valid
																								pid = true;
																								pid_field = strstr(chunk, "pid");
																								pid_field += 4;
																								for (int i = 0; i < 9; i++) {
																																pid_value[i] = pid_field[i];
																								}
																								for (int i = 1; i < 9; i++) {
																																if (pid_value[i] < '0' || pid_value[i] > '9')
																																								pid = false;
																								}
																}

																if (!passeport) {
																								if (byr & iyr & eyr & hgt & hcl & ecl & pid) {
																																nb_passeports++;
																								}

																								printf("Passport end\n");

																								passeport = true; byr = false; iyr = false; eyr = false; hgt = false; hcl = false; ecl = false; pid = false, cid = false;
																}
								}
								printf("Passports : %d\n", nb_passeports);


								fclose(fp);
}
