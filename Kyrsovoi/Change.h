#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно Change

class Change : public CDialogEx
{
	DECLARE_DYNAMIC(Change)

public:
	Change(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~Change();
	dra* f;
// Данные диалогового окна
	enum { IDD = IDD_CHANGE };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
public:
	void Set_first(dra*);
	virtual BOOL OnInitDialog();
	CComboBox Sel_Obj;
//	CString Sel_obj1;

	afx_msg void OnCbnSelchangeCombo1();
	CEdit RotX;
	CEdit RotY;
	CEdit RotZ;
	CEdit ScaleX;
	CEdit ScaleY;
	CEdit ScaleZ;
	CEdit TransX;
	CEdit TransY;
	CEdit TransZ;
	CSliderCtrl Red;
	CSliderCtrl Green;
	CSliderCtrl Blue;


	afx_msg void OnBnClickedOk();
	int Material;
	CButton MAT1;
	CButton PROZR;
};
