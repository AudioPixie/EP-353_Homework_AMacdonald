#include <stdlib.h>
#include <sndfile.h>
#include <stdio.h>
#include <time.h>
#include "soundpipe.h"
#include "PitchShift.h"

int init(){
    SoundFile inFile;
    
    // Open input file and create output file
    int error = openInputSndFile3(&inFile);

    if(error) return 1;
    
    // Clean up
    sf_close(inFile.file);

    return 0;
}

int openInputSndFile3(SoundFile *sndFile){

    //Initialize SF_INFO with 0s (Required for reading)
    memset(&sndFile->info, 0, sizeof(SF_INFO));

    //Open the original sound file as read mode
    sndFile->file = sf_open(iInputFileName, SFM_READ, &sndFile->info);
    if(!sndFile->file){//Check if the file was succefully opened
        printf("Error : could not open file : %s\n", iInputFileName);
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

    // assign length of file for output file
    len = ((double)sndFile->info.frames);
    printf("Len: %f\n", len);

    return 0;
}

void pitchProcess(sp_data *sp, void *udata) {
    UserData *ud = udata;
    SPFLOAT diskin = 0, pshift = 0;
    sp_diskin_compute(sp, ud->diskin, NULL, &diskin);
    sp_pshift_compute(sp, ud->pshift, &diskin, &pshift);
    sp->out[0] = pshift;
}

int pitch() {
    srand(1234567);
    UserData ud;
    sp_data *sp;
    sp_create(&sp);

    sp_pshift_create(&ud.pshift);
    sp_diskin_create(&ud.diskin);    

    sp_pshift_init(sp, ud.pshift);
    *ud.pshift->shift = 3;
    *ud.pshift->window = 500;
    /* half window size is smoothest sounding */
    *ud.pshift->xfade = 250;
    sp_diskin_init(sp, ud.diskin, iInputFileName);

    sp->len = len;
    sp_process(sp, &ud, pitchProcess);

    sp_pshift_destroy(&ud.pshift);
    sp_diskin_destroy(&ud.diskin);

    sp_destroy(&sp);
    return 0;
}
