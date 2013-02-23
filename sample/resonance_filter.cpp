#define _USE_MATH_DEFINES
#include "math.h"
#include "resonance_filter.h"

resonance_filter::resonance_filter()
{
	reset();
}

void resonance_filter::setSampleRate(double sampleRate)
{
	_sampleRate = sampleRate;
	reset();
}

void resonance_filter::reset()
{
	_x_buf[0] = _x_buf[1] = 0.0f;
	_y_buf[0] = _y_buf[1] = 0.0f;
}

void resonance_filter::setCutoff(double value)
{
	_param_filter_cutoff = value;
}

void resonance_filter::setResonance(double value)
{
	_param_filter_resonance = value;
}

void resonance_filter::setHigh(double value)
{
	_param_filter_high = value;
}

void resonance_filter::setBand(double value)
{
	_param_filter_band = value;
}

void resonance_filter::setLow(double value)
{
	_param_filter_low = value;
}

//----------------
// TODO: 説明
//----------------
void resonance_filter::updateFilter()
{
	bool a = false;
	if( _param_filter_cutoff_old != _param_filter_cutoff ||
		_param_filter_resonance_old != _param_filter_resonance )
	{
		a = true;
		_param_filter_cutoff_old = _param_filter_cutoff;
		_param_filter_resonance_old = _param_filter_resonance;
	}


	bool b = false;
	if( _param_filter_high_old != _param_filter_high ||
		_param_filter_band_old != _param_filter_band ||
		_param_filter_low_old != _param_filter_low )
	{
		b = true;
		_param_filter_high_old = _param_filter_high;
		_param_filter_band_old = _param_filter_band;
		_param_filter_low_old = _param_filter_low;
	}


	if( a == false && b == false )
	{
		return;
	}

	if( _param_filter_resonance < 1.0e-12 )
	{
		// ゼロ割回避
		return;
	}

	const double alpha = ::tan( _param_filter_cutoff * M_PI / _sampleRate );
	const double beta = alpha*alpha + alpha / _param_filter_resonance + 1.0;

	if( a )
	{
		// b1
		_filter_b1 = alpha*alpha - 1.0;
		_filter_b1 += _filter_b1;
		_filter_b1 /= beta;

		// b2
		_filter_b2
			= alpha*alpha
			- alpha/_param_filter_resonance
			+ 1.0;
		_filter_b2 /= beta;
	}

	if( a || b )
	{
		// a0
		_filter_a0
			= _param_filter_low*alpha*alpha
			+ _param_filter_band*alpha/_param_filter_resonance
			+ _param_filter_high;
		_filter_a0 /= beta;

		// a1
		_filter_a1
			= _param_filter_low*alpha*alpha
			- _param_filter_high;
		_filter_a1 += _filter_a1;
		_filter_a1 /= beta;

		// a2
		_filter_a2
			= _param_filter_low*alpha*alpha
			- _param_filter_band*alpha/_param_filter_resonance
			+ _param_filter_high;
		_filter_a2 /= beta;
	}
}

double resonance_filter::process(double value)
{
	double filterd_value
			= _filter_a0 * value
			+ _filter_a1 * _x_buf[0]
			+ _filter_a2 * _x_buf[1]
			- _filter_b1 * _y_buf[0]
			- _filter_b2 * _y_buf[1];

	_x_buf[1] = _x_buf[0];
	_x_buf[0] = value;
	_y_buf[1] = _y_buf[0];
	_y_buf[0] = filterd_value;

	return filterd_value;
}
