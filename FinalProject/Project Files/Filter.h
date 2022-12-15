#pragma once

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sndfile.h>
#include "PitchShift.h"

#define kInputFileName "test.wav"
#define kOutputFileName "Filtered.wav"

// function prototypes
int openInputSndFile(SoundFile *inFile);
int createOutputSndFile(SoundFile *inFile, SoundFile *outFile);
void lowpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize);
void highpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize);
int filter();