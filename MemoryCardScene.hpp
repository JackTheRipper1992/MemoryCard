//
//  MemoryCardScene.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/8.
//
//

#ifndef MemoryCardScene_hpp
#define MemoryCardScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "MemoryCardLevel.hpp"
#include "ScoreStrategyBase.h"
#include <memory>
#include "EnergyBar.hpp"
#include "ScoreText.hpp"
USING_NS_CC;
//这里用Layer的好处在于，随时可以创建一个Layer然后可以加入到scene中
class MemoryCardScene:public Layer{
private:
    cocos2d::Size m_visible_size;
    cocos2d::Vec2 m_visible_origin;
protected:
    int m_now_level;//当前关卡数
    int m_total_level;//关卡总数
    std::vector<LevelData > m_level_list;//存放关卡数据的容器
    MemoryCardLevel* m_memory_card_level;//当前关卡对象
    //如果引用次数为0 自动释放对象
    std::shared_ptr<ScoreStrategyBase> m_score_strategy;
    LevelData m_now_level_data;//当前关卡数据
    ScoreData m_score_data;//关卡分数
    EnergyBar* m_energy_bar;//创建能量条对象
    ScoreText* m_score_text;//关卡分数显示对象
    ui::Button* m_pause_bt;
public:
    MemoryCardScene();
    virtual ~MemoryCardScene();
    static Scene* CreateScene(std::shared_ptr<ScoreStrategyBase> score_strategy);
    static MemoryCardScene* create(std::shared_ptr<ScoreStrategyBase> score_strategy);
    virtual bool InitWithScoreStragegy(std::shared_ptr<ScoreStrategyBase> score_strategy);
    virtual void NewGame();//开始新的游戏
    virtual void update(float dt);//重写的update函数，在里面实现分数和能量条的实时变化
    virtual void InitLevelList();//用存放关卡数据的csv文件初始化存放关卡容器的对象
    virtual void NextLevel();//下一关
    virtual bool InitUI();//创建暂停按钮、能量条、分数显示
};
#endif /* MemoryCardScene_hpp */
