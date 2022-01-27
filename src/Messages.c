#define WIDTH	30

/*
	Declarations
*/
int strLength(char*);

char* createStrDivide(char * header) {
	char *divider = (char*) malloc((WIDTH+2)*sizeof(char));
	char *strPtr = divider;

	int i=0;
	int headerStartIndex = WIDTH/2 - strLength(header)/2;

	for (i; i<headerStartIndex; i++) {
		if (i==0 || i==(WIDTH-1)) {
			*strPtr = '!';
		} else {
			*strPtr = '-';
		}
		strPtr++;
	}

	while(*header != '\0') {
		*strPtr = *header;
		header++;
		strPtr++;
		i++;
	}

	for (i; i<WIDTH; i++) {
		if (i==0 || i==(WIDTH-1)) {
			*strPtr = '!';
		} else {
			*strPtr = '-';
		}
		strPtr++;
	}

	*strPtr = '\n';
	*(strPtr+1) = '\0';

	return &divider[0];
}

/*
	Computes length of string
*/
int strLength(char * inStr) {
	int length = 0;

	while(*inStr != '\0') {
		inStr++;
		length++;
	}

	return length;
}