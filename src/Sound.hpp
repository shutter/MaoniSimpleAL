#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <string.h>
#include <Maoni.hpp>
#include <Maoni/Path.hpp>
#include <AL/al.h>

class Sound: public Path
{

public:
	Sound(std::string const& path);
	~Sound();

	virtual void play();
	void setConfig(bool play);
	void setSourcePos(Vec3 position);
	void setListenerPos(Vec3 position);

private:
	void createSoundBuffer(const std::string filename);
	void changed();

private:
	ALuint soundBuffer, soundSource;
	ALint state;

	bool play_;

private:
	void reset();
	const char* const filter() const;
};

#endif /* SOUND_HPP_ */
