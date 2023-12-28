#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef float sample[3];

// OR gate
sample train_or[] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

// AND gate
sample train_and[] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1}
};

// NAND gate
sample train_nand[] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

sample *train = train_and;
size_t train_count = 4;

// #define train_count (sizeof(train)/sizeof(train[0]))

float sigmoidf(float x) {
	return 1.f / (1.f + expf(-x));
}


float rand_float(void) {
	return (float) rand() / (float) RAND_MAX;
}



float cost(float w1, float w2, float b) {
	float result = 0;

	for (size_t i = 0; i < train_count; ++i) {
		float x1 = train[i][0];
		float x2 = train[i][1];
		float y  = sigmoidf(x1*w1 + x2*w2 + b);
		float d  = y - train[i][2];
		result += d*d;
	}

	return result /= train_count;
}


int main(void) {

	srand(time(0));

	float w1 = rand_float()*10 - 5;
	float w2 = rand_float()*10 - 5;
	float b = rand_float()*10 - 5;

	float eps = 1e-1;
	float rate = 1e+1;

	for (int i = 0; i < 100*1000; i++) {
		float c = cost(w1, w2, b);
		// printf("w1: %f w2: %f b: %f cost: %f\n", w1, w2, b, c);
		// printf("%f\n", c);
		float dw1 = (cost(w1 + eps, w2, b) - c)/eps;
		float dw2 = (cost(w1, w2 + eps, b) - c)/eps;
		float db = (cost(w1, w2, b + eps) - c)/eps;

		w1 -= rate*dw1;
		w2 -= rate*dw2;
		b  -= rate*db;
	}

	// printf("w1: %f w2: %f cost: %f\n", w1, w2, cost(w1, w2, b));


	for (size_t i = 0; i < train_count; ++i) {
		float x1 = train[i][0];
		float x2 = train[i][1];
		float y = sigmoidf(x1*w2 + x2*w2 + b);
		printf("%f ----- %f\n", y, train[i][2]);
	}

	return 0;
}
