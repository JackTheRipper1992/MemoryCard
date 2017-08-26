//
//  ScoreStrategy.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/8.
//
//

#include "ScoreStrategy.hpp"

ScoreStrategy::ScoreStrategy():m_continuous_temp(0){
    
}
void ScoreStrategy::excute(ScoreData *score_data, CardData *data_a, CardData *data_b){
    if(data_a->m_number==data_b->m_number){
        //配对成功 增长能量 增加连击数
        ++m_continuous_temp;//连击数需要在一次失败的匹配后置0
        if(m_continuous_temp>score_data->m_max_continuous){
            score_data->m_max_continuous=m_continuous_temp;
        }
        score_data->m_energy+=100;
        //增加分数 取连击数作为倍数 连击数越大 一次得分越高
        score_data->m_score+=100*m_continuous_temp;
    }else{
        //如果卡片是第一次翻开 说明之前不可预见卡片正面的数字 未能进行有效记忆 则不扣除能量
        if(data_a->m_flip_count<1&&data_b->m_flip_count<1){
            
        }else{
        m_continuous_temp=0;
        score_data->m_energy-=100;
        }
    }
    data_a->m_flip_count++;
    data_b->m_flip_count++;
}
