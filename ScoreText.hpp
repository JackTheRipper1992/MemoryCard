//
//  ScoreText.hpp
//  MemoryCard
//
//  Created by 刘颖 on 17/7/11.
//
//

#ifndef ScoreText_hpp
#define ScoreText_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGui.h"
USING_NS_CC;

class ScoreText:public Node{
protected:
    ui::TextAtlas* m_text;
    int m_score;
public:
    ScoreText();
    virtual ~ScoreText();
    CREATE_FUNC(ScoreText);
    virtual bool init();
    virtual void UpdateView(int value);
};
#endif /* ScoreText_hpp */
