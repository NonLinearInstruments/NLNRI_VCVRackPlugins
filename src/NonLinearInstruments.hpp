#include "rack.hpp"

using namespace rack;


extern Plugin *pluginInstance;

////////////////////
// module widgets
////////////////////

extern Model *modelQU4DiT;

extern Model *modelBallisticENV;

extern Model *modelLuciCell;
extern Model *modelLuci4AudioSum;
extern Model *modelLuci4ParamDistr;
extern Model *modelLuciControlRND;
extern Model *modelLuciControlFREQ;
extern Model *modelLuciControlINFcoarse;


////////////////////////
// module components
////////////////////////

struct LuciVeryLargeBlueKnob : SVGKnob {
	LuciVeryLargeBlueKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciVeryLargeBlueKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};


struct KorgLargeGoldKnob : SVGKnob {
	KorgLargeGoldKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgLargeGoldKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgLargeBlueKnob : SVGKnob {
	KorgLargeBlueKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgLargeBlueKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgLargeGreyKnob : SVGKnob {
	KorgLargeGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgLargeGreyKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};


struct KorgMedGoldKnob : SVGKnob {
	KorgMedGoldKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgMedGoldKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};


struct KorgMedGreyKnob : SVGKnob {
	KorgMedGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgMedGreyKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgSmallGreyKnob : SVGKnob {
	KorgSmallGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSvg( APP->window->loadSvg(asset::plugin(pluginInstance, "res/KorgSmallGreyKnob.svg")) );
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgCKSS : SVGSwitch /*, ToggleSwitch*/ {
	KorgCKSS() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance,"res/KorgCKSS_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance,"res/KorgCKSS_1.svg")));
	}
};

struct LuciControlRandomizeButton : SVGSwitch /*, MomentarySwitch*/ {
	LuciControlRandomizeButton() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LuciControlRandomizeButton.svg")));
	}
};


struct BigLuciButton : SVGSwitch /*, MomentarySwitch*/ {
	BigLuciButton() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BigLEDButton.svg")));
	}
};

template <typename BASE>
struct	luciControlRandomizeLight : BASE {
	luciControlRandomizeLight() {
		this->box.size = (Vec(80, 80));
	}
};

template <typename BASE>
struct luciLight : BASE {
	luciLight() {
		this->box.size = mm2px(Vec(100, 100));
	}
};

