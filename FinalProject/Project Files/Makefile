# C compiler command
CC=clang
# Any compiler flags (-g, -Wall, etc)
CFLAGS=
# The main executable name
TARGET=main
# Libraries to inlcude
LIBS=-lsndfile -lsoundpipe
# Remove command
RM=rm

# Since the "all" target is the first, it is the default target and will be run when we run "make"
# The name is arbitrary 
all: $(TARGET).c PitchShift.c PitchShift.h Filter.c Filter.h Flanger.c Flanger.h
	$(CC) $(CFLAGS) $(TARGET).c PitchShift.c Filter.c Flanger.c -o $(TARGET) $(LIBS)

# Run the program
run: $(TARGET)
	./$(TARGET)