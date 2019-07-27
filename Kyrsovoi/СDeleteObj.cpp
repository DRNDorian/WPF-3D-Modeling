// СDeleteObj.cpp: файл реализации
//

#include "stdafx.h"
#include "Kyrsovoi.h"
#include "СDeleteObj.h"
#include "afxdialogex.h"


// диалоговое окно СDeleteObj

IMPLEMENT_DYNAMIC(СDeleteObj, CDialogEx)

СDeleteObj::СDeleteObj(CWnd* pParent /*=NULL*/)
	: CDialogEx(СDeleteObj::IDD, pParent)
{

}

СDeleteObj::~СDeleteObj()
{
}

void СDeleteObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Sel_Obj, Sel_Obj);
}


BEGIN_MESSAGE_MAP(СDeleteObj, CDialogEx)
	ON_BN_CLICKED(IDOK, &СDeleteObj::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений СDeleteObj

void СDeleteObj::OnBnClickedOk()
{
	num=Sel_Obj.GetCurSel();
	CDialogEx::OnOK();
}

void СDeleteObj::Set_first(dra* first)
{
	f=first;
}

BOOL СDeleteObj::OnInitDialog()
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


