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

	LuciControlINFcoarse() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlINFcoarse::step() {

		outputs[INFLUENCE_COARSE_OUTPUT].value = params[INFLUENCE_COARSE_PARAM].value + params[INFLUENCE_FINE_INPUT].value;

}

struct LuciControlINFcoarseWidget : ModuleWidget { 
	LuciControlINFcoarseWidget(LuciControlINFcoarse *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/LuciControlINFcoarse.svg")));
	
	addParam(ParamWidget::create<LuciVeryLargeBlueKnob>(Vec(40, 55), module, LuciControlINFcoarse::INFLUENCE_COARSE_PARAM, 0.f, 10.f, 0.001f ));
	addOutput(Port::create<PJ301MPort>(Vec(344, 172), Port::OUTPUT, module, LuciControlINFcoarse::INFLUENCE_COARSE_OUTPUT));
	//addInput(Port::create<PJ3410Port>(Vec(2, 172), Port::INPUT, module, LuciControlINFcoarse::INFLUENCE_COARSE_MOD_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(172, 344), Port::INPUT, module, LuciControlINFcoarse::INFLUENCE_FINE_INPUT));

	}
};

Model *modelLuciControlINFcoarse = Model::create<LuciControlINFcoarse, LuciControlINFcoarseWidget>("NonLinearInstruments", "LuciControlINFL", "Luci Ctrl INFLUENCE", CONTROLLER_TAG);
