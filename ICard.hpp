//
//  ICard.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#ifndef ICard_hpp
#define ICard_hpp

#include <stdio.h>
#include <functional>
#include "CardState.h"
#include "CardData.h"
class ICard{//函数接口基类，该类声明纯虚函数作为接口
public:
    virtual void FlipToBack(const std::function<void()> &callback=nullptr)=0;
    virtual void FlipToFront(const std::function<void()> &callback=nullptr)=0;
    virtual CardState GetCardState() const=0;
    virtual void SetCardData(CardData data)=0;
    virtual CardData* GetCardData()=0;
};

#endif /* ICard_hpp */
