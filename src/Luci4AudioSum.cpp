#include "NonLinearInstruments.hpp"
#include "classes/Luci.cpp"

// a small utility module for mixing 4 audio signals

struct Luci4AudioSum : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_1,
		INPUT_2,
		INPUT_3,
		INPUT_4,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_1,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Luci4AudioSum() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void Luci4AudioSum::step() {
		outputs[OUTPUT_1].value = (
		inputs[INPUT_1].value +
		inputs[INPUT_2].value +
		inputs[INPUT_3].value +
		inputs[INPUT_4].value
		) * 0.250000f ;
}


struct Luci4AudioSumWidget : ModuleWidget { Luci4AudioSumWidget(Luci4AudioSum *module); };

Luci4AudioSumWidget::Luci4AudioSumWidget(Luci4AudioSum *module) : ModuleWidget(module) {
	box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Luci4AudioSum.svg")));
		addChild(panel);
	}

	addOutput(Port::create<PJ301MPort>(Vec(3, 310), Port::OUTPUT, module, Luci4AudioSum::OUTPUT_1));

	addInput(Port::create<PJ301MPort>(Vec(3, 40), Port::INPUT, module, Luci4AudioSum::INPUT_1));
	addInput(Port::create<PJ301MPort>(Vec(3, 90), Port::INPUT, module, Luci4AudioSum::INPUT_2));
	addInput(Port::create<PJ301MPort>(Vec(3, 140), Port::INPUT, module, Luci4AudioSum::INPUT_3));
	addInput(Port::create<PJ301MPort>(Vec(3, 190), Port::INPUT, module, Luci4AudioSum::INPUT_4));

}

Model *modelLuci4AudioSum = Model::create<Luci4AudioSum, Luci4AudioSumWidget>("NonLinearInstruments", "Luci4AudioSum", "Luci 4 Audio Sum", MIXER_TAG);
