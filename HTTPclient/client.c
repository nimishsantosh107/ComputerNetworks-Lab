#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char command[100] = "curl ";
	system(strcat(command, argv[1]));
	return 0;
}