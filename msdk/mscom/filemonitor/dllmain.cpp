// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "FileMonitor.h"
#include "FileMonitorSrv.h"
#include "DiskMonitor.h"
USE_DEFAULT_DLL_MAIN;
BEGIN_CLIDMAP
	CLIDMAPENTRY_BEGIN
		CLIDMAPENTRY_NOROT(CLSID_FileMonitor,CFileMonitor)
		CLIDMAPENTRY(CLSID_FileMonitorSrv,CFileMonitorSrv)
		
	CLIDMAPENTRY_END
END_CLIDMAP_AND_EXPORTFUN;