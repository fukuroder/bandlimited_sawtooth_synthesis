#pragma once

// include
#include <array>

// class
class bandlimited_sawtooth_oscillator_note;

//
class bandlimited_sawtooth_oscillator
{
public:
	// constructor
	bandlimited_sawtooth_oscillator();

	//
	void setFeedback(double value);

	//
	void updateEnvelope(bandlimited_sawtooth_oscillator_note &note);

	//
	void updateOscillater(bandlimited_sawtooth_oscillator_note& note);

	//
	void setAttackTime(double attackTime);

	//
	void setReleaseTime(double releaseTime);

	//
	void setSampleRate(int srate);

protected:
	//
	std::array<double, (1<<13)+1> _sinTable;
	
	//
	double _feedback;

	//
	double _attack_decrement;

	//
	double _release_decrement;

	//
	int _srate;

	//
	double LinearInterpolatedSin( double iT );

	//
	double BLIT( double T, int N );
};
