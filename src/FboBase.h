
#pragma once

#include "ofMain.h"
#include "ofFbo.h"

class FboBase : public ofFbo {
public:
    
    void clear() { begin(); ofClear(0, 0); end(); }

    void scaleIntoMe(ofFbo& _fbo) { scaleIntoMe(_fbo.getTexture()); };
    void scaleIntoMe(ofTexture& _tex) {  begin(); _tex.draw(0, 0, getWidth(), getHeight()); end(); };
    
    void drawIntoMe(ofFbo& _fbo) { scaleIntoMe(_fbo.getTexture()); };
    void drawIntoMe(ofTexture& _tex) {  begin(); _tex.draw(0, 0); end(); };
    
    GLint getInternalFormat() { return getTexture().getTextureData().glInternalFormat; };
    
};
