#include <Adafruit_MCP4725.h>
#include "Notes.h"
Adafruit_MCP4725 dac;

int low_octave = 2;                    // lowest MIDI octave corresponding with a 0~1V CV output
byte low_note = (1 + low_octave) * 12; // lowest accepted MIDI note value based on octave setting
byte note_max = 60;                    // maximum number of notes     (60 = 5 octaves, note 0..59)

//unsigned int dac_data[61]; // array with values for DAC (all notes)
unsigned int dac_value; // 12-bit value used by DAC
int seqNote;

void initDAC()
{
    dac.begin(0x60);
}

void sendToDac(int dac_value)
{
    dac_value = max(dac_value, 0);    // limit the minimum DAC value to 0
    dac_value = min(dac_value, 4095); // limit the maximum DAC value to 4095
    dac.setVoltage(dac_value, false); // send the value to the DAC to change the CV
}

void sendNote(int seqNote)
{

    int note = seqNote;         //- low_note; // convert the midi_note value to a note value (note value is 0..60)
    dac_value = dac_data[note]; // lookup the corresponding DAC value for note
    sendToDac(dac_value);       // send this value to the DAC
}

//  DAC     note    CV
//------------------------
unsigned int dac_data[] = {
    0,   //  0  0,0000 V
    62,  //  1  0,0833 V
    140, //  2  0,1667 V
    202, //  3  0,2500 V
    276, //  4  0,3333 V
    340, //  5  0,4167 V
    411, //  6  0,5000 V
    478, //  7  0,5833 V
    546, //  8  0,6667 V
    616, //  9  0,7500 V
    682, // 10  0,8333 V
    754, // 11  0,9167 V

    816,  // 12  1,0000 V
    891,  // 13  1,0833 V
    952,  // 14  1,1667 V
    1027, // 15  1,2500 V
    1086, // 16  1,3333 V
    1162, // 17  1,4167 V
    1222, // 18  1,5000 V
    1297, // 19  1,5833 V
    1361, // 20  1,6667 V
    1434, // 21  1,7500 V
    1501, // 22  1,8333 V
    1569, // 23  1,9167 V

    1639, // 24  2,0000 V
    1705, // 25  2,0833 V
    1777, // 26  2,1667 V
    1840, // 27  2,2500 V
    1916, // 28  2,3333 V
    1977, // 29  2,4167 V
    2053, // 30  2,5000 V
    2112, // 31  2,5833 V
    2189, // 32  2,6667 V
    2252, // 33  2,7500 V
    2325, // 34  2,8333 V
    2390, // 35  2,9167 V

    2460, // 36  3,0000 V
    2527, // 37  3,0833 V
    2594, // 38  3,1667 V
    2665, // 39  3,2500 V
    2730, // 40  3,3333 V
    2803, // 41  3,4167 V
    2865, // 42  3,5000 V
    2941, // 43  3,5833 V
    3001, // 44  3,6667 V
    3076, // 45  3,7500 V
    3137, // 46  3,8333 V
    3213, // 47  3,9167 V

    3275, // 48  4,0000 V
    3349, // 49  4,0833 V
    3415, // 50  4,1667 V
    3485, // 51  4,2500 V
    3554, // 52  4,3333 V
    3621, // 53  4,4167 V
    3693, // 54  4,5000 V
    3758, // 55  4,5833 V
    3834, // 56  4,6667 V
    3895, // 57  4,7500 V
    3972, // 58  4,8333 V
    4031, // 59  4,9167 V

    4095 // 60  5,0000 V
};

unsigned char dac_notes[] = {'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G', 'A', 'A', 'B'};
