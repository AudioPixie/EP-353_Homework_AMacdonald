#Splatoon Voice Changer - User's Manual
###Installations
-

Download this folder and unzip it on your computer.

**Requires installations of libsndfile and soundpipe**

To install libsndfile, first install [homebrew](brew.sh). 
	
* Run the following command in terminal and enter your password if prompted

`/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

* Once homebrew is installed, install libsndfile by running the following command in terminal and enter your password if prompted

`brew install libsndfile`

Once libsndfile is installed, install soundpipe by downloading the master folder [here](https://github.com/SeesePlusPlus/soundpipe).

* Once it is downloaded, unzip it. This will create a folder called `Soundpipe-master`.
* Navigate to `Soundpipe-master` using the `cd` command in terminal
* Run the following command: `make`
* Once that is done compiling, run the following command. You will be prompted to enter your password: `sudo make install`

###Running the project
-

Start by putting whatever mono wav file you want to affect in the `Project Files` folder.

* To run the project, open `PitchShift.h` located in the `Project Files` folder.

* Look at line 9, it should say:

`#define iInputFileName "GAMEOVER.wav" // <- file to modify`

* Change `GAMEOVER.wav` to whatever the name of your file is.

* Navigate to the `Project Files` folder in your terminal and run the following command:

`make && make run`

* If things aren't working as expected, try running the two following commands and then trying to make it again.

`export C_INCLUDE_PATH=/opt/homebrew/include/`

`export LIBRARY_PATH=/opt/homebrew/lib/`

###Output
-

You will now have 3 new files in the `Project Files` folder. The one titled `Final` is the one with all of the effects applied.