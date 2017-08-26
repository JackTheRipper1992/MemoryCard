#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::Size m_visible_size;
    cocos2d::Vec2 m_visible_origin;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
