#define KMED 3
#define KKMED 1 // for 3x3
#define MAX_HEIGHT 800
#define MAX_WIDTH 800

typedef unsigned char pix_t;
pix_t median(pix_t window[KMED*KMED]);
void median_filter_image (pix_t in_pix[MAX_HEIGHT][MAX_WIDTH],
						  pix_t out_pix[MAX_HEIGHT][MAX_WIDTH],
						  short int height,
						  short int width) {

	short int r, c;
	pix_t pix, med, window[KMED*KMED];
	signed char x, y;

	L1:for (r = 0; r < height; r++) {
	#pragma HLS LOOP_TRIPCOUNT min=600 max=1080 avg=720
		L2:for(c = 0; c < width; c++) {
		#pragma HLS LOOP_TRIPCOUNT min=800 max=1920 avg=1280
		#pragma HLS PIPELINE II=1
			if ((r >= KMED-1) && (r < height) &&
				(c >= KMED-1) && (c <= width)	) {
				for (y = -2; y <= 0; y++) {
					for (x = -2; x <= 0; x++) {
						window[(2 + y) * KMED + (2 + x)] = in_pix[r+y][c+y];
					}
					pix = median(window);
				}
			}
			else {
				pix = 0;
			}
			if (r > 0 && c > 0) {
				out_pix[r-KKMED][c-KKMED] = pix;
			}
		}
	}
}


