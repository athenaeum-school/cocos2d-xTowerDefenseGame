#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    HudLayer *hud = new HudLayer();
    hud->init();
    scene->addChild(hud);
    layer->_hud = hud;
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	this->initPhysics();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pickup.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("hit.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("move.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TileMap.caf");
    
	CreateBackground();	//�w�i�������\�b�h��

    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }
    
    CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
    
    int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
    int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();

    
	CreatePlayer(x,y);

	this->setTouchEnabled(true);

	CreateObj().Create(this, _world, enemy, ccp(x,y) );	//�I�u�W�F�N�g�����N���X��enemy��������

	scheduleUpdate();	//update���\�b�h�����s
    
    return true;
}

void HelloWorld::update(float dt)
{
	_world->Step(dt,10,10);

	//CreateObj().update(dt);	//�I�u�W�F�N�g�̍X�V���\�b�h

	for(b2Body* subbody = _world->GetBodyList(); subbody; subbody = subbody->GetNext())
	{
		if(subbody->GetUserData() != NULL)
		{
			CCSprite* SP = (CCSprite*)subbody->GetUserData();	//P_body�Ɋi�[���ꂽuserdate(Sprite)�̎��o��

			SP->setPosition(CCPointMake(P_body->GetPosition().x * PTM_RATIO, P_body->GetPosition().y * PTM_RATIO));	//P_body�Ɋ��蓖�Ă�ꂽ�摜�̈ʒu��P_body�̈ʒu�ɐݒ�

		}
	}
}

//�w�i�ݒ胁�\�b�h
void HelloWorld::CreateBackground()
{
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("TileMap.tmx");
    _background = _tileMap->layerNamed("Background");
    _foreground = _tileMap->layerNamed("Foreground");
    
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    
    //this->addChild(_tileMap);

}


//�v���C���[�쐬
void HelloWorld::CreatePlayer(int x, int y)
{
	CCSprite* playerSprite = CCSprite::create("Player.png");	//�v���C���[�ɓ��Ă�摜�̐ݒ�
	playerSprite->setPosition(ccp(x,y));	//�����ʒu�̐ݒ�
	this->addChild(playerSprite);	//playerSprite�̐���

	//���������̏�����
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;	//���I�ɐݒ�
	bodyDef.userData = playerSprite;	//playerSprite��userDate�Ɋi�[
	bodyDef.position.Set(x/PTM_RATIO,y/PTM_RATIO);	//bodyDef�̐����ʒu��ݒ�

	P_body = _world->CreateBody(&bodyDef);	//bodyDef�̐ݒ肪������P_body�Ƃ���b2body�𐶐�

	//�`��̏�����
	b2CircleShape circleShape;	//�`����T�[�N���ɐݒ�
	circleShape.m_radius = 50/PTM_RATIO;	//�a��50�s�N�Z��

	b2FixtureDef fixDef;
	fixDef.shape = &circleShape;	//�`������
	fixDef.density = 1.0f;	//���x
	fixDef.friction = 0.5f;	//���C��
	fixDef.restitution = 1.0f;	//�����W��
	P_body->CreateFixture(&fixDef);	//P_body�Ɍ`���ݒ�

	this->setViewPointCenter(playerSprite->getPosition());

}

//����������
void HelloWorld::initPhysics()
{
	//���[���h�̕����ݒ�
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);	//�Qworld�̏d�͂�ݒ�
	_world = new b2World(gravity);	//_world��gravity�����
 
	//debugDraw�̐ݒ�
	_debugDraw = new GLESDebugDraw( PTM_RATIO );
	_world->SetDebugDraw(_debugDraw);
 
	//DebudDraw���g�p���邽��CCLayer��draw�N���X���I�[�o�[���C�h���Ă���
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
}

void HelloWorld::setViewPointCenter(CCPoint position)
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}

#pragma mark - handle touches

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCPoint touchPoint = pDirector->convertToGL(touch->getLocation());

	CreatePlayer(touchPoint.x, touchPoint.y);

    return true;
}

void HelloWorld::setPlayerPosition(CCPoint position)
{
    CCPoint tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->tileGIDAt(tileCoord);
    if (tileGid) {
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
        if (properties) {
            CCString *collision = new CCString();
            *collision = *properties->valueForKey("Collidable");
            if (collision && (collision->compare("True") == 0)) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.caf");
                return;
            }
            CCString *collectible = new CCString();
            *collectible = *properties->valueForKey("Collectable");
            if (collectible && (collectible->compare("True") == 0)) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
                _numCollected++;
                _hud->numCollectedChanged(_numCollected);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pickup.caf");
            }
        }
    }
    _player->setPosition(position);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("move.caf");
}

void HelloWorld::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

void HelloWorld::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	_world->DrawDebugData();
	kmGLPopMatrix();
}
 
//new�Ń��������m�ۂ���_world��_debugDraw��autorelease����Ȃ����߃f�X�g���N�^�ɂĉ��
HelloWorld::~HelloWorld()
{
	delete _debugDraw;
    _debugDraw = NULL;
 
    delete _world;
    _world = NULL;
}
