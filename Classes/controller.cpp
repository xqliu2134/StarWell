//
// Created by swd1 on 18-2-3.
//

#include "controller.h"

USING_NS_CC;

StarWell::StarWell(std::string path) {
    log("%s new StarWell", TAG);
    sprite = Sprite::create(path);
}

StarWell::~StarWell() {
}

static WellController *s_WellController = nullptr;

WellController *WellController::getInstance() {
    if (s_WellController == nullptr) {
        s_WellController = new(std::nothrow) WellController();
    }
    return s_WellController;
}

StarWell blocks[MAX_WELL][MAX_WELL];

void WellController::initStarWell(int size) {
    log("%s initStarWell %i", TAG, size);
    std::string blockWells[] = {s_block_blue, s_block_green, s_block_purple, s_block_red,
                                s_block_yellow,
                                s_block_select};
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create(s_block_blue);
    float x = sprite->getContentSize().width / 2;
    for (int row = MAX_WELL; row > 0; row--) {
        for (int col = MAX_WELL; col > 0; col--) {
            int k = RandomHelper::random_int(0, 6);
            StarWell *starWell = new(std::nothrow) StarWell(blockWells[k]);
            float py = visibleSize.height - sprite->getContentSize().height * row;
            float px = x + sprite->getContentSize().width * col;
            log("%s initStarWell px = %f,py = %f", TAG, px, py);
            starWell->setPositionX(px);
            starWell->setPositionY(py);
            starWell->setRow(row);
            starWell->setCol(col);
            starWell->setMoveX(px);
            starWell->setMoveY(sprite->getContentSize().height * row);
            blocks[0][0] = *starWell;
        }
    }
}

StarWell[][] WellController::getBlocks() {
    return blocks;
}

void WellController::moveAction(StarWell &well) {
    log("%s createStarWell", TAG);
    auto action = EaseIn::create(
            MoveTo::create(DURATION, Vec2(well.getMoveX(), well.getMoveY())), SPEED);
    well.getSprite()->runAction(action);
}