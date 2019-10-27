#include "midi_lib.h"

/* Global Variables */

PmError retval;
PortMidiStream *mstream;

int MIDI_RandomNumber(int lower_range, int upper_range)
{
    int x;

    if (upper_range < lower_range)
    {
        x = upper_range;
        upper_range = lower_range;
        lower_range = x;
    }
    return lower_range + rand() %(upper_range -lower_range +1);

}

void MIDI_PauseFor(int time_in_milliseconds)
{
    long time;

    time = Pt_Time(NULL);
    while(Pt_Time(NULL) - time < time_in_milliseconds);

}

void MIDI_SendNote(int pitch, int channel, int velocity)
{
    int channel1,  velocity1;

    channel1 = 1 + (channel % 16);
    velocity1 = velocity % 128;

    Pm_WriteShort(mstream, 0, Pm_Message(SBYTE(MD_NOTEON,channel1), pitch, velocity1));
}

void MIDI_ProgramChange(int channel, int instrument)
{
    int channel1, instrument1;

    instrument1 = 1+ (instrument % 128);
    channel1 = 1 + (channel % 16);

    Pm_WriteShort(mstream, 0, Pm_Message(SBYTE(MD_PRG,channel1), instrument1, 0));
}

void MIDI_Init(void)
{
    Pm_Initialize();
    Pt_Start(1, NULL, NULL);
    retval = Pm_OpenOutput(&mstream, 0,NULL,512,NULL,NULL,0);
    if(retval != pmNoError)
    {
        printf("error: %s \n", Pm_GetErrorText(retval));
    }
    else /* set channel 1 to grand piano */
        MIDI_ProgramChange(1, 1);
}

void MIDI_Close(void)
{
    Pm_Close(mstream);
    Pm_Terminate();
}

