#include <stdio.h>
#include <string.h>
#include <ctype.h>

int IsPwOk(char * pw, int size_of_pw){
    char password[8];
    memcpy(password, pw, size_of_pw/2);
    return 0 == strcmp(password, "1312");
}

/* This function converts hex string to ascii string
** Example: input=32334142 output=23AB
** Warning: Do not give any string that contains 00
*/
void hexToAscii(char *passInHex){
	char temp[3];
	char ch;
	int num;
	int i;
	for(i = 0; i < strlen(passInHex); i = i + 2){
		temp[0] = passInHex[i];
		temp[1] = passInHex[i + 1];
		temp[2] = '\0';
		sscanf(temp, "%x", &num);
		ch = num;
		passInHex[i / 2] = ch;
	}
	passInHex[i / 2] = '\0';

}

/* int isalnum(char c) function is inside ctype.h library.
** It checks if character is alphanumeric or not.
*/
void readFileIfPermitted(const char *fileName, const char *logFileName){
	printf("Reading the file : %s\n", fileName);
	if(isalnum(fileName[0]) || isalnum(logFileName[0])){
		FILE *filePointer;
		int c;
		filePointer = fopen(fileName, "r");

		if(filePointer == NULL){
			FILE *logFile;
			logFile = fopen(logFileName, "w");
			fprintf (logFile, "An unauthorized access attempt has occurred.");
			printf("Error recorded in log file.");
		}
		while ((c = fgetc(filePointer)) != EOF){
			printf("%c", (char)c);
		}

		fclose(filePointer);
	}
	else{
		printf("Invalid filename has been entered.");
	}

	return;
}

int main(int argc, char **argv){
	int admin_priv = 0;
	int admin_pw_check = 0;
	int size_of_argv = strlen(argv[1]);


	hexToAscii(argv[1]);
	admin_pw_check = IsPwOk(argv[1], size_of_argv);
	if (!admin_pw_check) {
		printf("Admin password is not accepted.\n");
	}
	else {
		printf("Admin password is accepted.\n");
		admin_priv = 1;
	}

	if(admin_priv == 1){
		char fn[20], ln[20];
		printf("Please enter the file name to read. ");
		scanf("%s", fn);
		printf("Please enter the log file to write, in case an unauthorized access is attempted. ");
		scanf("%s", ln);
		readFileIfPermitted(fn, ln);
	}    
	else{
		printf("You are not authorized. \n");
	}
}
