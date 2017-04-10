#pragma once

//
//  ofxPostGlitch.h
//
//  Created by maxilla inc. on 2013/02/01.
//
//

#ifndef __ofxPostGlitchExample__ofxPostGlitch__
#define __ofxPostGlitchExample__ofxPostGlitch__

#include "ofMain.h"

#define GLITCH_NUM 17

enum ofxPostGlitchType {
	OFXPOSTGLITCH_CONVERGENCE,
	OFXPOSTGLITCH_GLOW,
	OFXPOSTGLITCH_SHAKER,
	OFXPOSTGLITCH_CUTSLIDER,
	OFXPOSTGLITCH_TWIST,
	OFXPOSTGLITCH_OUTLINE,
	OFXPOSTGLITCH_NOISE,
	OFXPOSTGLITCH_SLITSCAN,
	OFXPOSTGLITCH_SWELL,
	OFXPOSTGLITCH_INVERT,
	OFXPOSTGLITCH_CR_HIGHCONTRAST,
	OFXPOSTGLITCH_CR_BLUERAISE,
	OFXPOSTGLITCH_CR_REDRAISE,
	OFXPOSTGLITCH_CR_GREENRAISE,
	OFXPOSTGLITCH_CR_REDINVERT,
	OFXPOSTGLITCH_CR_BLUEINVERT,
	OFXPOSTGLITCH_CR_GREENINVERT
};

class PostGlitch
{
public:
	PostGlitch() {
		targetBuffer = NULL;
		shader[0].load("shader/convergence");
		shader[1].load("shader/glow");
		shader[2].load("shader/shaker");
		shader[3].load("shader/cut_slider");
		shader[4].load("shader/twist");
		shader[5].load("shader/outline");
		shader[6].load("shader/noise");
		shader[7].load("shader/slitscan");
		shader[8].load("shader/swell");
		shader[9].load("shader/invert");
		shader[10].load("shader/crHighContrast");
		shader[11].load("shader/crBlueraise");
		shader[12].load("shader/crRedraise");
		shader[13].load("shader/crGreenraise");
		shader[14].load("shader/crRedinvert");
		shader[15].load("shader/crBlueinvert");
		shader[16].load("shader/crGreeninvert");
	}

	/* Initialize & set target Fbo */
	void setup(ofFbo* buffer_);

	/* Set target Fbo */
	void setFbo(ofFbo* buffer_);

	/* Switch each effects on/off */
	void setFx(ofxPostGlitchType type_, bool enabled);

	/* Toggle each effects on/off */
	void toggleFx(ofxPostGlitchType type_);

	/* Return current effect's enabled info*/
	bool getFx(ofxPostGlitchType type_);

	/* Apply enable effects to target Fbo */
	void generateFx();

protected:
	bool		bShading[GLITCH_NUM];
	ofShader	shader[GLITCH_NUM];
	ofFbo*		targetBuffer;
	ofFbo		ShadingBuffer;
	ofPoint		buffer_size;
	float ShadeVal[4];

	ofPlanePrimitive plane;
};

#endif /* defined(__ofxPostGlitchExample__ofxPostGlitch__) */
