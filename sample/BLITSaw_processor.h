#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "BLITSaw_oscillator.h"
#include <array>

using namespace Steinberg;
using namespace Steinberg::Vst;
namespace MyVst {

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
		int32 numOuts);
	virtual tresult PLUGIN_API setProcessing (TBool state);
	virtual tresult PLUGIN_API process(ProcessData& data);

protected:

	//
	enum
	{
		Leak,
	};

	//
	std::array<BLITSaw_oscillator_note, 8> _notes;

	//
	BLITSaw_oscillator blit;
};

} // namespace
