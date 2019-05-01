#include "stdafx.h"
#include "AltDataStream.h"


CAltDataStream::CAltDataStream()
{
	m_sFile = _T("");
}

CAltDataStream::~CAltDataStream()
{
}

void CAltDataStream::SetFile(const std::wstring& sFile)
{
	m_sFile = sFile;
}

std::wstring CAltDataStream::GetFile()
{
	return m_sFile;
}

// Returns the number of streams. To deallocate the pStreams, call
// ReleaseStreams.
int CAltDataStream::GetStreams(std::vector<STREAM_INFO*>& streams)
{
	if(m_sFile.empty())
	{
		return 0;
	}

	HANDLE hFile;

	hFile = CreateFile( m_sFile.c_str(), 
						GENERIC_READ, 
						FILE_SHARE_READ, 
						NULL, 
						OPEN_EXISTING, 
						FILE_FLAG_BACKUP_SEMANTICS, 
						NULL );

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	BYTE				baData[sizeof(WIN32_STREAM_ID) + sizeof(TCHAR)];
	LPWIN32_STREAM_ID	pStrmId;
	DWORD				dwBytesToRead;
	DWORD				dwBytesRead;
	LPVOID				pContext;
	BOOL				bResult;
	LARGE_INTEGER		liDataSize;
	DWORD				dwNameSize;	
	DWORD				dwLowByteSeeked;
	DWORD				dwHighByteSeeked;
	STREAM_INFO*		info;
						
	pContext	  = NULL;
	bResult		  = TRUE;

	streams.clear();

	while(bResult)
	{
		dwBytesToRead = sizeof(baData);
		info = NULL;
		
		// read the header part
		if(!BackupRead(	hFile, 
						baData,
						dwBytesToRead,
						&dwBytesRead,
						FALSE, // am I done?
						FALSE,
						&pContext ) )
		{
			bResult = false;
		}
		else
		{
			if(dwBytesRead == 0)
			{
				bResult = false;
			}
			else
			{
				// saving the header info
				pStrmId = (LPWIN32_STREAM_ID)baData;
				dwNameSize = pStrmId->dwStreamNameSize;
				liDataSize = pStrmId->Size;

				if(dwNameSize > 0)
				{
					// read the stream name
					TCHAR* wcsStreamName = new TCHAR[dwNameSize + sizeof(TCHAR)];
					
					ZeroMemory(wcsStreamName, dwNameSize + 2);
					CopyMemory(wcsStreamName, pStrmId->cStreamName, 6);

					dwBytesToRead = dwNameSize - 6;
					LPBYTE lpBuffer = new BYTE[dwBytesToRead + 1];
					
					if(!BackupRead(	hFile, 
									lpBuffer,
									dwBytesToRead,
									&dwBytesRead,
									FALSE, // am I done?
									FALSE,
									&pContext ) )
					{
						bResult = FALSE;
					}			
					
					CopyMemory((wcsStreamName + 3), lpBuffer, dwBytesToRead);

					info = new STREAM_INFO();
					info->sName = wcsStreamName;
					info->lSize = liDataSize.LowPart;
					info->baData[0] = NULL;

					streams.push_back(info);

					delete[] wcsStreamName;
					delete[] lpBuffer;

					pStrmId = NULL;
				}
				
				// Read the stream data, first check if any data is present
				// or not
				if(liDataSize.LowPart != 0 || liDataSize.HighPart != 0)
				{
					dwLowByteSeeked = 0;
					dwHighByteSeeked = 0;
					
					DWORD dwLowBytesSeek;

					dwLowBytesSeek = liDataSize.LowPart;

					if(info)
					{
						if(dwLowBytesSeek > MAX_STREAM_DATA_PREVIEW_SIZE)
						{
							BackupRead(	hFile, 
									info->baData,
									MAX_STREAM_DATA_PREVIEW_SIZE,
									&dwBytesRead,
									FALSE, // am I done?
									FALSE,
									&pContext );
							
							// now that we have read a small portion of the data,
							// we need to seek till the end so that we move to 
							// the next stream's header section
							dwLowBytesSeek -= MAX_STREAM_DATA_PREVIEW_SIZE; 

							bResult = BackupSeek(hFile, 
											 dwLowBytesSeek,
											 0,
											 &dwLowByteSeeked,
											 &dwHighByteSeeked,
											 &pContext);

							if(dwLowByteSeeked > 0)
							{
								bResult = true;
							}
						}
						else
						{
							// since the amount of stream data is even smaller 
							// that what we wish to read, lets just read everything
							// that is there
							bResult = BackupRead(hFile, 
												 info->baData,
												 dwLowBytesSeek,
												 &dwBytesRead,
												 FALSE, // am I done?
												 FALSE,
												 &pContext );	
						}					
					} // if(info)
					else
					{
						bResult = BackupSeek(hFile, 
											 dwLowBytesSeek,
											 0,
											 &dwLowByteSeeked,
											 &dwHighByteSeeked,
											 &pContext);

							if(dwLowByteSeeked > 0)
							{
								bResult = true;
							}
					}
				}
			}
		}
	} // while

	BackupRead(	hFile, 
				NULL,
				0,
				&dwBytesRead,
				TRUE, // am I done?
				FALSE,
				&pContext );

	CloseHandle(hFile);
	
	return streams.size();
}

void CAltDataStream::ReleaseStreams(std::vector<STREAM_INFO*>& streams)
{	
	STREAM_INFO* pStream;	

	for(int nIndex = 0; nIndex < streams.size(); nIndex++)
	{
		pStream = (STREAM_INFO*)streams[nIndex];
		delete pStream;
	}
}
