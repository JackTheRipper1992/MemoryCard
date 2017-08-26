//
//  ScoreStrategyBace.h
//  MemoryCard
//
//  Created by 刘颖 on 17/7/8.
//
//

#ifndef ScoreStrategyBace_h
#define ScoreStrategyBace_h

#include "ScoreData.h"
#include "CardData.h"

class ScoreStrategyBase{
public:
    virtual void excute(ScoreData* score,CardData* data_a,CardData* data_b)=0;//虚方法 待实现
    
    
    
    
    
};


#endif /* ScoreStrategyBace_h */
