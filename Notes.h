#ifndef NOTES_H
#define NOTES_H

void sendNote(int seqNote);
extern unsigned char dac_notes[12];
extern unsigned int dac_data[61];
void initDAC();

#endif
