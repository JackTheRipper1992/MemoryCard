//
//  StartScene.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/27.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "BackGround.hpp"
#include "ui/CocosGUI.h"

USING_NS_CC;

class StartScene:public Layer{
protected:
    BackGround* m_background;
    Sprite* m_logo;
    ui::Button* m_start_bt;
    ui::Button* m_rank_bt;
    ui::Button* m_exit_bt;
public:
    StartScene();
    virtual ~StartScene();
    CREATE_FUNC(StartScene);
    virtual bool init();
    static Scene* CreateStartScene();
    

};
#endif /* StartScene_hpp */
