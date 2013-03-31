// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BD20FFBC_BD69_4806_AD95_20F2F3F61682__INCLUDED_)
#define AFX_STDAFX_H__BD20FFBC_BD69_4806_AD95_20F2F3F61682__INCLUDED_

#if _MSC_VER > 1000
#define for if (false) ; else for // For Scope Error
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _SCB_REPLACE_MINIFRAME
#include "control_bar\sizecbar.h"
#include "control_bar\scbarg.h"
#include "control_bar\scbarcf.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD20FFBC_BD69_4806_AD95_20F2F3F61682__INCLUDED_)
