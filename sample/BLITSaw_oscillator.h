#pragma once

// include
#include <array>
#include "pluginterfaces/vst/ivstevents.h"

namespace Steinberg {namespace Vst {

//
class BLITSaw_oscillator_note
{
public:
	//
	BLITSaw_oscillator_note();

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
class BLITSaw_oscillator
{
public:
	// constructor
	BLITSaw_oscillator();

	//
	void setLeak(double value);

	//
	void updateOscillater(BLITSaw_oscillator_note& note);


protected:
	//
	std::array<double, (1<<10)+1> _sinTable;
	
	//
	double _Leak;

	//
	double LinearInterpolatedSin( double iT );

	//
	double BLIT( double T, int N );
};

}} //  namespace
