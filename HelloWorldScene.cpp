#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Card.hpp"
#include "CardFactory.hpp"
#include "MemoryCardLevel.hpp"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
  
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    m_visible_size=Director::getInstance()->getVisibleSize();
    m_visible_origin=Director::getInstance()->getVisibleOrigin();
//    CardFactory factory;
//    auto card=dynamic_cast<Card*>(factory.CreateCard(2, 0));
//    card->setPosition(m_visible_origin+m_visible_size/2);
//    this->addChild(card);
    LevelData level_data={};
    level_data.row=4;
    level_data.column=3;
    auto level=MemoryCardLevel::Create(level_data);
    level->setAnchorPoint(Vec2(0.5f,0.5f));
    level->setIgnoreAnchorPointForPosition(false);
    level->setPosition(m_visible_origin+m_visible_size/2);
    
    auto scale_fix_width=m_visible_size.width/(level->getContentSize().width+40);
    level->setScale(scale_fix_width);
    addChild(level);
    //给预先设置好的回调函数赋lambda表达式
    level->RegisterCallfunc([](CardData* data_a,CardData* data_b){
        CCLOG("%d %d",data_a->m_number,data_b->m_number);
    }, [](){
        CCLOG("Mission Complete!");
    });
    
    return true;
}


