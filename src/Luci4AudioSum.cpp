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

	Luci4AudioSum() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void Luci4AudioSum::process(const ProcessArgs& args) {
	outputs[OUTPUT_1].value = (
		inputs[INPUT_1].getVoltage() +
		inputs[INPUT_2].getVoltage() +
		inputs[INPUT_3].getVoltage() +
		inputs[INPUT_4].getVoltage()
	) * 0.250000f ;
}


struct Luci4AudioSumWidget : ModuleWidget { Luci4AudioSumWidget(Luci4AudioSum *module); };

Luci4AudioSumWidget::Luci4AudioSumWidget(Luci4AudioSum *module) {
	setModule(module);
	box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SvgPanel *panel = new SvgPanel();
		panel->box.size = box.size;
		panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Luci4AudioSum.svg")));
		addChild(panel);
	}

	addOutput(createOutput<PJ301MPort>(Vec(3, 310), module, Luci4AudioSum::OUTPUT_1));

	addInput(createInput<PJ301MPort>(Vec(3, 40), module, Luci4AudioSum::INPUT_1));
	addInput(createInput<PJ301MPort>(Vec(3, 90), module, Luci4AudioSum::INPUT_2));
	addInput(createInput<PJ301MPort>(Vec(3, 140), module, Luci4AudioSum::INPUT_3));
	addInput(createInput<PJ301MPort>(Vec(3, 190), module, Luci4AudioSum::INPUT_4));

}

Model *modelLuci4AudioSum = createModel<Luci4AudioSum, Luci4AudioSumWidget>("Luci4AudioSum");
