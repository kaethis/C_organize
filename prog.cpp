#include <ctype.h>
#include <cstring>
#include <dirent.h>
#include <errno.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


const char  *RUN_ARG = "RUN";


std::string  prog_name;


static int organize(){

	struct dirent  *dir_p;

	DIR  *dir_curr, *dir_sub, *dir_tmp;


	string  cmd;


	errno = 0;

	dir_curr = opendir(".");

	if(errno != 0)
		return -1;


	while((dir_p = readdir(dir_curr)) != NULL){

		errno = 0;


		dir_tmp = opendir(dir_p->d_name);

		if((errno != 0) && (strcmp(dir_p->d_name, prog_name.c_str()) != 0)){

			string  dir_name;

			dir_name += toupper(dir_p->d_name[0]);


			cmd = "mkdir ";

			if(isalpha(dir_p->d_name[0]) || isdigit(dir_p->d_name[0])){

				errno = 0;


				dir_sub = opendir(dir_name.c_str());

				if(dir_sub == NULL){

					cmd += dir_name[0];

					system(cmd.c_str());
				}


				cmd = "mv \"";

				cmd += dir_p->d_name;
				cmd += "\" \"./";
				cmd += dir_name;
				cmd += "/";
				cmd += dir_p->d_name;
				cmd += "\"";


				system(cmd.c_str());
			}
		}
	}


	return 0;
}


int main(int argc, char *argv[]){

	prog_name = argv[0];

	prog_name = prog_name.substr(2, prog_name.length()-2);


	printf(" _   _   __           ___ __  _ \n");
	printf("/ \\ |_) /__  /\\  |\\ |  |   / |_ \n");
	printf("\\_/ | \\ \\_| /--\\ | \\| _|_ /_ |_ \n");
	printf("-------------------------------\n");

	if((argc < 2) || (strcmp(argv[1], RUN_ARG))){

		fprintf(stderr, "ORGANIZE sorts ALL files in the\n");
		fprintf(stderr, " CURRENT WORKING DIRECTORY into\n");
		fprintf(stderr, " alphanumeric sub-directories.\n");

		return -1;
	}


	if(organize() != 0){

		fprintf(stderr, "AN ERROR OCCURED!\n/");

		return -1;
	}


	printf("                      COMPLETE!\n");
	


	return 0;
}
