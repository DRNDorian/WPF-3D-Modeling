#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// ���������� ���� �DeleteObj

class �DeleteObj : public CDialogEx
{
	DECLARE_DYNAMIC(�DeleteObj)

public:
	�DeleteObj(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~�DeleteObj();
	void Set_first(dra*);
	int num;
	dra *f;
// ������ ����������� ����
	enum { IDD = IDD_DelObj };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox Sel_Obj;
	virtual BOOL OnInitDialog();
};
