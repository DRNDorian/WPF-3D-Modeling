// Change.cpp: файл реализации
//

#include "stdafx.h"
#include "Kyrsovoi.h"
#include "Change.h"
#include "afxdialogex.h"

// диалоговое окно Change

IMPLEMENT_DYNAMIC(Change, CDialogEx)

Change::Change(CWnd* pParent /*=NULL*/)
	: CDialogEx(Change::IDD, pParent)
	, Material(0)
{
	

}

Change::~Change()
{
}

void Change::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Sel_Obj);
	DDX_Control(pDX, IDC_ROT_X, RotX);
	DDX_Control(pDX, IDC_ROT_Y, RotY);
	DDX_Control(pDX, IDC_ROT_Z, RotZ);
	DDX_Control(pDX, IDC_SCALE_X, ScaleX);
	DDX_Control(pDX, IDC_SCALE_Y, ScaleY);
	DDX_Control(pDX, IDC_SCALE_Z, ScaleZ);
	DDX_Control(pDX, IDC_TRANS_X, TransX);
	DDX_Control(pDX, IDC_TRANS_Y, TransY);
	DDX_Control(pDX, IDC_TRANS_Z, TransZ);
	DDX_Control(pDX, IDC_SLIDER1, Red);
	DDX_Control(pDX, IDC_SLIDER2, Green);
	DDX_Control(pDX, IDC_SLIDER3, Blue);
	DDX_Radio(pDX, IDC_MAT, Material);
	DDX_Control(pDX, IDC_MAT, MAT1);
	DDX_Control(pDX, IDC_PROZR, PROZR);
}


BEGIN_MESSAGE_MAP(Change, CDialogEx)

	ON_CBN_SELCHANGE(IDC_COMBO1, &Change::OnCbnSelchangeCombo1)

	ON_BN_CLICKED(IDOK, &Change::OnBnClickedOk)

END_MESSAGE_MAP()


// обработчики сообщений Change


void Change::Set_first(dra* first)
{
	f=first;
}


BOOL Change::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for(dra *dra1=f; dra1!=NULL; dra1=dra1->next)
		{
			switch(dra1->obj->object)
			{
			case 0:
				str="Сфера";
				break;
			case 1:
				str="Тор";
				break;
			case 2:
				str="Пирамида_5";
				break;
			case 3:
				str="Икосаедр";
				break;
			case 4:
				str="Призма_3";
				break;
			case 5:
				str="Призма_5";
				break;
			case 6:
				str="Цилиндр";
				break;
			case 7:
				str="Пирамида_3";
				break;
			case 8:
				str="Полутор";
				break;
			}
			Sel_Obj.AddString(str);
			str="";
		}
	return TRUE;
}

void Change::OnCbnSelchangeCombo1()
{
	int i=Sel_Obj.GetCurSel();
	int j=0;
	CString S;
	dra *dra1;
	for( dra1=f; j<i; dra1=dra1->next)
		j++;
	int p[3];
	p[0]=dra1->obj->trans[0];
	p[1]=dra1->obj->trans[1];
	p[2]=dra1->obj->trans[2];
	S.Format(_T("%i"), p[0]);
	TransX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	TransY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	TransZ.SetWindowTextW(S);
	p[0]=dra1->obj->rotate[0];
	p[1]=dra1->obj->rotate[1];
	p[2]=dra1->obj->rotate[2];
	S.Format(_T("%i"), p[0]);
	RotX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	RotY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	RotZ.SetWindowTextW(S);
	p[0]=dra1->obj->scale[0];
	p[1]=dra1->obj->scale[1];
	p[2]=dra1->obj->scale[2];
	S.Format(_T("%i"), p[0]);
	ScaleX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	ScaleY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	ScaleZ.SetWindowTextW(S);
	Red.SetRangeMin(0,1);
	Red.SetRangeMax(255,1);
	Green.SetRangeMin(0,1);
	Green.SetRangeMax(255,1);
	Blue.SetRangeMin(0,1);
	Blue.SetRangeMax(255,1);
	Red.SetPos(dra1->obj->color[0]*255);
	Green.SetPos(dra1->obj->color[1]*255);
	Blue.SetPos(dra1->obj->color[2]*255);
	if(dra1->obj->material==1)
		{
		MAT1.SetCheck(BST_CHECKED);
		PROZR.SetCheck(BST_UNCHECKED);
		}
	else
		{
		MAT1.SetCheck(BST_UNCHECKED);
		PROZR.SetCheck(BST_CHECKED);
		}
}

void Change::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
	int i=Sel_Obj.GetCurSel();
	int j=0;
	dra *dra1;
	for( dra1=f; j<i; dra1=dra1->next)
		j++;
	CString S;
	TransX.GetWindowTextW(S);
	dra1->obj->trans[0]=_wtoi(S);
	TransY.GetWindowTextW(S);
	dra1->obj->trans[1]=_wtoi(S);
	TransZ.GetWindowTextW(S);
	dra1->obj->trans[2]=_wtoi(S);

	RotX.GetWindowTextW(S);
	dra1->obj->rotate[0]=_wtoi(S);
	RotY.GetWindowTextW(S);
	dra1->obj->rotate[1]=_wtoi(S);
	RotZ.GetWindowTextW(S);
	dra1->obj->rotate[2]=_wtoi(S);

	ScaleX.GetWindowTextW(S);
	dra1->obj->scale[0]=_wtoi(S);
	ScaleY.GetWindowTextW(S);
	dra1->obj->scale[1]=_wtoi(S);
	ScaleZ.GetWindowTextW(S);
	dra1->obj->scale[2]=_wtoi(S);

	dra1->obj->color[0]=((double)Red.GetPos())/255;
	dra1->obj->color[1]=((double)Green.GetPos())/255;
	dra1->obj->color[2]=((double)Blue.GetPos())/255;
	if(MAT1.GetCheck()==BST_CHECKED)
		dra1->obj->material=1;
	else
		dra1->obj->material=0;
}



