#ifndef _median_filter_h_
#define _median_filter_h_
#define MAX_HEIGHT 1080
#define MAX_WIDTH 1920
#define KMED 3
typedef unsigned char pix_t;
void median_filter_image (
		 short int height,
		 short int *width);
pix_t median(pix_t window[KMED*KMED]);

#endif // _median_filter_h_
