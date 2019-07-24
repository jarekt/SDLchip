#include <stdlib.h>
#include <time.h>
#include "chip.h"
unsigned char memory[4096];

unsigned short opcode;//current opcode
unsigned short stack[16];//return stack
unsigned char sp;//stack pointer
unsigned short ir;//index reg
unsigned short pc;//program counter



unsigned char V[16];//16 8bit registers

unsigned char timerS;//sound timer
unsigned char timerD;//delay timer


unsigned char gfx_buf[256];//bit array for monochrome gfx (64*32)/8 bytes

void (*op_table[16])();
void (*math_table[15])();


unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#define CARRY(condition) (V[15] = (condition) ? 1 : 0)//maybe remove one CARRY
void xorBit(int bit)
{
    if(bit<2048){
        if(V[15] == 0){CARRY(gfx_buf[bit/8] & (1 << (bit%8)));}
        gfx_buf[bit/8] ^= (1 << (bit%8));
    }
}

void setBit(int bit)
{
    gfx_buf[bit/8] |= (1 << (bit%8));
}

void clearBit(int bit)
{
    gfx_buf[bit/8] &= ~(1 << (bit%8));
}

int readBit(int bit)
{
    return gfx_buf[bit/8] & (1 << (bit%8));
}


void init()
{
    srand(time(0));
    pc = 0x200;//512
    ir = 0;
    sp = 0;
    for (int i = 0; i < 4096; i++)
    {
        memory[i] = 0;
    }
    for (int i = 0; i < 256; i++)
    {
        gfx_buf[i] = 0;
    }
    for (int i = 0; i < 80; i++)
    {
        memory[i + 0x50] = chip8_fontset[i];
    }
}

int fetch()
{   
    if(pc > 4096){return 0;}
    opcode = (memory[pc] << 8) | (memory[pc+1]);
    pc += 2;
    return 1;
}

void execute()
{
    op_table[(opcode & 0xF000) >> 12]();
}
////////////////////////////////////
////////////////////////////////////
#define NNN (opcode & 0x0FFF)
#define N (opcode & 0x0F)
#define KK (opcode & 0xFF)
#define X ((opcode & 0xF00) >> 8)
#define Y ((opcode & 0x0F0) >> 4)
#define CARRY(condition) (V[15] = (condition) ? 1 : 0)
//macro defines

void NULLop(){}//does nothing

void mathBranch()//branches to math table
{
    math_table[opcode & 0x000F]();
}
//misc functions


void ZERO()
{
    if ((opcode & 0xFF) == 0xE0)//00E0
    {
        for (int i = 0; i < (64*32)/8; i++)
        {
            gfx_buf[i] = 0;
        }
    }
    else if ((opcode & 0xFF) == 0xEE)//00EE
    {
        if (sp)
        {
            pc = stack[--sp];//decrement return stack
        }    
    }    
}
void JP()//1nnn
{
    pc = NNN;
}
void CALL()//2nnn
{
    stack[sp++] = pc;
    pc = NNN;
}
void SE()//3xkk
{
    if (V[X] == KK)
    {
        pc += 2;
    }
    
}
void SNE()//4xkk
{
    if (V[X] != KK)
    {
        pc += 2;
    }
}
void SER()//5xy0
{
    if (V[X] == V[Y])
    {
        pc += 2;
    }
    
}
void LD()//6xkk
{
    V[X] = KK;
}
void ADD()//7xkk
{
    V[X] += KK;
}
//opcode functions

void LD2()//8xy0
{
    V[X] = V[Y];
}
void OR()//8xy1
{
    V[X] |= V[Y];
}
void AND()//8xy2
{
    V[X] &= V[Y];
}
void XOR()//8xy3
{
    V[X] ^= V[Y];
}
void ADD2()//8xy4
{
    CARRY(V[X] + V[Y] > 255);
    V[X] += V[Y];
}
void SUB()//8xy5
{
    CARRY(V[X] > V[Y]);
    V[X] -= V[Y];
}
void SHR()//8xy6
{
    CARRY(V[X] & 0x1);//mybe shift if not working properly
    V[X] >>= 1;
}
void SUBN()//8xy7
{
    CARRY(V[Y] > V[X]);
    V[X] = V[Y] - V[X];
}
void SHL()//8xyE
{
    CARRY(V[X] & 0x8);//same as shr
    V[X] <<= 1;
}
//math functions

void SNE2()//9xy0
{
    if (V[X] != V[Y])
    {
        pc += 2;
    }
    
}
void LD3()//Annn
{
    ir = NNN;
}
void JP2()//Bnnn
{
    pc = V[0] + NNN;
}
void RND()//Cxkk
{
    V[X] = rand()%255 & KK;
}
void DRW()//Dxyn
{
    V[15] = 0;//for carry flag
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((memory[ir+i] & 0x80 >> j) == 0x80 >> j)
            {
                xorBit(((V[Y]+i)*64)+V[X]+j);
            }
        } 
    }
    //draws a sprite on x,y with height N
    //located on ir
    //sets carry flag (draw) flag
}
void SKP()
{
    if((opcode & 0x0F) == 0x0E)//Ex9E
    {
        if(key[V[X]] == 1)
        {
            pc += 2;
        }
    }
    else//ExA1
    {
        if(key[V[X]] != 1)
        {
            pc += 2;
        }
    }
}
void fBranch()
{
    switch (opcode & 0xF0FF)
    {
    case 0xF007:
        V[X] = timerD;
        break;
    case 0xF00A:
        do 
        {
            V[X] = getEvents(1);
        }
        while(V[X] > 15);
        break;
    case 0xF015:
        timerD = V[X];
        break;
    case 0xF018:
        timerS = V[X];
        break;
    case 0xF01E:
        ir += V[X];
        break;
    case 0xF029:
        ir = V[X]*5 + 0x50;//sprite adress of sprite num vx - hopefully works
        break;
    case 0xF033://prob not the smartest nor fastest implementation
        memory[ir] = V[X] %1000 / 100;//hundreds
        memory[ir+1] = V[X] %100 / 10;//tens
        memory[ir+2] = V[X] %10;//ones
        break;
    case 0xF055:
        for (int i = 0; i <= X; i++)
        {
            memory[ir+i] = V[i];
        }
        break;
    case 0xF065:
        for (int i = 0; i <= X; i++)
        {
            V[i] = memory[ir+i];
        }
        break;
    default:
        break;
    }
}
////////////////////////////////////
////////////////////////////////////

void (*op_table[16])() = {ZERO, JP, CALL, SE, SNE, SER, LD, ADD,
                     mathBranch, SNE2, LD3, JP2, RND, DRW, SKP, fBranch};
void (*math_table[15])() = {LD2, OR, AND, XOR, ADD2, SUB, SHR, SUBN, NULLop, NULLop, NULLop, NULLop, NULLop, NULLop, SHL};
//function tables