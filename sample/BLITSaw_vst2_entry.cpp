#include "public.sdk/source/vst/vst2wrapper/vst2wrapper.h"
#include "BLITSaw_vst3_guids.h"

//------------------------------------------------------------------------
::AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return Steinberg::Vst::Vst2Wrapper::create (GetPluginFactory(), Steinberg::Vst::AGainProcessorUID, 'bLiT', audioMaster);
}
