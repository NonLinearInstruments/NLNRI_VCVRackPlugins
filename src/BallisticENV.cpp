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
		MODE_OSC,
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
		TOP_TRIG_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		SHOOT_LIGHT,
		NUM_LIGHTS
	};

	Ballistic parabola;

	BallisticENV() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void BallisticENV::step() {		
	parabola.setBounceOnOff( params[BOUNCE_ON_OFF].value );		
	parabola.setModeOsc( params[MODE_OSC].value );
	parabola.setImpulse( params[IMPULSE_PARAM].value + params[IMPULSE_MOD_PARAM].value * inputs[IMPULSE_INPUT].value  );
	parabola.setGravity( params[GRAVITY_PARAM].value + params[GRAVITY_MOD_PARAM].value * inputs[GRAVITY_INPUT].value  );
	parabola.setAngle  ( params[ANGLE_PARAM].value   + params[ANGLE_MOD_PARAM].value   * inputs[ANGLE_INPUT].value    );
	parabola.setBounce ( params[BOUNCE_PARAM].value  + params[BOUNCE_MOD_PARAM].value   * inputs[BOUNCE_INPUT].value   );
	parabola.shoot( params[SHOOT_PARAM].value   + inputs[TRIGGER_INPUT].value );
	outputs[X_OUTPUT].value = parabola.getAudio();
	outputs[C_OUTPUT].value = parabola.getControl();
	outputs[ZERO_TRIG_OUTPUT].value = parabola.getZeroTrigger();
}


BallisticENVWidget::BallisticENVWidget() {
	BallisticENV *module = new BallisticENV();
	setModule(module);
	box.size = Vec(10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/BallisticENV.svg")));
		addChild(panel);
	}
	
	addParam(createParam<CKSS>(Vec(124, 48), module, BallisticENV::MODE_OSC, 0.0, 1.0, 0.));
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 40), module, BallisticENV::IMPULSE_PARAM, 0.0, 1.0, 0.5 ));		
	addParam(createParam<RoundSmallBlackKnob>(Vec(42, 46), module, BallisticENV::IMPULSE_MOD_PARAM, 0.0, 1.0, 0.0 ));		
	addInput(createInput<PJ301MPort>(Vec(10, 50), module, BallisticENV::IMPULSE_INPUT)); // -5 ~ +5
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 95), module, BallisticENV::ANGLE_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<RoundSmallBlackKnob>(Vec(42, 101), module, BallisticENV::ANGLE_MOD_PARAM, 0.0, 1.0, 0.0 ));		
	addInput(createInput<PJ301MPort>(Vec(10, 105), module, BallisticENV::ANGLE_INPUT)); // -5 ~ +5
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 150), module, BallisticENV::GRAVITY_PARAM, 0.0, 1.0, 0.5));
	addParam(createParam<RoundSmallBlackKnob>(Vec(42, 156), module, BallisticENV::GRAVITY_MOD_PARAM, 0.0, 1.0, 0.0 ));		
	addInput(createInput<PJ301MPort>(Vec(10, 160), module, BallisticENV::GRAVITY_INPUT)); // -5 ~ +5
	
	addParam(createParam<CKSS>(Vec(124, 212), module, BallisticENV::BOUNCE_ON_OFF, 0.0, 1.0, 1.0));
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 205), module, BallisticENV::BOUNCE_PARAM, 0.0, 1.0, 0.5));
	addParam(createParam<RoundSmallBlackKnob>(Vec(42, 211), module, BallisticENV::BOUNCE_MOD_PARAM, 0.0, 1.0, 0.0 ));			
	addInput(createInput<PJ301MPort>(Vec(10, 215), module, BallisticENV::BOUNCE_INPUT)); // -5 ~ +5
	
	addParam(createParam<CKD6>(Vec(96, 260), module, BallisticENV::SHOOT_PARAM, 0.0, 5.0, 0.0));
	addInput(createInput<PJ301MPort>(Vec(32, 262), module, BallisticENV::TRIGGER_INPUT));	
    
	
	addOutput(createOutput<PJ301MPort>(Vec(10, 318), module, BallisticENV::X_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(45, 318), module, BallisticENV::C_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(80, 318), module, BallisticENV::ZERO_TRIG_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(115,318), module, BallisticENV::TOP_TRIG_OUTPUT));
	
}
