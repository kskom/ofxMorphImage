#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /*
     apply morph vertex data to another video 
    */
    
    ofSetVerticalSync(true);
    
    src.loadMovie("ink.mov");
    target.loadMovie("amoeba.mov");
    
    output.loadMovie("test.mov");
    output.play();
    
    morphImage.setup(src.width, src.height, 2, 0.5);
    
    morphImage.setSource(src, target);
    morphImage.update();
    
    morphImage.setStrength(0.5);

    
    src.play();
    target.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    src.update();
    target.update();
    output.update();
    
    if(src.isFrameNew()) {
        morphImage.setSource(src, target);
        morphImage.update();
    }
    
    morphImage.setStrength(ofSignedNoise(ofGetElapsedTimef())*3.0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    morphImage.draw(output, output);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(20,20));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
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
