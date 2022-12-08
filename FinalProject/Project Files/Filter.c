#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>

/* ----------------------- 
    TO RUN
----------------------- */

// export C_INCLUDE_PATH=/opt/homebrew/include/
// export LIBRARY_PATH=/opt/homebrew/lib/
// clang FilterFlanger.c -lsndfile && ./a.out

#define kInputFileName "OHYEAH.wav"
#define kOutputFileName "Out1.wav"

//Hold SNDFILE and SF_INFO together
typedef struct SoundFile {
    SNDFILE *file;
    SF_INFO info;
}   SoundFile;

//Function prototypes
int openInputSndFile(SoundFile *inFile);
int createOutputSndFile(SoundFile *inFile, SoundFile *outFile);
void lowpass(float *inBuffer, float *outBuffer, sf_count_t bufferSize);
void highpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize);

float CUTOFF = 5000.0f;
int SAMPLE_RATE;

float amplitude = 80.0f;
float frequency = 20.0f;

int main(){
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
    //lowpass(inBuffer, outBuffer, bufferSize);
    highpass(inBuffer, outBuffer, LFObuffer, bufferSize);
  
    // Create output file and write the result
    error = createOutputSndFile(&inFile, &outFile);
    if(error) return 1;
    sf_write_float(outFile.file, outBuffer, bufferSize);
  
    // Clean up
    sf_close(inFile.file);
    sf_close(outFile.file);
}

//TODO: Implement your DSP here
void lowpass(float *inBuffer, float *outBuffer, sf_count_t bufferSize)
{
    double RC = 1.0/(CUTOFF*2*M_PI);  
    double dt = 1.0/SAMPLE_RATE;  
    double alpha = dt/(RC+dt); 
    outBuffer[0] = inBuffer[0];
    for(int i = 1; i < bufferSize; ++i) 
    {  
        outBuffer[i] = outBuffer[i-1] + (alpha*(inBuffer[i] - outBuffer[i-1])); 
    } 
} 

void highpass(float *inBuffer, float *outBuffer, float *LFObuffer, sf_count_t bufferSize)
{
    outBuffer[0] = inBuffer[0];
    for(int i = 1; i < bufferSize; ++i) 
    {  
        double RC = 1.0/(CUTOFF*2*M_PI);  
        double dt = 1.0/SAMPLE_RATE;  
        double alpha = dt/(RC+dt); 
        outBuffer[i] = alpha * (outBuffer[i-1] + inBuffer[i] - inBuffer[i-1]);
        float LFOsample = amplitude * sin(2.0 * M_PI * (frequency/SAMPLE_RATE) * i);
        LFObuffer[i] = LFOsample;
        CUTOFF += LFOsample;
    } 
} 

// float cutoffMod(float *sineBuffer){
//     for (int t = 0; t < kNumFrames; t++){
//         // Compute A sin(2πft+φ). Phase is ignored in this case.
//         // frequency/kSampleRate converts frequency (continous) to sample rate representation (discrete).
//         float sample = amplitude * sin(2.0 * M_PI * (frequency/kSampleRate) * t);
//         // Write the same sample into all channels
//         for(int c = 0; c < kNumChannels; c++){
//         buffer[kNumChannels * t + c] = sample;
//         }
//     }
// }

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