#//
//  Card.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ICard.hpp"

USING_NS_CC;

class Card:public ICard,public Node{//继承基类并实现虚函数
    Card();
    virtual ~Card();
protected:
    CardState m_card_state;//声明卡片状态对象 此对象只能用该类型的成员进行赋值
    CardData m_card_data;//声明卡片数据对象
    CC_PROPERTY(Node*, m_back_image, BackImage);
    CC_PROPERTY(Node*, m_front_image, FrontImage);
    void FlipFromTo(Node* a,Node* b,const std::function<void()> &callback=nullptr);//声明翻转函数的通用函数
public:
    CREATE_FUNC(Card);
    virtual void FlipToBack(const std::function<void()> &callback=nullptr);//继承基类方法并在cpp文件实现它
    virtual void FlipToFront(const std::function<void()> &callback=nullptr);//继承基类方法并在cpp文件实现它
    virtual CardState GetCardState() const;//继承基类方法并在cpp文件实现它
    virtual void SetCardData(CardData data);//继承基类方法并在cpp文件实现它
    virtual CardData* GetCardData();//继承基类方法并在cpp文件实现它
    
    
    
};
#endif /* Card_hpp */
