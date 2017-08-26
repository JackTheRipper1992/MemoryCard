//
//  SceneMediator.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/8/1.
//
//

#include "SceneMediator.hpp"
#include "RankScene.hpp"
#include "StartScene.hpp"
#include "MemoryCardScene.hpp"
#include "ScoreStrategy.hpp"
#include <memory>

SceneMediator* SceneMediator::m_instance=nullptr;

SceneMediator* SceneMediator::GetInstance(){
    if(m_instance==nullptr){
        m_instance=new SceneMediator();
    }
    return m_instance;
}
void SceneMediator::GoToStartScene(){
    auto scene=StartScene::CreateStartScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(0.25f, scene));
}
void SceneMediator::GoToGameScene(){
    std::shared_ptr<ScoreStrategy > score_strategy(new ScoreStrategy());
    auto scene=MemoryCardScene::CreateScene(score_strategy);
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(0.25, scene));
}
void SceneMediator::GoToRankScene(){
    auto scene=RankScene::CreatRankScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(0.25, scene));
}
