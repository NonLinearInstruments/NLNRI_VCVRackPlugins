#include "NonLinearInstruments.hpp"
#include "classes/Luci.cpp"


struct LuciCell : Module {
	enum ParamIds {
		RESET_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		//CMOD_INPUT,
		NORTH_INPUT,
		EAST_INPUT,
		SOUTH_INPUT,
		WEST_INPUT,
		RND_INPUT,
		FREQ_INPUT,
		INFLUENCE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		XN_OUTPUT,
		TRIG_OUT,
		NORTH_TRIG_OUT,
		EAST_TRIG_OUT,
		SOUTH_TRIG_OUT,
		WEST_TRIG_OUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		RESET_LIGHT,
		NUM_LIGHTS
	};


	luciCell MyLuci;
	float audioOut = 0.f;
	// do the light thing
	//float lightLambda = 0.075;
	float lightLambda = 0.025;
	float resetLight = 0.0;

	LuciCell() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(RESET_PARAM, 0.0, 1.0, 0.0);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciCell::process(const ProcessArgs& args) {

	// receive neighbour cells triggers
	MyLuci.setTriggers(
		inputs[NORTH_INPUT].getVoltage(),
		inputs[EAST_INPUT].getVoltage(),
		inputs[SOUTH_INPUT].getVoltage(),
		inputs[WEST_INPUT].getVoltage()
	);
	// randomize function
	MyLuci.randomize(inputs[RND_INPUT].getVoltage());
	// adjust frequency with 1v/oct
	float gotFreq = inputs[FREQ_INPUT].getVoltage();
	MyLuci.setFrequency(gotFreq);
	// ... and lightLambda acordingly
	// here 60 is supposed to be screen refresh frequency
	//if(gotFreq > 60.f){
	//	lightLambda = 0.001f;
	//} else {
		//lightLambda =
	//}

	// adjust influence +/-5v
	MyLuci.setInfluence(inputs[INFLUENCE_INPUT].getVoltage());
	// run the cell
	audioOut = MyLuci.process();
	// get audio signal
	outputs[XN_OUTPUT].setVoltage(std::isfinite(audioOut) ? audioOut : 0.f);
	// feed outputs with the same internal own cell's trigger
	bool gotLuciTrigger = MyLuci.getLuciTrigger();
	outputs[NORTH_TRIG_OUT].setVoltage(gotLuciTrigger);
	outputs[EAST_TRIG_OUT].setVoltage(gotLuciTrigger);
	outputs[SOUTH_TRIG_OUT].setVoltage(gotLuciTrigger);
	outputs[WEST_TRIG_OUT].setVoltage(gotLuciTrigger);


	// Reset thru button or own luci trigger
	if (params[RESET_PARAM].getValue() > 0 || gotLuciTrigger ) {
		resetLight = 1.0;
		MyLuci.resetLuci();
	}
	resetLight -= resetLight / lightLambda / args.sampleRate;
	lights[RESET_LIGHT].value = resetLight;
}

struct LuciCellWidget : ModuleWidget { 
	LuciCellWidget(LuciCell *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciCell.svg")));

		addOutput(createOutput<PJ301MPort>(Vec(2, 2), module, LuciCell::XN_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(2, 210), module, LuciCell::NORTH_TRIG_OUT));
		addOutput(createOutput<PJ301MPort>(Vec(210, 2), module, LuciCell::WEST_TRIG_OUT));
		addOutput(createOutput<PJ301MPort>(Vec(210, 344), module, LuciCell::EAST_TRIG_OUT));
		addOutput(createOutput<PJ301MPort>(Vec(344, 210), module, LuciCell::SOUTH_TRIG_OUT));

		addInput(createInput<PJ3410Port>(Vec(2, 162), module, LuciCell::NORTH_INPUT));
		addInput(createInput<PJ3410Port>(Vec(2, 344), module, LuciCell::FREQ_INPUT));
		addInput(createInput<PJ3410Port>(Vec(162, 2), module, LuciCell::WEST_INPUT));
		addInput(createInput<PJ3410Port>(Vec(162, 344), module, LuciCell::EAST_INPUT));
		addInput(createInput<PJ3410Port>(Vec(344, 2), module, LuciCell::INFLUENCE_INPUT));
		addInput(createInput<PJ3410Port>(Vec(344, 162), module, LuciCell::SOUTH_INPUT));
		addInput(createInput<PJ3410Port>(Vec(344, 344), module, LuciCell::RND_INPUT));

		addParam(createParam<BigLuciButton>(Vec(35, 35), module, LuciCell::RESET_PARAM));
		
		addChild(createLight<luciLight<BlueLight>>(Vec(40, 40), module, LuciCell::RESET_LIGHT));
	}
};

Model *modelLuciCell = createModel<LuciCell, LuciCellWidget>("LuciCell");
