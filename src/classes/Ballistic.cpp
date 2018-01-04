#pragma once
#include "dsp/digital.hpp"
namespace rack {

// a basic parabolic projectile motion
// https://en.wikipedia.org/wiki/Projectile_motion

struct Ballistic {

	// newtonian
	float impulse = 10.f;
	float gravity = 9.8f; // g
	float angle = 45.f;
	float zenith = 1.f / (pow(impulse, 2) / (2.f * gravity));
	float bounce = 0.000001f;
	
	// integration
	const float radFactor  = 3.141592653589793238462f / 180.f;
	float delta = 1.f / engineGetSampleRate();
	float phase = 0.f;
		
	// signal
	float yValue = 0.f;
	float audioOut = 0.f;
	float controlOut = 0.f;
	float topTrigOut = 0.f;
	PulseGenerator zeroTrigOut;
	bool isRunning = false;
	bool bounceOnOff = false;
	bool isReBounding = false;
	int reBoundCount = 0;
	bool modeOsc = false;
	
	// get switches from panel
	
	void setBounceOnOff ( bool _bounceOnOff ){
		bounceOnOff = _bounceOnOff;
	}
	
	void setModeOsc( bool _modeOsc ){
		modeOsc = _modeOsc;
	}
	
	//get parameters from panel
	
	void setImpulse( float _impulse ){
		if(isRunning){
			// avoid very small impulses. 
			impulse = 0.01f + 100.f * pow ( clampf( _impulse, 0.f, 1.f ) ,2) ;
		}
	}
	
	void setGravity( float _gravity )
	{
		if(isRunning){
			// avoid zero gravity. Max. 10g
			gravity = 0.01f + 98.f * clampf( _gravity, 0.f, 1.f );
			}
	}	
	
	void setAngle  ( float _angle ){
		if(isRunning){
			// avoid shoot at 0º. max angle slightly less than 90ª
			// angle in degrees ( parameter must be 0. ~ 1. )	
			if(isReBounding){
				angle = radFactor *  ( 0.001f + ( 89.998 * clampf( _angle, 0.f, 1.f) * pow(bounce,(float)reBoundCount) ));
				} else {
				angle = radFactor *  ( 0.001f + ( 89.998 * clampf( _angle, 0.f, 1.f) ));
				}
			}
	}
	
	void setBounce ( float _bounce){
		// use a log scale
		bounce = ( 6.f + log10( clampf( _bounce, 0.000001f, 0.99f))) / 6.f;
	}
		
	
	//get parameter values and compute trajectory
	void shoot (bool trigger){			
		//get trigger
		if ( trigger ){ 
			isRunning = true; 
			isReBounding = false;
			reBoundCount = 0.f;
			}
		
		if( isRunning ){						
			// max. height
			zenith = (pow(impulse, 2) / (2.f * gravity));
			// integrate trajectory normalized to 1
			yValue = ((impulse * sin( angle ) * phase) - (gravity * pow( phase, 2) * 0.5f ) ) / zenith;
			phase += delta;			
			// touch the ground 
			if( yValue < 0.f ){ 
				//
				zeroTrigOut.trigger(1e-3);	
				// check bounce mode
				if ( bounceOnOff ){
				yValue =  0.f;
				phase = 0.f;
				isReBounding = true;
				reBoundCount++;
				} else {
				isRunning = false;	
				isReBounding = false;
				reBoundCount = 0;
				yValue = 0.f;
				}
			}
			// if modeOsc is selected, switch signal sign for impair rebounds
			if (isReBounding && modeOsc) {
				if(reBoundCount % 2 != 0){
					yValue *= -1.f;
					}
				}	
		} else {
			// not running ? silence...
			yValue = audioOut = phase = reBoundCount = 0.f;
		}
		// feed signals
		audioOut =  5.f * yValue;
		controlOut = 10.f * std::abs ( yValue ); 
	}

	// retrieve audio signal
	float getAudio () {
		return std::isfinite( audioOut ) ? audioOut : 0.f;
	}
	
	// retrieve control signal
	float getControl () {
		return std::isfinite( controlOut ) ? controlOut : 0.f;
	}
	
	// retrieve zero trigger
	float getZeroTrigger (){
		return ( 10.f * (float) zeroTrigOut.process(1.0 / engineGetSampleRate()) );
	}
};

}; // namespace rack
