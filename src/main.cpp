/*
 * A Maoni OpenAL sample using ALURE wrapper
 * Positioning requires a mono sound file (wave/ogg)
 */

#include <GL/glew.h>
#include <Maoni.hpp>
#include "Sound.hpp"
#include <GL/glu.h>
#include <math.h>

RENDER_ALGORITHM(MaoniSound,
		(bool, play, false)
		(mutable Sound, mysound, "../Fantasie-Impromptu_--_Frederic_Chopin.ogg")
		(float, velocity, 1.f)
		(bool, demo, true)
		(Vec3, source_pos, Vec3(0.f, 0.f, 1.f))
		(Vec3, listener_pos, Vec3(0.f, 0.f, 0.f))
)
{
	static Vec3 sourcePos(0.f, 0.f, 0.f);
	static Vec3 listenerPos(0.f, 0.f, 0.f);

	static float degree;

	mysound.setConfig(play);

	if (play && demo)
	{
		sourcePos.data[0] = sin((degree += velocity) * M_PI / 180);
		sourcePos.data[1] = 0.f;
		sourcePos.data[2] = cos((degree += velocity) * M_PI / 180);

		listenerPos.data[0] = 0.f;
		listenerPos.data[1] = 0.f;
		listenerPos.data[2] = 0.f;

	}else{
		sourcePos = source_pos;
		listenerPos = listener_pos;
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

	mysound.play();
}
