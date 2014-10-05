#define _USE_MATH_DEFINES
#include <math.h>
#include "BLITSaw_oscillator.h"

namespace MyVst {

// constructor
BLITSaw_oscillator_note::BLITSaw_oscillator_note()
:_adsr(Off)
,t(0.0)
,saw(0.0)
,n(0)
,dt(0.0)
{
}

//
void BLITSaw_oscillator_note::release()
{
	_adsr = Off;
}

//
void BLITSaw_oscillator_note::trigger(const NoteOnEvent& noteOn, double srate)
{
	_noteOn = noteOn; // copy
	_adsr = On;
	saw = 0.0;
	t = 0.5;

	//
	double freq = 440.0*( ::pow(2.0, (_noteOn.pitch - _note_no_center)/12.0 ));
	n = static_cast<int>(srate / 2.0 / freq);
	dt = freq / srate;
}

//
int32 BLITSaw_oscillator_note::id()const
{
	return _noteOn.noteId;
}

//
double BLITSaw_oscillator_note::velocity()const
{
	return _noteOn.velocity;
}

// constructor
BLITSaw_oscillator::BLITSaw_oscillator()
{
	// sine wave table
	for(size_t ii = 0; ii< _sinTable.size()-1; ii++)
	{
		_sinTable[ii] = sin( 2.0*M_PI * ii/(_sinTable.size()-1));
	}
	_sinTable.back() = 0.0;

	_Leak = 0.995;
}

//
void BLITSaw_oscillator::setLeak(double value)
{
	_Leak = value;
}

//
double BLITSaw_oscillator::LinearInterpolatedSin( double x )
{
	//
	double pos = (_sinTable.size()-1) * x;

	//
	unsigned int idx_A = static_cast<int>(pos);

	//
	double s = pos - idx_A;

	//
	return (1.0-s) * _sinTable[idx_A] + s*_sinTable[idx_A+1];
}

//
double BLITSaw_oscillator::BLIT( double t, int N )
{
	//
	double x_denominator = LinearInterpolatedSin( 0.5*t );

	if( x_denominator < 1.0e-12 )
	{
		return 2.0*(2*N+1);
	}

	double x_numerator = LinearInterpolatedSin(::fmod((N+0.5)*t, 1.0));

	return 2.0*x_numerator/x_denominator;
}

//
void BLITSaw_oscillator::updateOscillater(BLITSaw_oscillator_note& note)
{
	note.t += note.dt;
	if ( 1.0 <= note.t )note.t -= 1.0;

	note.saw = note.saw*_Leak + (BLIT(note.t, note.n)-2.0)*note.dt;
}

} // namespace