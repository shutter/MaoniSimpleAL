#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alure.h>
#include <string.h>
#include <Maoni.hpp>
#include <Maoni/Path.hpp>

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

	std::string old_filename;
	bool play_, change_flag;

private:
	void reset();
	const char* const filter() const;
};

#endif /* SOUND_HPP_ */
