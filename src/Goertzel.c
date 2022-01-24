#include <stdio.h>
#include <stdlib.h>     /* strtof */
#include <string.h>
#include <math.h>
#include "ToneTable.h"
#include "Signals.h"

#define PI 3.141592653589793
#define SAMPLING_RATE	4000.0	//4kHz
#define BUFF_SIZE	320	//Block size

/* global variables */
float buffer[BUFF_SIZE];

/* Definitions */
long Goertzel(float *, const int *, float*, unsigned int);
void loadBuffer();
void clearBuffer();
void printBuffer();
void saveBuffer();
void addSignal(int);

/* Main loop */
void main() {
	buildTones(); /* Build the tone table */
	clearBuffer();

	int choice;
	int active = 1;

	printf("!------Goertzel Testing------!\n");

	while (active) {
		printf("select from below:\n");
		printf("0. EXIT\n");
		printf("1. Load buffer\n"); /* Load signal into buffer */
		printf("2. Print buffer\n"); /* Load from */
		printf("3. Save buffer\n"); /* TODO!!! */
		printf("4. Test Frequency\n"); /* TODO!!! */ /* Test if a frequency is present */
		printf("!----------------------------!\n");

		printf("Enter: ");
		scanf("%d", &choice);
		printf("!----------------------------!\n");

		switch(choice) {
			case 0:
					active = 0;
					break;
			case 1:
					loadBuffer();
					break;
			case 2:
					printBuffer();
					break;
			case 3:
					saveBuffer();
					break;
			case 4:
					//testFreq();
					break;
			default:
					printf("Invalid response!");
					break;
		}
	}
}

/*
	Taps is equivalent to Q(n-1) is the formula, aka previous term.
	It is initially 0 for the first two calculations
*/
long Goertzel(float *buffer, const int *kterm, float *taps, unsigned int N) {
	float omega = (float) (2 * PI * (*kterm))/N;
	float cr = cos(omega);
	float ci = sin(omega);
	float coeff = 2*cr;
	printf("Coeff: %.6f ", coeff);

	float *sprev = taps; //Q(n-1)
	float *sprev2 = taps+1; //Q(n-2)
	*sprev = 0;
	*sprev2 = 0;

	for (int n = 0; n<N; n++) {
		float s = *buffer + (coeff * (*sprev)) - (*sprev2);
		*sprev2 = *sprev;
		*sprev = s;
		buffer++;
	}

	return (long) abs((*sprev2) * (*sprev) + (*sprev * *sprev) - coeff*(*sprev)*(*sprev2));
}

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

	GenerateWave(&buffer[0], &freq, BUFF_SIZE, SAMPLING_RATE);
	printf("Signal of %.2f Hz added to buffer!\n", freq);
}

void printBuffer() {
	float *buffPtr = &buffer[0];

	printf("BUFFER: ");
	for (int i = 0; i < BUFF_SIZE; i++) {
		printf("%.2f ", *buffPtr);
		buffPtr++;
	}
	printf("\n");
}

void clearBuffer() {
	float *buffPtr = &buffer[0];

	for (int i = 0; i < BUFF_SIZE; i++) {
		*buffPtr = 0.0;
		buffPtr++;
	}
	printf("Buffer cleared!\n");
}

/* TODO: Add audio file support */
/* TODO: Fix file save functionality */
void saveBuffer() {
	char filePath[256]; /*256 char limit*/

	printf("Input file path: ");
	fgets(filePath, sizeof(filePath), stdin);
/*
	FILE *outFile;
	outFile = fopen(&filePath[0], "w");

	char outputTxt[BUFF_SIZE*2 - 1] = "";

	for (int i=0; i<BUFF_SIZE; i++) {
		if (i == BUFF_SIZE-1) {
			fprintf(outFile, "%.2f", buffer[i]);
		} else {
			fprintf(outFile, "%.2f\n", buffer[i]);
		}

	}

	printf(strcat("Saving file to: ", filePath));
	fclose(outFile); */
}