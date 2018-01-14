#include "NonLinearInstruments.hpp"
#include "classes/Luci.cpp"

// a small utility module for mixing 4 audio signals

struct LuciControl : Module {
	enum ParamIds {
		RANDOMIZE_PARAM,
		FREQUENCY_PARAM,
		INFLUENCE_COARSE_PARAM,
		INFLUENCE_FINE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		RANDOMIZE_INPUT,
		FREQUENCY_INPUT,
		INFLUENCE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		RANDOMIZE_OUTPUT,
		FREQUENCY_OUTPUT,
		INFLUENCE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		RANDOMIZE_LIGHT,
		NUM_LIGHTS
	};
		
	LuciControl() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
	// do the light thing
	float lightLambda = 0.075;
	float randomizeLight = 0.0;
	// hold randomize param value
	float gotRandomize = 0.f;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControl::step() {
	
		outputs[FREQUENCY_OUTPUT].value = params[FREQUENCY_PARAM].value ;
		outputs[INFLUENCE_OUTPUT].value = params[INFLUENCE_COARSE_PARAM].value + params[INFLUENCE_FINE_PARAM].value ;
		
		gotRandomize = params[RANDOMIZE_PARAM].value;
		outputs[RANDOMIZE_OUTPUT].value = gotRandomize;
		// Reset button light 
		if ( gotRandomize > 0 ) {
			randomizeLight = 1.0;
			}
		randomizeLight -= randomizeLight / lightLambda / engineGetSampleRate();
		lights[RANDOMIZE_LIGHT].value = randomizeLight;
		
}

LuciControlWidget::LuciControlWidget() {
	LuciControl *module = new LuciControl();
	setModule(module);
	box.size = Vec(12 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/LuciControl.svg")));
		addChild(panel);
	}
	
	addParam(createParam<LuciControlRandomizeButton>(Vec(35, 35), module, LuciControl::RANDOMIZE_PARAM, 0.0, 1.0, 0.0));
	addChild(createLight<luciControlRandomizeLight<BlueLight>>(Vec(35, 35), module, LuciControl::RANDOMIZE_LIGHT));
	addOutput(createOutput<PJ301MPort>(Vec(141, 55), module, LuciControl::RANDOMIZE_OUTPUT));	
	
	addParam(createParam<KorgLargeBlueKnob>(Vec(77, 140), module, LuciControl::FREQUENCY_PARAM, 0.0, 10.0, 1. ));
	addOutput(createOutput<PJ301MPort>(Vec(141, 158), module, LuciControl::FREQUENCY_OUTPUT));	
	
	addParam(createParam<KorgLargeBlueKnob>(Vec(15, 214), module, LuciControl::INFLUENCE_COARSE_PARAM, 1., 1.5, 1. ));
	addParam(createParam<KorgLargeBlueKnob>(Vec(77, 214), module, LuciControl::INFLUENCE_FINE_PARAM, -0.00124, 0.00124, 0. ));
	addOutput(createOutput<PJ301MPort>(Vec(141, 232), module, LuciControl::INFLUENCE_OUTPUT));	
		
	//addOutput(createOutput<PJ301MPort>(Vec(3, 310), module, LuciControl::OUTPUT_1));

//	addInput(createInput<PJ301MPort>(Vec(3, 40), module, LuciControl::INPUT_1));
//	addInput(createInput<PJ301MPort>(Vec(3, 90), module, LuciControl::INPUT_2));
//	addInput(createInput<PJ301MPort>(Vec(3, 140), module, LuciControl::INPUT_3));
//	addInput(createInput<PJ301MPort>(Vec(3, 190), module, LuciControl::INPUT_4));

}