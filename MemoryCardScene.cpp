//
//  MemoryCardScene.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/8.
//
//

#include "MemoryCardScene.hpp"
#include "BackGround.hpp"
#include "PauseBox.hpp"
#include "StartScene.hpp"
#include "UseDefaultData.h"
#include "SceneMediator.hpp"
#include "SimpleAudioEngine.h"
MemoryCardScene::MemoryCardScene():
m_score_data({}),
m_memory_card_level(nullptr)
{
    m_score_data.m_energy=1000;
}
MemoryCardScene::~MemoryCardScene()
{
    this->unscheduleUpdate();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
Scene* MemoryCardScene::CreateScene(std::shared_ptr<ScoreStrategyBase> score_strategy)
{
    auto scene=Scene::create();
    auto layer=MemoryCardScene::create(score_strategy);
    scene->addChild(layer,1);
    auto back_ground=BackGround::create();
    scene->addChild(back_ground,0);
    return scene;
}
MemoryCardScene* MemoryCardScene::create(std::shared_ptr<ScoreStrategyBase> score_strategy)
{
    MemoryCardScene *layer=new(std::nothrow)MemoryCardScene();
    if(layer&&layer->InitWithScoreStragegy(score_strategy)){
        layer->autorelease();
        return layer;
    }else{
        delete layer;
        layer=nullptr;
        CC_SAFE_DELETE(layer);
        return nullptr;
    }
}
//传递MemoryCardScene类型的layer的this指针
bool MemoryCardScene::InitWithScoreStragegy(std::shared_ptr<ScoreStrategyBase> score_strategy)
{
    if(!Layer::init()){
        return false;
    }
    m_score_strategy=score_strategy;
        //初始化关卡容器
    InitLevelList();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("pitpat.mp3");
    
    //开始新的游戏
    NewGame();
    
    //启动update方法
    this->scheduleUpdate();
    return true;
}
//继续传递this指针
void MemoryCardScene::InitLevelList(){//这里解析csv文件
    //利用FileUtils加载csv文件
    auto str=FileUtils::getInstance()->getStringFromFile("level_list.csv");
    std::vector<std::string> row_data;//创建一个临时的vector存放分割出来的行
    char* row=strtok((char*)str.c_str(), "\n");//分割csv文件,每次切割返回一个指向切割出来部分的指针
    while(row){//利用while循环进行持续的切割，如果切割完毕，row等于空，退出循环
        row_data.push_back(row);
        row=strtok(nullptr,"\n");
    }//循环完成后，行切割完毕，每行单独存入vector
    
    for(auto row=row_data.begin();row!=row_data.end();++row){//列的切割
        char* game_row=strtok((char*)row->c_str(), ",");
        char* game_column=strtok(nullptr, ",");
        char* game_loss=strtok(nullptr, ",");
        if(game_row==nullptr||game_column==nullptr||game_loss==nullptr){
            continue;//结束当前for循环
        }
        LevelData level_data;
        level_data.row=atoi(game_row);//将字符串转化为int类型
        level_data.column=atoi(game_column);
        level_data.loss=atoi(game_loss);
        //待数据转化为int类型后，进行游戏数据有效性的判断
        if(level_data.row*level_data.column<=0||(level_data.row*level_data.column)%2!=0||level_data.loss<0){
            continue;//结束当前for循环
        }
        m_level_list.push_back(level_data);
    }
    m_total_level=m_level_list.size();
}
void MemoryCardScene::NewGame()
{
    m_now_level=-1;
    NextLevel();
}
void MemoryCardScene::NextLevel(){
    m_visible_size=Director::getInstance()->getVisibleSize();
    m_visible_origin=Director::getInstance()->getVisibleOrigin();
    InitUI();
//    LevelData level_data={};
//    level_data.row=4;
//    level_data.column=3;
//    level_data.loss=20;//设置损耗值为20 值越大 损耗越快
    m_now_level++;
    if(m_now_level>=m_total_level)////////////////////////////////////////////////////////////////////////////待修改
    {
        m_now_level=0;
    }
    m_now_level_data=m_level_list[m_now_level];//从关卡容器中取出关卡数据创建新关卡
    auto level=m_memory_card_level=MemoryCardLevel::Create(m_now_level_data);
    //设置游戏关卡的位置坐标并添加至显示
    level->setAnchorPoint(Vec2(0.5f,0.5f));
    level->setIgnoreAnchorPointForPosition(false);
    level->setPosition(m_visible_origin+m_visible_size/2);
    auto scale_fix_width=m_visible_size.width/(level->getContentSize().width+40);
    level->setScale(2);
    level->setOpacity(0);
    addChild(level);
    level->runAction(Spawn::create(FadeIn::create(1.0f),ScaleTo::create(0.25f, scale_fix_width), NULL));
    m_memory_card_level=level;//纪录当前关卡
    //给预先设置好的回调函数赋lambda表达式
    level->RegisterCallfunc([this](CardData* data_a,CardData* data_b){
        m_score_strategy->excute(&m_score_data, data_a, data_b);
        CCLOG("score: %d,energy: %d,maxcontinuous: %d",m_score_data.m_score,m_score_data.m_energy,m_score_data.m_max_continuous);
    }, [this](){
        
        CCLOG("Mission Complete!");
        m_memory_card_level->removeFromParent();
        NextLevel();
    });
}
void MemoryCardScene::update(float dt)
{
    Layer::update(dt);
    m_score_data.m_energy-=this->m_now_level_data.loss*dt;
    if(m_score_data.m_energy>1000){
        m_score_data.m_energy=1000;
    }else if(m_score_data.m_energy<0){
        m_score_data.m_energy=0;
    }
    m_energy_bar->UpdateView(m_score_data.m_energy);
    m_score_text->UpdateView(m_score_data.m_score);
    
    if(m_score_data.m_energy<=0){
        //游戏结束
        UserDefault::getInstance()->setIntegerForKey("NEW_SCORE", m_score_data.m_score);
        std::vector<int> score_list;
        score_list.push_back(m_score_data.m_score);
        for(int i=0;i<5;i++){
            int score=UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,i).c_str(),0);
            score_list.push_back(score);
        }
        std::sort(score_list.begin(), score_list.end(), [](int &a,int &b){return a>b;});
        for(int rank=0;rank<10;){//setIntegerForKey函数里的％d需要int值，临时变量i不是int类型
        for(auto i=score_list.begin();i!=score_list.end();i++){
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,rank).c_str(), *i);//i是迭代器，＊i才是值
            rank++;
            }
        }
        this->unscheduleUpdate();
        SceneMediator::GetInstance()->GoToRankScene();
    }
    if(m_score_data.m_energy<600){
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((600.0f-m_score_data.m_energy)/600.0f);
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
    }
    
}
bool MemoryCardScene::InitUI(){
    //创建能量条
    m_energy_bar=EnergyBar::create();
    m_energy_bar->setPosition(Vec2(m_visible_origin.x+m_visible_size.width/2-13,
                                   m_visible_origin.y+m_visible_size.height-m_energy_bar->getContentSize().height));
    this->addChild(m_energy_bar,2);
    //创建分数显示对象
    m_score_text=ScoreText::create();
    m_score_text->setPosition(Vec2(m_visible_origin.x+m_visible_size.width-10,
                                   m_visible_origin.y+m_visible_size.height-12));
    this->addChild(m_score_text,2);
    
    m_pause_bt=ui::Button::create("pause.png");
    m_pause_bt->setAnchorPoint(Vec2(0,1));
    m_pause_bt->setPosition(Vect(m_visible_origin.x,m_visible_origin.y+m_visible_size.height));
    this->addChild(m_pause_bt);
    
    m_pause_bt->addClickEventListener([this](Ref* ref){
        this->unscheduleUpdate();
        auto pause_box=PauseBox::create();
        pause_box->RegisterCallback([this,pause_box](){
            pause_box->removeFromParent();
            this->scheduleUpdate();
        }, [](){
//            auto scene=StartScene::CreateStartScene();
//            Director::getInstance()->pushScene(scene);
            SceneMediator::GetInstance()->GoToStartScene();
        });
//        pause_box->setPosition(m_visible_size/2);
        this->addChild(pause_box);
    });
    return true;
}
