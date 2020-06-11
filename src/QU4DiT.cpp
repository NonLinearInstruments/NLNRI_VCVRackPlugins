#include "NonLinearInstruments.hpp"

/* 
This instrument explores the Quadratic iterator, also known as Logistic map 
(after the Verhulst's logistic equation). 
More precisely, the chaotic range arising for parameter values above roughly 3.5
https://en.wikipedia.org/wiki/Logistic_map

Panel .svg and logo by Alfredo Santamaría http://www.hakken.com.mx/gui.php
*/

struct QU4DiT : Module {
	enum ParamIds {
		C_PARAM,
		CMOD_DEPTH,
		C_OFFSET,
		NUM_PARAMS
	};
	enum InputIds {
		CMOD_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		XN_OUTPUT,
		YN_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	float ax = 0.1;
	float ay = 0.1;
	float axnew = 0.0;
	float aynew = 0.0;
	float Cparam = 3.57;
	float Coffset = 0.0;
	float Xout = 0.0;
	float y_out = 0.0;
	float Cmax = 3.9;
	float Cmin = 3.56;
	float Off_range = 3.999999 - Cmax;
	float C_range = Cmax - Cmin;
	float Cvalue = Cmin;
	float CmodValue = 0.0;
	float CmodDepthParam = 0.0;

	QU4DiT() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(C_PARAM, 0.0, 1.0, 0.5);
		configParam(C_OFFSET, 0.0, 1.0, 0.0);
		configParam(CMOD_DEPTH, 0.0, 1.0, 0.0);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiT::process(const ProcessArgs& args) {
	CmodDepthParam = clamp ( params[CMOD_DEPTH].getValue(), 0.f, 1.f );
	CmodValue = clamp ( inputs[CMOD_INPUT].getVoltage() / 5.f , -1.f, 1.f ) * CmodDepthParam * .025f;
	Cvalue =  C_range * clamp ( params[C_PARAM].getValue(), 0.f, 1.f );
	Cparam = clamp ( Cmin + Cvalue + CmodValue, Cmin , Cmax );
	Coffset = Off_range * clamp ( params[C_OFFSET].getValue(), 0.f, 1.f );
	axnew = Cparam * ax * ( 1.f - ax );
	aynew = ( Cparam + Coffset ) * ay * ( 1.f - ay );
	Xout = axnew * 10.f - 5.f;
	y_out = aynew * 10.f - 5.f;
	outputs[XN_OUTPUT].setVoltage(std::isfinite(Xout) ? Xout : 0.f);
	outputs[YN_OUTPUT].setVoltage(std::isfinite(y_out) ? y_out : 0.f);
	ax = axnew;
	ay = aynew;
}

struct QU4DiTWidget : ModuleWidget { 
	QU4DiTWidget(QU4DiT *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/QU4DiT.svg")));

		addParam(createParam<KorgLargeGoldKnob>(Vec(17, 58), module, QU4DiT::C_PARAM));
		addParam(createParam<KorgMedGreyKnob>(Vec(26, 140), module, QU4DiT::C_OFFSET));
		addParam(createParam<KorgMedGreyKnob>(Vec(26, 200), module, QU4DiT::CMOD_DEPTH));

		addInput(createInput<PJ301MPort>(Vec(32, 260), module, QU4DiT::CMOD_INPUT));

		addOutput(createOutput<PJ301MPort>(Vec(15, 310), module, QU4DiT::XN_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(50, 310), module, QU4DiT::YN_OUTPUT));
	}
};

Model *modelQU4DiT = createModel<QU4DiT, QU4DiTWidget>("QU4DiT");
