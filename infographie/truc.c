// -----------------------------------
// AJOUT DU SUPPORT DES COULEURS 25/09
// -----------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** surface de dessin
 */

struct Surface
{
    int width;         ///<. 1 argeur
    int height;        ///< hauteur
    double *r, *v, *b; ///< pixels composante
};

typedef struct Surface SURFACE;

/** alloue une surface
 * @param s surfacé a c onstruire
 * @param width lai~geur de la Su rfac e, a ~llouer
 * @param height hauceur de ln .s11 r fil o-~ a allouer 1
 */
void surface(SURFACE *s, int width, int height)
{
    s->r = (double *)malloc(width * height * sizeof(double));
    s->v = (double *)malloc(width * height * sizeof(double));
    s->b = (double *)malloc(width * height * sizeof(double));
    if (s->r != NULL && s->v != NULL && s->b != NULL)
    {
        s->width = width;
        s->height = height;
    }
}

/** desalloue une surface
 * @param s surface à detruire
 */
void _surface(SURFACE *s)
{
    free(s->r);
    free(s->v);
    free(s->b);
}

/** remplit une surface avec une valeur
 * @param s surface a remplir
 * @param value valeur de remplissage
 */
void fill(SURFACE *s, double value)
{
    for (double *ir = s->r, *iv = s->v, *ib = s->b, *e = s->r + s->width * s->height; ir != e; ++ir, ++iv, ++ib)
    {
        *ir = value;
        *iv = value;
        *ib = value;
    }
}

int iclamp(int nb, int min, int max)
{
    int value;
    if (nb > max)
    {
        value = max;
    }
    else if (nb < min)
    {
        value = min;
    }
    else
    {
        value = nb;
    }

    return value;
}

/** ecrit une surface sur un flot de sortie, au format PGM
 * @param s surface a ecrire
 * @param f flot de sortie
 * @return le nombre de caracteres sortis
 */
int ppm_write(SURFACE *s, FILE *f)
{
    int max = 255;
    int count = fprintf(f, "P3\n#_png_write\n%d %d\n%d\n", s->width, s->height, max);
    int cr = s->width;
    for (double *ir = s->r, *iv = s->v, *ib = s->b, *e = s->r + s->width * s->height; ir != e; ++ir, ++iv, ++ib)
    {
        count += fprintf(f, "%d %d %d", iclamp(*ir * max, 0, max), iclamp(*iv * max, 0, max), iclamp(*ib * max, 0, max));
        if (--cr)
            count += fprintf(f, "\n");
        else
        {
            cr = s->width;
            count += fprintf(f, "\n");
        }
    }
    return count;
}

/** lit, vers une surface, une image au format PGM sur un flot d'entree
 * @param s surface a initialiser
 * @param f flot d'entree
 * @return 0 en cas de probleme, 1 si la lecture s'est bien terminee
 */
int ppm_read(SURFACE *s, FILE *f)
{
    if (fgetc(f) != 'P')
        return 0;
    if (fgetc(f) != '3')
        return 0;
    if (fgetc(f) != '\n')
        return 0;
    char c;
    while ((c = fgetc(f)) == '#')
        while (fgetc(f) != '\n')
            ;

    ungetc(c, f);
    int width, height, max;
    if (fscanf(f, "%d%d%d", &width, &height, &max) != 3)
        return 0;
    SURFACE surf;
    surface(&surf, width, height);
    if (surf.r == NULL || surf.v == NULL || surf.b == NULL)
        return 0;
    for (double *ir = surf.r, *iv = surf.v, *ib = surf.b, *e = surf.r + surf.width * surf.height; ir != e; ++ir, ++iv, ++ib)
    {
        int valueR, valueV, valueB;
        if (fscanf(f, "%d %d %d", &valueR, &valueV, &valueB) != 3)
        {
            _surface(&surf);
            return 0;
        }
        *ir = (double)valueR / max;
        *iv = (double)valueV / max;
        *ib = (double)valueB / max;
    }
    *s = surf;
    return 1;
}

int ppm_rectangle(SURFACE *s, int x1, int y1, int x2, int y2, int couleur[3])
{

    int max = 255;
    if (x1 < 0 || x1 > max || x2 < 0 || x2 > max || y1 < 0 || y1 > max || y2 < 0 || y2 > max)
    {
        return -1;
    }
    double *ir, *ib, *iv;
    if (s->r == NULL || s->v == NULL || s->b == NULL)
        return 0;
    for (int i = 0; i < x2 - x1; i++)
    {
        for (int j = 0; j < y2 - y1; j++)
        {
            ir = s->r + x1 + i + (s->width * (y1 + j));
            *ir = (double)couleur[0] / max;
            iv = s->v + x1 + i + (s->width * (y1 + j));
            *iv = (double)couleur[1] / max;
            ib = s->b + x1 + i + (s->width * (y1 + j));
            *ib = (double)couleur[2] / max;
        }
    }

    return 1;
}

void FPB(SURFACE *in, SURFACE *out)
{
    int max = 255;
    double moyenne[3], nb;
    for (int i = 0; i < in->height; i++)
    {
        for (int j = 0; j < in->width; j++)
        {
            nb = 0;
            // remose à zero de moyenne
            for (int ite = 0; ite < 3; ite++)
            {
                moyenne[ite] = 0;
            }

            if (i - 1 >= 0)
            {
                if (j - 1 >= 0)
                {
                    nb++;
                    moyenne[0] += *(in->r + (in->width * (i - 1) + j - 1));
                    moyenne[1] += *(in->v + (in->width * (i - 1) + j - 1));
                    moyenne[2] += *(in->b + (in->width * (i - 1) + j - 1));
                }
                if (j + 1 < in->width)
                {
                    nb++;
                    moyenne[0] += *(in->r + (in->width * (i - 1) + j + 1));
                    moyenne[1] += *(in->v + (in->width * (i - 1) + j + 1));
                    moyenne[2] += *(in->b + (in->width * (i - 1) + j + 1));
                }

                nb++;
                moyenne[0] += *(in->r + (in->width * (i - 1) + j));
                moyenne[1] += *(in->v + (in->width * (i - 1) + j));
                moyenne[2] += *(in->b + (in->width * (i - 1) + j));
            }
            if (i + 1 < in->height)
            {
                if (j - 1 >= 0)
                {
                    nb++;
                    moyenne[0] += *(in->r + (in->width * (i + 1) + j - 1));
                    moyenne[1] += *(in->v + (in->width * (i + 1) + j - 1));
                    moyenne[2] += *(in->b + (in->width * (i + 1) + j - 1));
                }
                if (j + 1 < in->width)
                {
                    nb++;
                    moyenne[1] += *(in->v + (in->width * (i + 1) + j + 1));
                    moyenne[0] += *(in->r + (in->width * (i + 1) + j + 1));
                    moyenne[2] += *(in->b + (in->width * (i + 1) + j + 1));
                }

                nb++;
                moyenne[0] += *(in->r + (in->width * (i + 1) + j));
                moyenne[1] += *(in->v + (in->width * (i + 1) + j));
                moyenne[2] += *(in->b + (in->width * (i + 1) + j));
            }

            if (j - 1 >= 0)
            {
                nb++;
                moyenne[0] += *(in->r + (in->width * (i) + j - 1));
                moyenne[1] += *(in->v + (in->width * (i) + j - 1));
                moyenne[2] += *(in->b + (in->width * (i) + j - 1));
            }
            if (j + 1 < in->width)
            {
                nb++;
                moyenne[0] += *(in->r + (in->width * (i) + j + 1));
                moyenne[1] += *(in->v + (in->width * (i) + j + 1));
                moyenne[2] += *(in->b + (in->width * (i) + j + 1));
            }

            nb++;
            moyenne[0] += *(in->r + (in->width * (i) + j));
            moyenne[1] += *(in->v + (in->width * (i) + j));
            moyenne[2] += *(in->b + (in->width * (i) + j));

            *(out->r + (in->width * (i) + j)) = moyenne[0] / nb;
            *(out->v + (in->width * (i) + j)) = moyenne[1] / nb;
            *(out->b + (in->width * (i) + j)) = moyenne[2] / nb;
        }
    }
}

void FPB_extended(SURFACE *in, SURFACE *out, int flou)
{
    int max = 255;
    double moyenne[3], nb;
    for (int i = 0; i < in->height; i++)
    {
        for (int j = 0; j < in->width; j++)
        {

            nb = 0;
            // remose à zero de moyenne
            for (int ite = 0; ite < 3; ite++)
            {
                moyenne[ite] = 0;
            }

            for (int i1 = -1 * flou; i1 <= flou; i1++)
            {
                for (int j1 = -1 * flou; j1 < flou; j1++)
                {
                    if (i + i1 >= 0 && i+i1<in->height)
                    {
                        if (j + j1 >= 0 && j + j1 < in->width)
                        {
                            nb++;
                            moyenne[0] += *(in->r + (in->width * (i + i1) + j + j1));
                            moyenne[1] += *(in->v + (in->width * (i + i1) + j + j1));
                            moyenne[2] += *(in->b + (in->width * (i + i1) + j + j1));
                        }
                        
                    }
                }
            }

            *(out->r + (in->width * (i) + j)) = moyenne[0] / nb;
            *(out->v + (in->width * (i) + j)) = moyenne[1] / nb;
            *(out->b + (in->width * (i) + j)) = moyenne[2] / nb;
        }
    }
}

/* ------------------
 * Application (test)
 */
int main()
{
    // cree une surface
    SURFACE surf;
    SURFACE surf2;
    // test: lecture d'image
    FILE *input = fopen("sortie.ppm", "r");
    if (input == NULL)
    {
        // creation d'une image originale
        surface(&surf, 100, 100);
        assert(surf.r != NULL); // controle sanitaire
        assert(surf.v != NULL); // controle sanitaire
        assert(surf.b != NULL); // controle sanitaire
        // fill(&surf, 1);         // fond uni
        int v[3] = {0, 255, 0}, r[3] = {255, 0, 0}, b[3] = {0, 0, 255}, j[3] = {255, 255, 0};
        ppm_rectangle(&surf, 4, 4, 48, 48, b);
        ppm_rectangle(&surf, 52, 4, 96, 48, j);
        ppm_rectangle(&surf, 4, 52, 96, 96, r);
    }
    else // copier une image dans un nouveau fichier draw.ppm
    {

        int ok = ppm_read(&surf, input);

        fclose(input);
        assert(ok);
        assert(surf.r != NULL); // controle sanitaire
        assert(surf.v != NULL); // controle sanitaire
        assert(surf.b != NULL); // controle sanitaire

        surface(&surf2, surf.width, surf.height);

        FPB_extended(&surf, &surf2, 10);
    }
    int w = surf.width, h = surf.height;
    // test: ecriture d'image
    FILE *output = fopen("draw.ppm", "w");

    assert(output != NULL); // controle sanitaire
    ppm_write(&surf2, output);
    fclose(output);
    // nettoyage
    //_surface(&surf);
    return 0;
}