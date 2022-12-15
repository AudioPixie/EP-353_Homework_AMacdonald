#pragma once

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sndfile.h>
#include "soundpipe.h"

#define iInputFileName "OHYEAH.wav" // <- file to modify

float len;

typedef struct {
    sp_pshift *pshift;
    sp_diskin *diskin;
} UserData;

//Hold SNDFILE and SF_INFO together
typedef struct SoundFile {
  SNDFILE *file;
  SF_INFO info;
} SoundFile;

//Function prototypes

void pitchProcess(sp_data *sp, void *udata);
int pitch();
int openInputSndFile3(SoundFile *inFile);
int init();