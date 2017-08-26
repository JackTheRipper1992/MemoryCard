//
//  CardFactory.cpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#include "CardFactory.hpp"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Card.hpp"
USING_NS_CC;
ICard* CardFactory::CreateCard(int back_id, int number){
    const int card_size=60;//设置卡片大小常量 用于截取卡片资源
    //创建背景
    if(back_id<0||back_id>7){//一共8种卡片背面颜色可选，如果输入的数字不再0～7范围内 则默认使用0方案配色
        back_id=0;
    }
    int x=(back_id%2)*card_size;//通过输入的back_id进行颜色截取
    int y=(back_id/2)*card_size;
    //通过以上计算的值将卡片背景色选出
    auto back_image=Sprite::create("card_back.png",Rect(x,y,card_size,card_size));
    //设置卡片的正面背景色和字体样式
    auto front_image=Node::create();
    front_image->setContentSize(Size(card_size,card_size));
    front_image->addChild(Sprite::create("card_front.png"));
    auto number_text=ui::TextAtlas::create(StringUtils::format("%d",number), "card_number.png", 140, 140, "0");
    front_image->addChild(number_text);
    
    
    //创建卡片的数据对象
    CardData data={};//初始化临时变量卡片数据为空
    data.m_number=number;//设置卡片的数字
    
    //创建卡片 设置属性 并返回
    auto card=Card::create();
    card->SetCardData(data);
    card->setBackImage(back_image);
    card->setFrontImage(front_image);
    card->setContentSize(back_image->getContentSize());
    return card;
}
