#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Commons.h"
#include "controller.h"

USING_NS_CC;

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    WellController *wellController = WellController::getInstance();

    log("%s width = %f , height = %f", TAG, visibleSize.width, visibleSize.height);

    char title[256];
    sprintf(title, "width:%f,height:%f", visibleSize.width, visibleSize.height);

    auto label = Label::createWithTTF(title, f_arial, 18);
    label->setPosition(visibleSize.width / 2, visibleSize.height);
    this->addChild(label);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto sprite1 = Sprite::create(s_block_blue);
    sprite1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite1->setPosition(sprite1->getContentSize().width / 2,
                         visibleSize.height - sprite1->getContentSize().height);

    auto sprite2 = Sprite::create(s_block_green);
    sprite2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite2->setPosition(sprite2->getContentSize().width / 2,
                         visibleSize.height - sprite2->getContentSize().height * 2);

    auto move_ease_in_1 = EaseIn::create(
            MoveTo::create(0.5f, Vec2(sprite1->getContentSize().width / 2,
                                      sprite1->getContentSize().height * 2)), 0.8f);
    auto move_ease_in_2 = EaseIn::create(
            MoveTo::create(0.5f,
                           Vec2(sprite2->getContentSize().width / 2,
                                sprite2->getContentSize().height)),
            0.5f);

    auto delay = DelayTime::create(2.5f);
    auto seq1 = Sequence::create(move_ease_in_1, delay, nullptr);
    auto seq2 = Sequence::create(move_ease_in_2, delay->clone(), nullptr);

    sprite1->runAction(RepeatForever::create(seq1));
    sprite2->runAction(RepeatForever::create(seq2));

    this->addChild(sprite1);
    this->addChild(sprite2);

    wellController->initStarWell(5);
    Vector<StarWell> blocks = wellController->getBlocks();
    log("%s blocks size is %i", TAG, blocks.size());
    return true;
}


void HelloWorld::menuCloseCallback(Ref *pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
