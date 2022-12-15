#pragma once

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sndfile.h>
#include "PitchShift.h"

#define fInputFileName "Filtered.wav"
#define fOutputFileName "Final.wav"
#define fDepth 0.002 // Second
#define fOffset 0.005 // Second (Needs to be bigger than or equal to kDepth to avoid negative numbers)
#define fRate 0.8 //Hz
#define kThreshold 0.8f // 0-1

//Function prototypes
int openInputSndFile2(SoundFile *inFile);
int createOutputSndFile2(SoundFile *inFile, SoundFile *outFile);
void process(float *inBuffer, float *outBuffer, sf_count_t bufferSize);
int flanger();