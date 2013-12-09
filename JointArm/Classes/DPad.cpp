//
//  DPad.cpp
//  JointArm
//
//  Created by cesc on 13-12-9.
//
//

#include "DPad.h"

DPad::DPad(){
    
    _delegate = NULL;
    
    
}

DPad::~DPad(){
    
    
    _delegate = NULL;
    
}


bool DPad::initWithName(const cocos2d::CCString *name){
    
    if ( !CCSprite::initWithFile( name->getCString() )) {
        return false;
    }
    
    _direction = CCPointZero;
    _radius =  100.0f;
    isHolding = false;
    
    scheduleUpdate();
    
    return true;
}

DPad* DPad::createWithName(const cocos2d::CCString *name){
    
    DPad* d = new DPad;
    
    if ( d && d->initWithName( name )) {
        d->autorelease();
        return d;
    }
    
    CC_SAFE_DELETE( d );
    return NULL;
}


void DPad::update(float dt){
    
    if ( isHolding ) {
       
        if(_delegate){
            
            
            getDPadDelegate()->isHoldingDirection(this,  _direction );
        }
    }
    
    
}

bool DPad::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCPoint touchPoint = pTouch->getLocation();
    
    float distance = ccpDistance( touchPoint, this->getPosition() );
    
    if ( distance < _radius ) {
        
        isHolding = true;
        this->updateDirecton4TouchLocation( touchPoint );
        
        return true;
    }
    
    return false;
}

void DPad::updateDirecton4TouchLocation(cocos2d::CCPoint point){
    
    float radians = ccpToAngle(ccpSub( point, this->getPosition()));
    float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
    
    if (degrees <= 22.5 && degrees >= -22.5)
    {
        //right
        _direction = ccp(1.0, 0.0);
    }
    else if (degrees > 22.5 && degrees < 67.5)
    {
        //bottomright
        _direction = ccp(1.0, -1.0);
    }
    else if (degrees >= 67.5 && degrees <= 112.5)
    {
        //bottom
        _direction = ccp(0.0, -1.0);
    }
    else if (degrees > 112.5 && degrees < 157.5)
    {
        //bottomleft
        _direction = ccp(-1.0, -1.0);
    }
    else if (degrees >= 157.5 || degrees <= -157.5)
    {
        //left
        _direction = ccp(-1.0, 0.0);
    }
    else if (degrees < -22.5 && degrees > -67.5)
    {
        //topright
        _direction = ccp(1.0, 1.0);
    }
    else if (degrees <= -67.5 && degrees >= -112.5)
    {
        //top
        _direction = ccp(0.0, 1.0);
    }
    else if (degrees < -112.5 && degrees > -157.5)
    {
        //topleft
        _direction = ccp(-1.0, 1.0);
    }
    
    if ( _delegate ) {
    getDPadDelegate()->didChangedDirectorTo(this, _direction );
    }
    
}

void DPad::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCPoint touchPoint = pTouch->getLocation();
    
    this->updateDirecton4TouchLocation( touchPoint );
    
}

void DPad::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
   _direction = CCPointZero;
    isHolding = false;
    if( _delegate ){
        
        getDPadDelegate()->dpadTouchEnabled(this, _direction);
        
    }
    
}

void DPad::onEnterTransitionDidFinish(){
    CCNode::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this , 0, true );
}

void DPad::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate( this );
    CCNode::onExit();
}
