
// KyrsovoiView.h : интерфейс класса CKyrsovoiView
//

#pragma once


class CKyrsovoiView : public CView
{
protected: // создать только из сериализации
	CKyrsovoiView();
	DECLARE_DYNCREATE(CKyrsovoiView)
	private:
CClientDC *pdc;
HGLRC hGLRC;
POINT Curs;
LPPOINT PCurs;
// Атрибуты
public:
	CKyrsovoiDoc* GetDocument() const;
	HGLRC m_hglrc;
	void display();
// Операции
public:
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CKyrsovoiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCube();
	afx_msg void OnTor();
	afx_msg void OnPiramida5();
	afx_msg void OnIkosaedr();
	afx_msg void OnPrizma3();
	afx_msg void OnPrizma5();
	afx_msg void OnCylindr();
	afx_msg void OnPiramida3();
	afx_msg void OnPolytor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool click;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnWire();
	afx_msg void OnUnwire();
	afx_msg void OnChange();
	afx_msg void OnIncr();
	afx_msg void OnDecr();

	afx_msg void OnCilOn();
	afx_msg void OnCilOff();
	afx_msg void OnYdalOff();
	afx_msg void OnYdalOn();
	afx_msg void OnPointOff();
	afx_msg void OnPointOn();
	afx_msg void OnFileNew();
	afx_msg void OnOxy();
	afx_msg void OnOxz();
	afx_msg void OnOyz();
	afx_msg void OnKabinet();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnCrCil();
	afx_msg void OnCrCube();
	afx_msg void OnCrIkos();
	afx_msg void OnCrPir3();
	afx_msg void OnCrPir5();
	afx_msg void OnCrPolytor();
	afx_msg void OnCrPrizma5();
	afx_msg void OnCrTor();
	afx_msg void OnCrYspir3();
	afx_msg void OnDel();
	afx_msg void OnBenzopila();
};

#ifndef _DEBUG  // отладочная версия в KyrsovoiView.cpp
inline CKyrsovoiDoc* CKyrsovoiView::GetDocument() const
   { return reinterpret_cast<CKyrsovoiDoc*>(m_pDocument); }
#endif

