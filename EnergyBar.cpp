//
//  EnergyBar.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/11.
//
//

#include "EnergyBar.hpp"
EnergyBar::EnergyBar():m_percentage(0)
{

}
EnergyBar::~EnergyBar()
{
    
}

bool EnergyBar::init()
{
    if(!Node::init()){
        return false;
    }
    //能量条前景
    m_progress=ProgressTimer::create(Sprite::create("energy_front.png"));
    m_progress->setType(ProgressTimer::Type::BAR);//条状
    m_progress->setMidpoint(Vec2(0,0));//设置中点最左边
    m_progress->setBarChangeRate(Vec2(1,0));//设置可变区域为x方向
    //能量条背景
    m_bar_background=Sprite::create("energy_back.png");
    
    
    this->addChild(m_bar_background);
    this->addChild(m_progress);
    
    this->setContentSize(m_bar_background->getContentSize());
    UpdateView(1000);
    return true;
    
}
void EnergyBar::UpdateView(int value)
{
    auto percentage=value/1000.0f*100;
    if(abs(percentage-m_percentage)>1.0f){
        m_progress->runAction(EaseBackOut::create(ProgressTo::create(0.25, percentage)));//能量变化效果
        m_percentage=percentage;

    }
    }
