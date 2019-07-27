
// KyrsovoiView.cpp : реализация класса CKyrsovoiView
//

#include "stdafx.h"
#include "glut.h"
#include "glaux.h"
#include "math.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Kyrsovoi.h"
#endif
#include "KyrsovoiDoc.h"
#include "KyrsovoiView.h"
#include "Change.h"
#include "REATE_CYLINDR.h"
#include "Create_Cube.h"
#include "CreateIkosaedr.h"
#include "CreatePiramida3.h"
#include "CreatePiramida5.h"
#include "CreatePolytor.h"
#include "CreatePrizma3.h"
#include "CreatePrizma5.h"
#include "CreateTor.h"
#include "СDeleteObj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define cube 0
#define tor 1
#define piramida_5 2
#define ikosaedr 3
#define prizma_3 4
#define prizma_5 5
#define cilindr 6
#define piramida_3 7
#define polytor 8
#define benzopila 9
#define PI 3.141592
#define OXY 1
#define OXZ 2
#define OYZ 3
#define KAB 0
// CKyrsovoiView

IMPLEMENT_DYNCREATE(CKyrsovoiView, CView)

BEGIN_MESSAGE_MAP(CKyrsovoiView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKyrsovoiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CUBE, &CKyrsovoiView::OnCube)
	ON_COMMAND(ID_TOR, &CKyrsovoiView::OnTor)
	ON_COMMAND(ID_PIRAMIDA_5, &CKyrsovoiView::OnPiramida5)
	ON_COMMAND(ID_IKOSAEDR, &CKyrsovoiView::OnIkosaedr)
	ON_COMMAND(ID_PRIZMA_3, &CKyrsovoiView::OnPrizma3)
	ON_COMMAND(ID_PRIZMA_5, &CKyrsovoiView::OnPrizma5)
	ON_COMMAND(ID_CYLINDR, &CKyrsovoiView::OnCylindr)
	ON_COMMAND(ID_PIRAMIDA_3, &CKyrsovoiView::OnPiramida3)
	ON_COMMAND(ID_POLYTOR, &CKyrsovoiView::OnPolytor)
	ON_WM_CREATE()
	ON_WM_SIZE()
//	ON_WM_KEYDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_DESTROY()
ON_COMMAND(ID_WIRE, &CKyrsovoiView::OnWire)
ON_COMMAND(ID_UNWIRE, &CKyrsovoiView::OnUnwire)
ON_COMMAND(ID_CHANGE, &CKyrsovoiView::OnChange)
ON_COMMAND(ID_INCR, &CKyrsovoiView::OnIncr)
ON_COMMAND(ID_DECR, &CKyrsovoiView::OnDecr)

ON_COMMAND(ID_CIL_ON, &CKyrsovoiView::OnCilOn)
ON_COMMAND(ID_CIL_OFF, &CKyrsovoiView::OnCilOff)
ON_COMMAND(ID_YDAL_OFF, &CKyrsovoiView::OnYdalOff)
ON_COMMAND(ID_YDAL_ON, &CKyrsovoiView::OnYdalOn)
ON_COMMAND(ID_POINT_OFF, &CKyrsovoiView::OnPointOff)
ON_COMMAND(ID_POINT_ON, &CKyrsovoiView::OnPointOn)
ON_COMMAND(ID_FILE_NEW, &CKyrsovoiView::OnFileNew)
ON_COMMAND(ID_OXY, &CKyrsovoiView::OnOxy)
ON_COMMAND(ID_OXZ, &CKyrsovoiView::OnOxz)
ON_COMMAND(ID_OYZ, &CKyrsovoiView::OnOyz)
ON_COMMAND(ID_KABINEt, &CKyrsovoiView::OnKabinet)
ON_COMMAND(ID_UP, &CKyrsovoiView::OnUp)
ON_COMMAND(ID_DOWN, &CKyrsovoiView::OnDown)
ON_COMMAND(ID_LEFT, &CKyrsovoiView::OnLeft)
ON_COMMAND(ID_RIGHT, &CKyrsovoiView::OnRight)
ON_COMMAND(ID_CR_CIL, &CKyrsovoiView::OnCrCil)
ON_COMMAND(ID_CR_CUBE, &CKyrsovoiView::OnCrCube)
ON_COMMAND(ID_CR_IKOS, &CKyrsovoiView::OnCrIkos)
ON_COMMAND(ID_CR_PIR3, &CKyrsovoiView::OnCrPir3)
ON_COMMAND(ID_CR_PIR5, &CKyrsovoiView::OnCrPir5)
ON_COMMAND(ID_CR_POLYTOR, &CKyrsovoiView::OnCrPolytor)
ON_COMMAND(ID_CR_PRIZMA5, &CKyrsovoiView::OnCrPrizma5)
ON_COMMAND(ID_CR_TOR, &CKyrsovoiView::OnCrTor)
ON_COMMAND(ID_CR_YSPIR3, &CKyrsovoiView::OnCrYspir3)
ON_COMMAND(ID_Del, &CKyrsovoiView::OnDel)
ON_COMMAND(ID_BENZOPILA, &CKyrsovoiView::OnBenzopila)
END_MESSAGE_MAP()

// создание/уничтожение CKyrsovoiView

HDC   g_hDC  = NULL;
HGLRC g_hRC  = NULL;
int X,Y=0;
float angleX=0; 
float angleY=0;
float angleZ=0;
float scale=5;
bool flag=false; //флаг для поворота мышью
int number=0;	//порядковый номер объекта
bool wire=false;
int projection=0;
int OX, OY=0;
int OZ=1;
GLfloat Oxy[16]={1,0,0,0,
				0,1,0,0,
				0,0,0,0,
				0,0,0,1};
GLfloat Oxz[16]={1,0,0,0,
				0,0,0,0,
				0,0,1,0,
				0,0,0,1};
GLfloat Oyz[16]={0,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1};
GLfloat *set_matrix(GLfloat matrix[16])
{matrix[0]=1;
matrix[1]=0;
matrix[2]=0;
matrix[3]=0;
matrix[4]=0;
matrix[5]=1;
matrix[6]=0;
matrix[7]=0;
matrix[8]=0;
matrix[9]=0;
matrix[10]=1;
matrix[11]=0;
matrix[12]=0;
matrix[13]=0;
matrix[14]=0;
matrix[15]=0;
return matrix;
}
CKyrsovoiView::CKyrsovoiView()
{
	// TODO: добавьте код создания
	
}

CKyrsovoiView::~CKyrsovoiView()
{
}

BOOL CKyrsovoiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// рисование CKyrsovoiView

void oci()
{
	glPushMatrix();
	glRasterPos3f(0,0, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'Z');
	glRasterPos3f(0,40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'Y');
	glRasterPos3f(40,0,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'X');
	glColor3d(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,-40);
		glVertex3f(0,0,40);
	glEnd();
	glColor3d(0,0,1);
		glBegin(GL_LINES);
		glVertex3f(0,-40,0);
		glVertex3f(0,40,0);
	glEnd();
	glColor3d(1,0,0);
		glBegin(GL_LINES);
		glVertex3f(-40,0,0);
		glVertex3f(40,0,0);
	glEnd();
	
	glPopMatrix();
}

void CKyrsovoiView::display()
{
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glClearColor(1,1,1,1);
glPushMatrix();
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_BLEND); 
glEnable(GL_LIGHTING);
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
GetDocument()->dra1=GetDocument()->first;
glRotated(angleX,1,0,1);
glRotated(angleY,0,1,1);
glTranslated(OX,OY,0);
glScalef(OZ,OZ,OZ);
oci();
	switch (projection)
	{
	case 0:
		break;
	case 1: 
		glMultMatrixf(Oxy);
		break;
	case 2:
		glMultMatrixf(Oxz);
		break;
	case 3:
		glMultMatrixf(Oyz);
		break;
	}

	do{if(GetDocument()->dra1!=NULL)
			{glColor3d(GetDocument()->dra1->obj->color[0],GetDocument()->dra1->obj->color[1],GetDocument()->dra1->obj->color[2]);
			if(GetDocument()->dra1->obj->material==true)
				{
				glBlendFunc(GL_SRC_ALPHA,GL_ZERO); 
				float mat_specular[] = {1,1,1,1};
				glMaterialf ( GL_FRONT_AND_BACK ,GL_SHININESS, 60);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
				}
			else
				{
				glBlendFunc(GL_ONE,GL_ONE); 
				//glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR); 
				float mat_specular[] = {1,1,1,1};
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
				}

			//Рисуем сферу
			switch (GetDocument()->dra1->obj->object)
				{case cube:
				{
				glPushMatrix();
				glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
				glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
				glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
				glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
				glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
				if(wire==true)
					glutWireSphere(GetDocument()->dra1->obj->param[0], GetDocument()->dra1->obj->param[1], GetDocument()->dra1->obj->param[2]);
				else
					glutSolidSphere(GetDocument()->dra1->obj->param[0], GetDocument()->dra1->obj->param[1], GetDocument()->dra1->obj->param[2]);
				glPopMatrix();
				GetDocument()->dra1=GetDocument()->dra1->next;
				}
				break;
				
				case tor:
					{glPushMatrix();
					glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
					glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
					glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
					glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
					glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
					if(wire==true)
						glutWireTorus(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[1],GetDocument()->dra1->obj->param[2],GetDocument()->dra1->obj->param[3]);
					else
						glutSolidTorus(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[1],GetDocument()->dra1->obj->param[2],GetDocument()->dra1->obj->param[3]);
					glPopMatrix();
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					break;
				case piramida_5:
					{
					glPushMatrix();
					glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
					glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
					glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
					glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
					glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
					if(wire==true)
					{
					glBegin(GL_LINE_LOOP);
						glVertex3d(2,-2,0);
						glVertex3d(4,2,0);
						glVertex3d(0,5,0);
						glVertex3d(-4,2,0);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_LINES);
						glVertex3d(2,-2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4,2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,5,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-4,2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,-2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
					glEnd();
						}
					else
					{glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glEnable(GL_NORMALIZE);
					glBegin(GL_POLYGON);
						//glNormal3f(0.5,0.5,1);
						glVertex3d(2,-2,0);
						glVertex3d(4,2,0);
						glVertex3d(0,5,0);
						glVertex3d(-4,2,0);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3f(0.5,0.5,0.5);
						glVertex3d(2,-2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4,2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3f(0.5,0.6,0.5);
						glVertex3d(4,2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,5,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3f(0.5,0.8,0.5);
						glVertex3d(0,5,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-4,2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3f(0.5,0.5,0.5);
						glVertex3d(-4,2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3f(1,0.5,0.5);
						glVertex3d(-2,-2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(2,-2,0);
					glEnd();
					}
					glPopMatrix();
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					break;		
				case ikosaedr:
					{
						glPushMatrix();
						glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
						glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
						glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
						glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
						glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
						if(wire==true)
						{glPushMatrix();
						glScalef(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[0]);
						glutWireIcosahedron();
						glPopMatrix();
						}
					else
						{glPushMatrix();
						glScalef(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[0]);
						glutSolidIcosahedron();
						glPopMatrix();
						}
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					glPopMatrix();
					break;
					//Призма с 4-х угольным основанием
				case prizma_3:
					{
					glPushMatrix();
					glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
					glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
					glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
					glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
					glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
					if(wire==true)
						{
						glBegin(GL_LINE_LOOP);
							glVertex3d(2,-1,0);
							glVertex3d(-2, -1, 0);
							glVertex3d(0,3,0);
							glVertex3d(4, 3, 0);
						glEnd();
						glBegin(GL_LINE_LOOP);
						glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2, -1, GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4, 3, GetDocument()->dra1->obj->param[0]);
							/*glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,GetDocument()->dra1->obj->param[0]);*/
						glEnd();
						glBegin(GL_LINES);
						glVertex3d(2,-1,0);
						glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2, -1, 0);
						glVertex3d(-2, -1, GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,3,0);
						glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4, 3, 0);
						glVertex3d(4, 3, GetDocument()->dra1->obj->param[0]);
						/*	glVertex3d(2,-1,0);
							glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(0,3,0);
							glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,0);
							glVertex3d(-2,-1,GetDocument()->dra1->obj->param[0]);*/
						glEnd();
						}
					else
						{
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						glEnable(GL_NORMALIZE);
						glBegin(GL_POLYGON);
							//glNormal3f(0,0,-1);
						glVertex3d(2, -1, 0);
						glVertex3d(-2, -1, 0);
						glVertex3d(0, 3, 0);
						glVertex3d(4, 3, 0);
						glEnd();
						glBegin(GL_POLYGON);
							//glNormal3f(0,0,1);
						glVertex3d(2, -1, GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2, -1, GetDocument()->dra1->obj->param[0]);
						glVertex3d(0, 3, GetDocument()->dra1->obj->param[0]);
						glVertex3d(4, 3, GetDocument()->dra1->obj->param[0]);
						glEnd();
						glBegin(GL_POLYGON);
							//glNormal3f(0,-1,0);
							glVertex3d(2,-1,0);
							glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
							glVertex3d(0,3,0);	
						glEnd();
						glBegin(GL_POLYGON);
							//glNormal3f(0,-0.3,0);
							glVertex3d(0,3,0);
							glVertex3d(0,3,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,0);
						glEnd();
						glBegin(GL_POLYGON);
							//glNormal3f(0,0.3,0);
							glVertex3d(2,-1,0);
							glVertex3d(2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,GetDocument()->dra1->obj->param[0]);
							glVertex3d(-2,-1,0);
						glEnd();
						//2-я часть
						glBegin(GL_POLYGON);
						//glNormal3f(0,0.3,0);
						glVertex3d(0, 3, 0);
						glVertex3d(0, 3, GetDocument()->dra1->obj->param[0]);
						glVertex3d(4, 3, GetDocument()->dra1->obj->param[0]);
						glVertex3d(4, 3, 0);
						glEnd();
						}
					glPopMatrix();
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					break;
				case prizma_5:
					{
						glPushMatrix();
						glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
						glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
						glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
						glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
						glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
					if(wire==true)
					{glPushMatrix();
					glBegin(GL_LINE_LOOP);
						glVertex3d(2,-2,0);
						glVertex3d(4,2,0);
						glVertex3d(0,5,0);
						glVertex3d(-4,2,0);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_LINE_LOOP);
						glVertex3d(4,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(6,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(2,7,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-0,-0,GetDocument()->dra1->obj->param[0]);
					glEnd();
					glBegin(GL_LINES);
					glVertex3d(2,-2,0);
						glVertex3d(4,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4,2,0);
						glVertex3d(6,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,5,0);
						glVertex3d(2,7,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-4,2,0);
						glVertex3d(-2,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,-2,0);
						glVertex3d(-0,-0,GetDocument()->dra1->obj->param[0]);
					glEnd();
					glPopMatrix();
						}
					else
					{glPushMatrix();
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glEnable(GL_NORMALIZE);
					glBegin(GL_POLYGON);
						//glNormal3d(0,0,-1);
						glVertex3d(2,-2,0);
						glVertex3d(4,2,0);
						glVertex3d(0,5,0);
						glVertex3d(-4,2,0);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3d(0,0,1);
						glVertex3d(4,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(6,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(2,7,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3d(1,-1,-1);
						glVertex3d(2,-2,0);
						glVertex3d(4,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(6,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4,2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3d(1,-0.6,-0.6);
						glVertex3d(4,2,0);
						glVertex3d(6,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(2,7,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,5,0);
					glEnd();
					glBegin(GL_POLYGON);
					//	glNormal3d(1,-0.2,-0.2);
						glVertex3d(0,5,0);
						glVertex3d(2,7,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-4,2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3d(1,0.2,0.2);
						glVertex3d(-4,2,0);
						glVertex3d(-2,4,GetDocument()->dra1->obj->param[0]);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(-2,-2,0);
					glEnd();
					glBegin(GL_POLYGON);
						//glNormal3d(1,0.6,0.6);
						glVertex3d(-2,-2,0);
						glVertex3d(0,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(4,0,GetDocument()->dra1->obj->param[0]);
						glVertex3d(2,-2,0);
					glEnd();
					glPopMatrix();
					}
					glPopMatrix();
				GetDocument()->dra1=GetDocument()->dra1->next;
					}
					break;		
				case cilindr:
					{
						glPushMatrix();
						glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
						glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
						glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
						glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
						glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
						if(wire==true)
						{
						double vx;
						double vy;
						int c = 0;
						int b=GetDocument()->dra1->obj->param[2];
						double **vert=new double* [b+1];
						for(int i=0; i<=b;i++)
							vert[i]=new double[2];
						glPushMatrix();
						for(int i=0; i<b+1;i++)
							{float seta = i*360.0/b;
							vx=sin(seta/180*PI)*GetDocument()->dra1->obj->param[0];
							vy=cos(seta/180*PI)*GetDocument()->dra1->obj->param[0];
							vert[c][0] = vx;
							vert[c][1] = vy;
							 c += 1;
							}
						glBegin(GL_LINES);
						 for(int i = 0; i < b; i++)
						{
						 glVertex3f(vert[i][0]+2,  vert[i][1]+2, GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i][0],  vert[i][1],  -GetDocument()->dra1->obj->param[1]/2);

						 glVertex3f(vert[i][0],  vert[i][1],  -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);

						 glVertex3f(vert[i][0]+2,  vert[i][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);

						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);
						 }
						glEnd();
						glBegin(GL_LINES);
						 for(int i = 0; i < b; i++)
						{
						 glVertex3f(vert[i][0]+2,  vert[i][1]+2, GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(0+2, 0+2,  GetDocument()->dra1->obj->param[1]/2);
						 
						 glVertex3f(vert[i][0],  vert[i][1], -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);
						  glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(0, 0,  -GetDocument()->dra1->obj->param[1]/2);
						 }
						glEnd();
						glPopMatrix();
						}
					else
						{
						double vx;
						double vy;
						int c = 0;
						int b=GetDocument()->dra1->obj->param[2];
						double **vert=new double* [b+1];
						for(int i=0; i<=b;i++)
							vert[i]=new double[2];
						glPushMatrix();
						for(int i=0; i<b+1;i++)
							{float seta = i*360.0/b;
							vx=sin(seta/180*PI)*GetDocument()->dra1->obj->param[0];
							vy=cos(seta/180*PI)*GetDocument()->dra1->obj->param[0];
							vert[c][0] = vx;
							vert[c][1] = vy;
							 c += 1;
							}
						glBegin(GL_TRIANGLES);
						 for(int i = 0; i < b; i++)
						{
						//glNormal3d(-1+i/b,0,0);
						 glVertex3f(vert[i][0]+2,  vert[i][1]+2, GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i][0],  vert[i][1],  -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);

						 glVertex3f(vert[i][0]+2,  vert[i][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);
						 }
						glEnd();
						glBegin(GL_TRIANGLES);
						 for(int i = 0; i < b; i++)
						{
						//glNormal3d(1,0,0);
						 glVertex3f(vert[i][0]+2,  vert[i][1]+2, GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0]+2, vert[i+1][1]+2,  GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(0+2, 0+2,  GetDocument()->dra1->obj->param[1]/2);
						 //glNormal3d(-1,0,0);
						 glVertex3f(vert[i][0],  vert[i][1], -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(vert[i+1][0], vert[i+1][1],  -GetDocument()->dra1->obj->param[1]/2);
						 glVertex3f(0, 0,  -GetDocument()->dra1->obj->param[1]/2);
						 }
						glEnd();
						glPopMatrix();
						}
						glPopMatrix();
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					break;

					//Создаем сферу
				case polytor:
					{
						glPushMatrix();
						glTranslated(GetDocument()->dra1->obj->trans[0],GetDocument()->dra1->obj->trans[1],GetDocument()->dra1->obj->trans[2]);
						glRotatef(GetDocument()->dra1->obj->rotate[0],1,0,0);
						glRotatef(GetDocument()->dra1->obj->rotate[1],0,1,0);
						glRotatef(GetDocument()->dra1->obj->rotate[2],0,0,1);
						glScalef(GetDocument()->dra1->obj->scale[0],GetDocument()->dra1->obj->scale[1],GetDocument()->dra1->obj->scale[2]);
					if(wire==true)
						{	GLdouble eq_plane[4] = {0,0, 1, 0};
							glEnable(GL_CLIP_PLANE1);
							glClipPlane(GL_CLIP_PLANE1, eq_plane);
							glutWireSphere(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[1],GetDocument()->dra1->obj->param[2]);
							glDisable(GL_CLIP_PLANE1);
						}
					else
						{ GLdouble eq_plane[4] = {0,0, 1, 0};
							glEnable(GL_CLIP_PLANE1);
							glClipPlane(GL_CLIP_PLANE1, eq_plane);
							glutSolidSphere(GetDocument()->dra1->obj->param[0],GetDocument()->dra1->obj->param[1],GetDocument()->dra1->obj->param[2]);
							glDisable(GL_CLIP_PLANE1);

						}
					GetDocument()->dra1=GetDocument()->dra1->next;
					}
					glPopMatrix();
					break;
					//Косоугольная пирамида с 5-ти угольным основанием
				case piramida_3:
					{
								   glPushMatrix();
								   glTranslated(GetDocument()->dra1->obj->trans[0], GetDocument()->dra1->obj->trans[1], GetDocument()->dra1->obj->trans[2]);
								   glRotatef(GetDocument()->dra1->obj->rotate[0], 1, 0, 0);
								   glRotatef(GetDocument()->dra1->obj->rotate[1], 0, 1, 0);
								   glRotatef(GetDocument()->dra1->obj->rotate[2], 0, 0, 1);
								   glScalef(GetDocument()->dra1->obj->scale[0], GetDocument()->dra1->obj->scale[1], GetDocument()->dra1->obj->scale[2]);
								   if (wire == true)
								   {
									   glBegin(GL_LINE_LOOP);
									   glVertex3d(2, -2, 0);
									   glVertex3d(4, 2, 0);
									   glVertex3d(0, 5, 0);
									   glVertex3d(-4, 2, 0);
									   glVertex3d(-2, -2, 0);
									   
									   glEnd();
									   glBegin(GL_LINES);
									   glVertex3d(2, -2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(4, 2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(0, 5, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(-4, 2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(-2, -2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glEnd();
									   
								   }
								   else
								   {
									   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
									   glEnable(GL_NORMALIZE);
									   glBegin(GL_POLYGON);
									   //glNormal3f(0.5,0.5,1);
									   glVertex3d(2, -2, 0);
									   glVertex3d(4, 2, 0);
									   glVertex3d(0, 5, 0);
									   glVertex3d(-4, 2, 0);
									   glVertex3d(-2, -2, 0);
									   glEnd();
									   glBegin(GL_POLYGON);
									   //glNormal3f(0.5,0.5,0.5);
									   glVertex3d(2, -2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(4, 2, 0);
									   glEnd();
									   glBegin(GL_POLYGON);
									   //glNormal3f(0.5,0.6,0.5);
									   glVertex3d(4, 2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(0, 5, 0);
									   glEnd();
									   glBegin(GL_POLYGON);
									   //glNormal3f(0.5,0.8,0.5);
									   glVertex3d(0, 5, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(-4, 2, 0);
									   glEnd();
									   glBegin(GL_POLYGON);
									   //glNormal3f(0.5,0.5,0.5);
									   glVertex3d(-4, 2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(-2, -2, 0);
									   glEnd();
									   glBegin(GL_POLYGON);
									   //glNormal3f(1,0.5,0.5);
									   glVertex3d(-2, -2, 0);
									   glVertex3d(0, 0, GetDocument()->dra1->obj->param[0]);
									   glVertex3d(2, -2, 0);
									   glEnd();
								   }
								   glPopMatrix();
								   GetDocument()->dra1 = GetDocument()->dra1->next;
				}
					break;	
				}
			}
	}while(GetDocument()->dra1!=NULL);
	glPopMatrix();
	

	SwapBuffers( wglGetCurrentDC() );

}
void CKyrsovoiView::OnDraw(CDC* pDC)
{

CKyrsovoiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: добавьте здесь код отрисовки для собственных данных
}


// печать CKyrsovoiView


void CKyrsovoiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKyrsovoiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CKyrsovoiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CKyrsovoiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CKyrsovoiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKyrsovoiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CKyrsovoiView

#ifdef _DEBUG
void CKyrsovoiView::AssertValid() const
{
	CView::AssertValid();
}

void CKyrsovoiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKyrsovoiDoc* CKyrsovoiView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKyrsovoiDoc)));
	return (CKyrsovoiDoc*)m_pDocument;
}
#endif //_DEBUG


//Добавла
void CKyrsovoiView::OnCube()
{
			GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[3];
			ob->param[0] = 3;		
			ob->param[1] = 10;		
			ob->param[2] = 10;		//размер
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=cube;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnTor()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[4];
			ob->param[0]=1;
			ob->param[1]=12;
			ob->param[2]=8;
			ob->param[3]=50;	
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=tor;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnPiramida5()
{
			GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[1];			
			ob->param[0]=5;
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=piramida_5;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnIkosaedr()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[1];			//Радиус вписанноу окружности
			ob->param[0]=2;
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=ikosaedr;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnPrizma3()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[1];
			ob->param[0]=2;
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=prizma_3;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnPrizma5()
{
			GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[1];
			ob->param[0]=2;
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=prizma_5;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnCylindr()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[4];
			ob->param[0]=2;				//радиус
			ob->param[1]=4;				//высота
			ob->param[2]=20;			//разбиениe
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=cilindr;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnPiramida3()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[1];
			ob->param[0]=2;				//высота
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=piramida_3;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
		GetDocument()->first=GetDocument()->dra1;
}


void CKyrsovoiView::OnPolytor()
{
	GetDocument()->dra1=new dra;	
			obj *ob=new obj;
			ob->num_obj=number;
			number++;
			ob->param=new double[3];
			ob->param[0]=1;				//Радиус внутренний
			ob->param[1]=20;				//Радиус внешний
			ob->param[2]=12;			//Разбиения вдоль
	//		ob->param[3]=50;			//Разбиения поперёк
			ob->color[0]=1;
			ob->color[1]=0;
			ob->color[2]=0;
			ob->material=true;
			set_matrix(ob->matrix);
			for(int i=0; i<3;i++)
				{ob->rotate[i]=0;
				ob->trans[i]=0;
				ob->scale[i]=1;
				}
			ob->object=polytor;
			GetDocument()->dra1->obj=ob;
			GetDocument()->dra1->next=GetDocument()->first;
			GetDocument()->first=GetDocument()->dra1;
}
int SetWindowPixelFormat(HDC hDC)
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;
    pfd.dwFlags   = PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER;
    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 32;
    pfd.cRedBits       = 8;
    pfd.cRedShift      = 16;
    pfd.cGreenBits     = 8;
    pfd.cGreenShift    = 8;
    pfd.cBlueBits      = 8;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 64;
    pfd.cAccumRedBits  = 16;
    pfd.cAccumGreenBits   = 16;
    pfd.cAccumBlueBits    = 16;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 8;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;
    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
       return 0;
    }
    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
        return 0;

    return 1;
}
int CKyrsovoiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{if (CView::OnCreate(lpCreateStruct) == -1)
                return -1;
        pdc = new CClientDC(this);
        if(SetWindowPixelFormat(pdc->m_hDC)==FALSE)
        return -1;
         hGLRC = wglCreateContext(pdc->m_hDC);
    if(hGLRC == NULL)
        return -1;
    if(wglMakeCurrent(pdc->m_hDC, hGLRC)==FALSE)
        return -1;

        return 0;
}

void CKyrsovoiView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

   glViewport(0,0,cx,cy);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-40,40, -40,40, -40,40);
   glMatrixMode( GL_MODELVIEW );

}


//void CKyrsovoiView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}


void CKyrsovoiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	click=true;
	GetCursorPos(&Curs);
	PCurs=&Curs;
	Y=PCurs->x;
	X = PCurs->y;
	CView::OnLButtonDown(nFlags, point);
}


void CKyrsovoiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	click=false;
	CView::OnLButtonUp(nFlags, point);
}


void CKyrsovoiView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(click==true)
			{GetCursorPos(&Curs);
			PCurs=&Curs;
			int y = PCurs->x;
			int x = PCurs->y;
			angleX += (X-x);
			angleY += (Y-y);
			X = x; Y = y;}
	CView::OnMouseMove(nFlags, point);
}


void CKyrsovoiView::OnDestroy()
{
	if(wglGetCurrentContext()!=NULL)
   wglMakeCurrent(NULL, NULL) ;
    if(hGLRC!=NULL)
        {
      wglDeleteContext(hGLRC);
      hGLRC = NULL;
    }
        delete pdc;
	CView::OnDestroy();
	// TODO: добавьте свой код обработчика сообщений
}


void CKyrsovoiView::OnWire()
{
	wire=true;
}


void CKyrsovoiView::OnUnwire()
{
	wire=false;
}


void CKyrsovoiView::OnChange()
{

	Change change;
	change.Set_first(GetDocument()->first);
	change.DoModal();
}


void CKyrsovoiView::OnIncr()
{
	OZ++;
}


void CKyrsovoiView::OnDecr()
{
	OZ--;
}





void CKyrsovoiView::OnCilOn()
{
glPushMatrix();
glEnable(GL_LIGHT1);
GLfloat light1_color[]={0,1,0,1};
GLfloat light1_position[] = { 15.0, -20.0, 10.0, 1.0 };
GLfloat light1_dir[]={0,0,0};
glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
glLightfv(GL_LIGHT1, GL_SPECULAR, light1_color);
glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);
glPopMatrix();
}


void CKyrsovoiView::OnCilOff()
{
	glDisable(GL_LIGHT1);
}


void CKyrsovoiView::OnYdalOff()
{
	glDisable(GL_LIGHT2);
}


void CKyrsovoiView::OnYdalOn()
{
glPushMatrix();
glEnable(GL_LIGHT2);
GLfloat light1_color[]={0,1,1,1};
GLfloat light1_position[] = { 0.0, 15.0, -20.0, 1.0 };
GLfloat light1_dir[]={0,0,0};
glLightfv(GL_LIGHT2, GL_POSITION, light1_position);
glLightfv(GL_LIGHT2, GL_SPECULAR, light1_color);
glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_color);
glPopMatrix();
}


void CKyrsovoiView::OnPointOff()
{
	glDisable(GL_LIGHT3);
}


void CKyrsovoiView::OnPointOn()
{
glPushMatrix();
glEnable(GL_LIGHT3);
GLfloat light1_color[]={0,0,1,1};
GLfloat light1_position[] = { 0.0, 0.0, 20.0, 1.0 };
glLightfv(GL_LIGHT3, GL_POSITION, light1_position);
glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);
glLightfv(GL_LIGHT3, GL_SPECULAR, light1_color);
glLightfv(GL_LIGHT3, GL_DIFFUSE, light1_color);
glPopMatrix();
}


void CKyrsovoiView::OnFileNew()
{
	GetDocument()->first=NULL;
}


void CKyrsovoiView::OnOxy()
{
	projection=OXY;
}


void CKyrsovoiView::OnOxz()
{
	projection=OXZ;
}


void CKyrsovoiView::OnOyz()
{
	projection=OYZ;
}


void CKyrsovoiView::OnKabinet()
{
	projection=KAB;
}


void CKyrsovoiView::OnUp()
{
	OX++;
}


void CKyrsovoiView::OnDown()
{
	OX--;
}


void CKyrsovoiView::OnLeft()
{
	OY++;
}


void CKyrsovoiView::OnRight()
{
	OY--;
}


void CKyrsovoiView::OnCrCil()
{
	CREATE_CYLINDR CYL;
	OnCylindr();
	CYL.Set_first(GetDocument()->first);
	CYL.Get_Numb(number);
	number++;
	CYL.DoModal();
	if(CYL.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
		
}

void CKyrsovoiView::OnCrCube()
{
	CCreate_Cube Cube;
	OnCube();
	Cube.Set_first(GetDocument()->first);
	Cube.Get_Numb(number);
	number++;
	Cube.DoModal();
	if(Cube.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrIkos()
{
	CCreateIkosaedr Ikos;
	OnIkosaedr();
	Ikos.Set_first(GetDocument()->first);
	Ikos.Get_Numb(number);
	number++;
	Ikos.DoModal();
	if(Ikos.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrPir3()
{
	CCreatePrizma3 Pir3;
	OnPrizma3();
	Pir3.Set_first(GetDocument()->first);
	Pir3.Get_Numb(number);
	number++;
	Pir3.DoModal();
	if(Pir3.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrPir5()
{
	CCreatePiramida5 Pir5;
	OnPiramida5();
	Pir5.Set_first(GetDocument()->first);
	Pir5.Get_Numb(number);
	number++;
	Pir5.DoModal();
	if(Pir5.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrPolytor()
{
	CCreatePolytor Polytor;
	OnPolytor();
	Polytor.Set_first(GetDocument()->first);
	Polytor.Get_Numb(number);
	number++;
	Polytor.DoModal();
	if(Polytor.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrPrizma5()
{
	CCreatePrizma5 PR5;
	OnPrizma3();
	PR5.Set_first(GetDocument()->first);
	PR5.Get_Numb(number);
	number++;
	PR5.DoModal();
	if(PR5.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrTor()
{
	CCreateTor Tor;
	OnTor();
	Tor.Set_first(GetDocument()->first);
	Tor.Get_Numb(number);
	number++;
	Tor.DoModal();
	if(Tor.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnCrYspir3()
{
	CCreatePiramida3 Pir3;
	OnPiramida3();
	Pir3.Set_first(GetDocument()->first);
	Pir3.Get_Numb(number);
	number++;
	Pir3.DoModal();
	if(Pir3.Ex==0)
		{GetDocument()->first=GetDocument()->first->next;
		number--;}
}


void CKyrsovoiView::OnDel()
{
	dra *dra1=new dra;
	int j=0;
	СDeleteObj Del;
	Del.Set_first(GetDocument()->first);
	Del.DoModal();
	if(Del.num==0)
		GetDocument()->first=GetDocument()->first->next;
	else
		{for( dra1=GetDocument()->first; j<Del.num-1; dra1=dra1->next)
			j++;
		dra1->next=dra1->next->next;	
		}
}


void CKyrsovoiView::OnBenzopila()
{
	dra *dra1=new dra;
	OnCube();
	dra1 = GetDocument()->first;
	dra1->obj->color[0] = 0;
	dra1->obj->color[1] = 0;
	dra1->obj->color[2] = 1;
	dra1->obj->param[0] = 3;
	dra1->obj->param[1] = 10;
	dra1->obj->param[2] = 10;
	dra1->obj->trans[0] = 18;
	dra1->obj->trans[1] = 9;
	dra1->obj->trans[2] = 3;

	OnPiramida3();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=0;
	dra1->obj->color[1]=0;
	dra1->obj->color[2]=1;
	dra1->obj->param[0]=2;
	dra1->obj->rotate[0] = 0;
	dra1->obj->rotate[1] = 90;
	dra1->obj->rotate[2] = 0;
	dra1->obj->trans[0]=30;
	dra1->obj->trans[1]=18;
	dra1->obj->trans[2]=4;
	dra1->obj->scale[0] = 1;
	dra1->obj->scale[1] = 1;
	dra1->obj->scale[2] = 5;

	OnPolytor();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=0;
	dra1->obj->color[1]=1;
	dra1->obj->color[2]=0;
	dra1->obj->param[0]=1;
	dra1->obj->param[1]=20;
	dra1->obj->param[2]=12;
	dra1->obj->trans[0]=10;
	dra1->obj->trans[1]=8;
	dra1->obj->trans[2]=3;
	dra1->obj->rotate[0]=0;
	dra1->obj->rotate[1]=-90;
	dra1->obj->rotate[2]=0;
	dra1->obj->scale[0] = 3;
	dra1->obj->scale[1] = 3;
	dra1->obj->scale[2] = 3;

	OnCylindr();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=0;
	dra1->obj->color[1]=1;
	dra1->obj->color[2]=1;
	dra1->obj->param[0]=2;
	dra1->obj->param[1]=4;
	dra1->obj->param[2]=20;
	dra1->obj->trans[0]=18;
	dra1->obj->trans[1]=18;
	dra1->obj->trans[2]=2;
	dra1->obj->rotate[0] = 45;
	dra1->obj->rotate[1] = 98;
	dra1->obj->rotate[2] = 96;
	dra1->obj->scale[0] = 1;
	dra1->obj->scale[1] = 1;
	dra1->obj->scale[2] = 7;

	OnIkosaedr();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=1;
	dra1->obj->color[1]=0;
	dra1->obj->color[2]=1;
	dra1->obj->param[0]=2;
	dra1->obj->trans[0]=0;
	dra1->obj->trans[1]=17;
	dra1->obj->trans[2]=3;
	dra1->obj->rotate[0] = 0;
	dra1->obj->rotate[1] = 0;
	dra1->obj->rotate[2] = 30;

	OnPrizma5();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=1;
	dra1->obj->color[1]=1;
	dra1->obj->color[2]=0;
	dra1->obj->param[0]=2;
	dra1->obj->trans[0]=0;
	dra1->obj->trans[1]=12;
	dra1->obj->trans[2]=6;
	dra1->obj->rotate[0]=0;
	dra1->obj->rotate[1]=85;
	dra1->obj->rotate[2]=0;
	dra1->obj->scale[0] = 1;
	dra1->obj->scale[1] = 1;
	dra1->obj->scale[2] = 12;

	OnPrizma5();
	dra1 = GetDocument()->first;
	dra1->obj->color[0] = 1;
	dra1->obj->color[1] = 1;
	dra1->obj->color[2] = 0;
	dra1->obj->param[0] = 2;
	dra1->obj->trans[0] = 0;
	dra1->obj->trans[1] = 12;
	dra1->obj->trans[2] = 0;
	dra1->obj->rotate[0] = 0;
	dra1->obj->rotate[1] = 85;
	dra1->obj->rotate[2] = 0;
	dra1->obj->scale[0] = 1;
	dra1->obj->scale[1] = 1;
	dra1->obj->scale[2] = 12;

	OnTor();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=0;
	dra1->obj->color[1]=0;
	dra1->obj->color[2]=1;
	dra1->obj->param[0]=1;
	dra1->obj->param[1]=12;
	dra1->obj->param[2]=8;
	dra1->obj->param[3]=50;
	dra1->obj->trans[0]=15;
	dra1->obj->trans[1]=17;
	dra1->obj->trans[2]=2;
	dra1->obj->rotate[0]=90;
	dra1->obj->rotate[1]=0;
	dra1->obj->rotate[2]=0;

	OnPrizma3();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=1;
	dra1->obj->color[1]=0;
	dra1->obj->color[2]=0;
	dra1->obj->param[0]=2;
	dra1->obj->scale[0]=2;
	dra1->obj->scale[1]=4;
	dra1->obj->scale[2]=2;

	OnPiramida5();
	dra1=GetDocument()->first;
	dra1->obj->color[0]=0;
	dra1->obj->color[1]=1;
	dra1->obj->color[2]=0;
	dra1->obj->param[0]=5;
	dra1->obj->rotate[0]=-90;
	dra1->obj->rotate[1]=0;
	dra1->obj->rotate[2]=45;
	dra1->obj->trans[0]=22;
	dra1->obj->trans[1]=18;
	dra1->obj->trans[2]=3;
}
