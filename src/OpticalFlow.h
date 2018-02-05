
#pragma once

#include "ofMain.h"
#include "SwapBuffer.h"
#include "OpticalFlowShader.h"
#include "GaussianBlurShader.h"

class OpticalFlow {
public:
    
    OpticalFlow();
    void setup(int _width, int _height);
    void update(float _deltaTime = 0);
    void setSource(ofTexture& _tex);
    
    ofTexture&	getTexture() {return getOpticalFlow() ;};
    ofTexture&	getOpticalFlow() {return velocityBuffer.getTexture();};
    ofTexture&	getOpticalFlowDecay() {if(doBlur.get()) return blurBuffer.getTexture(); else return velocityBuffer.getTexture(); };
    
    int			getFlowVectorSize(){return width * height;};
    ofVec2f*	getFlowVectors();
    float		getAverageFlow();
    
    int			getWidth() {return width;};
    int			getHeight(){return height;};
    
    
    float		getStrength()	{return strength.get();}
    int			getOffset()		{return offset.get();}
    float		getLambda()		{return lambda.get();}
    float		getThreshold()	{return threshold.get();}
    bool		getInverseX()	{return doInverseX.get();}
    bool		getInverseY()	{return doInverseY.get();}
    bool		getBlurActive()	{return doBlur.get();}
    float		getBlurRadius() {return blurRadius.get();}
    
    void		setStrength(float value)	{strength.set(value);}
    void		setOffset(int value)		{offset.set(value);}
    void		setLambda(float value)		{lambda.set(value);}
    void		setThreshold(float value)	{threshold.set(value);}
    void		setInverseX(bool value)		{doInverseX.set(value);}
    void		setInverseY(bool value)		{doInverseY.set(value);}
    void		setBlurActive(bool value) {doBlur.set(value);}
    void		setBlurRadius(float value) {blurRadius.set(value);}
    
    ofParameterGroup	parameters;
protected:
    ofParameter<float>	strength;
    ofParameter<int>	offset;
    ofParameter<float>	lambda;
    ofParameter<float>	threshold;
    ofParameter<bool>	doInverseX;
    ofParameter<bool>	doInverseY;
    ofParameter<bool>	doBlur;
    ofParameterGroup	timeBlurParameters;
    ofParameter<float>	blurRadius;
    
    int		width;
    int		height;
    float	deltaTime;
    float   lastTime;
    float	timeStep;
    
    bool bSourceSet;
    
    ofTexture velocityTexture;
    
    FboBase velocityBuffer;
    FboBase blurBuffer;
    SwapBuffer sourceSwapBuffer;
    OpticalFlowShader opticalFlowShader;
    GaussianBlurShader blurShader;
    
    float*	flowFloats;
    ofVec2f* flowVectors;
    bool	flowVectorsDidUpdate;
    
};
