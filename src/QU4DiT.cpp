#include "NonLinearInstruments.hpp"

/* 
This instruments explores the Quadratic iterator, also known as Logistic map 
(after the Verhulst's logistic equation). 
More precisely, the chaotic range arising for parameter values above roughly 3.5
https://en.wikipedia.org/wiki/Logistic_map
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

	/* Init variables */
	
	float ax = 0.1;
	float ay = 0.1;
	float axnew = 0.0;
	float aynew = 0.0;
	float Cparam = 3.57;
	float Coffset = 0.0;
	float x_out = 0.0;
	float y_out = 0.0;

	/* END Init variables */

	QU4DiT() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiT::step() {
	
	
	Cparam = params[C_PARAM].value;
	
	Coffset = params[C_OFFSET].value * 0.199;
	
	axnew = Cparam * ax * ( 1 - ax );
	aynew = ( Cparam + Coffset ) * ay * ( 1 - ay );
	
	x_out = axnew * 5.;
	y_out = aynew * 5.;

	outputs[XN_OUTPUT].value = isfinite(x_out) ? x_out : 0.f;
	outputs[YN_OUTPUT].value = isfinite(y_out) ? y_out : 0.f;

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

	
	addParam(createParam<RoundHugeBlackKnob>(Vec(17, 40), module, QU4DiT::C_PARAM, 3.57, 3.8, 3.57));
	addParam(createParam<RoundBlackKnob>(Vec(28, 125), module, QU4DiT::C_OFFSET, 0.0, 1.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(28, 190), module, QU4DiT::CMOD_DEPTH, -3.0, 3.0, 0.0));
	
	addInput(createInput<PJ301MPort>(Vec(33, 250), module, QU4DiT::CMOD_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(15, 310), module, QU4DiT::XN_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(50, 310), module, QU4DiT::YN_OUTPUT));

}
