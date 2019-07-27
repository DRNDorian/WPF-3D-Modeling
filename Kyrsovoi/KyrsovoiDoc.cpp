
// KyrsovoiDoc.cpp : реализация класса CKyrsovoiDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Kyrsovoi.h"

#endif
#include "KyrsovoiDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKyrsovoiDoc
IMPLEMENT_DYNCREATE(CKyrsovoiDoc, CDocument)

BEGIN_MESSAGE_MAP(CKyrsovoiDoc, CDocument)
END_MESSAGE_MAP()


	// создание/уничтожение CKyrsovoiDoc
CKyrsovoiDoc::CKyrsovoiDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CKyrsovoiDoc::~CKyrsovoiDoc()
{
}

BOOL CKyrsovoiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	first=NULL;
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// сериализация CKyrsovoiDoc

void CKyrsovoiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int i=0;
		for(dra *dra1=first; dra1!=NULL; dra1=dra1->next)
			i++;
		ar<<i;
		for(dra *dra1=first; dra1!=NULL; dra1=dra1->next)
		{	
		if(dra1!=NULL)
		{for(int i=0; i<16; i++)
			ar<<dra1->obj->matrix[i];
		ar<<dra1->obj->num_obj;
		ar<<dra1->obj->object;
		ar<<dra1->obj->material;
		switch (dra1->obj->object)
				{case 0:
					{ar<<dra1->obj->param[0];
					}
					break;
				case 1:
					{for(int i=0; i<4;i++)
						ar<<dra1->obj->param[i];
					}
					break;
				case 2:
					{
						ar<<dra1->obj->param[0];
					}
					break;
				case 3:
					{
						ar<<dra1->obj->param[0];
					}
					break;
				case 4:
					{
						ar<<dra1->obj->param[0];
					}
					break;
				case 5:
					{
						ar<<dra1->obj->param[0];
					}
					break;
				case 6:
					{
						for(int i=0; i<3;i++)
						ar<<dra1->obj->param[i];
					}
					break;
				case 7:
					{
						ar<<dra1->obj->param[0];
					}
					break;
				case 8:
					{
						for(int i=0; i<4;i++)
						ar<<dra1->obj->param[i];
					}
					break;
				}
		for(int i=0; i<3; i++)
		{ar<<dra1->obj->rotate[i];
		ar<<dra1->obj->scale[i];
		ar<<dra1->obj->trans[i];
		ar<<dra1->obj->color[i];
		}
		}
		}
	}
	else
	{
		first=NULL;
		int j;
		ar>>j;
		for(int i=0; i<j; i++)
			{dra1=new dra;
			obj *ob=new obj;
			for(int i=0; i<16; i++)
				ar>>ob->matrix[i];
			ar>>ob->num_obj;
			ar>>ob->object;
			ar>>ob->material;
			switch (ob->object)
				{case 0:
					{ob->param=new double[1];
					ar>>ob->param[0];
					}
					break;
				case 1:
					{
					ob->param=new double[4];
					for(int i=0; i<4;i++)
						ar>>ob->param[i];
					}
					break;
				case 2:
					{ob->param=new double[1];
						ar>>ob->param[0];
					}
					break;
				case 3:
					{ob->param=new double[1];
						ar>>ob->param[0];
					}
					break;
				case 4:
					{ob->param=new double[1];
						ar>>ob->param[0];
					}
					break;
				case 5:
					{ob->param=new double[1];
						ar>>ob->param[0];
					}
					break;
				case 6:
					{ob->param=new double[3];
						for(int i=0; i<3;i++)
						ar>>ob->param[i];
					}
					break;
				case 7:
					{ob->param=new double[1];
						ar>>ob->param[0];
					}
					break;
				case 8:
					{ob->param=new double[4];
						for(int i=0; i<4;i++)
						ar>>ob->param[i];
					}
					break;
				}
			for(int i=0; i<3; i++)
				{ar>>ob->rotate[i];
				ar>>ob->scale[i];
				ar>>ob->trans[i];
				ar>>ob->color[i];
				}
			dra1->obj=ob;
			dra1->next=first;
			first=dra1;
			}
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CKyrsovoiDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CKyrsovoiDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CKyrsovoiDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CKyrsovoiDoc

#ifdef _DEBUG
void CKyrsovoiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKyrsovoiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CKyrsovoiDoc


//BOOL CKyrsovoiDoc::OnOpenDocument(LPCTSTR lpszPathName)
//{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
//	first=NULL;
//	return TRUE;
//}


