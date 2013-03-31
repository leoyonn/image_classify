#if !defined(AFX_DIRTREECTRL_H__A6FFC441_2808_4303_BDFA_6DDD96AC96D5__INCLUDED_)
#define AFX_DIRTREECTRL_H__A6FFC441_2808_4303_BDFA_6DDD96AC96D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirTreeCtrl.h : header file
//
#include <Shlobj.h>
#include <direct.h>
/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl window

class CDirTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CDirTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirTreeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	HTREEITEM AddNewDirectory();
	CString GetSelectedDirectory();
//	CString GetFullPath (HTREEITEM item);
	void RefreshSubItems(HTREEITEM hParent);
	void RefreshShellRoot(LPCITEMIDLIST pidlRoot, BOOL bIncludeFiles = FALSE);
	void Initialize();
	virtual ~CDirTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDirTreeCtrl)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_currentEditItemChildren;
	CString m_SelectedDirectory;
	HTREEITEM m_desktop_root;
	BOOL m_bIncludeFiles;
	LPITEMIDLIST m_pidlRoot;
	IMalloc* m_pMalloc;
	IShellFolder* m_pDesktopFolder;

	// manage PIDLs
	static int ILGetLength(LPCITEMIDLIST pidl);
	static LPCITEMIDLIST ILGetNext(LPCITEMIDLIST pidl);
	static LPCITEMIDLIST ILGetLast(LPCITEMIDLIST pidl);
	LPITEMIDLIST ILCombine(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
	LPITEMIDLIST ILCloneFirst(LPCITEMIDLIST pidl);
	LPITEMIDLIST ILClone(LPCITEMIDLIST pidl)
	{
		return ILCombine(pidl, NULL);
	};
	void PreExpandItem(HTREEITEM hItem);	// before expanding
	void ExpandItem(HTREEITEM hItem);		// after expanded

	BOOL NeedsChildren(HTREEITEM hParent);	// true if no child items
	void DeleteChildren(HTREEITEM hParent);

	void PopulateRoot();
	BOOL WantsRefresh(HTREEITEM hItem);

	BOOL PopulateItem(HTREEITEM hParent);

//	CString GetPathFromHere (CString s, HTREEITEM itm);

	BOOL CDirTreeCtrl::FillItem(TVITEM& item, LPCITEMIDLIST pidl,
		IShellFolder* pParentFolder, LPCITEMIDLIST pidlRel);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
		LPARAM lParamSort);
	HTREEITEM m_hItemToPopulate;	// item being populated

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREECTRL_H__A6FFC441_2808_4303_BDFA_6DDD96AC96D5__INCLUDED_)
