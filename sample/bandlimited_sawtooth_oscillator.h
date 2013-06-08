#pragma once

// include
#include <array>

namespace Steinberg {namespace Vst {

// class
class bandlimited_sawtooth_oscillator_note;

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

}}