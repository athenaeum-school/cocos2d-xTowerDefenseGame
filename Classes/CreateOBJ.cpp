#include "CreateOBJ.h"
#include "HelloWorldScene.h"


CreateObj::~CreateObj()
{
}

CreateObj::CreateObj()
{

}

void CreateObj::Create(HelloWorld* Game,b2World* world, int type, CCPoint spwanPoint)
{
	//Enemy�I�u�W�F�N�g�̍쐬
	if(type == enemy)
	{		
		enemySprite = CCSprite::create("Player.png");	//�v���C���[�ɓ��Ă�摜�̐ݒ�
		enemySprite->setPosition(spwanPoint);	//�����ʒu�̐ݒ�
		Game->addChild(enemySprite);

		//���������̏�����
		enemyBodyDef.type = b2_dynamicBody;	//���I�ɐݒ�
		enemyBodyDef.userData = enemySprite;	//playerSprite��userDate�Ɋi�[
		enemyBodyDef.position.Set(spwanPoint.x/PTM_RATIO, spwanPoint.y/PTM_RATIO);	//bodyDef�̐����ʒu��ݒ�
		
		Enemy_body = world->CreateBody(&enemyBodyDef);	//Enemy�𐶐�


		//�`��̏�����
		b2CircleShape enemyShape;	//�`����T�[�N���ɐݒ�
		enemyShape.m_radius = 50/PTM_RATIO;	//�a��50�s�N�Z��

		b2FixtureDef enemyFixDef;
		enemyFixDef.shape = &enemyShape;	//�`������
		enemyFixDef.density = 1.0f;	//���x
		enemyFixDef.friction = 0.5f;	//���C��
		enemyFixDef.restitution = 1.0f;	//�����W��

		Enemy_body->CreateFixture(&enemyFixDef);

		Game->setViewPointCenter(enemySprite->getPosition());	//�J�����ʒu��Enemy�̈ʒu�ɐݒ�
	}

	//�^���b�g�I�u�W�F�N�g�̍쐬
	else if (type == Turret)
	{

	}

	else if(type == wall)
	{

	}

}

//�I�u�W�F�N�g�̍X�V���\�b�h
void CreateObj::update(float dt)
{

	enemyBodyDef.userData = enemySprite;
	CCSprite* testsprite = (CCSprite*)Enemy_body->GetUserData();
	//testsprite->setPosition(ccp(100 * PTM_RATIO, 500 * PTM_RATIO));
	//setPositionX(Enemy_body->GetPosition().x * PTM_RATIO);	//�I�u�W�F�N�g��X���W���擾���X�v���C�g�ɔ��f
	//setPositionY(Enemy_body->GetPosition().y * PTM_RATIO);	//�I�u�W�F�N�g��Y���W���擾���X�v���C�g�ɔ��f
	
	
	
	//if(Enemy_body->GetUserData() != NULL)
	{
		
		//std::cout<< Enemy_body->GetUserData();
		//CCSprite* e_sp = (CCSprite*)Enemy_body->GetUserData();
		//e_sp->setPosition(ccp(Enemy_body->GetPosition().x * PTM_RATIO, Enemy_body->GetPosition().y * PTM_RATIO));
	}

}