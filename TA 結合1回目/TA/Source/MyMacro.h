#ifndef MY_MACRO_H
#define MY_MACRO_H

//================================================
//
//	ϸ�.
//
//================================================

//�װү�.
#define ERR_MSG(str,title){MessageBox(NULL,str,title,MB_OK);}
//���.
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p);   (p)=NULL; } }


#endif//#ifndef MY_MACRO_H