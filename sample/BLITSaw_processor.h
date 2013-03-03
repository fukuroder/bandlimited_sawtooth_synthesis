﻿#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"

#include "bandlimited_sawtooth_oscillator_note_vst3.h"
#include "bandlimited_sawtooth_oscillator.h"
#include "resonance_filter.h"

#include <array>

namespace Steinberg { namespace Vst {

//-------------------------------------------------------------------------
// BLITSaw_processor Declaration
//-------------------------------------------------------------------------
class BLITSaw_processor : public AudioEffect
{
	/*コンストラクタ*/ 
	BLITSaw_processor();

public:
	/*インスタンス生成*/
	static FUnknown* createInstance(void* context);

	/*初期化（オーバーライド）*/
	virtual tresult PLUGIN_API initialize(FUnknown* context);

	/*バス設定（オーバーライド）*/
	virtual tresult PLUGIN_API setBusArrangements(
		SpeakerArrangement* inputs,
		int32 numIns,
		SpeakerArrangement* outputs,
		int32 numOuts
	);

	/*音声処理（オーバーライド）*/
	virtual tresult PLUGIN_API process(ProcessData& data);

	virtual tresult PLUGIN_API setProcessing (TBool state);

protected:

	/// パラメータID.
	enum
	{
		feedback,
		coarse,		///<
		fine,		///<
		attack,		///<
		release,	///<
		cutoff,
		resonance,
		high,
		band,
		low,
	};

	std::array<bandlimited_sawtooth_oscillator_note_vst3, 8> _notes;

	bandlimited_sawtooth_oscillator blit;

	resonance_filter _filter;
};
}}