#ifndef CCOMMON_H
#define	CCOMMON_H

#include "Global.h"

//���ʃN���X.
class clsCommon
{
public:
	clsCommon(){};
	virtual ~clsCommon(){};
	//�N���X��(){}�Ƃ���ƒ��̏�����cpp�ŏ������ɍς�.
	//�p����������̂ɂ�virtual��t����(���z�֐�).
	
	//����(��̧������)�ݒ�̐؂�ւ�.
	void SetBlend(bool bFlag);

	//�ϐ�.
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;

	ID3D11BlendState*		m_pBlendState;

};

#endif //#ifndef CCOMMON_H
