#pragma once

struct _AudioData {
	bool PlaySquare;
	double PlaySquareDuration;
};

class CPU {
public:
	CPU();
	virtual ~CPU();
	short int screen[32][64];
	_AudioData AudioData;

	void LoadInMemory(short int addr, unsigned char* buffer, short int size);
	void Step(short int PressedKey);
private:
	unsigned char RAM[4096];
	unsigned char reg[16];
	short int stack[24];
	short int stacklevel;
	short int I;
	short int PC;
	short int Delay_Timer;
	short int Sound_Timer;
	unsigned long lastclock;
	unsigned long clockspeed;
	bool Halt;
};

