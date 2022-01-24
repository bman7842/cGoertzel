

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

/*
	Reads in a text file where each line represents a timepoint
*/
void readTextFile(float *buffer, char* filename, int lines) {
	FILE *fp = fopen(filename, "r");

	char line[256];
	for (int i = 0; i<lines; i++) {
		fgets(line, sizeof(line), fp);
		*buffer = atof(line);
		buffer++;
	}

	fclose(fp);
}

/* TODO: Read in audio file and convert to buffer */