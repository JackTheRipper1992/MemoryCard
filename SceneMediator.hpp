//
//  SceneMediator.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/8/1.
//
//

#ifndef SceneMediator_hpp
#define SceneMediator_hpp

#include <stdio.h>
#include "cocos2d.h"

class SceneMediator{
protected:
    static SceneMediator* m_instance;
public:
    static SceneMediator* GetInstance();
    virtual void GoToStartScene();
    virtual void GoToRankScene();
    virtual void GoToGameScene();
    
    
    
};
#endif /* SceneMediator_hpp */
