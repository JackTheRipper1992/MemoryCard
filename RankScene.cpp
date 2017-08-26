//
//  RankScene.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/28.
//
//

#include "RankScene.hpp"
#include "UseDefaultData.h"
#include "SceneMediator.hpp"
RankScene::RankScene():
m_background(nullptr),
m_back_bt(nullptr),
m_score_sp(nullptr),
m_score_text(nullptr),
m_score_list(nullptr)
{
    
}

RankScene::~RankScene()
{
    
}

Scene* RankScene::CreatRankScene(){
    auto scene=Scene::create();
    auto layer=RankScene::create();
    scene->addChild(layer);
    return scene;
}
bool RankScene::init(){
    if(!Layer::init()){
        return false;
    }
    auto visible_size=Director::getInstance()->getVisibleSize();
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    
    m_background=BackGround::create();
    this->addChild(m_background);
    
    m_back_bt=ui::Button::create("back.png");
    m_back_bt->setAnchorPoint(Vec2(0,1));
    m_back_bt->setPosition(Vec2(visible_origin.x+5,visible_origin.y+visible_size.height-10));
    this->addChild(m_back_bt);
    m_back_bt->addClickEventListener([](Ref* ref){
        SceneMediator::GetInstance()->GoToStartScene();
    });
    
    m_score_sp=Sprite::create("new_score.png");
    m_score_sp->setAnchorPoint(Vec2(0,0.5f));
    m_score_sp->setPosition(Vec2(visible_origin.x+5,visible_origin.y+visible_size.height-50));
    this->addChild(m_score_sp);
    
    m_score_text=ui::TextAtlas::create("0", "number.png", 63, 83, "0");
    m_score_text->setAnchorPoint(Vec2(0,0.5f));
    m_score_text->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height-90));
    auto new_score=UserDefault::getInstance()->getIntegerForKey("NEW_SCORE", 0);
    m_score_text->setString(StringUtils::format("%d",new_score));
    this->addChild(m_score_text);
    
    
    m_score_list=Sprite::create("charts_score.png");
    m_score_list->setAnchorPoint(Vec2(0,0.5f));
    m_score_list->setPosition(Vec2(visible_origin.x+5,visible_origin.y+visible_origin.y+visible_size.height-120));
    this->addChild(m_score_list);
    
    for(int i=0;i<5;++i){
        int score=UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,i).c_str(),0);
        auto row=CreateRankList(i, score);
        row->setPosition(Vec2(visible_origin.x+visible_size.width/2,visible_origin.y+visible_size.height-120-40*i));
        this->addChild(row);
        
    } 
    return true;
}

Node* RankScene::CreateRankList(int rank, int score){
    auto visible_size=Director::getInstance()->getVisibleSize();
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    auto row=Node::create();
    auto row_name=ui::TextAtlas::create(StringUtils::format("%d",rank+1), "number.png", 63, 83, "0");
    auto s=ui::TextAtlas::create(StringUtils::format("%d",score),"number.png",63,83,"0");
    
    row_name->setAnchorPoint(Vec2(0,0.5f));
    s->setAnchorPoint(Vec2(1,0.5f));
    row_name->setPosition(Vec2(10,0));
    s->setPosition(Vec2(visible_size.width-10,0));
    row->addChild(row_name);
    row->addChild(s);
    
    row->setContentSize(Size(visible_size.width,100));
    row->setAnchorPoint(Vec2(0.5,0.5));
    return row;
    
    
    
}
