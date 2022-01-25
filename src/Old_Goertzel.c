#include <stdio.h>
#include <stdlib.h>     /* strtof */
#include <string.h>
#include <math.h>

#define PI 3.141592653589793
#define SAMPLING_RATE	4000.0	//4kHz
#define TARGET_FREQUENCY	794.3	//384.6 Hz
#define BLOCK_SIZE	320	//Block size
#define TEST_FACTOR	5 // How large of increments test intervals are

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
	float *sprev2 = taps+1;
	*sprev = 0;
	*sprev2 = 0;

	for (int n = 0; n<N; n++) {
		//printf("Q(%d) sprev: %.6f\n", n, *sprev);
		//printf("Q(%d) sprev2: %.6f\n", n, *sprev2);
		float s = *buffer + (coeff * (*sprev)) - (*sprev2);
		*sprev2 = *sprev;
		*sprev = s;
		buffer++;
		//printf("Q(%d): %.6f\n", n, s);
	}

	return (long) abs((*sprev2) * (*sprev) + (*sprev * *sprev) - coeff*(*sprev)*(*sprev2));
}

void Generate(float *buffer, float freq, int N, float sampleRate)
{
  float step = (freq * 2.0 * PI) / sampleRate;
  printf("FREQUENCY: %.6f\n", freq);
  printf("SAMPLERATE: %.6f\n", sampleRate);
  printf("STEP: %.6f\n", step);

  /* Generate the test data */
  for (int index = 0; index < N; index++)
  {
    *buffer = (100.0 * sin((float)index * step) + 100.0);
    buffer++;
  }
}

void readWaveFile(float *buffer, char* filename, int lines) {
	FILE *fp = fopen(filename, "r");

	char line[256];
	for (int i = 0; i<lines; i++) {
		fgets(line, sizeof(line), fp);
		*buffer = atof(line);
		buffer++;
	}

	fclose(fp);
}

void main() {
	float taps[2];
	float buffer[BLOCK_SIZE];
	char filename[] = "test_wave.txt";
	readWaveFile(&buffer[0], &filename[0], BLOCK_SIZE);

	/* For displaying buffer
	for (int i = 0; i<BLOCK_SIZE; i++) {
		printf("%.6f ", buffer[i]);
	}*/
	printf("Testing with test_wave.txt");

	for (float testFreq = TARGET_FREQUENCY-(4*TEST_FACTOR); testFreq <= TARGET_FREQUENCY + (4*TEST_FACTOR); testFreq += TEST_FACTOR) {
		int kterm = 0.5 + ((BLOCK_SIZE*(testFreq))/SAMPLING_RATE);
		printf("KTERM: %d ", kterm);
		long result = Goertzel(&buffer[0], &kterm, &taps[0], BLOCK_SIZE);
		printf("Testing frequency: %.6f. Result: %ld\n", testFreq, result);
	}

	float TEST_FREQUENCY = 222;
	printf("Testing with test frequency: %.2f", TEST_FREQUENCY);

	Generate(&buffer[0], TEST_FREQUENCY, BLOCK_SIZE, SAMPLING_RATE);
	for (float testFreq = TEST_FREQUENCY-(4*TEST_FACTOR); testFreq <= TEST_FREQUENCY + (4*TEST_FACTOR); testFreq += TEST_FACTOR) {
		int kterm = 0.5 + ((BLOCK_SIZE*(testFreq))/SAMPLING_RATE);
		printf("KTERM: %d ", kterm);
		long result = Goertzel(&buffer[0], &kterm, &taps[0], BLOCK_SIZE);
		printf("Testing frequency: %.6f. Result: %ld\n", testFreq, result);
	}
}