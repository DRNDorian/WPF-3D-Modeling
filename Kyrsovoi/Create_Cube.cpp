// Create_Cube.cpp: файл реализации
//

#include "stdafx.h"
#include "Kyrsovoi.h"
#include "Create_Cube.h"
#include "afxdialogex.h"


// диалоговое окно CCreate_Cube

IMPLEMENT_DYNAMIC(CCreate_Cube, CDialogEx)

CCreate_Cube::CCreate_Cube(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreate_Cube::IDD, pParent)
{

}

CCreate_Cube::~CCreate_Cube()
{
}

void CCreate_Cube::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TRANS_Z, TransX);
	DDX_Control(pDX, IDC_TRANS_Y, TransY);
	DDX_Control(pDX, IDC_TRANS_Z, TransZ);
	DDX_Control(pDX, IDC_TRANS_X, TransX);
	DDX_Control(pDX, IDC_SLIDER1, Red);
	DDX_Control(pDX, IDC_SLIDER2, Green);
	DDX_Control(pDX, IDC_SLIDER3, Blue);
	DDX_Control(pDX, IDC_SCALE_X, ScaleX);
	DDX_Control(pDX, IDC_SCALE_Y, ScaleY);
	DDX_Control(pDX, IDC_SCALE_Z, ScaleZ);
	DDX_Control(pDX, IDC_ROT_X, RotX);
	DDX_Control(pDX, IDC_ROT_Y, RotY);
	DDX_Control(pDX, IDC_ROT_Z, RotZ);
	DDX_Control(pDX, IDC_EDGE_CUBE, Edge);
	DDX_Control(pDX, IDC_MAT, MAT);
	DDX_Control(pDX, IDC_PROZR, Prozr);
	DDX_Control(pDX, IDC_SP_RAZ01, SPRAZ1);
	DDX_Control(pDX, IDC_SP_RAZ2, SPRAZ2);
}


BEGIN_MESSAGE_MAP(CCreate_Cube, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCreate_Cube::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCreate_Cube::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений CCreate_Cube
void CCreate_Cube::Set_first(dra* first)
{
	f=first;
}

dra CCreate_Cube::Get_first()
{
	return *f;
}

void CCreate_Cube::Get_Numb(int N)
{
	Number=N;
}

void CCreate_Cube::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
	CString S;
			f->obj->num_obj=Number;
			f->obj->param=new double[4];

			Edge.GetWindowTextW(S);
			f->obj->param[0]=_wtoi(S);				//длина ребра
			SPRAZ1.GetWindowTextW(S);
			f->obj->param[1] = _wtoi(S);
			SPRAZ2.GetWindowTextW(S);
			f->obj->param[2] = _wtoi(S);
			S="";
			f->obj->color[0]=((double)Red.GetPos())/255;
			f->obj->color[1]=((double)Green.GetPos())/255;
			f->obj->color[2]=((double)Blue.GetPos())/255;

			if(MAT.GetCheck()==BST_CHECKED)
				f->obj->material=1;
			else
				f->obj->material=0;

			f->obj->matrix[0]=1;
			f->obj->matrix[1]=0;
			f->obj->matrix[2]=0;
			f->obj->matrix[3]=0;
			f->obj->matrix[4]=0;
			f->obj->matrix[5]=1;
			f->obj->matrix[6]=0;
			f->obj->matrix[7]=0;
			f->obj->matrix[8]=0;
			f->obj->matrix[9]=0;
			f->obj->matrix[10]=1;
			f->obj->matrix[11]=0;
			f->obj->matrix[12]=0;
			f->obj->matrix[13]=0;
			f->obj->matrix[14]=0;
			f->obj->matrix[15]=1;

			RotX.GetWindowTextW(S);
			f->obj->rotate[0]=_wtoi(S);
			S="";
			TransX.GetWindowTextW(S);
			f->obj->trans[0]=_wtoi(S);
			S="";
			ScaleX.GetWindowTextW(S);
			f->obj->scale[0]=_wtoi(S);
			S="";

			RotY.GetWindowTextW(S);
			f->obj->rotate[1]=_wtoi(S);
			S="";
			TransY.GetWindowTextW(S);
			f->obj->trans[1]=_wtoi(S);
			S="";
			ScaleY.GetWindowTextW(S);
			f->obj->scale[1]=_wtoi(S);
			S="";

			RotZ.GetWindowTextW(S);
			f->obj->rotate[2]=_wtoi(S);
			S="";
			TransZ.GetWindowTextW(S);
			f->obj->trans[2]=_wtoi(S);
			S="";
			ScaleZ.GetWindowTextW(S);
			f->obj->scale[2]=_wtoi(S);
			S="";

			f->obj->object=0;
			Ex=1;

}


BOOL CCreate_Cube::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString S;
	int p[3];
	p[0]=0;
	p[1]=0;
	p[2]=0;
	S.Format(_T("%i"), p[0]);
	TransX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	TransY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	TransZ.SetWindowTextW(S);
	p[0]=0;
	p[1]=0;
	p[2]=0;
	S.Format(_T("%i"), p[0]);
	RotX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	RotY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	RotZ.SetWindowTextW(S);
	p[0]=1;
	p[1]=1;
	p[2]=1;
	S.Format(_T("%i"), p[0]);
	ScaleX.SetWindowTextW(S);
	S.Format(_T("%i"), p[1]);
	ScaleY.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	ScaleZ.SetWindowTextW(S);
	p[0]=5;
	p[1]=2;
	p[2]=10;
	S.Format(_T("%i"), p[0]);
	Edge.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	SPRAZ1.SetWindowTextW(S);
	S.Format(_T("%i"), p[2]);
	SPRAZ2.SetWindowTextW(S);
	Red.SetRangeMin(0,1);
	Red.SetRangeMax(255,1);
	Green.SetRangeMin(0,1);
	Green.SetRangeMax(255,1);
	Blue.SetRangeMin(0,1);
	Blue.SetRangeMax(255,1);
	Red.SetPos(1*255);
	Green.SetPos(0);
	Blue.SetPos(1);
	MAT.SetCheck(BST_CHECKED);
	Prozr.SetCheck(BST_UNCHECKED);
	return true;
}


void CCreate_Cube::OnBnClickedCancel()
{
	Ex=0;
	CDialogEx::OnCancel();

}
