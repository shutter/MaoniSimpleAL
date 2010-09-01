/*
 * A Maoni OpenAL sample using ALURE wrapper
 * Positioning requires a mono sound file (wave/ogg)
 */

#include <GL/glew.h>
#include <Maoni.hpp>
#include "sound.hpp"
#include <GL/glu.h>
#include <math.h>

RENDER_ALGORITHM(MaoniSound,
		(bool, play, false)
		(Path, file, "../brass2rass.ogg")
		(float, velocity, 1.f)
		(bool, demo, true)
		(float, source_pos_x, 0.f)
		(float, source_pos_y, 0.f)
		(float, source_pos_z, 1.f)
		(float, listener_pos_x, 0.f)
		(float, listener_pos_y, 0.f)
		(float, listener_pos_z, 0.f)
)
{
	static Vec3 sourcePos(0.f, 0.f, 0.f);
	static Vec3 listenerPos(0.f, 0.f, 0.f);

	static float degree;

	// Sound
	static sound mysound;
	mysound.setConfig(file.path(), play);

	if (play && demo)
	{
		sourcePos.data[0] = sin((degree += velocity) * M_PI / 180);
		sourcePos.data[1] = 0.f;
		sourcePos.data[2] = cos((degree += velocity) * M_PI / 180);

		listenerPos.data[0] = 0.f;
		listenerPos.data[1] = 0.f;
		listenerPos.data[2] = 0.f;

	}else{
		sourcePos.data[0] = source_pos_x;
		sourcePos.data[1] = source_pos_y;
		sourcePos.data[2] = source_pos_z;

		listenerPos.data[0] = listener_pos_x;
		listenerPos.data[1] = listener_pos_y;
		listenerPos.data[2] = listener_pos_z;
	}
	mysound.setSourcePos(sourcePos);
	mysound.setListenerPos(listenerPos);

	// Positions
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	//Listener
	glPushMatrix();
	glTranslatef(listenerPos.data[0], listenerPos.data[1], listenerPos.data[2]);
	glColor3f(1.f, 0.f, 0.f);
	gluSphere(quadric, .05, 6, 6);
	glPopMatrix();

	//Source
	glPushMatrix();
	glTranslatef(sourcePos.data[0], sourcePos.data[1], sourcePos.data[2]);
	glColor3f(0.f, 1.f, 0.f);
	gluSphere(quadric, .05, 6, 6);
	glPopMatrix();

	gluDeleteQuadric(quadric);

	mysound.draw();
}
