#ifndef CHIP_H_
#define CHIP_H_

extern unsigned char memory[4096];

extern unsigned char timerS;
extern unsigned char timerD;

extern char key[16];

int readBit(int bit);
//reads from gfx buffer
char getEvents(char b_wait);
//used for keypresses
void init();
//inits the emu
int fetch();
//fetches opcode
void execute();
//executes a cycle

#endif