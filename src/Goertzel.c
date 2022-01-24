#include <stdio.h>
#include <stdlib.h>     /* strtof */
#include <string.h>
#include <math.h>
#include "ToneTable.h"

#define PI 3.141592653589793
#define SAMPLING_RATE	4000.0	//4kHz
#define BLOCK_SIZE	320	//Block size

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

void main() {
	buildTones(); /* Build the tone table */

	printf("A: %.1f", getFreq('F'));
}