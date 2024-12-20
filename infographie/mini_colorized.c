#include <stdio.h>
#include <stdlib.h>

// const int MAX_DEPTH = 255;

typedef struct {
    int width;
    int height;
    int depth;
    double *data;
} surface;

void initSurface(surface *s, int width, int height, int depth) {
    s->data = malloc(3 * width * height * sizeof(double));
    if (s->data == NULL) return;

    s->depth = depth;
    s->width = width;
    s->height = height;
}

void freeSurface(surface *s) {
    free(s->data);
}

void fillSurface(surface *s, int value) {
    for (int i = 0; i < 3 * s->width * s->height; ++i)
        s->data[i] = value;
}

int capValue(int val, int min, int max) {
    return val > max ? max
                     : val < min ? min
                                 : val;
}

int readPGM(surface *s, FILE *f) {
    if (fgetc(f) != 'P') return 0;
    if (fgetc(f) != '3') return 0;
    if (fgetc(f) != '\n') return 0;

    char c;
    while ((c = fgetc(f)) == '#')
        while (fgetc(f) != '\n');
    ungetc(c, f);

    int width, height, depth;
    if (fscanf(f, "%d %d %d", &width, &height, &depth) != 3) return 0;

    initSurface(s, width, height, depth);
    if (s->data == NULL) return 0;

    for (int i = 0; i < width * height; ++i) {
        int r, g, b;
        if (fscanf(f, "%d %d %d", &r, &g, &b) != 3) {
            freeSurface(s);
            return 0;
        }

        s->data[3 * i    ] = r / (double)depth;
        s->data[3 * i + 1] = g / (double)depth;
        s->data[3 * i + 2] = b / (double)depth;
    }

	return 1;
}

int writePGM(surface *s, FILE *f) {
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n", s->width, s->height, s->depth);

    int cr = s->width;
    for (int i = 0; i < s->width * s->height; ++i) {
        count += fprintf(
            f, "%d %d %d",
            capValue(s->depth * s->data[3 * i    ], 0, s->depth),
            capValue(s->depth * s->data[3 * i + 1], 0, s->depth),
            capValue(s->depth * s->data[3 * i + 2], 0, s->depth)
        );

        if (--cr) count += fprintf(f, " ");
        else {
            cr = s->width;
            count += fprintf(f, "\n");
        }
    }

    return count;
}

int doubleSize(surface *s) {
    surface new_s;
    initSurface(&new_s, s->width * 2, s->height * 2, s->depth);
    if (new_s.data == NULL) return 0;

    for (int i = 0; i < s->width * s->height; ++i) {
        double r = s->data[3 * i    ],
               g = s->data[3 * i + 1],
               b = s->data[3 * i + 2];

        int j = 2 * i + (i / s->width) * new_s.width;

        /* double val_1 = i % s->width == s->width - 1 ? s->data[i] : s->data[i+1];
        double val_2 = i / s->width == s->height - 1 ? s->data[i] : s->data[i+s->width];

        new_s.data[j] = val;
        new_s.data[j + 1] = (val+val_1)/2;
        new_s.data[j + new_s.width] = (val+val_2)/2;
        new_s.data[j + new_s.width + 1] = (val_1+val_2)/2; */

        new_s.data[j    ] = r;
        new_s.data[j + 1] = g;
        new_s.data[j + 2] = b;
    }

    freeSurface(s);
    *s = new_s;

    return 1;
}


void FPB( surface *in,FILE *f){
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n", in->width, in->height, in->depth);
    int cr = in->width;
    

    for(int k=in->width +1;k<=in->width*(in->height-1);k++){
            count += fprintf(
            f, " %d %d %d", ((in->data[3 *(k-in->width-1)]
            +
            in->data[3 *(k-in->width)]
            +
           in->data[3 *(k-in->width+1)]
            +
           in->data[3 *(k- 1)]
           +
           in->data[3*k]
            +
            in->data[3 * (k +1)]
            +
            in->data[3 * (k+in->width-1)]
            +
           in->data[3 * (k +in->width)]
            +
            in->data[3 * (k +in->width+1)])/9,
           (in->data[3 * (k -in->width-1)+1]
            +
            in->data[3 *(k -in->width)+1]
            +
            in->data[3 *(k -in->width+1)+1]
            +
            in->data[3 *(k - 1)+1]
            +
            in->data[3*k+1]
            +
           in->data[3 * (k +1)+1]
            +
            in->data[3 * (k+in->width-1)+1]
            +
           in->data[3 * (k +in->width)+1]
            +
            in->data[3 * (k +in->width+1)+1])/9,
            (in->data[3 * (k -in->width-1)+2]
            +
            in->data[3 *(k -in->width)+2]
            +
            in->data[3 *(k -in->width+1)+2]
            +
            in->data[3 *(k - 1)+2]
            +
            in->data[3*k+2]
            +
            in->data[3 * (k +1)+2]
            +
           in->data[3 * (k+in->width-1)+2]
            +
            in->data[3 * (k +in->width)+2]
            +
            in->data[3 * (k +in->width+1)+2])/9));
    }






}
















int main() {
	FILE *input = fopen("img.ppm", "r");
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

    // doubleSize(&img);

    FILE *output = fopen("sortie.ppm", "w");
    if (output == NULL) {
        printf("Failed to open the output file.\n");
        return 3;
    }

    FPB(&img, output);

    freeSurface(&img);
    fclose(output);

    printf("Successfully written the image.\n");
    return 0;
}