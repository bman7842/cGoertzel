float *MAIN_BUFFER;


void addSignal();
void clearBuffer();
void printBuffer();
void saveBuffer();

void loadBuffer() {
	int choice;
	int active = 1;

	while(active) {
		printf("!-------Buffer Loading-------!\n");
		printf("select from below:\n");
		printf("0. BACK\n");
		printf("1. Clear\n");
		printf("2. Add Letter\n");
		printf("3. Add Frequency\n");
		printf("4. Load from .txt\n"); /* TODO!!! */
		printf("5. Load from audio file\n"); /* TODO!!! */
		printf("!----------------------------!\n");

		printf("Enter: ");
		scanf("%d", &choice);
		printf("!----------------------------!\n");

		switch(choice) {
			case 0:
					active = 0;
					break;
			case 1:
					clearBuffer();
					break;
			case 2:
					addSignal(1);
					break;
			case 3:
					addSignal(0);
					break;
			default:
					printf("Invalid response!");
					break;
		}
	}
}

/* 
	mode = 0; frequency input 
	mode = 1; letter input
*/
void addSignal(int mode) {
	float freq;

	if (mode) {
		char letter;
		printf("Input a letter: ");
		scanf(" %c", &letter);
		freq = getFreq(letter);
	} else {
		printf("Input a frequency: ");
		scanf("%f", &freq);
	}

	GenerateWave(MAIN_BUFFER, &freq, DEFAULT_BUFF_SIZE, SAMPLING_RATE);
	printf("Signal of %.2f Hz added to buffer!\n", freq);
}

void clearBuffer() {
	free(MAIN_BUFFER);

	MAIN_BUFFER = (float*)calloc(BUFF_SIZE, sizeof(float));
	printf("Buffer cleared!\n");
}

void printBuffer() {
	float *tmpPtr = MAIN_BUFFER;

	printf("BUFFER: ");
	for (int i = 0; i < DEFAULT_BUFF_SIZE; i++) {
		printf("%.2f ", *tmpPtr);
		tmpPtr++;
	}
	printf("\n");
}

/* TODO: Add audio file support */
/* TODO: Fix file save functionality */
void saveBuffer() {
	char filePath[257]; /*256 char limit*/

	gets(filePath); /* Clear input */
	printf("Input file path: ");
	gets(filePath);

	FILE *outFile;
	outFile = fopen(&filePath[0], "w");
	float *tmpPtr = MAIN_BUFFER;

	char outputTxt[DEFAULT_BUFF_SIZE*2 - 1] = "";

	for (int i=0; i<DEFAULT_BUFF_SIZE; i++) {
		if (i == DEFAULT_BUFF_SIZE-1) {
			fprintf(outFile, "%.2f", *tmpPtr);
		} else {
			fprintf(outFile, "%.2f\n", *tmpPtr);
		}
		tmpPtr++;

	}
	printf("Success");
	char msg[] = "Saving file to: ";
	strcat(msg, filePath);
	printf(msg);
	fclose(outFile);
}