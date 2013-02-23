// include
#include "bandlimited_sawtooth_oscillator_note.h"

//---------
//
//---------
bandlimited_sawtooth_oscillator_note::bandlimited_sawtooth_oscillator_note()
:adsr(Silent)
,envelope(0.0)
,t(0.0)
,saw(0.0)
,n(0)
,dt(0.0)
{
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note::trigger(double pitch, int srate)
{	
	t = 0.5;
	saw = 0.0;

	adsr = Attack;
	envelope = 0.0;
	updateFrequency(pitch, srate);
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note::updateFrequency(double pitch, int srate)
{
	n = static_cast<int>(srate / 2.0 / pitch);
	dt = pitch / srate;
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note::release()
{
	adsr = Release;
}

