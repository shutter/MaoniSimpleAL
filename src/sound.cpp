#include "sound.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

sound::sound() :
	old_filename(""), play_(false), change_flag(false), soundBuffer(AL_NONE),
			state(AL_INITIAL), soundSource(NULL)
{

	if (!alureInitDevice(NULL, NULL))
		std::cout << alureGetErrorString();

	ALuint major, minor;
	alureGetVersion(&major, &minor);
	std::cout << "OpenAL " << major << "." << minor << std::endl;

	alListener3f(AL_POSITION, 0.f, 0.f, 0.f);

	alGenSources(1, &soundSource);
}

sound::~sound()
{
	alureShutdownDevice();
}

void sound::setConfig(std::string filename, bool play)
{
	if (filename != old_filename)
	{
		createSoundBuffer(filename);
		old_filename = filename;
		changed();
	}

	play_ = play;
}

void sound::changed()
{
	std::cout << "config changed!" << std::endl;
}

void sound::createSoundBuffer(const std::string filename)
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
		alureBufferDataFromFile(filename.c_str(), soundBuffer);
	}

	if (soundBuffer == AL_NONE)
	{
		std::cout << " failed! Could not load the file! :.("
				<< std::endl;
	}
	else
	{
		std::cout << " done!" << std::endl;
		alSourcei(soundSource, AL_BUFFER, soundBuffer);
	}
}

void sound::setSourcePos(Vec3 position)
{
	alSourcefv(soundSource, AL_POSITION, position);
}

void sound::setListenerPos(Vec3 position)
{
	alListenerfv(AL_POSITION, position);
}

void sound::draw()
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
