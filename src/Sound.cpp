#include "Sound.hpp"

#include <AL/alc.h>
#include <AL/alure.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Sound::Sound(std::string const& path) :
	play_(false), soundBuffer(AL_NONE), soundSource(NULL), Path(path)
{

	if (!alureInitDevice(NULL, NULL))
		std::cout << alureGetErrorString();

	ALuint major, minor;
	alureGetVersion(&major, &minor);
	std::cout << "OpenAL " << major << "." << minor << std::endl;

	alListener3f(AL_POSITION, 0.f, 0.f, 0.f);

	alGenSources(1, &soundSource);

	createSoundBuffer(path);
}

Sound::~Sound()
{
	alureShutdownDevice();
}

void Sound::setConfig(bool play)
{
	play_ = play;
}

void Sound::changed()
{
	std::cout << "config changed!" << std::endl;
}

void Sound::createSoundBuffer(const std::string filename)
{
	std::cout << "delete buffer...";
	alSourceStop(soundSource);
	alSourcei(soundSource, AL_BUFFER, NULL);
	std::cout << " done!" << std::endl;

	std::cout << "try to load file \"" << filename << "\"...";
	if (soundBuffer == AL_NONE)
	{
		soundBuffer = alureCreateBufferFromFile(filename.c_str());
	}
	else
	{
		std::cout << " try to replace ...";
		if(alureBufferDataFromFile(filename.c_str(), soundBuffer)==AL_FALSE) soundBuffer = AL_NONE;
	}

	if (soundBuffer == AL_NONE)
	{
		std::cout << " failed! Could not load the file! :.(" << std::endl;
	}
	else
	{
		std::cout << " done!" << std::endl;
		alSourcei(soundSource, AL_BUFFER, soundBuffer);
	}
}

void Sound::setSourcePos(Vec3 position)
{
	alSourcefv(soundSource, AL_POSITION, position);
}

void Sound::setListenerPos(Vec3 position)
{
	alListenerfv(AL_POSITION, position);
}

void Sound::play()
{
	alGetSourcei(soundSource, AL_SOURCE_STATE, &state);

	if (play_ && state != AL_PLAYING)
	{
		alSourcePlay(soundSource);
	}
	else if (!play_ && state == AL_PLAYING)
	{
		alSourcePause(soundSource);
	}
}

const char* const Sound::filter() const
{
	return "Sound files (*.wav *.ogg *.aiff)";
}

void Sound::reset()
{
	createSoundBuffer(path().c_str());
}
