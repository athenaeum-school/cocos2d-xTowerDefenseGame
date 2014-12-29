#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "GLES-Render.h"
#include "CreateOBJ.h"
#include "HudLayer.h"

USING_NS_CC;
#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer
{

protected:
	
	void EnemySpwan();

public:

	~HelloWorld();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

	virtual void CreateBackground(); //�w�i�쐬���\�b�h
	virtual void CreatePlayer(CCPoint point);	//�v���C���[�쐬���\�b�h
	virtual void CreateEnemy(CCPoint point);	//Enemy�쐬���\�b�h
	virtual void CreateBomb(CCPoint point);		//���e�쐬���\�b�h
	virtual void draw();	//debugDraw�쐬���\�b�h�@


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
    
	b2World* _world;	//b2World�p�̃t�B�[���h�錾
	CCSize ScreenSize;

	CCSpriteBatchNode* ESpriteBatchNode;

    CCPoint tileCoordForPosition(CCPoint position);
	
	b2Body* enemyBody;
	b2Body* TurretBody;
	b2Body* wallBody;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

private:

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