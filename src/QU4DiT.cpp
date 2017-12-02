#include "NonLinearInstruments.hpp"

/* 
This instruments explores the Quadratic iterator, also known as Logistic map (after the Verhulst's logistic equation). More precisely, the chaotic range arising for parameter values above roughly 3.5
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

	/*float phase = 0.0;
	float blinkPhase = 0.0;*/
	
	float ax = 0.1;
	float ay = 0.1;
	float axnew = 0.0;
	float aynew = 0.0;
	float Cparam = 3.57;
	float Coffset = 0.0;

	QU4DiT() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiT::step() {
	/*
	// Implement a simple sine oscillator
	float deltaTime = 1.0 / engineGetSampleRate();

	// Compute the frequency from the pitch parameter and input
	float pitch = params[C_PARAM].value;
	pitch += inputs[CMOD_INPUT].value;
	pitch = clampf(pitch, -4.0, 4.0);
	float freq = 440.0 * powf(2.0, pitch);

	// Accumulate the phase
	phase += freq * deltaTime;
	if (phase >= 1.0)
		phase -= 1.0;

	// Compute the sine output
	float sine = sinf(2 * M_PI * phase);
	outputs[XN_OUTPUT].value = 5.0 * sine;

	// Blink light at 1Hz
	blinkPhase += deltaTime;
	if (blinkPhase >= 1.0)
		blinkPhase -= 1.0;
	lights[BLINK_LIGHT].value = (blinkPhase < 0.5) ? 1.0 : 0.0;
	*/
	
	Cparam = params[C_PARAM].value;
	Coffset = params[C_OFFSET].value * 0.199;
	axnew = Cparam * ax * ( 1 - ax );
	aynew = ( Cparam + Coffset ) * ay * ( 1 - ay );
	outputs[XN_OUTPUT].value = axnew * 5.;
	outputs[YN_OUTPUT].value = aynew * 5.;
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

	/*addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    */
	
	addParam(createParam<RoundHugeBlackKnob>(Vec(17, 40), module, QU4DiT::C_PARAM, 3.57, 3.8, 3.57));
	addParam(createParam<RoundBlackKnob>(Vec(28, 125), module, QU4DiT::C_OFFSET, 0.0, 1.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(28, 190), module, QU4DiT::CMOD_DEPTH, -3.0, 3.0, 0.0));
	
	addInput(createInput<PJ301MPort>(Vec(33, 250), module, QU4DiT::CMOD_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(15, 310), module, QU4DiT::XN_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(50, 310), module, QU4DiT::YN_OUTPUT));

	/*addChild(createLight<MediumLight<RedLight>>(Vec(41, 35 ), module, QU4DiT::BLINK_LIGHT));*/
}
