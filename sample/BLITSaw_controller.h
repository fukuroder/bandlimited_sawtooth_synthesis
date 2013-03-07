#pragma once
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {namespace Vst {

// controller
class BLITSaw_controller : public EditController
{
	// constructor(private)
	BLITSaw_controller();

public:
	// create
	static FUnknown* create(void* context);

	// from EditController class
	virtual tresult PLUGIN_API initialize(FUnknown* context);
	virtual IPlugView* PLUGIN_API createView(const char* name);
	virtual tresult PLUGIN_API setState (IBStream* state);
	virtual tresult PLUGIN_API getState (IBStream* state);
};

// feedback Parameter
class BLITSaw_FeedBackParameter : public Parameter
{
public:
	BLITSaw_FeedBackParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// coarse pitch parameter
class BLITSaw_CoarsePitchParameter : public Parameter
{
public:
	BLITSaw_CoarsePitchParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// fine pitch parameter
class BLITSaw_FinePitchParameter : public Parameter
{
public:
	BLITSaw_FinePitchParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// attack parameter
class BLITSaw_AttackParameter : public Parameter
{
public:
	BLITSaw_AttackParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// release parameter
class BLITSaw_ReleaseParameter : public Parameter
{
public:
	BLITSaw_ReleaseParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// cutoff parameter
class BLITSaw_CutoffParameter : public Parameter
{
public:
	BLITSaw_CutoffParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// resonance Parameter
class BLITSaw_ResonanceParameter : public Parameter
{
public:
	BLITSaw_ResonanceParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// high parameter
class BLITSaw_HighParameter : public Parameter
{
public:
	BLITSaw_HighParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// band parameter
class BLITSaw_BandParameter : public Parameter
{
public:
	BLITSaw_BandParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

// low parameter
class BLITSaw_LowParameter : public Parameter
{
public:
	BLITSaw_LowParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

}} // namespace
