#include "NonLinearInstruments.hpp"
#include "classes/Ballistic.cpp"


struct BallisticENV : Module {
	enum ParamIds {
		IMPULSE_PARAM,
		IMPULSE_MOD_PARAM,
		ANGLE_PARAM,
		ANGLE_MOD_PARAM,
		GRAVITY_PARAM,
		GRAVITY_MOD_PARAM,
		SHOOT_PARAM,
		BOUNCE_PARAM,
		BOUNCE_MOD_PARAM,
		BOUNCE_ON_OFF,
		NUM_PARAMS
	};
	enum InputIds {
		IMPULSE_INPUT,
		ANGLE_INPUT,
		GRAVITY_INPUT,
		BOUNCE_INPUT,
		TRIGGER_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		X_OUTPUT,
		C_OUTPUT,
		ZERO_TRIG_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		SHOOT_LIGHT,
		NUM_LIGHTS
	};

	Ballistic parabola;

	BallisticENV() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(IMPULSE_PARAM, 0.0, 1.0, 0.5);
		configParam(IMPULSE_MOD_PARAM, 0.0, 1.0, 0.0);
		configParam(ANGLE_PARAM, 0.0, 1.0, 1.0);
		configParam(ANGLE_MOD_PARAM, 0.0, 1.0, 0.0);
		configParam(GRAVITY_PARAM, 0.0, 1.0, 0.5);
		configParam(GRAVITY_MOD_PARAM, 0.0, 1.0, 0.0);
		configParam(BOUNCE_ON_OFF, 0.0, 1.0, 1.0);
		configParam(BOUNCE_PARAM, 0.0, 1.0, 0.5);
		configParam(BOUNCE_MOD_PARAM, 0.0, 1.0, 0.0);
		configParam(SHOOT_PARAM, 0.0, 5.0, 0.0);
	}
	void process(const ProcessArgs& args) override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};

void BallisticENV::process(const ProcessArgs& args) {		
	parabola.setBounceOnOff( params[BOUNCE_ON_OFF].getValue() );		
	parabola.setImpulse( params[IMPULSE_PARAM].getValue() + params[IMPULSE_MOD_PARAM].getValue() * inputs[IMPULSE_INPUT].getVoltage()  );
	parabola.setGravity( params[GRAVITY_PARAM].getValue() + params[GRAVITY_MOD_PARAM].getValue() * inputs[GRAVITY_INPUT].getVoltage()  );
	parabola.setAngle  ( params[ANGLE_PARAM].getValue()   + params[ANGLE_MOD_PARAM].getValue()   * inputs[ANGLE_INPUT].getVoltage()    );
	parabola.setBounce ( params[BOUNCE_PARAM].getValue()  + params[BOUNCE_MOD_PARAM].getValue()  * inputs[BOUNCE_INPUT].getVoltage()   );
	parabola.shoot( params[SHOOT_PARAM].getValue()   + inputs[TRIGGER_INPUT].getVoltage() );
	outputs[X_OUTPUT].setVoltage(parabola.getAudio());
	outputs[C_OUTPUT].setVoltage(parabola.getControl());
	outputs[ZERO_TRIG_OUTPUT].setVoltage(parabola.getZeroTrigger());
}


// here changes to 0.6.0 !!

struct BallisticENVWidget : ModuleWidget { 

BallisticENVWidget(BallisticENV *module) {
		setModule(module);
	
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BallisticENV.svg")));

		addParam(createParam<KorgMedGreyKnob>(Vec(75, 40), module, BallisticENV::IMPULSE_PARAM));
		addParam(createParam<KorgSmallGreyKnob>(Vec(40, 48), module, BallisticENV::IMPULSE_MOD_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 50), module, BallisticENV::IMPULSE_INPUT)); // -5 ~ +5
		
		addParam(createParam<KorgMedGreyKnob>(Vec(75, 95), module, BallisticENV::ANGLE_PARAM));
		addParam(createParam<KorgSmallGreyKnob>(Vec(40, 103), module, BallisticENV::ANGLE_MOD_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 105), module, BallisticENV::ANGLE_INPUT)); // -5 ~ +5
		
		addParam(createParam<KorgMedGreyKnob>(Vec(75, 150), module, BallisticENV::GRAVITY_PARAM));
		addParam(createParam<KorgSmallGreyKnob>(Vec(40, 158), module, BallisticENV::GRAVITY_MOD_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 160), module, BallisticENV::GRAVITY_INPUT)); // -5 ~ +5
		
		addParam(createParam<KorgCKSS>(Vec(58, 192), module, BallisticENV::BOUNCE_ON_OFF));
		addParam(createParam<KorgMedGreyKnob>(Vec(75, 216), module, BallisticENV::BOUNCE_PARAM));
		addParam(createParam<KorgSmallGreyKnob>(Vec(40, 222), module, BallisticENV::BOUNCE_MOD_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 224), module, BallisticENV::BOUNCE_INPUT)); // -5 ~ +5
		
		addParam(createParam<CKD6>(Vec(42, 262), module, BallisticENV::SHOOT_PARAM));
		addInput(createInput<PJ301MPort>(Vec(10, 264), module, BallisticENV::TRIGGER_INPUT));
		
		addOutput(createOutput<PJ301MPort>(Vec(11, 320), module, BallisticENV::X_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(45, 320), module, BallisticENV::C_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(80, 320), module, BallisticENV::ZERO_TRIG_OUTPUT));
	}	
};

Model *modelBallisticENV = createModel<BallisticENV, BallisticENVWidget>("BallisticENV");
