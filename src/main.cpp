#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>

using namespace geode::prelude;

void tomatoBG(CCNode* parent, const std::string& name) {
    auto bg = parent->getChildByID(name);
    if (!bg) return;	
	auto plsno = typeinfo_cast<CCSprite*>(bg);
	auto plsno2 = typeinfo_cast<CCScale9Sprite*>(bg);
	if (!plsno && !plsno2) return;

	auto audio = FMODAudioEngine::sharedEngine();
	if (audio->getActiveMusic(0).empty()) {
		audio->playMusic("mariotomato.mp3"_spr, true, 1.0f, 0);
	}

	// thank me geode for not being stupid enough to break everything. im so smart
	auto parentID = bg->getParent()->getID();
	auto parentID2 = bg->getParent()->getParent()->getID();
	if (parentID == "ModItem" || // <-- geode menu
		parentID == "CustomSongWidget" ||
		parentID == "main-node" ||
		parentID == "custom-songs-widget" ||
		parentID == "gauntlet-node" ||
		parentID == "challenge-node" ||
		parentID == "top-quest" ||
		parentID == "middle-quest" ||
		parentID == "bottom-quest" ||
		parentID2 == "CommentCell"
	) return;

    bg->setVisible(false);
    auto tomato = CCSprite::create("bg.gif"_spr);
    if (!tomato) return;

    auto win = CCDirector::sharedDirector()->getWinSize();
    tomato->setPosition({ win.width / 2, win.height / 2 });
    tomato->setScaleX(win.width / tomato->getContentSize().width);
    tomato->setScaleY(win.height / tomato->getContentSize().height);
    parent->addChild(tomato, bg->getZOrder());
}

class $modify(MTMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto audio = FMODAudioEngine::sharedEngine();
		if (audio->getActiveMusic(0) != "mariotomato.mp3"_spr) {
			audio->playMusic("mariotomato.mp3"_spr, true, 1.0f, 0);
		}

		return true;
	}
};

class $modify(MTNode, CCNode) {
    void onEnter() {
        CCNode::onEnter();

    	tomatoBG(this, "bg");
		tomatoBG(this, "background");
		tomatoBG(this, "main-menu-bg");
    }
};
