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

	LuciControlFREQ() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(FREQUENCY_PARAM, 0.0, 8.0, 1.0);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlFREQ::process(const ProcessArgs& args) {
	outputs[FREQUENCY_OUTPUT].setVoltage(params[FREQUENCY_PARAM].getValue() + params[FREQUENCY_INPUT].getValue());
}

struct LuciControlFREQWidget : ModuleWidget { 
	LuciControlFREQWidget(LuciControlFREQ *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciControlFREQ.svg")));

		addParam(createParam<LuciVeryLargeBlueKnob>(Vec(40, 55), module, LuciControlFREQ::FREQUENCY_PARAM));
		addOutput(createOutput<PJ301MPort>(Vec(344, 172), module, LuciControlFREQ::FREQUENCY_OUTPUT));
		addInput(createInput<PJ3410Port>(Vec(2, 172), module, LuciControlFREQ::FREQUENCY_INPUT));
	}
};

Model *modelLuciControlFREQ = createModel<LuciControlFREQ, LuciControlFREQWidget>("LuciControlFREQ");
