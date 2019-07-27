#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// диалоговое окно СDeleteObj

class СDeleteObj : public CDialogEx
{
	DECLARE_DYNAMIC(СDeleteObj)

public:
	СDeleteObj(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~СDeleteObj();
	void Set_first(dra*);
	int num;
	dra *f;
// Данные диалогового окна
	enum { IDD = IDD_DelObj };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox Sel_Obj;
	virtual BOOL OnInitDialog();
};
