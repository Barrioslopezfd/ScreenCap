#include <X11/Xutil.h>
#include <stdlib.h>
#include <time.h>
#include <png.h>

int main(void) 
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "error opening display\n");
        exit(1);
    }

    int screen = XDefaultScreen(display);
	Window win = XRootWindow(display, screen);

    XWindowAttributes attrs;
    XGetWindowAttributes(display, win, &attrs);
    int w = attrs.width;
    int h = attrs.height;
    printf("Screen width is %d\nScreen height is %d\n", w, h);

    XImage *img = XGetImage(display, win, 0, 0, w, h, AllPlanes, ZPixmap);
    if (img == NULL) {
        fprintf(stderr, "Error getting XImage\n");
        exit(1);
    }

    char filename[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(filename, sizeof(filename), "%y-%m-%d-%H-%M-%S.png", t);
    char filepath[300];
    snprintf(filepath, sizeof(filepath), "screenshots/%s", filename);
    printf("Saving file to %s\n", filepath);

    FILE *f = fopen(filepath, "wb");
    if (f == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(f);
        fprintf(stderr, "Error creating png pointer\n");
        exit(1);
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(f);
        fprintf(stderr, "Error creating info pointer\n");
        exit(1);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(f);
        fprintf(stderr, "Error creating info pointer\n");
        exit(1);
    }

    png_init_io(png_ptr, f);

    png_set_IHDR(png_ptr, info_ptr, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    png_bytep *row_pointers = malloc(sizeof(png_bytep) * h);
    if (!row_pointers) {
        fprintf(stderr, "Error allocating memory for row pointers\n");
        exit(1);
    }

    for (int y = 0; y < h; y++) {
        row_pointers[y] = malloc(3 * w * sizeof(png_byte));
        if (!row_pointers[y]) {
            fprintf(stderr, "Error allocating memory for row %d\n", y);
            exit(1);
        }
        for (int x = 0; x < w; x++) {
            unsigned long pixel = XGetPixel(img, x, y);
            unsigned char r = (pixel >> 16) & 0xFF;
            unsigned char g = (pixel >> 8) & 0xFF;
            unsigned char b = pixel & 0xFF;
            row_pointers[y][x * 3 + 0] = r;
            row_pointers[y][x * 3 + 1] = g;
            row_pointers[y][x * 3 + 2] = b;
        }
    }

    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);

    for (int y = 0; y < h; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(f);

    XDestroyImage(img);
    XCloseDisplay(display);

    exit(0);
}
