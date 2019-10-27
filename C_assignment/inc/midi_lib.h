#include <stdlib.h>
#include <portmidi.h>
#include <porttime.h>
#include <stdio.h>

#ifndef __MIDI_LIB__
#define __MIDI_LIB__

#define MD_NOTEON 0x90
#define MD_NOTEOFF 0x80
#define MD_PRG  0xC0
#define SBYTE(mess,chan) mess | chan

/**
    Returns a pseudo random integer in range
    [lower_range, upper_range]

    @param lower_range Lowest number the random number will be
    @param upper_range Highest number the random number will be
    @return random number between or equal to lower_range and
    upper_range

*/
int MIDI_RandomNumber(int lower_range, int upper_range);

/**
    Waits for some milliconds
    @param time_in_milliseconds Time to wait for in ms.
*/
void MIDI_PauseFor(int time_in_milliseconds);

/**
    Send a Midi note of the specified pitch, channel and velocity
    @param pitch Pitch of note
    @param channel Channel of note
    @param velocity Velocity of note
*/
void MIDI_SendNote(int pitch, int channel, int velocity);

/**
    Changes a channel to a different instrument
    @param channel Channel to change
    @param instrument Index of instrument, see
    http://soundprogramming.net/file-formats/general-midi-instrument-list/
    for a full list
*/
void MIDI_ProgramChange(int channel, int instrument);

/**
    Initialise the MIDI connection
*/
void MIDI_Init(void);

/**
    Close the MIDI connection
*/
void MIDI_Close(void);


#endif /* __MIDI_LIB__ */
