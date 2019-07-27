#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CCreateIkosaedr

class CCreateIkosaedr : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateIkosaedr)

public:
	CCreateIkosaedr(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCreateIkosaedr();
	void Set_first(dra* );
	void Get_Numb(int );
	dra* f;
	int Number;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_CREATE_IKOSAEDR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit TransX;
	CEdit TransY;
	CEdit TransZ;
	CSliderCtrl Red;
	CSliderCtrl Blue;
	CSliderCtrl Green;
	CEdit ScaleX;
	CEdit ScaleY;
	CEdit ScaleZ;
	CEdit RotX;
	CEdit RotY;
	CButton MAT;
	CEdit RotZ;
	CEdit Rad;
	CButton PROZR;
	afx_msg void OnBnClickedCancel();
};
