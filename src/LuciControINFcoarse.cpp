#include "NonLinearInstruments.hpp"

struct LuciControlINFcoarse : Module {
	enum ParamIds {
		INFLUENCE_COARSE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		INFLUENCE_COARSE_INPUT,
		//INFLUENCE_COARSE_MOD_INPUT,
		INFLUENCE_FINE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		INFLUENCE_COARSE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	LuciControlINFcoarse() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(INFLUENCE_COARSE_PARAM, 0.f, 10.f, 0.001f);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlINFcoarse::process(const ProcessArgs& args) {
	outputs[INFLUENCE_COARSE_OUTPUT].setVoltage(params[INFLUENCE_COARSE_PARAM].getValue() + params[INFLUENCE_FINE_INPUT].getValue());
}

struct LuciControlINFcoarseWidget : ModuleWidget { 
	LuciControlINFcoarseWidget(LuciControlINFcoarse *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciControlINFcoarse.svg")));
		
		addParam(createParam<LuciVeryLargeBlueKnob>(Vec(40, 55), module, LuciControlINFcoarse::INFLUENCE_COARSE_PARAM));
		
		addOutput(createOutput<PJ301MPort>(Vec(344, 172), module, LuciControlINFcoarse::INFLUENCE_COARSE_OUTPUT));
		//addInput(createInput<PJ3410Port>(Vec(2, 172), module, LuciControlINFcoarse::INFLUENCE_COARSE_MOD_INPUT));
		
		addInput(createInput<PJ3410Port>(Vec(172, 344), module, LuciControlINFcoarse::INFLUENCE_FINE_INPUT));
	}
};

Model *modelLuciControlINFcoarse = createModel<LuciControlINFcoarse, LuciControlINFcoarseWidget>("LuciControlINFL");
