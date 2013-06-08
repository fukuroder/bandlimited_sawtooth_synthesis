#define _USE_MATH_DEFINES
#include <math.h>
#include "bandlimited_sawtooth_oscillator.h"
#include "bandlimited_sawtooth_oscillator_note.h"

#ifdef _DEBUG
#include <windows.h>
#endif

namespace Steinberg { namespace Vst {

// constructor
bandlimited_sawtooth_oscillator::bandlimited_sawtooth_oscillator()
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
void bandlimited_sawtooth_oscillator::setLeak(double value)
{
	_Leak = value;
}

//-------------
// 
//-------------
double bandlimited_sawtooth_oscillator::LinearInterpolatedSin( double x )
{
#ifdef _DEBUG
	if( x < 0.0 || 1.0 < x)
	{
		::OutputDebugString(L"x:range error");
		return 0.0;
	}
#endif

	// スケーリング
	double pos = (_sinTable.size()-1) * x;

	// 位置を計算
	unsigned int idx_A = static_cast<int>(pos);

	// 距離を算出
	double s = pos - idx_A;

	// 線形補間
	return (1.0-s) * _sinTable[idx_A] + s*_sinTable[idx_A+1];
}

//-------------
// BLIT
//-------------
double bandlimited_sawtooth_oscillator::BLIT( double t, int N )
{
	// 分母
	double x_denominator = LinearInterpolatedSin( 0.5*t );

	if( x_denominator < 1.0e-12 )// TODO: 要チューニング
	{
#ifdef _DEBUG
		::OutputDebugString(L"ロピタルの定理を適用");
#endif
		// ゼロ割防止。ロピタルの定理を適用
		return 2.0*(2*N+1);
	}

	// 分子
	double x_numerator = LinearInterpolatedSin(::fmod((N+0.5)*t, 1.0));

	return 2.0*x_numerator/x_denominator;
}

//-------------
//
//-------------
void bandlimited_sawtooth_oscillator::updateOscillater(bandlimited_sawtooth_oscillator_note& note)
{
	note.t += note.dt;
	if ( 1.0 <= note.t )note.t -= 1.0;

	note.saw = note.saw*_Leak + (BLIT(note.t, note.n)-2.0)*note.dt;
}

}}