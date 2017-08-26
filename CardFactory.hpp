//
//  CardFactory.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#ifndef CardFactory_hpp
#define CardFactory_hpp

#include <stdio.h>
#include "ICard.hpp"

class CardFactory{
public:
    virtual ICard* CreateCard(int back_id,int number);//声明一个返回值是ICard* 类型的函数
    
    
    
    
};

#endif /* CardFactory_hpp */
