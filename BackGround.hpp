//
//  BackGround.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/9.
//
//

#ifndef BackGround_hpp
#define BackGround_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BackGround:public Node{
protected:
    Sprite *m_background;
public:
    BackGround();
    virtual ~BackGround();
    CREATE_FUNC(BackGround);
    virtual bool init();
    
    virtual void update(float dt);
    
};
#endif /* BackGround_hpp */
