#include "DataStruct.c"

void buildTones(){
	install('A', 312.6);
	install('B', 346.7);
	install('C', 384.6);
	install('D', 426.6);
	install('E', 473.2);
	install('F', 524.8);
	install('G', 582.1);
	install('H', 645.7);
	install('J', 716.1);
	install('K', 794.3);
	install('L', 881.0);
	install('M', 977.2);
	install('P', 1083.9);
	install('Q', 1202.3);
	install('R', 1333.0);
	install('S', 1479.1);
}

float getFreq(char c) {
	return lookup(c)->freq;
}