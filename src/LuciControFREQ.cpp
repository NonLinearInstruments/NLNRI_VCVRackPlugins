#include "NonLinearInstruments.hpp"

struct LuciControlFREQ : Module {
	enum ParamIds {
		FREQUENCY_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FREQUENCY_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		FREQUENCY_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	LuciControlFREQ() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlFREQ::step() {

		outputs[FREQUENCY_OUTPUT].value = params[FREQUENCY_PARAM].value + params[FREQUENCY_INPUT].value;

}

struct LuciControlFREQWidget : ModuleWidget { 
	LuciControlFREQWidget(LuciControlFREQ *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/LuciControlFREQ.svg")));
		
	addParam(ParamWidget::create<LuciVeryLargeBlueKnob>(Vec(40, 55), module, LuciControlFREQ::FREQUENCY_PARAM, 0.0, 8.0, 1. ));
	addOutput(Port::create<PJ301MPort>(Vec(344, 172), Port::OUTPUT, module, LuciControlFREQ::FREQUENCY_OUTPUT));
	addInput(Port::create<PJ3410Port>(Vec(2, 172), Port::INPUT, module, LuciControlFREQ::FREQUENCY_INPUT));

	}
};

Model *modelLuciControlFREQ = Model::create<LuciControlFREQ, LuciControlFREQWidget>("NonLinearInstruments", "LuciControlFREQ", "Luci Ctrl FREQ", CONTROLLER_TAG);
