#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <complex.h>

#include "fft.h"

#define N 256  

// globals
float in[N];
float complex out[N];

typedef struct
{
  float left;
  float right;
} Frame;


typedef struct
{
  Music music;
} Plug;

void audio_callback(void *bufferData,unsigned int frames);

typedef void (*plug_init_t)(Plug *plug, const char *music_file_path);
typedef void (*plug_update_frame_t)(Plug *plug);
