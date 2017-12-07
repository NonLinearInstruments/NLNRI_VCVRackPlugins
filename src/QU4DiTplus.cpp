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
		CMOD_DEPTH,
		C_OFFSET,
		NUM_PARAMS
	};
	enum InputIds {
		CMOD_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		XN_OUTPUT,
		YN_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};
	
	logisticMap QUADinstrument;
	
	QU4DiTplus() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void QU4DiTplus::step() {

	QUADinstrument.setCmod_depth_param ( clampf( params[CMOD_DEPTH].value, 0.f, 1.f ));
	QUADinstrument.setCmod_value ( clampf( inputs[CMOD_INPUT].value / 5.f , -1.f, 1.f ));
	QUADinstrument.setC_value (clampf ( params[C_PARAM].value, 0.f, 1.f ));
	

	QUADinstrument.process();
	outputs[XN_OUTPUT].value = QUADinstrument.getAudio();
	outputs[YN_OUTPUT].value = QUADinstrument.getAudio();
	
}


QU4DiTplusWidget::QU4DiTplusWidget() {
	QU4DiTplus *module = new QU4DiTplus();
	setModule(module);
	//box.size = Vec( 6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);
	box.size = Vec( 150, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/QU4DiTplus.svg")));
		addChild(panel);
	}
	
	addParam(createParam<Davies1900hLargeBlackKnob>(Vec(17, 40), module, QU4DiTplus::C_PARAM, 0.0, 1.0, 0.5 ));
	addParam(createParam<Davies1900hBlackKnob>(Vec(28, 125), module, QU4DiTplus::C_OFFSET, 0.0, 1.0, 0.0));
	addParam(createParam<Davies1900hBlackKnob>(Vec(28, 190), module, QU4DiTplus::CMOD_DEPTH, 0.0, 1.0, 0.0));
	
	addInput(createInput<PJ301MPort>(Vec(33, 250), module, QU4DiTplus::CMOD_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(46, 310), module, QU4DiTplus::XN_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(80, 310), module, QU4DiTplus::YN_OUTPUT));

}
