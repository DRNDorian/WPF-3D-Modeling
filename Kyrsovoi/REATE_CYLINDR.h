#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CREATE_CYLINDR

class CREATE_CYLINDR : public CDialogEx
{
	DECLARE_DYNAMIC(CREATE_CYLINDR)

public:
	CREATE_CYLINDR(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CREATE_CYLINDR();
	void Set_first(dra*);
	dra Get_first();
	void Get_Numb(int);
	dra* f;
	int Ex;
// Данные диалогового окна
	enum { IDD = IDD_CREATE_CILINDR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit TransX;
	CEdit TransY;
	CEdit TransZ;
	CEdit RotX;
	CEdit RotY;
	CEdit RotZ;
	CEdit ScaleX;
	CEdit ScaleY;
	CEdit ScaleZ;
	CEdit Height;
	CEdit Radius;
	CEdit Razb;
	CButton Mat;
	CSliderCtrl Red;
	CSliderCtrl Green;
	CSliderCtrl Blue;
	CButton Prozr;
	afx_msg void OnBnClickedCancel();
};
