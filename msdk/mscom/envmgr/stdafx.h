// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

//////////////////////////////////////////////////////////////////////////


#include <atlbase.h>
#include <atlstr.h>

#define GroupName _T("envmgr")
#define MODULE_NAME	GroupName

#include <assert.h>
#include <mscom/mscominc.h>
#include <mslog/msdkoutput.h>
#include <mslog/stdlog.h>


//////////////////////////////////////////////////////////////////////////
struct IModuleMgr
{
	virtual HRESULT InsertModule(LPCTSTR lpszPath,CMSComLoader* pLoader = NULL) = 0;
	virtual HRESULT CreateInstance( LPCTSTR lpszModule,REFCLSID rclsid, IMSBase *prot, IMSBase *punkOuter, const IID& riid, void **ppv) = 0;
	virtual HRESULT UnloadNow(LPCTSTR lpszModule) = 0;
};

struct IClassMgr
{
	virtual HRESULT AddClsid(LPCTSTR lpszModule,LPCTSTR lpszClsid,LPCTSTR lpszProgid = NULL,LPCTSTR lpszName = NULL) = 0;
	virtual HRESULT RemoveClsid(REFCLSID clsid) = 0;
	virtual HRESULT CreateInstance(REFCLSID rclsid, IMSBase *prot, IMSBase *punkOuter, const IID& riid, void **ppv) = 0;
	virtual LPCTSTR GetModuleFileName(REFCLSID clsid) = 0;
};



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
