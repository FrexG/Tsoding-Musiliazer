#pragma once

#include <stdio.h>
#include <string.h>

#include <raylib.h>

#define W 800
#define H 600
#define ARRAY_LEN(x) sizeof(x) / sizeof(x[0])




size_t bufferSize = 4080;
size_t global_frames_count = 0;
static const float volume = 0.2;

// function declarations
void audio_callback(void *bufferData, unsigned int frames);
bool reload_libplug(void);
