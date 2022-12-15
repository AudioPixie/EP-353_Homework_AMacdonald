#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sndfile.h>
#include "Flanger.h"
#include "PitchShift.h"

//Global Variables
float gOffset, gDepth;
int gSampleRate;
float gCompRatio, gGain;

int flanger(){
    SoundFile inFile, outFile;
  
    //Open input file and create output file
    int error = openInputSndFile2(&inFile);

    if(error) return 1;

    // Get buffer size  
    sf_count_t bufferSize = inFile.info.frames;

    //Allocate buffers for sound processing
    float inBuffer[bufferSize];
    float outBuffer[bufferSize];

    //Copy content the file content to the buffer
    sf_read_float(inFile.file, inBuffer, bufferSize);
    
    gOffset = inFile.info.samplerate * fOffset;
    gDepth = inFile.info.samplerate * fDepth;
    gSampleRate = inFile.info.samplerate;

    //process inBuffer and copy the result to outBuffer
    process(inBuffer, outBuffer, bufferSize);
    
    //Create output file and write the result
    error = createOutputSndFile2(&inFile, &outFile);
    if(error) return 1;
    sf_write_float(outFile.file, outBuffer, bufferSize);
    
    //Clean up
    sf_close(inFile.file);
    sf_close(outFile.file);

    return 0;
}

void process(float *inBuffer, float *outBuffer, sf_count_t bufferSize){
    sf_count_t m; // distance in integer
    float distance, delayPosition, delta;
    
    for(sf_count_t n = 0; n < bufferSize; n++){
        outBuffer[n] = inBuffer[n];
      
        delayPosition = gOffset + gDepth * sin(2.0 * M_PI * fRate * n / gSampleRate);
        distance = (float) n - delayPosition; // Caluclate the distance of delayPosition to n in samples
        m = (int) distance; // Make the distance into integer for indexing
        delta = distance - (float)m; // Get the fractional part of the distance for amplitude control
      
        if (m >= 0 && m + 1 < bufferSize){
            // Mix original signals based on sample distance
            outBuffer[n] += delta * inBuffer[m + 1] + (1.0 - delta) * inBuffer[m]; 
        }

        if(outBuffer[n] > kThreshold){
            outBuffer[n] = kThreshold + (outBuffer[n] - kThreshold) * gCompRatio; //Compress positive signals
        } else if(outBuffer[n] < -kThreshold){
            outBuffer[n] = -kThreshold + (outBuffer[n] + kThreshold) * gCompRatio; //Compress negative signals
        }
      
    }
}

int openInputSndFile2(SoundFile *sndFile){
    //Initialize SF_INFO with 0s (Required for reading)
    memset(&sndFile->info, 0, sizeof(SF_INFO));

    //Open the original sound file as read mode
    sndFile->file = sf_open(fInputFileName, SFM_READ, &sndFile->info);
    if(!sndFile->file){//Check if the file was succefully opened
        printf("Error : could not open file : %s\n", fInputFileName);
        puts(sf_strerror(NULL));
        return 1;
    }

    //Check if the file format is in good shape
    if(!sf_format_check(&sndFile->info)){	
        sf_close(sndFile->file);
        printf("Invalid encoding\n");
        return 1;
    }

    //Check if the file is mono
    if(sndFile->info.channels > 1){
        printf("Input file is not mono\n");
        return 1;
    }

    //print out information about opened sound file
    printf("Sample rate for this file is %d\n", sndFile->info.samplerate);
    printf("A number of channels in this file is %d\n", sndFile->info.channels);
    printf("A number of frames in this file is %lld\n", sndFile->info.frames);
    printf("time is %f\n", (double)sndFile->info.frames / sndFile->info.samplerate);

    return 0;
}

int createOutputSndFile2(SoundFile *inFile, SoundFile *outFile){
    //Open another sound file in write mode
    outFile->file = sf_open(fOutputFileName, SFM_WRITE, &inFile->info);
    if(!outFile->file){//Check if the file was succefully opened
        printf("Error : could not open file : %s\n", fOutputFileName);
        puts(sf_strerror(NULL));
        return 1;
    }
    return 0;
}