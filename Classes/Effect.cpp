#include "Effect.h"
#include "SimpleAudioEngine.h"
#include "Config.h"

Effect::Effect():sprite(NULL)
{
}

Effect::~Effect()
{
}

Effect * Effect::create()
{
	Effect *p = new Effect();
	if (p)
	{
		p->autorelease();
		return p;
	}
	else 
	{
		delete p;
		p = NULL;
		return NULL;
	}
}

void Effect::loadExplosion()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosion.plist");
	Vector<SpriteFrame*> animFrames;

	for (int i = 1; i < 35; ++i)
	{
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("explosion_%02d.png",i));
		animFrames.pushBack(frame);
	}
	Animation *animation = Animation::createWithSpriteFrames(animFrames,0.04);
	AnimationCache::getInstance()->addAnimation(animation,"Explosion");
}

void Effect::explode(Node *pSender, Point pos)
{
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("explosion_01.png");
	Sprite *explosion = Sprite::createWithSpriteFrame(frame);
	pSender->addChild(explosion);
	explosion->setPosition(pos);

	Size size = explosion->getContentSize();

	//爆炸后删除精灵
	CallFuncN *removeFunc = CallFuncN::create([&](Node *pSender) {pSender->removeFromParent(); });

	Animation *animation = AnimationCache::getInstance()->animationByName("Explosion");
	explosion->runAction(Sequence::create(Animate::create(animation),removeFunc,NULL));

	if (Config::getInstance()->isAudio) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/shipDestroyEffect.mp3", false);
	}
}

void Effect::bulletExplode(Node * pSender, Point pos)
{
	Sprite* explode = Sprite::create("hit.jpg");
	BlendFunc cb = { GL_SRC_ALPHA,GL_ONE };
	explode->setBlendFunc(cb);
	explode->setPosition(pos);
	explode->setRotation(CCRANDOM_0_1() * 360);
	explode->setScale(0.75);
	pSender->addChild(explode);

	CallFuncN* removeExplode = CallFuncN::create([&](Node* pSender) {pSender->removeFromParent(); });
	explode->runAction(ScaleBy::create(0.3, 2, 2));
	explode->runAction(Sequence::create(FadeOut::create(0.3), removeExplode, NULL));
}

Label* Effect::hpEffect(Point pos, int hpValue)
{
	Label *label = Label::create("-" + Value(hpValue).asString(), "Arial", 20);
	label->setColor(Color3B(255, 0, 0));
	label->setPosition(Point(pos.x ,pos.y + 10));

	//移动字体
	MoveBy *moveBy = MoveBy::create(0.3f,Point(0,25));
	//删除字体
	CallFunc *callFunc = CallFunc::create([=]() {label->removeFromParentAndCleanup(true); });
	//运行动作
	label->runAction(Sequence::create(moveBy, callFunc, NULL));

	return label;

}
