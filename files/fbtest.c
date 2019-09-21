/*
To test that the Linux framebuffer is set up correctly, and that the device permissions
are correct, use the program below which opens the frame buffer and draws a gradient-
filled red square:

retrieved from:
Testing the Linux Framebuffer for Qtopia Core (qt4-x11-4.2.2)

http://cep.xor.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <math.h>

struct timeval stop, start;

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((long int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    x=0;
    y=0;

    char a=0;
	
	int xx=vinfo.xres;
	int yy=vinfo.yres;
	
	
//	struct timespec start, end;
//	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
//	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//	uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

	
    while (1) {

	a++;
	
	gettimeofday(&start, NULL);
//	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
			

    // Figure out where in memory to put the pixel
    for (y = 0; y < yy; y++)
        for (x = 0; x < xx; x++) {

            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = a;        // Some blue
                *(fbp + location + 1) = x + a;
                *(fbp + location + 2) = y - a;
                *(fbp + location + 3) = 0;      // No transparency
        //location += 4;
            } else  { //assume 16bpp
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }

        }
 
	gettimeofday(&stop, NULL);
// 	clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	long tl = stop.tv_usec - start.tv_usec;

 	unsigned int dl;

 	dl = tl * 60;
 	
 	if ( dl  < 0 ) dl = 1;
 	if ( dl  > 10000 ) dl = 10000;
 	
 	
 	fprintf( stdout, "[i] tik        %d - %lu - %d -----\r", a, tl, dl);
	usleep( dl  );
    }

    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
