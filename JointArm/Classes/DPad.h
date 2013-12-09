//
//  DPad.h
//  JointArm
//
//  Created by cesc on 13-12-9.
//
//

#ifndef __JointArm__DPad__
#define __JointArm__DPad__

#include "cocos2d.h"
using namespace cocos2d;

class DPad;
class DPadDelegate  {
    
    
public:
    
        virtual void didChangedDirectorTo( DPad* _dpad, CCPoint direction ) = 0;
        virtual void isHoldingDirection( DPad* _dpad, CCPoint direction ) = 0;
        virtual void dpadTouchEnabled( DPad* _dpad, CCPoint direction ) = 0;
};

class DPad : public CCSprite , public CCTargetedTouchDelegate {
    
    
public:
    
   DPad();
    ~DPad();
    void onEnterTransitionDidFinish();
    void onExit();
    void update(float dt);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    
    static DPad* createWithName( const CCString* name );
    
    bool initWithName( const CCString* name );

    bool isHolding;

    void updateDirecton4TouchLocation( CCPoint point );
    
    CC_SYNTHESIZE(DPadDelegate*, _delegate, DPadDelegate);
    

private:
    float _radius;
    CCPoint _direction;


    
    
};

#endif /* defined(__JointArm__DPad__) */
