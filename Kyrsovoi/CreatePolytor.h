#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ���������� ���� CCreatePolytor

class CCreatePolytor : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePolytor)

public:
	CCreatePolytor(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CCreatePolytor();
	void Set_first(dra* );
	void Get_Numb(int );
	dra* f;
	int Number;
	int Ex;
// ������ ����������� ����
	enum { IDD = IDD_CREATE_POLYTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

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
