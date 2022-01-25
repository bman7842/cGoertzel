#include <stdio.h>
#include <stdlib.h>     /* strtof */
#include <string.h>
#include <math.h>
#include "ToneTable.h"
#include "Signals.h"
#include "Settings.h"
#include "BufferManipulation.c"

/* Definitions */
long Goertzel(float *, const int *, float*, unsigned int);
void testFreq();

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
		printf("5. Settings\n");
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
					testFreq();
					break;
			case 5:
					updateSettings();
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

int computeK(float *freq) {
	return (int) (BUFF_SIZE*(*freq))/SAMPLING_RATE;
}

void testFreq() {
	float freq;

	printf("Input frequency: ");
	scanf("%f", &freq);

	int kterm = computeK(&freq);

	float taps[2];
	long squarMag = Goertzel(MAIN_BUFFER, &kterm, &taps[0], BUFF_SIZE);

	printf("Squared magnitude: %ld\n", squarMag);
	char response[4] = "NO";
	if (squarMag>CUTOFF) {
		strcpy(response, "YES");
	}
	printf(" > %ld? %s\n", CUTOFF, response);
}