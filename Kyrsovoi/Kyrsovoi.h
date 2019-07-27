
// Kyrsovoi.h : главный файл заголовка для приложения Kyrsovoi
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "glut.h"
#include "glaux.h"

// CKyrsovoiApp:
// О реализации данного класса см. Kyrsovoi.cpp
struct ex{
bool Exit_flag; //true=кнопка ок
};
struct obj
{
int object;
int num_obj;
double color[3];
double trans[3];
double rotate[3];
double scale[3];
double *param;
GLfloat matrix[16];
bool material;				//True=матовый
};

struct dra
{
	obj *obj;
	dra *next;
};


class CKyrsovoiApp : public CWinAppEx
{
public:
	CKyrsovoiApp();

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
//	afx_msg void OnChange();

};

extern CKyrsovoiApp theApp;
