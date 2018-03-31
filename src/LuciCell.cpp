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

	LuciCell() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void LuciCell::step() {

	// receive neighbour cells triggers
	MyLuci.setTriggers(
		inputs[NORTH_INPUT].value,
		inputs[EAST_INPUT].value,
		inputs[SOUTH_INPUT].value,
		inputs[WEST_INPUT].value
		);
	// randomize function
	MyLuci.randomize(inputs[RND_INPUT].value);
	// adjust frequency with 1v/oct
	float gotFreq = inputs[FREQ_INPUT].value;
	MyLuci.setFrequency(gotFreq);
	// ... and lightLambda acordingly
	// here 60 is supposed to be screen refresh frequency
	//if(gotFreq > 60.f){
	//	lightLambda = 0.001f;
	//} else {
		//lightLambda =
	//}

	// adjust influence +/-5v
	MyLuci.setInfluence(inputs[INFLUENCE_INPUT].value);
	// run the cell
	audioOut = MyLuci.process();
	// get audio signal
	outputs[XN_OUTPUT].value = std::isfinite(audioOut) ? audioOut : 0.f;
	// feed outputs with the same internal own cell's trigger
	bool gotLuciTrigger = MyLuci.getLuciTrigger();
	outputs[NORTH_TRIG_OUT].value =
	outputs[EAST_TRIG_OUT].value =
	outputs[SOUTH_TRIG_OUT].value =
	outputs[WEST_TRIG_OUT].value = gotLuciTrigger;


	// Reset thru button or own luci trigger
	if (params[RESET_PARAM].value > 0 || gotLuciTrigger ) {
		resetLight = 1.0;
		MyLuci.resetLuci();
	}
	resetLight -= resetLight / lightLambda / engineGetSampleRate();
	lights[RESET_LIGHT].value = resetLight;

}

struct LuciCellWidget : ModuleWidget { 
	
	LuciCellWidget(LuciCell *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/LuciCell.svg")));
		
	addOutput(Port::create<PJ301MPort>(Vec(2, 2), Port::OUTPUT, module, LuciCell::XN_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(2, 210), Port::OUTPUT, module, LuciCell::NORTH_TRIG_OUT));
	addOutput(Port::create<PJ301MPort>(Vec(210, 2), Port::OUTPUT, module, LuciCell::WEST_TRIG_OUT));
	addOutput(Port::create<PJ301MPort>(Vec(210, 344), Port::OUTPUT, module, LuciCell::EAST_TRIG_OUT));
	addOutput(Port::create<PJ301MPort>(Vec(344, 210), Port::OUTPUT, module, LuciCell::SOUTH_TRIG_OUT));

	addInput(Port::create<PJ3410Port>(Vec(2, 162), Port::INPUT, module, LuciCell::NORTH_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(2, 344), Port::INPUT, module, LuciCell::FREQ_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(162, 2), Port::INPUT, module, LuciCell::WEST_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(162, 344), Port::INPUT, module, LuciCell::EAST_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(344, 2), Port::INPUT, module, LuciCell::INFLUENCE_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(344, 162), Port::INPUT, module, LuciCell::SOUTH_INPUT));
	addInput(Port::create<PJ3410Port>(Vec(344, 344), Port::INPUT, module, LuciCell::RND_INPUT));

	addParam(ParamWidget::create<BigLuciButton>(Vec(35, 35), module, LuciCell::RESET_PARAM, 0.0, 1.0, 0.0));
	addChild(ModuleLightWidget::create<luciLight<BlueLight>>(Vec(40, 40), module, LuciCell::RESET_LIGHT));
	}
};

Model *modelLuciCell = Model::create<LuciCell, LuciCellWidget>("NonLinearInstruments", "LuciCell", "Luci Cell", OSCILLATOR_TAG);
