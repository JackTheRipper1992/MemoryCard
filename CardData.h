//
//  CardData.h
//  MemoryCard
//
//  Created by 刘颖 on 17/7/5.
//
//

#ifndef CardData_h
#define CardData_h
struct CardData{//创建一个只用于卡片存储数据的头文件CardData.h 内部包涵一个结构体
    int m_number;//纪录卡片正面数字的变量 设置卡片数字时用一个临时的number，然后将临时的number存储到成员变量
    int m_row;//纪录卡片所在的行
    int m_column;//纪录卡片所在的列
    int m_flip_count;//纪录卡片的翻转次数 用途（逻辑判断标识）：1、判断卡片是正面显示还是背面，
                                                      //2、判断卡片是否是第一次翻开，用于积分策略控制
    
};

#endif /* CardData_h */
