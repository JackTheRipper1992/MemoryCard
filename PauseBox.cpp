//
//  PauseBox.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/23.
//
//

#include "PauseBox.hpp"
#include "ui/CocosGui.h"
PauseBox::PauseBox(){
    
}
PauseBox::~PauseBox(){
    
}
bool PauseBox::init(){
    if(!Layer::init()){
        return false;
    }
    auto visible_size=Director::getInstance()->getVisibleSize();
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    
    auto background=LayerColor::create(Color4B(0, 0, 0, 200));
    auto box=ui::Scale9Sprite::create("message_box.png");
    auto continue_bt=ui::Button::create("continue.png");
    auto end_game_bt=ui::Button::create("end_game.png");
    
    box->setContentSize(Size(150,100));
    box->setPosition(visible_origin+visible_size/2);
    
    continue_bt->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2+25));
    end_game_bt->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2-25));
    
    this->setContentSize(visible_size);
    
    this->addChild(background);
    this->addChild(box);
    this->addChild(continue_bt);
    this->addChild(end_game_bt);
    
    RegisterCallback(m_continue_callback, m_end_game_callback);
    
    continue_bt->addClickEventListener([this](Ref* ref){
        if(m_continue_callback!=nullptr){
            m_continue_callback();
        }
    });

    end_game_bt->addClickEventListener([this](Ref* ref){
        if(m_end_game_callback!=nullptr){
            m_end_game_callback();
        }
    });
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[](Touch* t,Event* e){return true;};
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);//首先让背景和屏幕一样大，然后把触摸事件发生在背景上，并且swallowtouched，防止向下传递，引起方块翻转。游戏逻辑错乱。
    return true;
}
void PauseBox::RegisterCallback(std::function<void ()> continue_callback, std::function<void ()> end_game_callback){
    m_end_game_callback=end_game_callback;
    m_continue_callback=continue_callback;
    
}
