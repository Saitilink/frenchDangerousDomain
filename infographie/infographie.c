#include <stdio.h>
#include <stdlib.h>

const int MAX_SCALE = 256;

typedef struct s {
    int width;
    int height;
    int depth;
    double *data;
} surface;

void initSurface(surface *s, int width, int height, int depth) {
    s->data = malloc(width * height * sizeof(double));
    if (s->data == NULL) return;

    s->depth = depth;
    s->width = width;
    s->height = height;
}

void freeSurface(surface *s) {
    free(s->data);
}

void fillSurface(surface *s, int value) {
    for (int i = 0; i < s->width * s->height; ++i)
        s->data[i] = value;
}

int readPGM(surface *s, FILE *f) {
    if (fgetc(f) != 'P') return 0;
    if (fgetc(f) != '2') return 0;
    if (fgetc(f) != '\n') return 0;

    char c;
    while ((c = fgetc(f)) == '#')
        while (fgetc(f) != '\n');
    ungetc(c, f);

    int width, height, depth;
    if (fscanf(f, "%d%d%d", &width, &height, &depth) != 3) return 0;

    initSurface(s, width, height, depth);
    if (s->data == NULL) return 0;

    for (int i = 0; i < width * height; ++i) {
        int value;
        if (fscanf(f, "%d", &value) != 1) {
            freeSurface(s);
            return 0;
        }

        s->data[i] = value / (double)depth;
    }

	return 1;
}

int writePGM(surface *s, FILE *f) {
    int count = fprintf(f, "P2\n# writePGM\n%d %d\n%d\n", s->width, s->height, s->depth);

    int cr = s->width;
    for (int i = 0; i < s->width * s->height; ++i) {
		int val = s->data[i] * s->depth;
		if (val < 0) val = 0;
		else if (val > s->depth) val = s->depth;

        count += fprintf(f, "%d", val);

        if (--cr) count += fprintf(f, " ");
        else {
            cr = s->width;
            count += fprintf(f, "\n");
        }
    }

    return count;
}
/*
int doubleSize(surface *s) {
    surface new_s;
    initSurface(&new_s, s->width * 2, s->height * 2,   s->depth);
    if (new_s.data == NULL) return 0;

    for (int i = 0; i < s->width * s->height; ++i) {
        double val = s->data[i];

        int j = 2 * i + (i / s->width) * new_s.width;

        double val_1 = i % s->width == s->width - 1 ? s->data[i] : s->data[i+1];
        double val_2 = i / s->width == s->height - 1 ? s->data[i] : s->data[i+s->width];

        new_s.data[j] = val;
        new_s.data[j + 1] = (val+val_1)/2;
        new_s.data[j + new_s.width] = (val+val_2)/2;
        new_s.data[j + new_s.width + 1] = (val_1+val_2)/2;
    }

    freeSurface(s);
    *s = new_s;

    return 1;
}
*/
int main() {
	FILE *input = fopen("img.pgm", "r");
	if (input == NULL) { 
		printf("Failed to open the input file.\n");
		return 1;
	}

    surface img;
    if (!readPGM(&img, input)) {
        printf("Failed to read the input file.\n");
        return 2;
    }

	fclose(input);

    doubleSize(&img);

    FILE *output = fopen("output.pgm", "w");
    if (output == NULL) {
        printf("Failed to open the output file.\n");
        return 3;
    }

    writePGM(&img, output);

    freeSurface(&img);
    fclose(output);

    printf("Successfully written the image.\n");
    return 0;
}