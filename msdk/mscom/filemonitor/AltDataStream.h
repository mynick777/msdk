#pragma once
#define EXTRA_STRM_BYTES 512
#define MAX_STREAM_DATA_PREVIEW_SIZE 64

#include <string>

typedef struct tagSTREAM_INFO
{
	std::wstring sName;
	LONG	lSize;
	BYTE	baData[MAX_STREAM_DATA_PREVIEW_SIZE];

} STREAM_INFO;

typedef HANDLE(*FindFirstStreamPtr)(LPCWSTR, STREAM_INFO_LEVELS, LPVOID, DWORD dwFlags) ;

class CAltDataStream
{
public:
	CAltDataStream();
	virtual ~CAltDataStream();

	void SetFile(const std::wstring&);
	std::wstring GetFile();

	int GetStreams(std::vector<STREAM_INFO*>& streams);
	void ReleaseStreams(std::vector<STREAM_INFO*>& streams);

private:
	std::wstring m_sFile;
};


//int main()
//{
//	CAltDataStream ads;
//	ads.SetFile(L"D:\\ChromeDownload\\¤U¸ü (6).jpg");
//	CPtrList streams;
//	ads.GetStreams(streams);
//
//	TCHAR szData[MAX_STREAM_DATA_PREVIEW_SIZE + 2];
//	DWORD dwSize;
//
//	for (int nIndex = 0; nIndex < streams.GetCount(); nIndex++)
//	{
//		POSITION pos = streams.FindIndex(nIndex);
//
//		LVITEM lvItem;
//		STREAM_INFO* pStream = (STREAM_INFO*)streams.GetAt(pos);
//		TCHAR		 szBuffer[20];
//
//		// Stream Name
//		lvItem.mask = LVIF_TEXT;
//		lvItem.iItem = nIndex;
//		lvItem.iSubItem = 0;
//		lvItem.pszText = pStream->sName.GetBuffer(0);
//
//		// Size
//		_itot_s(pStream->lSize, szBuffer, 10);
//
//		// Data
//		if (pStream->lSize > MAX_STREAM_DATA_PREVIEW_SIZE)
//		{
//			dwSize = MAX_STREAM_DATA_PREVIEW_SIZE;
//		}
//		else
//		{
//			dwSize = pStream->lSize;
//		}
//
//		ZeroMemory(szData, (MAX_STREAM_DATA_PREVIEW_SIZE + 2) * sizeof(TCHAR));
//
//		for (int nIndex = 0; nIndex < pStream->lSize; nIndex++)
//		{
//			szData[nIndex] = pStream->baData[nIndex];
//		}
//	}
//
//	std::wstring check(szData);
//
//	if (std::string::npos != check.find_first_of(L"ZoneId=3"))
//	{
//		int get = 1;
//	}
//	ads.ReleaseStreams(streams);
//	return 0;
//}


//CoInitialize(NULL);
//CComPtr<IZoneIdentifier> spzi;
//spzi.CoCreateInstance(CLSID_PersistentZoneIdentifier);
//DWORD dwZone;
//if (SUCCEEDED(CComQIPtr<IPersistFile>(spzi)
//	->Load(L"D:\\ChromeDownload\\Streams.zip", STGM_READ)) &&
//	SUCCEEDED(spzi->GetId(&dwZone))) {
//	printf("Zone identifier is %d\n", dwZone);
//}
//else {
//	printf("Couldn't get zone identifier (perhaps there isn't one)\n");
//}