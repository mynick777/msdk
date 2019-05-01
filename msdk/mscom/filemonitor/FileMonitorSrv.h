#pragma once

#include <filemonitor/IFileMonitor.h>
#include <mscomhelper/connectionpointhelper.h>
#include "mscomhelper/UseConnectionPoint.h"
//���������̷�
class CFileMonitorSrv
	:public IMsPlugin
	,public IMsPluginRun
	,public IOnFileMonitor
	,public IDiskChangeConnectPoint
	,public CConnectionPointContainerHelper<CFileMonitorSrv> //ʵ�����ӵ�
	,private CUnknownImp
{
public:
	CFileMonitorSrv(void);
	~CFileMonitorSrv(void);
	UNKNOWN_IMP5_(IMsPlugin,IMsPluginRun,IOnFileMonitor,IMsConnectionPointContainer,IDiskChangeConnectPoint);
	HRESULT init_class(IMSBase* pRot, IMSBase* pOuter)
	{
		RASSERT(pRot,E_INVALIDARG);
		m_pRot = pRot;
		return S_OK;
	}

	STDMETHOD(Init)(void*);
	STDMETHOD(Uninit)();
	STDMETHOD(Start)();
	STDMETHOD(Stop)();

	STDMETHOD(OnFileActionChange)(DWORD dwMask,LPCWSTR lpName, DWORD dwAttribute);
	STDMETHOD(OnFileActionTimeOut)(DWORD dwTimer);
	STDMETHOD(OnDiskChange)(
		DWORD dwCtrlMask,   //�̷���������:���ɾ��
		DWORD dwType,		//�̷����ͣ�U�̣�Ӳ�̡�����DiskType_Unknown
		LPCWSTR lpName		//�̷�����:c:\\ ;
		);

private:
	UTIL::com_ptr<IMscomRunningObjectTable> m_pRot;
	UTIL::com_ptr<IFileMonitor>	m_pFileMonitor;
	CConnectionPointHelper m_FileChangeConnectPoint;
	UseConnectPoint<IDiskChangeConnectPoint> m_useDiskChangePoint;
};
