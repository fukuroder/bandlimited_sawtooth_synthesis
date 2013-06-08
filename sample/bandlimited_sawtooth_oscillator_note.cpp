#include "bandlimited_sawtooth_oscillator_note.h"
#include <math.h>

namespace Steinberg {namespace Vst {

// constructor
bandlimited_sawtooth_oscillator_note::bandlimited_sawtooth_oscillator_note()
:_adsr(Off)
,t(0.0)
,saw(0.0)
,n(0)
,dt(0.0)
,srate(44100)
,_old_pitch_bend(0.0)
,_pitch_bend(0.0)
{
}

//
void bandlimited_sawtooth_oscillator_note::setSampleRate(int srate)
{
	this->srate = srate;
}

//
void bandlimited_sawtooth_oscillator_note::release()
{
	_adsr = Off;
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note::trigger(const NoteOnEvent& noteOn)
{
	_noteOn = noteOn; // コピー
	_adsr = On;

	//
	double freq = 440.0*( ::pow(2.0, (_noteOn.pitch - _note_no_center)/12.0 + _pitch_bend));
	n = static_cast<int>(srate / 2.0 / freq);
	dt = freq / srate;
	_old_pitch_bend = _pitch_bend;
}

/// タグ取得.
int32 bandlimited_sawtooth_oscillator_note::id()const
{
	return _noteOn.noteId;
}

//---------
//
//---------
double bandlimited_sawtooth_oscillator_note::velocity()const
{
	return _noteOn.velocity;
}

}}
