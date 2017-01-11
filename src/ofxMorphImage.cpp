//
//  ofxMorphImage.cpp
//  ImageMorph
//
//  Created by oyama on 2015/03/27.
//
//

#include "ofxMorphImage.h"

//---------------------------------------------------------------------------
void ofxMorphImage::setup(int w, int h, int stepSize = 2, float rescale = 0.5) {
    
    width = w, height = h;
    
    strength = 0.0;
    this->rescale = rescale;
    this->stepSize = stepSize;
    
    scaleFactor = 1. / 10;
    srcMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    targetMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    xSteps = 1+((rescale * w) / stepSize);
    ySteps = 1+((rescale * h) / stepSize);
    for(int y = 0; y < ySteps; y++) {
        for(int x = 0; x < xSteps; x++) {
            srcMesh.addVertex(ofVec2f(x, y) * stepSize / rescale);
            targetMesh.addVertex(ofVec2f(x, y) * stepSize / rescale);
        }
    }
    for(int y = 0; y + 1 < ySteps; y++) {
        for(int x = 0; x + 1 < xSteps; x++) {
            int nw = y * xSteps + x;
            int ne = nw + 1;
            int sw = nw + xSteps;
            int se = sw + 1;
            srcMesh.addIndex(nw);
            srcMesh.addIndex(ne);
            srcMesh.addIndex(se);
            srcMesh.addIndex(nw);
            srcMesh.addIndex(se);
            srcMesh.addIndex(sw);
            targetMesh.addIndex(nw);
            targetMesh.addIndex(ne);
            targetMesh.addIndex(se);
            targetMesh.addIndex(nw);
            targetMesh.addIndex(se);
            targetMesh.addIndex(sw);
        }
    }
    
    optFlow.setup(w*rescale, h*rescale);
    parameters = optFlow.parameters;
}
//---------------------------------------------------------------------------
void ofxMorphImage::setSource(ofBaseHasTexture &src, ofBaseHasTexture &target) {
    optFlow.setSource(src.getTexture());
    optFlow.setSource(target.getTexture());
}
//---------------------------------------------------------------------------
void ofxMorphImage::setSource(ofBaseHasTexture &target) {
    optFlow.setSource(target.getTexture());
}
//---------------------------------------------------------------------------
void ofxMorphImage::update() {
    optFlow.update();
}
//---------------------------------------------------------------------------
void ofxMorphImage::setStrength(float val) {
    strength = val;
}
//---------------------------------------------------------------------------
void ofxMorphImage::draw(ofBaseHasTexture &src, ofBaseHasTexture &target) {
    if(optFlow.getOpticalFlowDecay().isAllocated()) {
        morphShader.update(optFlow.getOpticalFlowDecay(), src, target, srcMesh, targetMesh, strength, scaleFactor, rescale);
    }
}
//---------------------------------------------------------------------------
