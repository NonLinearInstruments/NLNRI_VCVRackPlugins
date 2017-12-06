#include "NonLinearInstruments.hpp"

/* 
This instrument explores the Quadratic iterator, also known as Logistic map 
(after the Verhulst's logistic equation). 
More precisely, the chaotic range arising for parameter values above roughly 3.5
https://en.wikipedia.org/wiki/Logistic_map

Panel .svg and logo by Alfredo Santamaría http://www.hakken.com.mx/gui.php

Changelog:

v0.5.0 : first release
v0.5.1 : Changed SVG panel - minor code cleansing
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
	float x_out = 0.0;
	float y_out = 0.0;
	float C_max = 3.9;
	float C_min = 3.56;
	float Off_range = 3.999999 - C_max;
	float C_range = C_max - C_min;
	float C_value = C_min;
	float Cmod_value = 0.0;
	float Cmod_depth_param = 0.0;

	
	QU4DiT() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiT::step() {
	
	Cmod_depth_param = clampf ( params[CMOD_DEPTH].value, 0.f, 1.f );
	Cmod_depth_param *= Cmod_depth_param;
	Cmod_value = clampf ( inputs[CMOD_INPUT].value / 5.f , -1.f, 1.f ) * Cmod_depth_param;
	C_value =  C_range * clampf ( params[C_PARAM].value, 0.f, 1.f );
	Cmod_value = Cmod_value * (C_max - C_value);
	
	Cparam = clampf ( C_min + C_value + Cmod_value, C_min , C_max );
						
	Coffset = Off_range * clampf ( params[C_OFFSET].value, 0.f, 1.f );
	
	axnew = Cparam * ax * ( 1.f - ax );
	aynew = ( Cparam + Coffset ) * ay * ( 1.f - ay );
	
	x_out = axnew * 5.f;
	y_out = aynew * 5.f;

	outputs[XN_OUTPUT].value = std::isfinite(x_out) ? x_out : 0.f;
	outputs[YN_OUTPUT].value = std::isfinite(y_out) ? y_out : 0.f;

	ax = axnew;
	ay = aynew;
	
}


QU4DiTWidget::QU4DiTWidget() {
	QU4DiT *module = new QU4DiT();
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/QU4DiT.svg")));
		addChild(panel);
	}

	
	addParam(createParam<RoundHugeBlackKnob>(Vec(17, 40), module, QU4DiT::C_PARAM, 0.0, 1.0, 0.5 ));
	addParam(createParam<RoundBlackKnob>(Vec(28, 125), module, QU4DiT::C_OFFSET, 0.0, 1.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(28, 190), module, QU4DiT::CMOD_DEPTH, 0.0, 1.0, 0.0));
	
	addInput(createInput<PJ301MPort>(Vec(33, 250), module, QU4DiT::CMOD_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(15, 310), module, QU4DiT::XN_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(50, 310), module, QU4DiT::YN_OUTPUT));

}
