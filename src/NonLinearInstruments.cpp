#include "NonLinearInstruments.hpp"


// The plugin-wide instance of the Plugin class
Plugin *plugin;

void init(Plugin *p) {
	plugin = p;
	// This is the unique identifier for your plugin
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/NonLinearInstruments/NLNRI_VCVRackPlugins";
	p->manual = "https://github.com/NonLinearInstruments/NLNRI_VCVRackPlugins/blob/master/README.md";

	// For each module, specify the ModuleWidget subclass, manufacturer slug (for saving in patches), manufacturer human-readable name, module slug, and module name
	p->addModel(modelQU4DiT);
	p->addModel(modelBallisticENV);
	p->addModel(modelLuciCell);
	p->addModel(modelLuci4AudioSum);
	p->addModel(modelLuci4ParamDistr);
	p->addModel(modelLuciControlRND);
	p->addModel(modelLuciControlFREQ);
	p->addModel(modelLuciControlINFcoarse);
	//p->addModel(modelLuciControlINFfine);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
