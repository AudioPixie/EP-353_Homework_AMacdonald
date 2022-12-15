#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>
#include "Filter.h"
#include "PitchShift.h"

float CUTOFF = 1000.0f;
int SAMPLE_RATE;

float amplitude = 30.0f;
float frequency = 15.0f;

int filter(){
    SoundFile inFile, outFile;
    
    // Open input file and create output file
    int error = openInputSndFile(&inFile);

    if(error) return 1;

    // Get buffer size
    sf_count_t bufferSize = inFile.info.frames;
   

    SAMPLE_RATE = inFile.info.samplerate;

    // Allocate buffers for sound processing
    float inBuffer[bufferSize];
    float outBuffer[bufferSize];
    float LFObuffer[bufferSize];

    // Copy content the file content to the buffer
    sf_read_float(inFile.file, inBuffer, bufferSize);
  
    // Process inBuffer and copy the result to outBuffer
    lowpass(inBuffer, outBuffer, LFObuffer, bufferSize);
    //highpass(inBuffer, outBuffer, LFObuffer, bufferSize);
  
    // Create output file and write the result
    error = createOutputSndFile(&inFile, &outFile);
    if(error) return 1;
    sf_write_float(outFile.file, outBuffer, bufferSize);
  
    // Clean up
    sf_close(inFile.file);
    sf_close(outFile.file);

    return 0;
}

void lowpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize)
{
    outBuffer[0] = inBuffer[0];
    for(int i = 1; i < bufferSize; ++i) 
    {  
        // data
        double RC = 1.0/(CUTOFF*2*M_PI);  
        double dt = 1.0/SAMPLE_RATE;  
        double alpha = dt/(RC+dt); 

        // filtering
        outBuffer[i] = outBuffer[i-1] + (alpha*(inBuffer[i] - outBuffer[i-1])); 

        // lfo
        float LFOsample = amplitude * sin(2.0 * M_PI * (frequency/SAMPLE_RATE) * i);
        LFObuffer[i] = LFOsample;
        CUTOFF += LFOsample;
    } 
} 

void highpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize)
{
    outBuffer[0] = inBuffer[0];
    for(int i = 1; i < bufferSize; ++i) 
    {  
        // data
        double RC = 1.0/(CUTOFF*2*M_PI);  
        double dt = 1.0/SAMPLE_RATE;  
        double alpha = dt/(RC+dt); 

        // filtering
        outBuffer[i] = alpha * (outBuffer[i-1] + inBuffer[i] - inBuffer[i-1]);

        // lfo
        float LFOsample = amplitude * sin(2.0 * M_PI * (frequency/SAMPLE_RATE) * i);
        LFObuffer[i] = LFOsample;
        CUTOFF += LFOsample;
    } 
} 

int openInputSndFile(SoundFile *sndFile){
    //Initialize SF_INFO with 0s (Required for reading)
    memset(&sndFile->info, 0, sizeof(SF_INFO));

    //Open the original sound file as read mode
    sndFile->file = sf_open(kInputFileName, SFM_READ, &sndFile->info);
    if(!sndFile->file){//Check if the file was succefully opened
        printf("Error : could not open file : %s\n", kInputFileName);
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

int createOutputSndFile(SoundFile *inFile, SoundFile *outFile){
    //Open another sound file in write mode
    outFile->file = sf_open(kOutputFileName, SFM_WRITE, &inFile->info);
    if(!outFile->file){//Check if the file was succefully opened
        printf("Error : could not open file : %s\n", kOutputFileName);
		    puts(sf_strerror(NULL));
		    return 1;
	}
    return 0;
}