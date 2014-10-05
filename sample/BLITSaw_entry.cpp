#include "BLITSaw_processor.h"
#include "BLITSaw_controller.h"
#include "BLITSaw_guids.h"
#include "public.sdk/source/main//pluginfactoryvst3.h"

//
bool InitModule()
{
	// nothing to do
	return true;
}

//
bool DeinitModule()
{
	// nothing to do
	return true;
}

namespace MyVst{
	// define factory
	BEGIN_FACTORY_DEF(
		"fukuroda",							// vendor
		"https://github.com/fukuroder",		// url
		"mailto:fukuroder@live.jp")			// e-mail

		// register processor
		DEF_CLASS2(
		INLINE_UID_FROM_FUID(BLITSawProcessorID),	// processor's GUID
		PClassInfo::kManyInstances,					// ?
		kVstAudioEffectClass,						// category
		"BLITSaw",									// plug-in name
		kDistributable,								// Component flag
		PlugType::kInstrumentSynth,					// sub category
		"1.0.0.000",								// plug-in version
		kVstVersionString,							// VSTSDK version
		BLITSaw_processor::create)					// create method

		// register controller
		DEF_CLASS2(
		INLINE_UID_FROM_FUID(BLITSawControllerID),	// controller's GUID
		PClassInfo::kManyInstances,					// ?
		kVstComponentControllerClass,				// category
		"BLITSaw Controller",						// plug-in name
		0,											// N/A
		"",											// N/A
		"1.0.0.000",								// plug-in version
		kVstVersionString,							// create method
		BLITSaw_controller::create)					// create method

	END_FACTORY
} // namespace
