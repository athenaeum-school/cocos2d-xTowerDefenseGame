#include "CreateOBJ.h"

CreateObj::~CreateObj()
{
}

void CreateObj::Create(int type,CCPoint spwanPoint)
{
	if(type == enemy)
	{		
		CCSprite* enemySprite = CCSprite::create("Player.png");	//�v���C���[�ɓ��Ă�摜�̐ݒ�
		enemySprite->setPosition(spwanPoint);	//�����ʒu�̐ݒ�

		//���������̏�����
		b2BodyDef enemyBodyDef;
		enemyBodyDef.type = b2_dynamicBody;	//���I�ɐݒ�
		enemyBodyDef.userData = enemySprite;	//playerSprite��userDate�Ɋi�[
		enemyBodyDef.position.Set(spwanPoint.x/PTM_RATIO, spwanPoint.y/PTM_RATIO);	//bodyDef�̐����ʒu��ݒ�


		//�`��̏�����
		b2CircleShape enemyShape;	//�`����T�[�N���ɐݒ�
		enemyShape.m_radius = 50/PTM_RATIO;	//�a��50�s�N�Z��

		b2FixtureDef enemyFixDef;
		enemyFixDef.shape = &enemyShape;	//�`������
		enemyFixDef.density = 1.0f;	//���x
		enemyFixDef.friction = 0.5f;	//���C��
		enemyFixDef.restitution = 1.0f;	//�����W��


	}

	else if (type == Turret)
	{

	}

	else if(type == wall)
	{

	}
}