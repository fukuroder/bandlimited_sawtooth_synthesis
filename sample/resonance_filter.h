#pragma once

class resonance_filter
{
protected:
	double _sampleRate;
	double _param_filter_cutoff;
	double _param_filter_cutoff_old;
	double _param_filter_resonance;
	double _param_filter_resonance_old;
	double _param_filter_high;
	double _param_filter_high_old;
	double _param_filter_band;
	double _param_filter_band_old;
	double _param_filter_low;
	double _param_filter_low_old;

	double _filter_a0;
	double _filter_a1;
	double _filter_a2;
	double _filter_b1;
	double _filter_b2;

	double _x_buf[2];
	double _y_buf[2];

public:
	resonance_filter();

	void setSampleRate(double sampleRate);
	void setCutoff(double value);
	void setResonance(double value);
	void setHigh(double value);
	void setBand(double value);
	void setLow(double value);

	void updateFilter();

	double process(double value);
	void reset();


};
