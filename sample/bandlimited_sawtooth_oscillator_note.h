#pragma once

/// BLITノコギリ波ノート基底クラス.
class bandlimited_sawtooth_oscillator_note
{
public:

	/// ADSR.
	enum ADSR
	{
		Silent,	///< 無音
		Attack,	///< アタック
		Const,	///< 一定
		Release ///< リリース
	};

	/// コンストラクタ.
	bandlimited_sawtooth_oscillator_note();

	//void updateEnvelope();

	/// ノートオン.
	void trigger(double pitch, int srate);

	/// 周波数更新.
	void updateFrequency(double pitch, int srate);

	void setFinePitch(double finePitch);

	void setCorasePitch(double CorasePitch);

	/// ノートリリース.
	void release();

	/// ノート破棄.
	virtual void kill() = 0;

	/// ベロシティ取得.
	virtual double velocity() = 0;

	/// ADSR.
	ADSR	adsr;

	/// エンベロープ.
	double	envelope;

	/// 現在の時間.
	double	t;

	/// 現在の値.
	double	saw;
	
	/// 倍音数.
	int		n;

	/// 刻み幅.
	double	dt;
};
