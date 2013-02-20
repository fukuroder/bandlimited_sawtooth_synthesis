#pragma once

// include
#include "bandlimited_sawtooth_oscillator_note.h"
#include "pluginterfaces/vst/ivstevents.h"

namespace Steinberg {namespace Vst {

/// FLStudio用BLITノコギリ波ノートクラス.
class bandlimited_sawtooth_oscillator_note_vst3 : public bandlimited_sawtooth_oscillator_note
{
public:

	/// コンストラクタ.
	bandlimited_sawtooth_oscillator_note_vst3(int sampleRate);

	virtual ~bandlimited_sawtooth_oscillator_note_vst3();

	/// ノートオン.
	void trigger(const NoteOnEvent& noteOn);

	/// タグ取得.
	int32 id()const;

	/// 周波数更新
	void updateFrequency();

	void setFinePitch(double finePitch);

	void setCorasePitch(double CorasePitch);

	void setPitchBend(double pitchBend);

	/// ノート破棄.
	virtual void kill();

	/// ベロシティ取得.
	virtual double velocity();

protected:

	NoteOnEvent _noteOn;

	int _sampleRate;

	/// 周波数.
	double _old_pitch_bend;
	double _pitch_bend;

	double _old_param_osci_coarse;
	double _param_osci_coarse;

	double _old_param_osci_fine;
	double _param_osci_fine;

	/// 中央のノートナンバー
	static const int _note_no_center = 69;
};

}}