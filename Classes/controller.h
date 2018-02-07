//
// Created by swd1 on 18-2-3.
//
#include "cocos2d.h"
#include "Commons.h"
#include "Utils.h"
#include<stdio.h>
#include<stdlib.h>

USING_NS_CC;

class StarWell {
public:
    StarWell(std::string path);

    ~StarWell();

    void setCol(int x) {
        col = x;
    }

    int getCol() {
        return col;
    }

    void setRow(int y) {
        row = y;
    }

    int getRow() {
        return row;
    }

    void setPositionX(float x) {
        positionX = x;
    }

    float getPositionX() {
        return positionX;
    }

    void setPositionY(float y) {
        positionY = y;
    }

    float getPositionY() {
        return positionY;
    }

    float getMoveX() {
        return moveX;
    }

    void setMoveX(float x) {
        moveX = x;
    }

    float getMoveY() {
        return moveY;
    }

    void setMoveY(float y) {
        moveY = y;
    }

    Sprite *getSprite() {
        return sprite;
    }

protected:
    int col;
    int row;
    float positionX;
    float positionY;
    float moveX;
    float moveY;
    Sprite *sprite;
};

class WellController {
public:
    static WellController *getInstance();

    void initStarWell(int size);

    void moveAction(StarWell &well);

    StarWell[][] getBlocks();
};