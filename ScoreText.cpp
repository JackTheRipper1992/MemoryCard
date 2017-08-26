//
//  ScoreText.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/11.
//
//

#include "ScoreText.hpp"
ScoreText::ScoreText():m_score(0)
{
    
}
ScoreText::~ScoreText()
{
    
}
bool ScoreText::init()
{
    if(!Node::init()){
        return false;
    }
    m_text=ui::TextAtlas::create("0","number.png",63,83,"0");
    m_text->setAnchorPoint(Vec2(1,0.5));
    this->addChild(m_text);
    return true;
}
void ScoreText::UpdateView(int value)
{
    if(value==m_score){
        return;
    }
    m_score=value;
    m_text->setString(StringUtils::format("%d",value));
    auto effect=m_text->clone();
    effect->runAction(Sequence::create(
                                       Spawn::create(ScaleTo::create(0.25f, 2),
                                                     FadeOut::create(0.25),NULL),
                                       CallFunc::create([effect](){
                                        effect->removeFromParent();
    }),NULL));//当前显示分数失效后，对旧分数执行迅速的放大和淡化特效
    this->addChild(effect);
}
