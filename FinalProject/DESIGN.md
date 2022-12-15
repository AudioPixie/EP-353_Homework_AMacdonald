#Splatoon Voice Changer - Design
###Structure
-
The project is comprised of 3 stages: pitch shifting, filtering, and flanging. Each of these steps are their own respective c files with accompanying h files, and a main c file calls all of their core functions in order. A makefile is used to stitch everything together. There are 2 example wav files included for testing purposes

###Pitch Shift
-
The pitch shifting function is from [Soundpipe](https://github.com/SeesePlusPlus/soundpipe). I modified the shifting amount at `PitchShift.c:79` to get the desired effect. I also incorporated libsndfile reading functionality to the script to get the length of the file at the start of the process, as by default the pitch shifting script included with Soundpipe was hard-coded to 5 seconds. 

The accompanying h file includes all necessary definitions, typedefs, global variables, and function prototypes.

###Filter
-
There is a highpass and lowpass filter included in this script, although both work fine it is set up to use the lowpass in its current state. To switch to the highpass, change `Filter.c:37` to read "highpass" instead of "lowpass". The filter cutoff can be found at `Filter.c:8`. The filter script follows the digital audio effects template provided to us in class.

I modified an algorithm found [here](https://www.quora.com/Whats-the-C-coding-for-a-low-pass-filter) for the lpf and an algorithm found [here](https://stackoverflow.com/questions/13882038/implementing-simple-high-and-low-pass-filters-in-c) for the hpf. I added an lfo found at `Filter.c:66` (lpf) and `Filter.c:86` (hpf) that is then used to modulate the cutoff frequency. 

The accompanying h file includes all necessary definitions, typedefs, global variables, and function prototypes, as well as `PitchShift.h` for the SoundFile struct.

###Flanger
-

The flanger script is based on the one provided in the class materials. The accompanying h file includes all necessary definitions, typedefs, global variables, and function prototypes, as well as `PitchShift.h` for the SoundFile struct.

###Main
-

The main file calls all of the functions in order and outputs files for every stage of the process:

	test.wav		Pitch Shifting applied
	Filtered.wav	Filtering applied
	Final.wav 		Flanger applied
	
###Makefile
-

The Makefile constructs the commands necessary to run the full program in one step and includes all necessary libraries. This is the command I use to run everything at once:

`make && make run`