//
//  MemoryCardLevel.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/6.
//
//

#include "MemoryCardLevel.hpp"
#include "CardFactory.hpp"

#include "SimpleAudioEngine.h"

MemoryCardLevel::MemoryCardLevel():
m_select_a(nullptr),
m_select_b(nullptr),
m_unfinished_card(0)
{
    this->setCascadeOpacityEnabled(true);   
}
MemoryCardLevel::~MemoryCardLevel(){
    this->removeAllChildren();
//    this->_eventDispatcher->removeAllEventListeners();
}
MemoryCardLevel* MemoryCardLevel::Create(LevelData level_data){
    MemoryCardLevel *mcl=new(std::nothrow)MemoryCardLevel();
    if(mcl&&mcl->InitWithLevelData(level_data)){
        mcl->autorelease();
        return mcl;
    }
    CC_SAFE_DELETE(mcl);
    return nullptr;
}
bool MemoryCardLevel::InitWithLevelData(LevelData level_data){
    if(!Layer::init()){
        return false;
    }
    //判断提供的行列是否标准
    if((level_data.row*level_data.column)%2!=0){
        return false;
    }
    //将传入的值赋值到m_level_data 方便以后通过函数查看
    m_level_data=level_data;
    
    InitCardLayout();
    InitTouchEvent();
    return true;
}
//初始化卡片布局
void MemoryCardLevel::InitCardLayout(){
    int back_id=CCRANDOM_0_1()*8;
    for (int row=0; row<m_level_data.row;++row ) {
        std::vector<Card*> r(m_level_data.column);
        m_card_table.push_back(r);
    }
    //初始化卡片并填充到卡片数组
    auto visible_origin=Director::getInstance()->getVisibleOrigin();
    CardFactory card_factory;
    int number=0;
    Vector<Card*> card_vector;
    for(;number<m_level_data.row*m_level_data.column;++number){
        auto card=dynamic_cast<Card*>(card_factory.CreateCard(back_id, number/2));
        card_vector.pushBack(card);
    }
    this->m_unfinished_card=number;
    
    for(int row=0;row<m_level_data.row;++row){
        for(int column=0;column<m_level_data.column;++column){
            auto index=CCRANDOM_0_1()*card_vector.size();
            auto card=card_vector.at(index);
            card_vector.eraseObject(card);
            
            card->GetCardData()->m_row=row;
            card->GetCardData()->m_column=column;
            ++number;
            //设置卡片位置
            int space=20;
            auto card_size=card->getContentSize();
            card->setPosition(Vec2
                              ((card_size.width+space)*column+card_size.width/2,
                                (card_size.height+space)*row+card_size.height/2)
                              );
            //添加至容器
            m_card_table[row][column]=card;
            //添加至显示列表
            this->addChild(card);
            
            //设置涂层大小
            if(column==m_level_data.column-1&&row==m_level_data.row-1){
                this->setContentSize(Size((card_size.width+space)*column+card_size.width,
                                     (card_size.height+space)*row+card_size.height));
            }
        }
    }
    //循环结束
}
void MemoryCardLevel::RegisterCallfunc(std::function<void (CardData *, CardData *)> pair_call_back, std::function<void ()> complete_call_back){
    PairCallBack=pair_call_back;
    CompleteCallBack=complete_call_back;
}
//设置卡片触摸时间
void MemoryCardLevel::InitTouchEvent(){
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[&](Touch* touch,Event* event){
        Vec2 point=this->convertToNodeSpace(touch->getLocation());
        auto size=this->getContentSize();
        auto check_rect=Rect(0,0,size.width,size.height);
        if(check_rect.containsPoint(point)){
            return true;
        }
        return false;
    };
    listener->onTouchEnded=[&](Touch* touch,Event* event){
        Vec2 point=this->convertToNodeSpace(touch->getLocation());
        Card* select_temp=nullptr;
        for(auto row=0;row<m_level_data.row;++row){
            auto row_cards=m_card_table[row];
            for(auto column=0;column<m_level_data.column;++column){
                auto card=row_cards[column];
                
                //如果遍历到的卡片为空，则说明已经被消除，继续查找,此时还未监测touch成功
                if(card==nullptr){
                    continue;
                }
                //下面开始检测碰撞
                auto size=card->getContentSize();
                auto postion=card->getPosition();
                auto check_rect=Rect(postion.x-size.width/2,postion.y-size.height/2,size.width,size.height);
                if(check_rect.containsPoint(point)){
                    //用一张临时创建的卡片来记录二维数组中的card
                    select_temp=card;
                    break;//至此，选择一张正确区域的，且没有被消除的卡片完成。
                }
            }
        }
    //在这里检测是否选择了有效的卡片，有效的意义在于：1、该区域有卡片，不是空白的。2、该卡片是第一次点击，没有翻到正面
        if(select_temp==nullptr||m_select_a==select_temp){
            return;
        }
        //这里开始，是选择到了有效的卡片，当是第一次选择时，用a卡片记录临时卡片的值
        if(m_select_a==nullptr){
            m_select_a=select_temp;
            m_select_a->FlipToFront();
//            select_temp=nullptr;
        }else{//这里开始，是选择了有效的卡片，且是第二次选择，且选择的卡片不是第一次选择的a卡片
            //两种情况：1、匹配成功，2、匹配失败
            m_select_b=select_temp;
        
            auto card_data_a=m_select_a->GetCardData();
            auto card_data_b=m_select_b->GetCardData();
            //通知外层有卡片需要匹配
            if(PairCallBack!=nullptr){
                PairCallBack(card_data_a,card_data_b);
            }
            //如果卡片数字相等，匹配成功，消除卡片
            if(card_data_a->m_number==card_data_b->m_number){
                //这里的两个临时变量是用来存储点击时纪录的临时卡片，不是专门为了lambda表达式的捕获列表创建的局部变量
                auto card_a=m_select_a;
                auto card_b=m_select_b;
                
                m_select_b->FlipToFront([&,card_a,card_b](){
                    //这两个函数必须要回调，这样才能看出翻转后立即消除的效果
                    //添加消除动画并且移除
                    card_a->runAction(Sequence::create(Spawn::create(FadeOut::create(0.25f),ScaleTo::create(0.25f, 0), NULL),CallFunc::create([this,card_a](){
                        auto p=ParticleExplosion::create();
                        p->setPosition(card_a->getPosition());
                        p->setStartColor(Color4F(1,1,1,0.25));
                        p->setEndColor(Color4F(1,1,1,0.25));
                        p->setStartColorVar(Color4F(0.1,0.1,0.1,0.25));
                        p->setEndColorVar(Color4F(0.1,0.1,0.1,0.25));
                        p->setSpeed(600);
                        p->setSpeedVar(1200);
                        p->setAutoRemoveOnFinish(true);
                        this->addChild(p);
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ye.mp3");  
                        card_a->removeFromParent();
                    }),NULL));
                    card_b->runAction(Sequence::create(Spawn::create(FadeOut::create(0.25f),ScaleTo::create(0.25f, 0), NULL),CallFunc::create([this,card_b](){
                        auto p=ParticleExplosion::create();
                        p->setPosition(card_b->getPosition());
                        p->setStartColor(Color4F(1,1,1,0.25));
                        p->setEndColor(Color4F(1,1,1,0.25));
                        p->setStartColorVar(Color4F(0.1,0.1,0.1,0.25));
                        p->setEndColorVar(Color4F(0.1,0.1,0.1,0.25));
                        p->setSpeed(600);
                        p->setSpeedVar(1200);
                        p->setAutoRemoveOnFinish(true);
                        this->addChild(p);
                        card_b->removeFromParent();
                    }),NULL));
                    
                });
                //移除数组中的
                m_card_table[card_data_a->m_row][card_data_a->m_column]=nullptr;
                m_card_table[card_data_b->m_row][card_data_b->m_column]=nullptr;
                //重新初始化临时存储空间
                m_select_a=nullptr;
                m_select_b=nullptr;
//                select_temp=nullptr;
                
                m_unfinished_card-=2;
                //这里还需要继续检测是不是已经全部配对成功
                if(m_unfinished_card==0&&CompleteCallBack!=nullptr){
                    CompleteCallBack();
                }
            }else{//如果卡片数字不相等,翻回去
            //这里的两个临时变量是用来存储点击时纪录的临时卡片，不是专门为了lambda表达式的捕获列表创建的局部变量
                auto card_a=m_select_a;
                auto card_b=m_select_b;
                m_select_b->FlipToFront();
                card_a->FlipToBack();
                card_b->FlipToBack();
                m_select_a=nullptr;
                m_select_b=nullptr;
            }
        }
    };//TouchEnd结束
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
