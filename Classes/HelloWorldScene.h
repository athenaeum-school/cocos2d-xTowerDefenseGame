#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "GLES-Render.h"
#include "CreateOBJ.h"
#include "ContactListener.h"
#include "HudLayer.h"
#include "picojson.h"

USING_NS_CC;

#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer, public b2ContactListener
{

protected:
	

public:
	
	HelloWorld();
	~HelloWorld();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

	virtual void CreateBackground(); //�w�i�쐬���\�b�h
	virtual void CreatePlayer(CCPoint point);	//�v���C���[�쐬���\�b�h
	virtual void CreateEnemy(float dt);	//Enemy�쐬���\�b�h
	virtual void CreateBomb(CCPoint point);		//���e�쐬���\�b�h
	virtual void draw();	//debugDraw�쐬���\�b�h�@
	virtual void ElapsedTime(float dt);	//�o�ߎ��ԕ\�����\�b�h
	virtual void AddScore(int point);	//�X�R�A���Z���\�b�h

	virtual void severMessageLabel();

	virtual void RemoveOBJ(b2Body* body);

	void initPhysics(); //�������Z������

	void update(float dt); //update���\�b�h

    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void setViewPointCenter(CCPoint position);
    
    void registerWithTouchDispatcher();
    
    void setPlayerPosition(CCPoint position);
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    
    void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void DestroyObject(CCNode* Dobject, void* body);
    
	b2World* _world;	//b2World�p�̃t�B�[���h�錾
	CCSize ScreenSize;
	b2ContactListener* _contactListener;

	CCSpriteBatchNode* ESpriteBatchNode;

    CCPoint tileCoordForPosition(CCPoint position);
	b2Vec2 gravity;
	b2Body* enemyBody;
	b2Body* TurretBody;
	b2Body* wallBody;
	CCLabelTTF* ScoreLabel;
	CCLabelTTF* TimeLabel;
	CCLabelTTF* touchPosX;
	CCLabelTTF* touchPosY;
	int score;
	int time;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

private:

	void TouchPosLabel();
	void TouchPosLabelRenewal(CCPoint point);

	CCPoint spawnpoint;
	CCSpriteBatchNode* batchNode;
	b2Body* P_body;		//�v���C���[�̕����{�f�B

	GLESDebugDraw* _debugDraw;	//�����͈͂̉����p
	
    CCTMXTiledMap *_tileMap;	//TMX�f�[�^�i�[�t�B�[���h
    
    CCTMXLayer *_background;	//�w�i���C���[
    
    CCSprite *_player;	//�v���C���[�̃X�v���C�g
    
    CCTMXLayer *_meta;	//meta�f�[�^�̃��C���[
    
    CCTMXLayer *_foreground;	//foreground���C���[
    
    HudLayer *_hud;		//HUD���C���[
    
    int _numCollected;
	int count;
    

};

#endif // __HELLOWORLD_SCENE_H__