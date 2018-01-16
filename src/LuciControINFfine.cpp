/*
#include "NonLinearInstruments.hpp"

struct LuciControlINFfine : Module {
	enum ParamIds {
		INFLUENCE_FINE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		INFLUENCE_FINE_MOD_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		INFLUENCE_FINE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
		
	LuciControlINFfine() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
	
	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlINFfine::step() {
	
		outputs[INFLUENCE_FINE_OUTPUT].value = params[INFLUENCE_FINE_PARAM].value; //+ params[INFLUENCE_FINE_MOD].value;
		
}

LuciControlINFfineWidget::LuciControlINFfineWidget() {
	LuciControlINFfine *module = new LuciControlINFfine();
	setModule(module);
	box.size = Vec(25 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/LuciControlINFfine.svg")));
		addChild(panel);
	}
	
	addParam(createParam<LuciVeryLargeBlueKnob>(Vec(40, 55), module, LuciControlINFfine::INFLUENCE_FINE_PARAM, 0.f, 0.1f, 0.f ));
	addOutput(createOutput<PJ301MPort>(Vec(344, 172), module, LuciControlINFfine::INFLUENCE_FINE_OUTPUT));
	addInput(createInput<PJ3410Port>(Vec(2, 172), module, LuciControlINFfine::INFLUENCE_FINE_MOD_INPUT));		
	//addInput(createInput<PJ3410Port>(Vec(172, 344), module, LuciControlINFfine::INFLUENCE_FINE_INPUT));
		
	
}
*/