#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alure.h>
#include <string>
#include <Maoni.hpp>

class sound {

public:
	sound();
	~sound();

	virtual void draw();
	void setConfig(const std::string filename, bool play);
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

};

#endif /* SOUND_HPP_ */
