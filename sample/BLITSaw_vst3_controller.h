#pragma once
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {namespace Vst {

//-------------------------------------------------------------------------
// BLITSaw_vst3_controller Declaration
//-------------------------------------------------------------------------
class BLITSaw_vst3_controller : public EditController
{
	// コンストラクタ
	BLITSaw_vst3_controller();

public:
	// インスタンス生成
	static FUnknown* create(void* context);

	// 初期化（オーバーライド）
	virtual tresult PLUGIN_API initialize(FUnknown* context);

	virtual IPlugView* PLUGIN_API createView(const char* name);

	//virtual tresult PLUGIN_API setComponentState (IBStream* state);
	virtual tresult PLUGIN_API setState (IBStream* state);
	virtual tresult PLUGIN_API getState (IBStream* state);
	//virtual tresult PLUGIN_API setComponentHandler (IComponentHandler* handler);
};

// Feedback parameter
class BLITSaw_FeedBackParameter : public Parameter
{
public:
	BLITSaw_FeedBackParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_CoarsePitchParameter : public Parameter
{
public:
	BLITSaw_CoarsePitchParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_FinePitchParameter : public Parameter
{
public:
	BLITSaw_FinePitchParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_AttackParameter : public Parameter
{
public:
	BLITSaw_AttackParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_ReleaseParameter : public Parameter
{
public:
	BLITSaw_ReleaseParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_CutoffParameter : public Parameter
{
public:
	BLITSaw_CutoffParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_ResonanceParameter : public Parameter
{
public:
	BLITSaw_ResonanceParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_HighParameter : public Parameter
{
public:
	BLITSaw_HighParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_BandParameter : public Parameter
{
public:
	BLITSaw_BandParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

//
class BLITSaw_LowParameter : public Parameter
{
public:
	BLITSaw_LowParameter();
	virtual void toString(ParamValue normValue, String128 string)const;
};

}}
