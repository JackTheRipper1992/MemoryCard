//
//  EnergyBar.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/11.
//
//

#ifndef EnergyBar_hpp
#define EnergyBar_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class EnergyBar:public Node{
protected:
    ProgressTimer* m_progress;//使用该类来展示进度
    Sprite *m_bar_background;//创建显示对象
    float m_percentage;
public:
    EnergyBar();
    virtual ~EnergyBar();
    CREATE_FUNC(EnergyBar);
    virtual bool init();
    
    void UpdateView(int value);
    
    
    
};
#endif /* EnergyBar_hpp */
