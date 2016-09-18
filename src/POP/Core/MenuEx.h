//  MenuEx.h: interface for the CMenuEx class.
//  CMenuEx
//  ԭ���ߣ�lbird(֣��)
//  �޸�:(querw)������
//  �����ӿ�:
//  void LoadMenu();
//	BOOL ModifyMenuEx()	
//	BOOL AppendMenuEx()
//	BOOL RemoveMenuEx()
//	void LoadToolBar()
//  ԭ�ӿ�:
//	void SetHighLightColor(COLORREF crColor)
//	void SetBackColor(COLORREF)
//	void SetTextColor(COLORREF)
//	void SetImageLeft(UINT idBmpLeft)
//									
//						2004.7.23
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_)
#define AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_
#include "afxtempl.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>


class CHicons
{
public:
	std::map<UINT, HICON> m_mapIcons;	// COMMAND_ID->HICON

public:
	bool AddIcon(UINT nCommandID, HICON hIcon)
	{
		if (hIcon == NULL) return false;
		m_mapIcons[nCommandID] = hIcon;
		return true;
	}

	HICON GetIconByCommandId(UINT nCommandId)
	{
		std::map<UINT, HICON>::iterator pIter = m_mapIcons.find(nCommandId);
		if (pIter == m_mapIcons.end())
			return NULL;
		return pIter->second;
	}
};

typedef struct tagMENUITEM
{
	CString		strText;				//�˵��ı�
	UINT		uID;					//�˵�ID
	int			uIndex;					//�˵�ͼ��ı��
	int 		uPositionImageLeft;		//�˵����λͼ��λ��
	int			nSubMenuIndex;			//�����Ӳ˵�,��ʾ�������е�λ��
	tagMENUITEM()
	{
		strText = ""; 
		uID = 0; 
		uIndex = -1; 
		uPositionImageLeft = -1; 
		nSubMenuIndex = -1;
		pImageList = NULL;
		pLeftBitmap = NULL;
	};
	CImageList *pImageList;
	CBitmap *pLeftBitmap;
	CHicons * hIcons;
}MENUITEM,*LPMENUITEM;

///////////////////////////////////////////
class CMenuEx : public CMenu  
{
	DECLARE_DYNAMIC( CMenuEx )	
public:
	//����˵�,������������Ժ�,�˵��������Ի����
	BOOL LoadMenu(UINT uMenu);		
	
	//�޸�,����,ɾ���˵���,�Զ�ָ��Ϊ�Ի����
	BOOL ModifyMenuEx(UINT nPosition, UINT nFlags, UINT nIDNewItem = 0, LPCTSTR lpszNewItem = NULL );	
	BOOL AppendMenuEx(UINT nFlags, UINT nIDNewItem = 0, LPCTSTR lpszNewItem = NULL );
	BOOL RemoveMenuEx(UINT nPosition, UINT nFlags);
	
	//���빤����,����ָ��һ��λͼ�������������Դ��16ɫλͼ
	void LoadToolBar(UINT uToolBar,UINT uFace = 0);
	//void SetIconSize(CSize );
	bool AddIcon(UINT nCommandID, UINT nIconResource);
	BOOL GetMenuItem( UINT nID , MENUITEM * item );
	WCHAR m_szCheck[2];
	
	//������������
	void SetHighLightTextColor(COLORREF crColor);
	void SetBackColor(COLORREF);
	void SetTextColor(COLORREF);
	void SetHightLightRectColor( COLORREF clrRect , COLORREF clrBorder );
	void SetLeftColor( COLORREF );
	void SetImageLeft(UINT idBmpLeft,BOOL bIsPopupMenu = FALSE);
	
	virtual void MeasureItem(LPMEASUREITEMSTRUCT  lpMIS);	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	
	CMenuEx();
	virtual ~CMenuEx();

protected:
	int m_nSeparator;				//�ָ����ĸ߶�
	
	CSize m_szImageLeft;			//�˵����Ϊ��ĸ߶ȺͿ���
	CBitmap m_bmpImageLeft;			//�˵���ߵ�λͼ
	int m_nWidthLeftImage;			//�˵����λͼ�Ŀ���
	BOOL m_bHasImageLeft;			//�Ƿ��в��λͼ
	COLORREF m_clrSelectBorder;		//ѡ�п����ɫ
	COLORREF m_clrSelectRect;		//ѡ�п򱳾�ɫ
	COLORREF m_clrMenu;				//�˵�����ɫ
	COLORREF m_clrTextSelected;		//�˵���ѡ��ʱ�ı�����ɫ
	COLORREF m_clrLeft;				//�˵���ߵ���ɫ
	CImageList m_ImageList;			//�˵���λͼ�б�
	COLORREF m_clrText;				//�˵���û��ѡ��ʱ�ı�����ɫ
	CSize m_szImage;				//�˵���λͼ�Ĵ�С
	
	void	CalculateLeftImagePos(CMenu *pPopupMenu); //���¼������λͼ��λ��(��ײ��Ĳ˵����λͼ����� 0 )
	void	ChangeMenuStyle(CMenu* pMenu,HMENU hNewMenu);
	int		GetImageFromToolBar(UINT uToolBar,CToolBar *pToolBar,COLORREF	crMask=RGB(192,192,192),UINT uBitmap = 0);
	void	DrawImageLeft(CDC *pDC,CRect &rect,LPMENUITEM lpItem);
	void	TextMenu(CDC *pDC,CRect rect,CRect rcText,BOOL bSelected,BOOL bGrayed,LPMENUITEM lpItem);
	void	DrawMenuItemImage(CDC *pDC,CRect &rect,BOOL bSelected,BOOL bChecked,BOOL bGrayed,BOOL bHasImage,LPMENUITEM lpItem);
	void	GrayString(CDC *pDC,const CString &str,const CRect rect);

	CArray<CMenuEx *,CMenuEx *> m_SubMenuArr;
	CArray<MENUITEM *,MENUITEM *>m_MenuItemArr;
	CHicons m_hicons;
};

#endif // !defined(AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_)