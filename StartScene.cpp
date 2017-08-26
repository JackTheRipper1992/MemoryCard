//
//  StartScene.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/27.
//
//

#include "StartScene.hpp"
#include "SceneMediator.hpp"

StartScene::StartScene():
m_background(nullptr),
m_logo(nullptr),
m_start_bt(nullptr),
m_rank_bt(nullptr),
m_exit_bt(nullptr){
    
}

StartScene::~StartScene(){
    
}

Scene* StartScene::CreateStartScene(){
    auto scene=Scene::create();
    auto start_scene=StartScene::create();
    
    scene->addChild(start_scene);
    return scene;
}

bool StartScene::init(){
    if(!Layer::init()){
        return false;
    }
    auto visible_size=Director::getInstance()->getVisibleSize();
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    
    m_background=BackGround::create();
    this->addChild(m_background,0);
    
    m_logo=Sprite::create("logo.png");//游戏logo
    m_logo->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2+40));
    this->addChild(m_logo,1);
    
    m_start_bt=ui::Button::create("start.png");//开始按钮
    m_start_bt->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2-30));
    this->addChild(m_start_bt,1);
    
    m_rank_bt=ui::Button::create("charts.png");//排行榜按钮
    m_rank_bt->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2-70));
    this->addChild(m_rank_bt,1);
    
    m_exit_bt=ui::Button::create("exit.png");//结束按钮
    m_exit_bt->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height/2-110));
    this->addChild(m_exit_bt,1);
    
    m_start_bt->addClickEventListener([](Ref* ref){
        SceneMediator::GetInstance()->GoToGameScene();
    });
    m_rank_bt->addClickEventListener([](Ref* ref){
        SceneMediator::GetInstance()->GoToRankScene();
    });
    m_exit_bt->addClickEventListener([](Ref* ref){
        Director::getInstance()->end();
    });
    return true;
}
