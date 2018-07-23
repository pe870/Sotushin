#ifndef POSITION_H
#define POSITION_H

#pragma warning(disable:4005)




//LoadModelのm_vPosはここの定数を使用しているため.
//結合の際、必ず変更してビルドすること.
//Default Model Position.
const float GroundX =  0.0f;
const float GroundY = -0.5f;
const float GroundZ = -5.7f;

const float PlayerX =  0.0f;
const float PlayerY =  0.0f;
const float PlayerZ = -8.0f;

/***********①***********/
int scaffoldCntSqu = 0;
int Italy = L3;
const float scaffoldSquX = -1.7f;
const float scaffoldSquY = 0.1f;
const float scaffoldSquZ = 7.0f;

const float scaffoldSqumX = 1.7f;
const float scaffoldSqumY = 4.2f;
const float scaffoldSqumZ = 11.0f;


/***********②***********/




/***********(1)************/
int sawcontrollcnt = 0;
int Germany = MARK1;
const float	ObstacleX1 = -3.3f;
const float	ObstacleY1 = 4.3f;
const float ObstacleZ1 = 15.55f;
bool moveleft = false;



#endif