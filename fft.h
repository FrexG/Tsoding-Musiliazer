#pragma once

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <complex.h>


void dft(float in[], float complex out[], int N,float pi)
{
  for (int f = 0; f < N; ++f)
  {
    for (int k = 0; k < N; ++k)
    {
      float t = (float)k / N;
      out[f] += in[k] * cexp(2 * I * pi * f * t);
    }
  }
}

void fft(float in[], float complex out[], size_t stride, int N,float pi)
{
  assert(N > 0);
  if (N == 1)
  {
    out[0] = in[0];
    return;
  }

  fft(in, out, stride * 2, N / 2,pi);                          // even
  fft(in + stride, out + N / 2, stride * 2, N / 2,pi); // even

  for (size_t k = 0; k < N / 2; ++k)
  {
    float t = (float)k / N;
    float complex v = cexp(-2 * I * pi * t) * out[k + N / 2];
    float complex e = out[k];

    out[k] = e + v;
    out[k + N / 2] = e - v;
  }
}

float amplitude(float complex v)
{
  float r = fabsf(crealf(v));
  float i = fabsf(cimagf(v));

  if (r > i)
    return r;
  return i;
}