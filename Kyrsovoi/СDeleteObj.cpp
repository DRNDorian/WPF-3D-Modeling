// �DeleteObj.cpp: ���� ����������
//

#include "stdafx.h"
#include "Kyrsovoi.h"
#include "�DeleteObj.h"
#include "afxdialogex.h"


// ���������� ���� �DeleteObj

IMPLEMENT_DYNAMIC(�DeleteObj, CDialogEx)

�DeleteObj::�DeleteObj(CWnd* pParent /*=NULL*/)
	: CDialogEx(�DeleteObj::IDD, pParent)
{

}

�DeleteObj::~�DeleteObj()
{
}

void �DeleteObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Sel_Obj, Sel_Obj);
}


BEGIN_MESSAGE_MAP(�DeleteObj, CDialogEx)
	ON_BN_CLICKED(IDOK, &�DeleteObj::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� �DeleteObj

void �DeleteObj::OnBnClickedOk()
{
	num=Sel_Obj.GetCurSel();
	CDialogEx::OnOK();
}

void �DeleteObj::Set_first(dra* first)
{
	f=first;
}

BOOL �DeleteObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for(dra *dra1=f; dra1!=NULL; dra1=dra1->next)
		{
			switch(dra1->obj->object)
			{
			case 0:
				str="�����";
				break;
			case 1:
				str="���";
				break;
			case 2:
				str="��������_5";
				break;
			case 3:
				str="��������";
				break;
			case 4:
				str="������_3";
				break;
			case 5:
				str="������_5";
				break;
			case 6:
				str="�������";
				break;
			case 7:
				str="��������_3";
				break;
			case 8:
				str="�������";
				break;
			}
			Sel_Obj.AddString(str);
			str="";
		}
	return TRUE;
}


