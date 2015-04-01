//
//  ofxMorphImage.h
//  ImageMorph
//
//  Created by oyama on 2015/03/27.
//
//

#pragma once

#include "OpticalFlow.h"
#include "MorphShader.h"

class ofxMorphImage {
public:
    void setup(int w, int h, int stepSize, float rescale);
    void setSource(ofBaseHasTexture &src, ofBaseHasTexture &target);
    void setSource(ofBaseHasTexture &target);
    void setStrength(float val);
    void update();
    void draw(ofBaseHasTexture &src, ofBaseHasTexture &target);
    ofParameterGroup parameters;
private:
    OpticalFlow optFlow;
    ofVboMesh srcMesh, targetMesh;
    int stepSize, xSteps, ySteps;
    int width, height;
    float rescale, scaleFactor;
    float strength, learningRate;
    MorphShader morphShader;
};