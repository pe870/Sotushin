#ifndef POSITION_H
#define POSITION_H

#pragma warning(disable:4005)




//LoadModel��m_vPos�͂����̒萔���g�p���Ă��邽��.
//�����̍ہA�K���ύX���ăr���h���邱��.
//�㔼�̃\�[�X���ǂ̕����Ŗ������\���L.
//Default Model Position.
const float GroundX =  0.0f;
const float GroundY = -0.5f;
const float GroundZ = -5.7f;

const float PlayerX =  0.0f;
const float PlayerY =  0.0f;
const float PlayerZ = -8.0f;

//�J�E���g�n�͓��ꂵ���ق��������̂��𕷂�����.

/***********�@***********/
int scaffoldCntSqu = 0;
int Italy = L3;
const float scaffoldSquX = -1.7f;
const float scaffoldSquY = 0.1f;
const float scaffoldSquZ = 7.0f;

const float scaffoldSqumX = 1.7f;
const float scaffoldSqumY = 4.2f;
const float scaffoldSqumZ = 11.0f;


/***********�A***********/
int UpDownCnt = 0;
int France = S35;
const float upX = -1.4f;
const float upY = -0.9f;
const float upZ = 24.2f;

const float downX = 1.8;
const float downY = -4.8f;
const float downZ = 24.2f;


/***********(1)************/
int SawControllCnt = 0;
int Germany = MARK1;
const float	ObstacleX1 = -3.3f;
const float	ObstacleY1 = 4.3f;
const float ObstacleZ1 = 15.55f;



#endif