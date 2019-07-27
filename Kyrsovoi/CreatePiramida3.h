#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreatePiramida3

class CCreatePiramida3 : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePiramida3)

public:
	CCreatePiramida3(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreatePiramida3();
	void Set_first(dra* );

	void Get_Numb(int);
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_PIRAMIDA3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton MAT;
	CButton PROZR;
	CEdit HEIGHT;
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
