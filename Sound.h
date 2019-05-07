#pragma once
#include<SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

class Sound {
public:
	Sound();
	~Sound();
	void Play(double Volume, int Frequency, double Duration);
	void Stop();
private:
	SDL_AudioSpec AudioSpec;
	int Amplitude;
	int SampleRate;
	int DeviceID;
	short int* Buffer;
	short int SoundType; // 0 - Square, 1 - Saw, 2 - Triangle, 3 - Noise
	static void AudioCallback(void* UserData, unsigned char* buf, int bytes);
};