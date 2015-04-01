//
//  MorphShader.h
//  ImageMorph
//
//  Created by oyama on 2015/03/27.
//
//

#pragma once

#include "ofMain.h"
#include "AbstractShader.h"

class MorphShader : public AbstractShader {
public:
    
    MorphShader(){
        ofLogVerbose("init MorphShader");
        if (isProgrammableRenderer) {
            glThree();
        }
        else{
            glTwo();
        }
    }
    
    ofParameterGroup parameters;
    
protected:
    void glTwo() {
        vertexShader = GLSL120(
                               uniform sampler2DRect source;
                               uniform sampler2DRect flow;
                               uniform float scaleFactor;
                               uniform float strength;
                               uniform float sourceRescale;
                               uniform float flowRescale;
                               varying vec2 texCoord;
                               
                               void main() {
                                   vec2 baseCoord = gl_Vertex.xy;
                                   texCoord = baseCoord * sourceRescale;
                                   vec2 offset = texture2DRect(flow, baseCoord * flowRescale).xy;
                                   vec4 position = gl_Vertex;
                                   offset = offset / scaleFactor;
                                   position.x += strength * offset.x * 3;
                                   position.y += strength * offset.y * 3;
                                   gl_Position = gl_ModelViewProjectionMatrix * position;
                               }
                               );
        
        fragmentShader = GLSL120(
                                 uniform sampler2DRect source;
                                 uniform float strength;
                                 varying vec2 texCoord;
                                 uniform int bUseAlpha;
                                 
                                 void main() {
                                     vec4 color;
                                     if (bUseAlpha == 1) {
                                         color.rgb = texture2DRect(source, texCoord).rgb;
                                         
                                         color.a = 1.0 - strength;
                                         
                                     }
                                     else {
                                         color = texture2DRect(source, texCoord);
                                     }
                                     gl_FragColor = color;
                                 }
                                );
        shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        shader.linkProgram();

    }
    void glThree() {
        vertexShader = GLSL150(

                               uniform mat4 modelViewProjectionMatrix;
                               uniform sampler2DRect flow;
                               uniform float scaleFactor;
                               uniform float strength;
                               uniform float sourceRescale;
                               uniform float flowRescale;
                               in vec4 position;
                               in vec2	texcoord;
                               out vec2 texCoordVarying;
                               
                               void main() {
                                   texCoordVarying = position.xy * sourceRescale;
                                   
                                   vec2 offset = texture(flow, position.xy * flowRescale).xy;
                                   vec4 pos = position;
                                   offset = offset / scaleFactor;
                                   pos.x += strength * offset.x * 3;
                                   pos.y += strength * offset.y * 3;

                                   gl_Position = modelViewProjectionMatrix * pos;
                               }

                                 );
        fragmentShader = GLSL150(
                                 
                                 uniform sampler2DRect source;
                                 uniform float strength;
                                 uniform int bUseAlpha;
                                 out vec4 fragColor;
                                 in vec2 texCoordVarying;
                                 
                                 void main()
                                 {
                                     vec4 color;
                                     if (bUseAlpha == 1) {
                                         color.rgb = texture(source, texCoordVarying).rgb;
                                         
                                         color.a = 1.0 - strength;
                                     }
                                     else {
                                         color = texture(source, texCoordVarying);
                                     }
                                     fragColor = color;
                                 }


                                 );
        shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        shader.bindDefaults();
        shader.linkProgram();
    }
public:
    void update(ofTexture& flowTex, ofBaseHasTexture &src, ofBaseHasTexture &target,
                ofVboMesh& srcMesh, ofVboMesh& targetMesh, float strength, float scaleFactor, float rescale) {
        shader.begin();
        shader.setUniformTexture("source", target, 1);
        shader.setUniformTexture("flow", flowTex, 2);
        shader.setUniform1i("bUseAlpha", 0);
        shader.setUniform1f("strength", strength - 1.0);
        shader.setUniform1f("scaleFactor", scaleFactor);
        shader.setUniform1f("flowRescale", rescale);
        shader.setUniform1f("sourceRescale", 1);
        targetMesh.draw(OF_MESH_FILL);
        shader.end();
        
        shader.begin();
        shader.setUniformTexture("source", src, 1);
        shader.setUniformTexture("flow", flowTex, 2);
        shader.setUniform1i("bUseAlpha", 1);
        shader.setUniform1f("strength", strength);
        shader.setUniform1f("scaleFactor", scaleFactor);
        shader.setUniform1f("flowRescale", rescale);
        shader.setUniform1f("sourceRescale", 1);
        srcMesh.draw(OF_MESH_FILL);
        shader.end();
    }
};