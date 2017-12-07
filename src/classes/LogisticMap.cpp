// 
//  Base class for Quadratic iterator instruments
//

#pragma once

namespace rack {

struct logisticMap {

	float ax = 0.1;
	float axnew = 0.0;
	float Cparam = 3.57;
	float x_out = 0.0;
	float C_max = 3.999999;
	float C_min = 3.569959;
	float C_range = C_max - C_min;
	float C_value = C_min;
	float Cmod_value = 0.0;
	float Cmod_depth_param = 0.0;
	float output = 0.0;
	
	
	void setCmod_depth_param(float _value){
	Cmod_depth_param = _value;
	Cmod_depth_param *= Cmod_depth_param;
	}
	
	void setCmod_value(float _value){
	Cmod_value = _value * Cmod_depth_param;
	}

	void setC_value(float _value){
	C_value = _value * C_range;
	}

	void process (){
	Cmod_value = Cmod_value * (C_max - C_value);
	Cparam = clampf ( C_min + C_value + Cmod_value, C_min , C_max );
	axnew = Cparam * ax * ( 1.f - ax );
	output = std::isfinite( axnew ) ? 5. * axnew : 0.f;
	ax = axnew;
	
	}

	float getAudio () {
	return output;
	}
};

}; // namespace rack
