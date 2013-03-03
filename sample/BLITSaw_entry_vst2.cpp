#include "public.sdk/source/vst/vst2wrapper/vst2wrapper.h"
#include "BLITSaw_guids.h"

//------------------------------------------------------------------------
::AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return Steinberg::Vst::Vst2Wrapper::create (GetPluginFactory(), Steinberg::Vst::BLITSawProcessorID, 'bLiT', audioMaster);
}
