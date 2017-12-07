#include "NonLinearInstruments.hpp"
#include "classes/LogisticMap.cpp"

/* 
This instrument explores the Quadratic iterator, also known as Logistic map 
(after the Verhulst's logistic equation). 
More precisely, the chaotic range arising for parameter values above roughly 3.5
https://en.wikipedia.org/wiki/Logistic_map

Panel .svg and logo by Alfredo Santamaría http://www.hakken.com.mx/gui.php

Changelog:
v0.5.1 : first release

*/

struct QU4DiTplus : Module {
	enum ParamIds {
		C_PARAM,
		C_PARAM_FINE,
		CMOD_DEPTH,
		CFINE_MOD_DEPTH,
		DOWN_SAMPLE,
		//C_OFFSET,
		NUM_PARAMS
	};
	enum InputIds {
		CMOD_INPUT,
		CMOD_FINE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		XN_OUTPUT,
		//YN_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};
	
	logisticMap QUADinstrument;
	int downsample = 1;
	int samplecounter = 1;
	
	QU4DiTplus() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiTplus::step() {

	//downsample = (int) pow ( fmod( clampf( params[DOWN_SAMPLE].value, 0.f, 1.f ) * 8. , 2 ) , 2);
	
	if ( samplecounter >= downsample || samplecounter == 1){
	QUADinstrument.setCmod_depth_param ( clampf( params[CMOD_DEPTH].value, 0.f, 1.f ));
	QUADinstrument.setCmod_value ( clampf( inputs[CMOD_INPUT].value / 5.f , -1.f, 1.f ));
	QUADinstrument.setCvalue (clampf( params[C_PARAM].value, 0.f, 1.f ));
	QUADinstrument.setCvalueFine ( clampf( params[C_PARAM_FINE].value, -1.0f, 1.f));
	QUADinstrument.process();
	if(samplecounter >= downsample){samplecounter = 0;};
	};
		
	outputs[XN_OUTPUT].value = QUADinstrument.getAudio();
	
	samplecounter += 1;
	downsample = (int) ( 16. * clampf( params[DOWN_SAMPLE].value, 0.f, 1.f ));
		
}


QU4DiTplusWidget::QU4DiTplusWidget() {
	QU4DiTplus *module = new QU4DiTplus();
	setModule(module);
	box.size = Vec( 150, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/QU4DiTplus.svg")));
		addChild(panel);
	}
	
	addParam(createParam<Davies1900hLargeBlackKnob>(Vec(16, 47), module, QU4DiTplus::C_PARAM, 0.0, 1.0, 0.5 ));
	addParam(createParam<Davies1900hLargeBlackKnob>(Vec(83, 47), module, QU4DiTplus::C_PARAM_FINE, -1.0, 1.0, 0.0 ));
	addParam(createParam<Davies1900hBlackKnob>(Vec(16, 225), module, QU4DiTplus::CMOD_DEPTH, 0.0, 1.0, 0.0));
	addParam(createParam<Davies1900hLargeBlackKnob>(Vec(60, 120), module, QU4DiTplus::DOWN_SAMPLE, 0.0, 1.0, 0.0));
	
	addOutput(createOutput<PJ301MPort>(Vec(16, 328), module, QU4DiTplus::XN_OUTPUT));
	
	addInput(createInput<PJ301MPort>(Vec(16, 275), module, QU4DiTplus::CMOD_INPUT));
	
	addInput(createInput<PJ301MPort>(Vec(52, 275), module, QU4DiTplus::CMOD_FINE_INPUT));

//	addOutput(createOutput<PJ301MPort>(Vec(52, 328), module, QU4DiTplus::YN_OUTPUT));

}
