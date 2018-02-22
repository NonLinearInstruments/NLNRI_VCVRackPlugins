#include "NonLinearInstruments.hpp"
#include "classes/Luci.cpp"

// a small utility module for mixing 4 audio signals

struct Luci4ParamDistr : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_1,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_1,
		OUTPUT_2,
		OUTPUT_3,
		OUTPUT_4,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Luci4ParamDistr() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void Luci4ParamDistr::step() {
		outputs[OUTPUT_1].value =
		outputs[OUTPUT_2].value =
		outputs[OUTPUT_3].value =
		outputs[OUTPUT_4].value =
		inputs[INPUT_1].value ;
}

struct Luci4ParamDistrWidget : ModuleWidget { Luci4ParamDistrWidget(Luci4ParamDistr *module); };

Luci4ParamDistrWidget::Luci4ParamDistrWidget(Luci4ParamDistr *module) : ModuleWidget(module) {
	box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Luci4ParamDistr.svg")));
		addChild(panel);
	}

	addInput(Port::create<PJ301MPort>(Vec(3, 40), Port::INPUT, module, Luci4ParamDistr::INPUT_1));

	addOutput(Port::create<PJ301MPort>(Vec(3, 130), Port::OUTPUT, module, Luci4ParamDistr::OUTPUT_1));
	addOutput(Port::create<PJ301MPort>(Vec(3, 180), Port::OUTPUT, module, Luci4ParamDistr::OUTPUT_2));
	addOutput(Port::create<PJ301MPort>(Vec(3, 230), Port::OUTPUT, module, Luci4ParamDistr::OUTPUT_3));
	addOutput(Port::create<PJ301MPort>(Vec(3, 280), Port::OUTPUT, module, Luci4ParamDistr::OUTPUT_4));

}

Model *modelLuci4ParamDistr = Model::create<Luci4ParamDistr, Luci4ParamDistrWidget>("NonLinearInstruments", "Luci4ParamDistr", "Luci 4 Param Distr", MULTIPLE_TAG);
