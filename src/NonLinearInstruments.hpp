#include "rack.hpp"


using namespace rack;


extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct QU4DiTWidget : ModuleWidget { QU4DiTWidget(); };
//struct Luci8x8Widget : ModuleWidget { Luci8x8Widget(); };
struct BallisticENVWidget : ModuleWidget { BallisticENVWidget(); };

////////////////////////
// module components
////////////////////////

struct KorgLargeGoldKnob : SVGKnob {
	KorgLargeGoldKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		sw->svg = SVG::load(assetPlugin(plugin, "res/KorgLargeGoldKnob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgLargeGreyKnob : SVGKnob {
	KorgLargeGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		sw->svg = SVG::load(assetPlugin(plugin, "res/KorgLargeGreyKnob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};


struct KorgMedGoldKnob : SVGKnob {
	KorgMedGoldKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		sw->svg = SVG::load(assetPlugin(plugin, "res/KorgMedGoldKnob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};


struct KorgMedGreyKnob : SVGKnob {
	KorgMedGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		sw->svg = SVG::load(assetPlugin(plugin, "res/KorgMedGreyKnob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgSmallGreyKnob : SVGKnob {
	KorgSmallGreyKnob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		sw->svg = SVG::load(assetPlugin(plugin, "res/KorgSmallGreyKnob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct KorgCKSS : SVGSwitch, ToggleSwitch {
	KorgCKSS() {
		addFrame(SVG::load(assetPlugin(plugin,"res/KorgCKSS_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/KorgCKSS_1.svg")));
	}
};
