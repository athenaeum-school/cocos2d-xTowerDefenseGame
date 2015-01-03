#include "ContactListener.h"
#include "Option.h"

ContactListener::ContactListener(CCObject* target, SEL_CallFunc selector)
{
	Mtarget = target;
	Mselector = selector;
}

void ContactListener::BeginContact(b2Contact* contact)
{


	//�ڐG�����I�u�W�F�N�g��userdata���擾
	CCSprite* SpriteA = (CCSprite*)contact->GetFixtureA()->GetUserData();
	CCSprite* SpriteB = (CCSprite*)contact->GetFixtureB()->GetUserData();

	//�ڐG�����I�u�W�F�N�g��body���擾
	b2Body* BodyA = contact->GetFixtureA()->GetBody();
	b2Body* BodyB = contact->GetFixtureB()->GetBody();


	//A���̔�\������
	//SpriteA->setVisible(false);
	//SpriteA->removeFromParentAndCleanup(true);

	
	//B���̔�\������
	//SpriteB->setVisible(false);
	//SpriteB->removeFromParentAndCleanup(true);
}