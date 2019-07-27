#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreateTor

class CCreateTor : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateTor)

public:
	CCreateTor(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreateTor();
	void Set_first(dra* );
	void Get_Numb(int );
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_CREATE_TOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton MAT;
	CButton PROZR;
	CEdit RAD_IN;
	CEdit RAD_OUT;
	CEdit RAZB_HOR;
	CEdit RAZB_VERT;
	CEdit RotX;
	CEdit RotY;
	CEdit RotZ;
	CEdit ScaleX;
	CEdit ScaleY;
	CEdit ScaleZ;
	CSliderCtrl Red;
	CSliderCtrl Green;
	CSliderCtrl Blue;
	CEdit TransX;
	CEdit TransY;
	CEdit TransZ;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
