#include "Sound.h"
#include <time.h>

Sound::Sound () {
	Amplitude = 28000;
	SampleRate = 22050;
	Buffer = new short int[SampleRate * 5];

	AudioSpec.freq = SampleRate;
	AudioSpec.format = AUDIO_S16SYS;
	AudioSpec.channels = 1;
	AudioSpec.samples = 2048;
	AudioSpec.callback = NULL;

	DeviceID = SDL_OpenAudioDevice(NULL, 0, &AudioSpec, NULL, 0);
	if (DeviceID == 0) {
		fprintf (stderr, "Error creating audio device: %s\n", SDL_GetError());
	}
}

Sound::~Sound () {
	delete Buffer;
}

void Sound::Play(double Volume, int Frequency, double Duration) {
	if (SDL_GetQueuedAudioSize(DeviceID) >= 2048)
		return;

	int SampleCount = SampleRate * Duration;
	long long WaveDurationInMicroseconds = 1000000 / Frequency;

	if (Duration > 5) // Limit to 5 seconds
		Duration = 5;

	if (SoundType == 0) {
		for (int i = 0; i < SampleCount; i++) {
			double Time = (double) i / SampleRate;
			long long microsecs = Time * 1000000;

			if (microsecs % WaveDurationInMicroseconds <= WaveDurationInMicroseconds/2)
				Buffer[i] = - Amplitude * Volume;
			else
				Buffer[i] = Amplitude * Volume;
		}
	}

	SDL_QueueAudio (DeviceID, Buffer, sizeof(short int) * SampleCount);
	SDL_PauseAudioDevice(DeviceID, 0);
}

void Sound::Stop() {
	if (SDL_GetAudioDeviceStatus(DeviceID) == SDL_AUDIO_PLAYING) {
		SDL_PauseAudioDevice(DeviceID, 1);
	}
}
