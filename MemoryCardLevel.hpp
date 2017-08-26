//
//  MemoryCardLevel.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/6.
//
//

#ifndef MemoryCardLevel_hpp
#define MemoryCardLevel_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "LevelData.h"
#include <vector>
#include "Card.hpp"
using namespace cocos2d;

class MemoryCardLevel:public Layer{
private:
    //关卡数据
    LevelData m_level_data;
    
    //定义二维数组来存放卡片
    std::vector<std::vector<Card*> > m_card_table;
    
    //未消除完的卡片
    int m_unfinished_card;
    
    //一次配对中被选择的卡片a和b
    Card* m_select_a;
    Card* m_select_b;
    
    //两张卡片匹配时回调
    std::function<void(CardData* card_a,CardData* card_b)> PairCallBack;
    
    //全部匹配完成后回调
    std::function<void()> CompleteCallBack;
public:
    
    MemoryCardLevel();
    virtual ~MemoryCardLevel();
    
    static MemoryCardLevel* Create(LevelData level_data);
    virtual bool InitWithLevelData(LevelData level_data);
    
    //注册回调函数
    void RegisterCallfunc(std::function<void(CardData* card_a,CardData* card_b)> pair_call_back,std::function<void()> complete_call_back);
    
protected:
    void InitCardLayout();
    void InitTouchEvent();
};
#endif /* MemoryCardLevel_hpp */
