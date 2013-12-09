#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DPad.h"

class HelloWorld : public cocos2d::CCLayer,public DPadDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

           virtual void didChangedDirectorTo( DPad* _dpad, CCPoint direction );
        virtual void isHoldingDirection( DPad* _dpad, CCPoint direction );
    virtual void dpadTouchEnabled( DPad* _dpad, CCPoint direction );
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

void walk( CCPoint direction );
cocos2d::CCSprite* roleSprite;
};

#endif // __HELLOWORLD_SCENE_H__
