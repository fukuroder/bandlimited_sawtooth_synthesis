#pragma once

// include
#include <array>

// class
class bandlimited_sawtooth_oscillator_note;

class bandlimited_sawtooth_oscillator
{
public:
	/// コンストラクタ
	bandlimited_sawtooth_oscillator();

	///
	void setFeedback(double value);

	void updateEnvelope(bandlimited_sawtooth_oscillator_note &note);

	///
	void updateOcsillater(bandlimited_sawtooth_oscillator_note& note);

	void initializeOcsillater( bandlimited_sawtooth_oscillator_note& note );

		///
	double _attack_decrement;

	void setAttackTime(double attackTime, int sampleRate)
	{
		if( attackTime > 1.0e-12)
		{
			_attack_decrement = 1.0 / (attackTime * sampleRate);
		}
		else
		{
			_attack_decrement = 1.0;
		}
	}

	double _release_decrement;

	void setReleaseTime(double releaseTime, int sampleRate)
	{
		if( releaseTime > 1.0e-12)
		{
			_release_decrement = 1.0 / (releaseTime * sampleRate);
		}
		else
		{
			_release_decrement = 1.0;
		}
	}

protected:

	std::array<double, (1<<13)+1> _sinTable;
	double _feedback;

	//
	double LinearInterpolatedSin( double iT );

	//
	double BLIT( double T, int N );
};
