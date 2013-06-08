#pragma once
#include "pluginterfaces/vst/ivstevents.h"

namespace Steinberg {namespace Vst {

/// BLITノコギリ波ノート基底クラス.
class bandlimited_sawtooth_oscillator_note
{
public:
	/// コンストラクタ.
	bandlimited_sawtooth_oscillator_note();

	// ノートオン
	void trigger(const NoteOnEvent& noteOn);

	// タグ取得.
	int32 id()const;

	/// ベロシティ取得.
	double velocity()const;

	// ADSR.
	enum ADSR
	{
		// 
		Off,

		//
		On,
	};

	//
	void setSampleRate(int srate);

	/// ノートリリース.
	void release();



	/// 現在の時間.
	double	t;

	/// 現在の値.
	double	saw;
	
	/// 倍音数.
	int		n;

	/// 刻み幅.
	double	dt;

	//
	int srate;

	ADSR adsr()const{return _adsr;};

protected:

	/// ADSR.
	ADSR	_adsr;

	NoteOnEvent _noteOn;

	// 中央のノートナンバー
	static const int _note_no_center = 69;
};
}}
