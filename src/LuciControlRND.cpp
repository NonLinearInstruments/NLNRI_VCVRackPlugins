#include "NonLinearInstruments.hpp"

struct LuciControlRND : Module {
	enum ParamIds {
		RANDOMIZE_PARAM,

		NUM_PARAMS
	};
	enum InputIds {
		RANDOMIZE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		RANDOMIZE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		RANDOMIZE_LIGHT,
		NUM_LIGHTS
	};

	LuciControlRND() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(RANDOMIZE_PARAM, 0.0, 1.0, 0.0);
	}
	void process(const ProcessArgs& args) override;
	// do the light thing
	float lightLambda = 0.075;
	float randomizeLight = 0.0;
	// hold randomize param value
	float gotRandomize = 0.f;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciControlRND::process(const ProcessArgs& args) {
	gotRandomize = params[RANDOMIZE_PARAM].getValue() + params[RANDOMIZE_INPUT].getValue();
	outputs[RANDOMIZE_OUTPUT].setVoltage(gotRandomize);
	// Reset button light
	if ( gotRandomize > 0 ) {
		randomizeLight = 1.0;
	}
	randomizeLight -= randomizeLight / lightLambda / args.sampleRate;
	lights[RANDOMIZE_LIGHT].value = randomizeLight;
}

struct LuciControlRNDWidget : ModuleWidget { 
	LuciControlRNDWidget(LuciControlRND *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciControlRND.svg")));

		addParam(createParam<BigLuciButton>(Vec(35, 55), module, LuciControlRND::RANDOMIZE_PARAM));
		addChild(createLight<luciLight<BlueLight>>(Vec(40, 60), module, LuciControlRND::RANDOMIZE_LIGHT));
		addOutput(createOutput<PJ301MPort>(Vec(344, 172), module, LuciControlRND::RANDOMIZE_OUTPUT));
		addInput(createInput<PJ3410Port>(Vec(2, 172), module, LuciControlRND::RANDOMIZE_INPUT));
	}
};

Model *modelLuciControlRND = createModel<LuciControlRND, LuciControlRNDWidget>("LuciControlRND");
