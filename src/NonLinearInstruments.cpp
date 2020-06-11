#include "NonLinearInstruments.hpp"


// The pluginInstance-wide instance of the Plugin class
Plugin *pluginInstance;

void init(Plugin *p) {
	pluginInstance = p;

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

	// Any other pluginInstance initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
