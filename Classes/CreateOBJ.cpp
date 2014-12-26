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
