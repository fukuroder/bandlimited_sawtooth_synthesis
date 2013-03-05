#include "bandlimited_sawtooth_oscillator_note_vst3.h"
#include <math.h>

namespace Steinberg {namespace Vst {
//----------------
// コンストラクタ
//----------------
bandlimited_sawtooth_oscillator_note_vst3::bandlimited_sawtooth_oscillator_note_vst3()
:_old_pitch_bend(0.0),_pitch_bend(0.0)
{
}

bandlimited_sawtooth_oscillator_note_vst3::~bandlimited_sawtooth_oscillator_note_vst3()
{
	if( adsr != Silent )kill();
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note_vst3::trigger(const NoteOnEvent& noteOn)
{
	_noteOn = noteOn; // コピー

	double pitch = 440.0*( ::pow(2.0, ( _noteOn.pitch + _param_osci_coarse - _note_no_center)/12.0 + _param_osci_fine/1200.0 + _pitch_bend));
	bandlimited_sawtooth_oscillator_note::trigger(pitch);

	_old_pitch_bend = _pitch_bend;
	_old_param_osci_coarse = _param_osci_coarse;
	_old_param_osci_fine = _param_osci_fine;
}

	/// タグ取得.
int32 bandlimited_sawtooth_oscillator_note_vst3::id()const
{
	//return _noteOn.noteId;
	return _noteOn.pitch;
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note_vst3::updateFrequency()
{
	if( adsr == Silent )
	{
		return;
	}

	if( _old_pitch_bend != _pitch_bend ||
		_old_param_osci_coarse != _param_osci_coarse ||
		_old_param_osci_fine != _param_osci_fine)
	{
		double pitch = 440.0*( ::pow(2.0, ( _noteOn.pitch + _param_osci_coarse - _note_no_center)/12.0 + _param_osci_fine/1200.0 + _pitch_bend));
		bandlimited_sawtooth_oscillator_note::updateFrequency(pitch);

		_old_pitch_bend = _pitch_bend;
		_old_param_osci_coarse = _param_osci_coarse;
		_old_param_osci_fine = _param_osci_fine;
	}
}

//---------
//
//---------
double bandlimited_sawtooth_oscillator_note_vst3::velocity()
{
	return _noteOn.velocity;
}

//---------
//
//---------
void bandlimited_sawtooth_oscillator_note_vst3::kill()
{
}

//
void bandlimited_sawtooth_oscillator_note_vst3::setFinePitch(double finePitch)
{
	_param_osci_fine = finePitch;
}

//
void bandlimited_sawtooth_oscillator_note_vst3::setCorasePitch(double CorasePitch)
{
	_param_osci_coarse = CorasePitch;
}

//
void bandlimited_sawtooth_oscillator_note_vst3::setPitchBend(double pitchBend)
{
	_pitch_bend = pitchBend;
}

}}
