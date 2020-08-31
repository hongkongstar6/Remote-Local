#pragma once

#define CONNECT_FLAG 0xFFFA0FFF
#define CONNECT_CONFIG_FACTOR1 1
#define CONNECT_CONFIG_FACTOR2 3

#define SERVICE_FLAG 0xFFFA1FFF
//���߷�ʽ
enum
{	
	CONNECT_IP = 0x00,	//�̶�IP����	
	CONNECT_DNS,		//������������
	CONNECT_HTTP		//HTTP����IP����
};

//����ʽ
enum
{	
	PROXY_SOCK5 = 0x00,	//sock5����
	PROXY_HTTP,			//HTTP����	
	PROXY_ISA			//ISA����
};

#define SERVANTSHELL_REALNAME_LENGTH 17

#pragma pack(1)
typedef struct  _CONNECT_INFO
{
	int  nFlag;					//�ṹ����	
	int  nConnectType;			//���߷�ʽ
	char szAddr[64]; 			//���ߵ�ַ	
	int  nPort;					//����ʽ
	int  nProxyType;
	char szProxyAddr[64];		//�����ַ
	char szProxyUsername[32];	//�����û���	
	char szProxyPassword[32];	//��������	
	int  nProxyPort;			//����˿�	
	int	 nTryConnectIntervalM;	//�ͷ������Ͽ���,�������ӵ�ʱ����	
	int  nDefaultCommType;		//Ĭ�ϵ����ӷ�ʽ	//0-detect 1-http 2-dns	
	int  nFirstConnectHour;		//�������һ�����ӷ���˵�ʱ��
	int  nFirstConnectMinute;
	UINT nFirstDownSvtOffsetS;	//�״γ�������servant.dll��ƫ��ʱ��(s)
	UINT nDownSvtIntervalS;		//ÿ�γ�������servant.dll�ļ��ʱ��(s)
	char szGroups[255];			//servantshell��������ʵ����
	char szServantshellRealname[SERVANTSHELL_REALNAME_LENGTH];
}CONNECT_INFO, * PCONFIG_INFO;

typedef struct _SERVICE_INFO
{
	int nFlag;					//�ṹ����	
	char szServiceName[128];	//������
	char szDisplayName[128];	//��ʾ����
	char szServiceDecript[128];	//��������	
	TCHAR szInstalPath[256];	//��װ·��	
	BOOL bUseChameleon;			//�Ƿ���û�����װ
}SERVICE_INFO, * PSERVICE_INFO;