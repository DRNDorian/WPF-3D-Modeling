#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreate_Cube

class CCreate_Cube : public CDialogEx
{
	DECLARE_DYNAMIC(CCreate_Cube)

public:
	CCreate_Cube(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreate_Cube();
	void Set_first(dra* );
	dra Get_first();
	void Get_Numb(int);
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_CREATE_CUBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	CEdit TransX;
	CEdit TransY;
	CEdit TransZ;
	CEdit TransX;
	CSliderCtrl Red;
	CSliderCtrl Green;
	CSliderCtrl Blue;
	CEdit ScaleX;
	CEdit ScaleY;
	CEdit ScaleZ;
	CEdit RotX;
	CEdit RotY;
	CEdit RotZ;
	CEdit Edge;
	CButton MAT;
	CButton Prozr;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CEdit SPRAZ1;
	CEdit SPRAZ2;
};
