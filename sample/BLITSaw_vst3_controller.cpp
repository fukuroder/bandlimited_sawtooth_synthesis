#include "BLITSaw_vst3_controller.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "pluginterfaces/base/ibstream.h"
#include <math.h>

namespace Steinberg {namespace Vst {

//-------------------------------------------------------------------------
BLITSaw_vst3_controller::BLITSaw_vst3_controller()
{
	setKnobMode( kLinearMode );
}

//-------------------------------------------------------------------------
FUnknown* BLITSaw_vst3_controller::create(void* context)
{
	return (IEditController*)new BLITSaw_vst3_controller();
}

//-------------------------------------------------------------------------
tresult PLUGIN_API BLITSaw_vst3_controller::initialize(FUnknown* context)
{
	tresult result = EditController::initialize(context); 
	if (result != kResultOk)
	{ 
		return result; 
	}

	parameters.addParameter(new BLITSaw_FeedBackParameter());
	parameters.addParameter(new BLITSaw_CoarsePitchParameter());
	parameters.addParameter(new BLITSaw_FinePitchParameter());
	parameters.addParameter(new BLITSaw_AttackParameter());
	parameters.addParameter(new BLITSaw_ReleaseParameter());
	parameters.addParameter(new BLITSaw_CutoffParameter());
	parameters.addParameter(new BLITSaw_ResonanceParameter());
	parameters.addParameter(new BLITSaw_HighParameter());
	parameters.addParameter(new BLITSaw_BandParameter());
	parameters.addParameter(new BLITSaw_LowParameter());

	return kResultOk;
}

//-------------------------------------------------------------------------
IPlugView* PLUGIN_API BLITSaw_vst3_controller::createView (const char* name)
{
	for( int ii = 0; ii < getParameterCount(); ii++ )
	{
		performEdit(ii, getParamNormalized(ii));
	}

	VST3Editor* editor = nullptr;
	if (name != nullptr && strcmp(name, ViewType::kEditor) == 0)
	{
		editor= new VSTGUI::VST3Editor(this, "view", "BLITSaw_vst3.uidesc");
		if( editor ) editor->setIdleRate(50);
	}
	return editor;
}

//tresult PLUGIN_API BLITSaw_vst3_controller::setComponentState (IBStream* state)
//{
//	return kResultOk;
//}

tresult PLUGIN_API BLITSaw_vst3_controller::setState (IBStream* state)
{
	// set parameter
	if( state )
	{
		for( int ii = 0; ii < getParameterCount(); ii++ )
		{
			ParamValue value;
			if( state->read(&value, sizeof(ParamValue)) == kResultTrue )
			{
				setParamNormalized(ii, value);
				performEdit(ii, value);
			}
			else
			{
				return kResultFalse;
			}
		}
	}
	return kResultOk;
}

tresult PLUGIN_API BLITSaw_vst3_controller::getState (IBStream* state)
{
	if( state )
	{
		for( int ii = 0; ii < getParameterCount(); ii++ )
		{
			ParamValue value = parameters.getParameter(ii)->getNormalized();
			if( state->write(&value, sizeof(ParamValue)) != kResultTrue )
			{
				return kResultFalse;
			}
		}
	}
	return kResultOk;
}

//-------------------------------------------------------------------------
BLITSaw_FeedBackParameter::BLITSaw_FeedBackParameter()
	:Parameter(L"Feedback", 0, L"%", 0.5)
{
}

void BLITSaw_FeedBackParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f",( 0.99 + 0.01 * normValue ) * 100);
}

//-------------------------------------------------------------------------
BLITSaw_CoarsePitchParameter::BLITSaw_CoarsePitchParameter()
	:Parameter(L"Coarse Pitch", 1, L"semitone", 0.5)
{
}

void BLITSaw_CoarsePitchParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%+d", static_cast<int>( 48 * normValue + 0.5 ) - 24);
}

//-------------------------------------------------------------------------
BLITSaw_FinePitchParameter::BLITSaw_FinePitchParameter()
	:Parameter(L"Fine Pitch", 2, L"cent", 0.5)
{
}

void BLITSaw_FinePitchParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%+d", static_cast<int>( 200 * normValue + 0.5 ) - 100);
}

//-------------------------------------------------------------------------
BLITSaw_AttackParameter::BLITSaw_AttackParameter()
	:Parameter(L"Attack Time", 3, L"msec", 0.05)
{
}

void BLITSaw_AttackParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", normValue * 0.2);
}

//-------------------------------------------------------------------------
BLITSaw_ReleaseParameter::BLITSaw_ReleaseParameter()
	:Parameter(L"Release Time", 4, L"msec", 0.05)
{
}

//-------------------------------------------------------------------------
void BLITSaw_ReleaseParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", normValue * 0.2);
}

//-------------------------------------------------------------------------
BLITSaw_CutoffParameter::BLITSaw_CutoffParameter()
	:Parameter(L"Cutoff Frequency", 5, L"Hz", 0.0)
{	
}

//-------------------------------------------------------------------------
void BLITSaw_CutoffParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", 200.0 * ::pow(20.0, normValue));
}

//-------------------------------------------------------------------------
BLITSaw_ResonanceParameter::BLITSaw_ResonanceParameter()
	:Parameter(L"Resonance", 6, L"", 0.0)
{
}

//-------------------------------------------------------------------------
void BLITSaw_ResonanceParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", 0.70710678118654757274 * (1.0 - normValue) + 20.0*normValue);
}

//-------------------------------------------------------------------------
BLITSaw_HighParameter::BLITSaw_HighParameter()
	:Parameter(L"High", 7, L"", 1.0)
{
}

//-------------------------------------------------------------------------
void BLITSaw_HighParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", normValue);
}

//-------------------------------------------------------------------------
BLITSaw_BandParameter::BLITSaw_BandParameter()
	:Parameter(L"Band", 8, L"", 1.0)
{
}

//-------------------------------------------------------------------------
void BLITSaw_BandParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", normValue);
}

//-------------------------------------------------------------------------
BLITSaw_LowParameter::BLITSaw_LowParameter()
	:Parameter(L"Low", 9, L"", 1.0)
{
}

//-------------------------------------------------------------------------
void BLITSaw_LowParameter::toString(ParamValue normValue, String128 string)const
{
	::swprintf_s(string, 128, L"%.3f", normValue);
}

}}
