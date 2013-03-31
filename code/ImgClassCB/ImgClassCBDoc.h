// ImgClassCBDoc.h : interface of the CImgClassCBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUMBVIEWERDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_)
#define AFX_ImgClassCBDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ximage.h"

#include <vector>

using namespace std;

class CImgClassCBDoc : public CDocument
{
protected: // create from serialization only
	CImgClassCBDoc();
	DECLARE_DYNCREATE(CImgClassCBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgClassCBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowTrainImgs(int iClass, int iNum, LPCTSTR pstr);
	void ShowTestImgs(int iCls, bool bCorrect[], int iImgs_per_Cls[], int iNum, LPCTSTR pstr);
	int GetTypeFromFileName(LPCTSTR pstr);
	void SelectItem(int nIndex);
	CString m_strCurrentDirectory;
	vector<CString> m_vFileName;
	vector<CString> m_vImgNameTrain;
	vector<CString> m_vImgNameTest;
	void SelectDirectory(LPCTSTR pstr);
	CxImage* m_pSelectedImage;
	virtual ~CImgClassCBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_nSelectedItem;  // For avoiding load selected image twice
	void QuickSortString(vector<CString>& vString, int left, int right, CString& temp);
	//{{AFX_MSG(CImgClassCBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ImgClassCBDOC_H__CAA6AF66_0E6F_4D09_AE94_02CCD11C261F__INCLUDED_)
