#include <tests/exp/file_io.h>
#include <stdio.h>

void readfile() {
	FILE *fp;
	fp  = fopen("files/filename.txt", "r");

	if(!fp) {
		printf("Failed to open the File! \n");
		return;
	}

	char ch;


	while(fscanf(fp, "%c", &ch) != EOF) {
		printf("%c", ch);
	}

	fclose(fp);

	printf("\n");

}


void writefile_n(const char *fn, const char *str) {
	
	FILE *fp;
	fp = fopen(fn, "w");

	if(!fp) {
		printf("Failed to open file! \n");
		return;
	}
	
	fprintf(fp, "%s", str);

	fclose(fp);
}




