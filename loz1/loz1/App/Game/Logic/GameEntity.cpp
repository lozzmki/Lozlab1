#include"GameEntity.h"

void InteractEntity::render(){
	m_renderable.doRender();
}

void LivingEntity::update(double deltaTime){
	d_Attribute.d_hp.update(deltaTime);
	d_Attribute.d_mp.update(deltaTime);

	//���� ��Ʒ���� ����


}
void LivingEntity::render(){
	InteractEntity::render();
}