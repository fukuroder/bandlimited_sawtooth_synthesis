#include "BLITSaw_vst3.h"

#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/ivstevents.h"
#include <algorithm>


namespace Steinberg { namespace Vst {
//-------------------------------------------------------------------------
// BLITSaw_vst3 Implementation
//-------------------------------------------------------------------------
BLITSaw_vst3::BLITSaw_vst3()
{
	/*コントローラーを登録する*/
	setControllerClass(FUID(CONTROLLER_UID1,CONTROLLER_UID2,CONTROLLER_UID3,CONTROLLER_UID4));
}

//-------------------------------------------------------------------------
FUnknown* BLITSaw_vst3::createInstance(void* context)
{
	return (IAudioProcessor*)new BLITSaw_vst3();
}

//-------------------------------------------------------------------------
tresult PLUGIN_API BLITSaw_vst3::initialize(FUnknown* context)
{
	/*親クラス初期化処理*/
	tresult result = AudioEffect::initialize(context);
	if(result != kResultOk)
	{
		return result;
	}

	/*バスの設定*/
	addAudioInput(STR16("Stereo In"), SpeakerArr::kStereo);
	addAudioOutput(STR16("Stereo Out"), SpeakerArr::kStereo);

	return kResultOk;
}

//-------------------------------------------------------------------------
tresult PLUGIN_API BLITSaw_vst3::setBusArrangements(
	SpeakerArrangement* inputs,
	int32 numIns,
	SpeakerArrangement* outputs,
	int32 numOuts
){
	if( numIns == 1 && numOuts == 1 )
	{
		if( inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo )
		{
			return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
		}
	}
	return kResultFalse;
}

tresult PLUGIN_API BLITSaw_vst3::setProcessing (TBool state)
{
	// state 起動1 終了0
	if( state == 1 )
	{
		_notes.resize( 8, bandlimited_sawtooth_oscillator_note_vst3(processSetup.sampleRate));
		_filter.setSampleRate( processSetup.sampleRate );
	}

	return kResultOk;
}

//-------------------------------------------------------------------------
tresult PLUGIN_API BLITSaw_vst3::process(ProcessData& data)
{
	// update parameters
	if( data.inputParameterChanges )
	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
		for( int32 ii = 0; ii < numParamsChanged; ii++ )
		{
			IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(ii);
			if( paramQueue )
			{
				int32 offsetSamples;
				double value;
				// 末尾の値を取得
				if(paramQueue->getPoint(paramQueue->getPointCount() - 1, offsetSamples, value) == kResultTrue)
				{
					ParamID id = paramQueue->getParameterId();
					if( id == feedback )
					{
						// -> [0.99, 1.0]
						double feedback = 0.99 + 0.01 * value;  
						blit.setFeedback(feedback);
					}
					else if( id == coarse )
					{
						double coarse_pitch = static_cast<int>( 48 * value + 0.5 ) - 24;

						for(auto note = _notes.begin(); note != _notes.end(); ++note)
						{
							note->setCorasePitch( coarse_pitch );
						}
					}
					else if( id == fine )
					{
						double finepitch = static_cast<int>( 200 * value + 0.5 ) - 100;
						for(auto note = _notes.begin(); note != _notes.end(); ++note)
						{
							note->setFinePitch( finepitch );
						}
					}
					else if( id == attack )
					{
						double attack_time = value * 0.2; // [0, 0.2]
						blit.setAttackTime( attack_time, processSetup.sampleRate );
					}
					else if( id == release )
					{
						double release_time = value * 0.2; // [0, 0.2]
						blit.setReleaseTime( release_time, processSetup.sampleRate );
					}
					else if( id == cutoff )
					{
						double cutoff_freq = 200.0 * pow(20.0, (double)value); // [200, 4000]
						_filter.setCutoff( cutoff_freq );
		
					}
					else if( id == resonance )
					{
						double q = 0.70710678118654757274 * (1.0 - value) + 20.0*value;
						_filter.setResonance( q );
					}
					else if( id == high )
					{
						_filter.setHigh( value );
					}
					else if( id == band )
					{
						_filter.setBand( value );
					}
					else if( id == low )
					{
						_filter.setLow( value );
					}
				}
			}
		}
	}


	// process events
	if( data.inputEvents )
	{
		int nEventCount = data.inputEvents->getEventCount();

		for( int ii = 0; ii < nEventCount; ii++ )
		{
			Event e;
			tresult result = data.inputEvents->getEvent(ii, e);
			if( result != kResultOk )continue;

			if( e.type == Event::kNoteOnEvent )
			{
				// 利用可能なノートを検索する
				auto available_note = std::find_if(
					_notes.begin(),
					_notes.end(), 
					[](const bandlimited_sawtooth_oscillator_note_vst3& n){return n.adsr == bandlimited_sawtooth_oscillator_note::Silent;}); 

				if( available_note != _notes.end() )
				{
					// ノートON
					available_note->trigger( e.noteOn );
				}
			}
			else if( e.type == Event::kNoteOffEvent )
			{
				int32 note_id = e.noteOff.noteId;
				auto target_note = std::find_if(
					_notes.begin(),
					_notes.end(), 
					[note_id](const bandlimited_sawtooth_oscillator_note_vst3& n){return n.id() == note_id;}); 
				if( target_note != _notes.end() )
				{
					// ノートOFF
					target_note->release();
				}
			}
			else if( e.type == Event::kDataEvent )
			{
				unsigned char status = e.data.bytes[0] & 0xf0;	// ignoring channel


				if( status == 0xE0 )
				{
					unsigned char data1 = e.data.bytes[1] & 0x7f;
					unsigned char data2 = e.data.bytes[2] & 0x7f;

					double pitch_bend = (( data1 + data2*128 ) - 8192 ) / 8192.0;

					for(auto note = _notes.begin(); note != _notes.end(); ++note)
					{
						note->setPitchBend( pitch_bend );
					}
				}
			}


		}
	}

	for(auto note = _notes.begin(); note != _notes.end(); ++note)
	{
		// ピッチを更新
		note->updateFrequency();
	}

	
	_filter.updateFilter();

	/*--------*/
	/*音声処理*/
	/*--------*/
	if (data.numInputs == 1 && data.numOutputs == 1 )
	{
		if( data.inputs[0].numChannels == 2 )
		{
			//float** in  = data.inputs[0].channelBuffers32;
			float** out = data.outputs[0].channelBuffers32;

			const int32 sampleFrames = data.numSamples;
			for( int ii = 0; ii < sampleFrames; ii++ )
			{
				double value = 0.0;
				for(auto note = _notes.begin(); note != _notes.end(); ++note)
				{	
					if( note->adsr == bandlimited_sawtooth_oscillator_note::Silent )continue;

					// ノート毎の音を足し合わせる
					value += note->saw * note->envelope * note->velocity();
		
					// オシレーター更新
					blit.updateOcsillater( *note );

					// エンベロープ更新
					blit.updateEnvelope( *note );
				}

				//
				// フィルタを掛けたければ掛ける
				//
				double filterd_value = _filter.process(value);

				// 出力バッファに設定する
				double pan = 0.0;
				out[0][ii] = static_cast<float>( filterd_value * (1.0 - pan) * 0.5 );
				out[1][ii] = static_cast<float>( filterd_value * (1.0 + pan) * 0.5 );
			}
		}
	}
	return kResultOk;
}

}}
