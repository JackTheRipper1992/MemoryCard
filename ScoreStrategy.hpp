//
//  ScoreStrategy.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/8.
//
//

#ifndef ScoreStrategy_hpp
#define ScoreStrategy_hpp

#include <stdio.h>
#include "ScoreStrategyBase.h"


class ScoreStrategy:public ScoreStrategyBase{
private:
    int m_continuous_temp;//最大连击数的临时变量
public:
    ScoreStrategy();
    virtual void excute(ScoreData* score,CardData* data_a,CardData* data_b);

};
#endif /* ScoreStrategy_hpp */
