#pragma once

#define CONNECT_FLAG 0xFFFA0FFF
#define CONNECT_CONFIG_FACTOR1 1
#define CONNECT_CONFIG_FACTOR2 3

#define SERVICE_FLAG 0xFFFA1FFF
//上线方式
enum
{	
	CONNECT_IP = 0x00,	//固定IP上线	
	CONNECT_DNS,		//域名解析上线
	CONNECT_HTTP		//HTTP解析IP上线
};

//代理方式
enum
{	
	PROXY_SOCK5 = 0x00,	//sock5代理
	PROXY_HTTP,			//HTTP代理	
	PROXY_ISA			//ISA代理
};

#define SERVANTSHELL_REALNAME_LENGTH 17

#pragma pack(1)
typedef struct  _CONNECT_INFO
{
	int  nFlag;					//结构体标记	
	int  nConnectType;			//上线方式
	char szAddr[64]; 			//上线地址	
	int  nPort;					//代理方式
	int  nProxyType;
	char szProxyAddr[64];		//代理地址
	char szProxyUsername[32];	//代理用户名	
	char szProxyPassword[32];	//代理密码	
	int  nProxyPort;			//代理端口	
	int	 nTryConnectIntervalM;	//和服务器断开后,尝试连接的时间间隔	
	int  nDefaultCommType;		//默认的连接方式	//0-detect 1-http 2-dns	
	int  nFirstConnectHour;		//启动后第一次连接服务端的时间
	int  nFirstConnectMinute;
	UINT nFirstDownSvtOffsetS;	//首次尝试下载servant.dll的偏移时间(s)
	UINT nDownSvtIntervalS;		//每次尝试下载servant.dll的间隔时间(s)
	char szGroups[255];			//servantshell部署后的真实名称
	char szServantshellRealname[SERVANTSHELL_REALNAME_LENGTH];
}CONNECT_INFO, * PCONFIG_INFO;

typedef struct _SERVICE_INFO
{
	int nFlag;					//结构体标记	
	char szServiceName[128];	//服务名
	char szDisplayName[128];	//显示名称
	char szServiceDecript[128];	//服务描述	
	TCHAR szInstalPath[256];	//安装路径	
	BOOL bUseChameleon;			//是否采用混淆安装
}SERVICE_INFO, * PSERVICE_INFO;