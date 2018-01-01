#include "NonLinearInstruments.hpp"
#include "classes/Ballistic.cpp"


struct BallisticENV : Module {
	enum ParamIds {
		IMPULSE_PARAM,
		ANGLE_PARAM,
		GRAVITY_PARAM,
		SHOOT_PARAM,
		BOUNCE_PARAM,
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
		
	parabola.setBounceOnOff(
		params[BOUNCE_ON_OFF].value	
		);
		
	parabola.setModeOsc(
				params[MODE_OSC].value	
				);
		
	parabola.shoot(
		params[SHOOT_PARAM].value,
		params[IMPULSE_PARAM].value,
		params[GRAVITY_PARAM].value,
		params[ANGLE_PARAM].value,
		params[BOUNCE_PARAM].value
		);
			
	outputs[X_OUTPUT].value = parabola.getAudio();
	outputs[C_OUTPUT].value = parabola.getControl();
	
	/*
	CmodDepthParam = clampf ( params[CMOD_DEPTH].value, 0.f, 1.f );
	CmodDepthParam *= CmodDepthParam;
	CmodValue = clampf ( inputs[CMOD_INPUT].value / 5.f , -1.f, 1.f ) * CmodDepthParam;
	Cvalue =  C_range * clampf ( params[C_PARAM].value, 0.f, 1.f );
	CmodValue = CmodValue * (Cmax - Cvalue);
	
	Cparam = clampf ( Cmin + Cvalue + CmodValue, Cmin , Cmax );
						
	Coffset = Off_range * clampf ( params[C_OFFSET].value, 0.f, 1.f );
	
	axnew = Cparam * ax * ( 1.f - ax );
	aynew = ( Cparam + Coffset ) * ay * ( 1.f - ay );
	
	Xout = axnew * 5.f;
	y_out = aynew * 5.f;

	outputs[XN_OUTPUT].value = std::isfinite(Xout) ? Xout : 0.f;
	outputs[YN_OUTPUT].value = std::isfinite(y_out) ? y_out : 0.f;

	ax = axnew;
	ay = aynew;
	*/
	
}


BallisticENVWidget::BallisticENVWidget() {
	BallisticENV *module = new BallisticENV();
	setModule(module);
	box.size = Vec(12 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/BallisticENV.svg")));
		addChild(panel);
	}
	
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 40), module, BallisticENV::IMPULSE_PARAM, 0.0, 1.0, 0.5 ));
	addParam(createParam<CKSS>(Vec(10, 40), module, BallisticENV::MODE_OSC, 0.0, 1.0, 0.));
		
	addInput(createInput<PJ301MPort>(Vec(10, 58), module, BallisticENV::IMPULSE_INPUT));
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 95), module, BallisticENV::ANGLE_PARAM, 0.0, 1.0, 0.5));
	addInput(createInput<PJ301MPort>(Vec(10, 113), module, BallisticENV::ANGLE_INPUT));
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 150), module, BallisticENV::GRAVITY_PARAM, 0.0, 1.0, 0.5));
	addInput(createInput<PJ301MPort>(Vec(10, 168), module, BallisticENV::GRAVITY_INPUT));
	addParam(createParam<CKSS>(Vec(60, 205), module, BallisticENV::BOUNCE_ON_OFF, 0.0, 1.0, 1.0));
	addParam(createParam<Davies1900hBlackKnob>(Vec(78, 205), module, BallisticENV::BOUNCE_PARAM, 0.0, 1.0, 0.0));
	addInput(createInput<PJ301MPort>(Vec(10, 223), module, BallisticENV::BOUNCE_INPUT));
	addParam(createParam<CKD6>(Vec(78, 260), module, BallisticENV::SHOOT_PARAM, 0.0, 5.0, 0.0));
		
    
	
	addOutput(createOutput<PJ301MPort>(Vec(10, 310), module, BallisticENV::X_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(50, 310), module, BallisticENV::C_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(90, 310), module, BallisticENV::TOP_TRIG_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(130, 310), module, BallisticENV::ZERO_TRIG_OUTPUT));
	
}
