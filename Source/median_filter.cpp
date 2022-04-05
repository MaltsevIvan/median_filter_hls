#define MIN(x, y) ( (x) < (y) ? (x) : (y) )
#define MAX(x, y) ( (x) < (y) ? (y) : (x) )
#define KMED 3

typedef unsigned char pix_t;

pix_t median(pix_t window[KMED*KMED]) {
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_RESHAPE variable=window complete dim=1

	int const N = KMED * KMED;
	pix_t t[N], z[N];
	char i, k, stage;

	for (i=0; i < KMED*KMED; i++) {
		z[i] = window[i];
	}

	// network sorting
	for (stage = 1; stage <= N; stage++) {

		if ((stage % 2) == 1) k=0;
		else k=1;

		for (i = k; i < N-1; i = i + 2) {
			t[i] = MIN(z[i], z[i+1]);
			t[i+1] = MAX(z[i], z[i+1]);
			z[i] = t[i];
			z[i+1] = t[i+1];
		}
	}

	return z[N/2];
}
