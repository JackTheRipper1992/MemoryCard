//
//  Card.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#include "Card.hpp"
Card::Card():
m_front_image(nullptr),//初始化卡片正面对象 Node*类型
m_back_image(nullptr),//初始化卡片背面对象 Node*类型
m_card_state(CardState::BACK),//初始化卡片状态对象
m_card_data({})//空列表初始化卡片数据对象
{
    this->setCascadeColorEnabled(true);//打开颜色层级设置开关
}
Card::~Card(){
    this->removeAllChildren();//移除所有子节点
}
Node* Card::getBackImage()const{
    return m_back_image;//返回卡片背面对象
}
void Card::setBackImage(cocos2d::Node *var){
    if(var==nullptr){//首先判断传入的对象是否有效
        return;
    }
    if(m_back_image!=nullptr){//检查背面图片对象是否已有初始值，若初始值非空，则移除自身
        m_back_image->removeFromParent();
    }
    m_back_image=var;
    m_back_image->setCascadeColorEnabled(true);
    m_back_image->setVisible(true);
    addChild(m_back_image);
}
Node* Card::getFrontImage()const{
    return m_front_image;
}
void Card::setFrontImage(cocos2d::Node *var){
    if(var==nullptr){
        return;
    }
    if(m_front_image!=nullptr){ 
        m_front_image->removeFromParent();
    }
    m_front_image=var;
    m_front_image->setCascadeColorEnabled(true);
    m_front_image->setVisible(false);
    addChild(m_front_image);
}
void Card::FlipFromTo(Node* a, Node* b,const std::function<void()>&callback){
    if(a==nullptr||b==nullptr){//判断如果a，b无效，则返回
        return;
    }
    //首先进行初始化
    a->stopAllActions();//停止所有动作
    b->stopAllActions();
    
    a->setVisible(true);//让a面显示
    a->setScale(1.0f,1.0f);//设置缩放比例1：1
    
    b->setVisible(false);//让b面不可见
    b->setScale(0.0f,1.0f);//设置缩放比列0：1，设置scaleY为1是为了翻面的时候的真实感
    
    auto flipB=[a,b,callback](){//首先用lambda表达式创建一个可调用函数
        a->setVisible(false);//让a面不可见
        b->setVisible(true);//让b面显示
        
        CallFunc *func=nullptr;//初始化一个CallFunc* 类型的临时可调用对象为空
        if(callback!=nullptr){//判断如果传入的函数指针不为空，即该函数指针指向了外部的某个可执行对象
            func=CallFunc::create(callback);//就把这个函数指针继续传递给临时对象func
        }
        b->runAction(Sequence::create(ScaleTo::create(0.25f, 1.0f,1.0f),//创建一个动作序列，并回调刚刚初始化的谓词
                                      func,
                                      NULL));
    
    };
    
    a->runAction(Sequence::create(//这里执行翻转的第一个动作，a面的scaleX从1所放至0，并调用lambda表达式创建的新谓词
                                  ScaleTo::create(0.25f, 0.0f,1.0f),
                                  CallFunc::create(flipB),
                                  NULL));
}
void Card::FlipToBack(const std::function<void()> &callback ){//初始化从正面翻转至背面的接口函数
    if(m_card_state==CardState::BACK){//如果卡片已经是背面则返回
        return;
    }
    FlipFromTo(m_front_image, m_back_image,callback);//否则执行通用翻转函数，并传入参数
    this->m_card_state=CardState::BACK;//翻转完成并设置卡片状态
    
}
void Card::FlipToFront(const std::function<void()> &callback){//初始化从背面翻转至正面的接口函数
    if(m_card_state==CardState::FRONT)//如果卡片已经是正面则返回
    {
        return;
    }
    FlipFromTo(m_back_image, m_front_image,callback);//否则执行通用翻转函数，并传入参数
    this->m_card_state=CardState::FRONT;//翻转完成并设置卡片状态
}

CardState Card::GetCardState()const {//返回卡片状态
    return m_card_state;
}
CardData* Card::GetCardData(){//返回卡片数据
    return &m_card_data;
}
void Card::SetCardData(CardData data){//设置卡片数据
    this->m_card_data=data;
}
