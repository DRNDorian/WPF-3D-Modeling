#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreatePiramida5

class CCreatePiramida5 : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePiramida5)

public:
	CCreatePiramida5(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreatePiramida5();
	void Set_first(dra* );
	dra Get_first();
	void Get_Numb(int);
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_CREATE_PIRAMIDA_5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton MAT;
	CEdit HEIGHT;
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
};
