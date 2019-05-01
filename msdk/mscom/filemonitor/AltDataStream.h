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


