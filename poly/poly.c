#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

typedef struct poly_t poly_t;
struct poly_t
{
  int terms;
  int *coefficients;
  int *degrees;
};

poly_t *new_poly_from_string(const char *c)
{
  int current;

  poly_t *p = (poly_t *)malloc(sizeof(poly_t));
  if (p == NULL)
  {
    return NULL;
  }

  int coef, expo, sign, terms = 1;
  p->terms = 0;
  p->coefficients = malloc(sizeof(int) * terms);
  p->degrees = malloc(sizeof(int) * terms);

  current = *(c++);
  while (1)
  {
    coef = 1;
    expo = 0;
    sign = 1;

    if (current == '-')
    {
      sign = -1;
      current = *(c++);
      if (current == ' ')
      {
        current = *(c++);
      }
    }
    else if (current == '+')
    {
      current = *(c++);
      if (current == ' ')
      {
        current = *(c++);
      }
    }

    if (isdigit(current))
    {
      coef = (current - '0');
      current = *(c++);
      while (isdigit(current))
      {
        coef = coef * 10 + (current - '0');
        current = *(c++);
      }
      coef *= sign;
    }

    if (current == 'x')
    {
      expo = 1;
      current = *(c++);
      if (current == '^')
      {
        current = *(c++);
        expo = (current - '0');
        current = *(c++);
        while (isdigit(current))
        {
          expo = expo * 10 + (current - '0');
          current = *(c++);
        }
      }
    }
    
    p->coefficients[terms - 1] = coef;
    p->degrees[terms - 1] = expo;

    if (current == '\0')
    {
      break;
    }

    terms++;
    p->coefficients = realloc(p->coefficients, sizeof(int) * terms);
    p->degrees = realloc(p->degrees, sizeof(int) * terms);

    current = *(c++);
  }
  p->terms = terms;
  return p;
}

void free_poly(poly_t *p)
{
  free(p->coefficients);
  free(p->degrees);
  free(p);
}

poly_t *mul(poly_t *p1, poly_t *p2)
{
  int x, y, i = 0;

  int p1_terms = p1->terms;
  int *p1_coefs = p1->coefficients;
  int *p1_expos = p1->degrees;
  int p2_terms = p2->terms;
  int *p2_coefs = p2->coefficients;
  int *p2_expos = p2->degrees;

  int terms_max = p1_terms * p2_terms;

  int *coefs = (int *)calloc(terms_max, sizeof(int));
  int *expos = (int *)calloc(terms_max, sizeof(int));

  poly_t *product = malloc(sizeof(poly_t));
  product->terms = 0;
  product->coefficients = (int *)calloc(terms_max, sizeof(int));
  product->degrees = (int *)calloc(terms_max, sizeof(int));

  // multiply together terms
  for (x = 0; x < p1_terms; ++x)
  {
    int p1_coef = p1_coefs[x];
    int p1_expo = p1_expos[x];
    for (y = 0; y < p2_terms; ++y)
    {
      product->coefficients[i] = p1_coef * p2_coefs[y];
      product->degrees[i] = p1_expo + p2_expos[y];
      i++;
    }
  }

  // add together terms with same exponent
  int coef, expo, terms_after_add = 0;
  for (x = 0; x < terms_max; ++x)
  {
    coef = product->coefficients[x];
    expo = product->degrees[x];
    for (y = 0; y < terms_after_add + 1; ++y)
    {
      if (y == terms_after_add)
      {
        coefs[y] = coef;
        expos[y] = expo;
        terms_after_add++;
        break;
      }
      else if (expos[y] == expo)
      {
        coefs[y] += coef;
        break;
      }
    }
  }

  int largest_expo, last_expo = __INT_MAX__;
  int terms_after_sort = 0;
  for (x = 0; x < terms_after_add; ++x)
  {
    i = 0;
    largest_expo = 0;
    for (y = 0; y < terms_after_add; ++y)
    {
      expo = expos[y];
      if (expo >= largest_expo && expo < last_expo)
      {
        largest_expo = expo;
        i = y;
      }
    }

    coef = coefs[i];
    if (coef != 0)
    {
      product->coefficients[terms_after_sort] = coef;
      product->degrees[terms_after_sort] = largest_expo;
      terms_after_sort++;
    }
    last_expo = largest_expo;
  }

  product->terms = terms_after_sort;
  product->coefficients = realloc(product->coefficients, sizeof(int) * terms_after_sort);
  product->degrees = realloc(product->degrees, sizeof(int) * terms_after_sort);

  free(coefs);
  free(expos);
  return product;
}

void print_poly(poly_t *p)
{
  int coef, expo, terms = p->terms;

    for (size_t i = 0; i < terms; ++i)
    {
        coef = p->coefficients[i];
        expo = p->degrees[i];

        if(coef < 0){
            printf("- ");
            coef *= -1;
        }else if(i != 0){
            printf("+ ");
        }

        if(coef != 1 || expo == 0) {
            printf("%d", coef);
        }

        if(expo > 0){
            printf("x");
        }
        if(expo > 1){
            printf("^%d", expo);
        }

        if(i != terms - 1){
            printf(" ");
        }else{
            printf("\n");
        }
    }
}
