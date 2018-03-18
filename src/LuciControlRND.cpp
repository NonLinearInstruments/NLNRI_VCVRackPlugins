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

	LuciControlRND() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
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

void LuciControlRND::step() {

		gotRandomize = params[RANDOMIZE_PARAM].value + params[RANDOMIZE_INPUT].value;
		outputs[RANDOMIZE_OUTPUT].value = gotRandomize;
		// Reset button light
		if ( gotRandomize > 0 ) {
			randomizeLight = 1.0;
			}
		randomizeLight -= randomizeLight / lightLambda / engineGetSampleRate();
		lights[RANDOMIZE_LIGHT].value = randomizeLight;

}

struct LuciControlRNDWidget : ModuleWidget { LuciControlRNDWidget(LuciControlRND *module); };

LuciControlRNDWidget::LuciControlRNDWidget(LuciControlRND *module) : ModuleWidget(module) {
	box.size = Vec(25 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/LuciControlRND.svg")));
		addChild(panel);
	}

	addParam(ParamWidget::create<BigLuciButton>(Vec(35, 55), module, LuciControlRND::RANDOMIZE_PARAM, 0.0, 1.0, 0.0));
	addChild(ModuleLightWidget::create<luciLight<BlueLight>>(Vec(40, 60), module, LuciControlRND::RANDOMIZE_LIGHT));
	addOutput(Port::create<PJ301MPort>(Vec(344, 172), Port::OUTPUT, module, LuciControlRND::RANDOMIZE_OUTPUT));
	addInput(Port::create<PJ3410Port>(Vec(2, 172), Port::INPUT, module, LuciControlRND::RANDOMIZE_INPUT));

}

Model *modelLuciControlRND = Model::create<LuciControlRND, LuciControlRNDWidget>("NonLinearInstruments", "LuciControlRND", "Luci Ctrl RAND", CONTROLLER_TAG);
