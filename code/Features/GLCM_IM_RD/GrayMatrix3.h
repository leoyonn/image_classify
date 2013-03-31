// GrayMatrix3.h : main header file for the GRAYMATRIX3 application
//

#if !defined(AFX_GRAYMATRIX3_H__1FB8D5EA_3AD5_4C7E_A705_879403267BA2__INCLUDED_)
#define AFX_GRAYMATRIX3_H__1FB8D5EA_3AD5_4C7E_A705_879403267BA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGrayMatrix3App:
// See GrayMatrix3.cpp for the implementation of this class
//

class CGrayMatrix3App : public CWinApp
{
public:
	CGrayMatrix3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrayMatrix3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGrayMatrix3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAYMATRIX3_H__1FB8D5EA_3AD5_4C7E_A705_879403267BA2__INCLUDED_)
