#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    srcImg.load("kumamoto.jpg");
    targetImg.load("tokyo.jpg");
    
    /* 
     Setup plane mesh resolution and optical flow resolustion.
     width, height, stepSize, rescale
     */
    morphImage.setup(srcImg.getWidth(), srcImg.getHeight(), 2, 0.25);
    
    /*
     Set 2 sources for calculate optical flow.
     */
    morphImage.setSource(srcImg, targetImg);
    
    
    morphImage.setStrength(0);
    
    
    gui.setup(morphImage.parameters);
}
//--------------------------------------------------------------
void ofApp::update(){
    // calculate optical flow
    morphImage.update();

}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    morphImage.draw(srcImg, targetImg);
    
    gui.draw();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(20,ofGetHeight()-80));
    ofDrawBitmapStringHighlight("move mouse x to change strength", ofPoint(20,ofGetHeight()-40));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    float val = ofMap(x, 0, ofGetWidth(), 0.0, 1.0, true);
    morphImage.setStrength(val);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
