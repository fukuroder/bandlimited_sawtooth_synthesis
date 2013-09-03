#include "BLITSaw_controller.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "pluginterfaces/base/ibstream.h"

namespace Steinberg { namespace Vst {

//
BLITSaw_controller::BLITSaw_controller()
{
}

//
FUnknown* BLITSaw_controller::create(void* context)
{
	return (IEditController*)new BLITSaw_controller();
}

//
tresult PLUGIN_API BLITSaw_controller::initialize(FUnknown* context)
{
	tresult result = EditController::initialize(context);
	if (result != kResultOk)
	{
		return result;
	}

	parameters.addParameter(new BLITSaw_LeakParameter());

	return kResultOk;
}

//
BLITSaw_LeakParameter::BLITSaw_LeakParameter()
	:Parameter(L"Leak", 0, L"%", 0.5)
{
}

void BLITSaw_LeakParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f",( 0.99 + 0.01 * normValue ) * 100);
}

}} // namespace
