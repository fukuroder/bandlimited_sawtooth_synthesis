#include "BLITSaw_processor.h"
#include "BLITSaw_controller.h"
#include "BLITSaw_guids.h"
#include "public.sdk/source/main//pluginfactoryvst3.h"

//------------------------------------------------------------------------
// DLLロード後に呼ばれる
//------------------------------------------------------------------------
bool InitModule()
{
	/*何もしない*/
	return true;
}

//------------------------------------------------------------------------
// DLLアンロード後に呼ばれる
//------------------------------------------------------------------------
bool DeinitModule()
{
	/*何もしない*/
	return true;
}

using namespace Steinberg::Vst;

//------------------------------------------------------------------------
// ファクトリ定義
//------------------------------------------------------------------------
BEGIN_FACTORY_DEF(
	"fukuroda",							// 作成者
	"https://github.com/fukuroder",		// ホムペ
	"mailto:fukuroder@live.jp"			// メアド
)

/*プロセッサーの登録*/
DEF_CLASS2(
	INLINE_UID_FROM_FUID(BLITSawProcessorID),/*（決め打ち）*/
	PClassInfo::kManyInstances,	/*（決め打ち）*/
	kVstAudioEffectClass,		/*プロセッサーですよ*/
	"BLITSawOscillatorVST3",					/*プラグイン名*/
	kDistributable,		/*プロセッサーとコントローラーが分かれてますよ*/
	PlugType::kInstrumentSynth,	/*サブカテゴリー*/
	"1.0.0.000",				/*プラグインバージョン*/
	kVstVersionString,			/*（決め打ち）*/
	BLITSaw_processor::createInstance		/*BLITSaw_processorインスタンス生成メソッド*/
)

/*コントローラーの登録*/
DEF_CLASS2(
	INLINE_UID_FROM_FUID(BLITSawControllerID),/*（決め打ち）*/
	PClassInfo::kManyInstances,		/*（決め打ち）*/
	kVstComponentControllerClass,	/*コントローラーですよ*/
	"BLITSawOscillatorVST3 Controller",			/*プラグイン名*/
	0,								/*（未使用）*/
	"",								/*（未使用）*/
	"1.0.0.000",					/*プラグインバージョン*/
	kVstVersionString,				/*（決め打ち）*/
	BLITSaw_controller::create	/*BLITSaw_controllerインスタンス生成メソッド*/
)
END_FACTORY
