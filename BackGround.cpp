//
//  BackGround.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/9.
//
//

#include "BackGround.hpp"
BackGround::BackGround():
m_background(nullptr)
{
    
}
BackGround::~BackGround()
{
    this->unscheduleUpdate(); //如果类有update方法必须要在析构函数中停止它
}
bool BackGround::init()
{
    if(!Node::init()){
        return false;
    }
    
    
    m_background=Sprite::create("background.png");
    m_background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //下面将背景设置为平铺，利用cocos2d提供的纹理参数类
    Texture2D::TexParams texture_parameter={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};//实现纹理平铺的参数
    m_background->getTexture()->setTexParameters(texture_parameter);
    auto visible_size=Director::getInstance()->getVisibleSize();
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    auto texture_rect=Rect(visible_origin.x,visible_origin.y,
                           visible_origin.x+visible_size.width,visible_origin.y+visible_size.height);
    m_background->setTextureRect(texture_rect);
    this->addChild(m_background);
    scheduleUpdate();
    return true;
}
void BackGround::update(float dt)
{
    auto rect=m_background->getTextureRect();
    rect.origin.x+=10*dt;
    rect.origin.y+=10*dt;
    m_background->setTextureRect(rect);
}
