#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreatePrizma5

class CCreatePrizma5 : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePrizma5)

public:
	CCreatePrizma5(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreatePrizma5();
	void Set_first(dra* );
	void Get_Numb(int);
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_PRIZMA_5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit Height;
	CButton MAT;
	CButton PROZR;
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
