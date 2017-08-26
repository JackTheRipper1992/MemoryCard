//
//  PauseBox.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/23.
//
//

#ifndef PauseBox_hpp
#define PauseBox_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class PauseBox:public Layer{
protected:
    std::function<void()> m_continue_callback;
    std::function<void()> m_end_game_callback;
public:
    PauseBox();
    virtual ~PauseBox();
    CREATE_FUNC(PauseBox);
    virtual bool init();
    virtual void RegisterCallback(std::function<void()> continue_callback,std::function<void()> end_game_callback);
};
#endif /* PauseBox_hpp */
