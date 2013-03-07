#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "bandlimited_sawtooth_oscillator_note_vst3.h"
#include "bandlimited_sawtooth_oscillator.h"
#include "resonance_filter.h"
#include <array>

namespace Steinberg { namespace Vst {

//
class BLITSaw_processor : public AudioEffect
{
	// constructor(private)
	BLITSaw_processor();

public:
	// create
	static FUnknown* create(void* context);

	// from AudioEffect class
	virtual tresult PLUGIN_API initialize(FUnknown* context);
	virtual tresult PLUGIN_API setBusArrangements(
		SpeakerArrangement* inputs,
		int32 numIns,
		SpeakerArrangement* outputs,
		int32 numOuts
		);
	virtual tresult PLUGIN_API setProcessing (TBool state);
	virtual tresult PLUGIN_API process(ProcessData& data);


protected:

	// パラメータID.
	enum
	{
		feedback,   //
		coarse,		//
		fine,		//
		attack,		//
		release,	//
		cutoff,
		resonance,
		high,
		band,
		low,
	};

	//
	std::array<bandlimited_sawtooth_oscillator_note_vst3, 8> _notes;

	//
	bandlimited_sawtooth_oscillator blit;

	//
	resonance_filter _filter;
};

}} // namespace
