//
//  RankScene.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/28.
//
//

#ifndef RankScene_hpp
#define RankScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "BackGround.hpp"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;
class RankScene:public Layer{
protected:
    BackGround* m_background;
    ui::Button* m_back_bt;
    
    Sprite* m_score_sp;
    ui::TextAtlas* m_score_text;
    
    Sprite* m_score_list;
    std::vector<Node* > m_rank_vec;
    Node* CreateRankList(int rank,int score);
public:
    RankScene();
    virtual ~RankScene();
    CREATE_FUNC(RankScene);
    virtual bool init();
    
    static Scene* CreatRankScene();
    
    
    
};
#endif /* RankScene_hpp */
