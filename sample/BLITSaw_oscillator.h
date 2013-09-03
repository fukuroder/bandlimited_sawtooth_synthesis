#pragma once

// include
#include <array>
#include "pluginterfaces/vst/ivstevents.h"

namespace Steinberg {namespace Vst {

//
class bandlimited_sawtooth_oscillator_note
{
public:
	//
	bandlimited_sawtooth_oscillator_note();

	//
	void trigger(const NoteOnEvent& noteOn);

	//
	int32 id()const;

	//
	double velocity()const;

	// ADSR
	enum ADSR
	{
		// 
		Off,

		//
		On,
	};

	//
	void setSampleRate(int srate);

	//
	void release();


	//
	double	t;

	//
	double	saw;
	
	//
	int		n;

	//
	double	dt;

	//
	int srate;

	ADSR adsr()const{return _adsr;};

protected:

	// ADSR
	ADSR	_adsr;

	NoteOnEvent _noteOn;

	static const int _note_no_center = 69;
};

//
class bandlimited_sawtooth_oscillator
{
public:
	// constructor
	bandlimited_sawtooth_oscillator();

	//
	void setLeak(double value);

	//
	void updateOscillater(bandlimited_sawtooth_oscillator_note& note);


protected:
	//
	std::array<double, (1<<13)+1> _sinTable;
	
	//
	double _Leak;

	//
	double LinearInterpolatedSin( double iT );

	//
	double BLIT( double T, int N );
};

}} //  namespace
