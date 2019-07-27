#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ���������� ���� CCreatePrizma3

class CCreatePrizma3 : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePrizma3)

public:
	CCreatePrizma3(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CCreatePrizma3();
	void Set_first(dra* );
	void Get_Numb(int);
	dra* f;
	int Number;
	int Ex;
// ������ ����������� ����
	enum { IDD = IDD_PRIZMA_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

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