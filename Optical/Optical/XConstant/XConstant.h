#pragma once


extern const CString COMPANYNAME;
extern const CString APP_NAME;
extern const CString APP_VERSION;
extern const CString APP_REGISTRYKEY;
extern const CString APP_FONT;
extern const int FONT_SIZE;
extern const CString APP_ININAME;


extern const int MAIN_TOPHEIGHT; //顶部图片高度
extern const int MAIN_STATUSBARHEIGHT; //状态栏高度
extern const int TITLEBAR_HEIGHT; //标题栏高度

extern const int DLG_MINWIDTH; //子主对话框宽度
extern const int DLG_MINHIGHT; //子主对话框高度

extern const int DIS_WIDTH; //底部图标间隔
extern const int DIS_HIGHT; //底部图标间隔




//资源ID
extern const UINT ID_BEGIN;
extern const UINT ID_STATUSBAR;
extern const UINT ID_BTN_CLOSE;
extern const UINT ID_BTN_SET;
extern const UINT ID_BTN_MIN;
extern const UINT ID_LANGUAGE_ZH_CN;
extern const UINT ID_LANGUAGE_ZH_TW;
extern const UINT ID_LANGUAGE_EN;
extern const UINT ID_ABOUT;
extern const UINT ID_BTN_MESSAGEBOXDLG_1;
extern const UINT ID_BTN_MESSAGEBOXDLG_2;
extern const UINT ID_BTN_MESSAGEBOXDLG_3;
extern const UINT ID_STATIC_MESSAGEBOXDLG_TEXT;
extern const UINT ID_TOOLBAR;
extern const UINT ID_SETNET;




//消息ID
extern const UINT MSG_BTN_LCLICK;
extern const UINT MSG_UDP;
extern const UINT MSG_TOOBAR_ITEMLCLICK;


//定时器
#define TIMERID_WELCOMETEXT				1 //更新界面欢迎文字
#define TIMERELAPSE_WELCOMETEXT			60000

#define TIMERID_HEART                   2
#define TIMESPACE_HEART                 3000

#define TIMERID_LOAD					3
#define TIMERSPACE_LOAD					1000


//释放
#define RELEASE(X) if(NULL!=X){delete X;X=NULL;}

//语言类型
enum LANGUAGETYPE
{
	LANGUAGETYPE_ZH_CN,
	LANGUAGETYPE_EN,
	LANGUAGETYPE_ZH_TW,

	LANGUAGETYPE_NULL
};

//操作类型
enum OPERATETYPE
{
	OPERATETYPE_WELCOMETEXT,
	OPERATETYPE_LOGIN,
	OPERATETYPE_LOGINOUT,
	OPERATETYPE_HEART,


	OPERATETYPE_NULL

};


//对话框类型
enum DLGTYPE
{
	DLGTYPE_POWERMANAGE=1,
	DLGTYPE_HOSTCONFIG,

	DLGTYPE_NULL
};

//子对话框类型
enum SUBBTNTYPE
{
	//
	SUBBTNTYPE_USERMANAGE=1,
	SUBBTNTYPE_NODEMANAGE,
	SUBBTNTYPE_LOGIN,


	SUBBTNTYPE_NULL
};

//用户权限
enum USERPOWER
{
	USERPOWER_ADMIN=0,
	USERPOWER_NORMAL=1,

	USERPOWER_NULL=-1
};

//用户管理操作
enum USEROPERATE
{
	USEROPERATE_ADD,
	USEROPERATE_DEL,
	USEROPERATE_ALTER,

	USEROPERATE_NULL
	
};

//包头
typedef enum
{
	PACKETHEAD_FULL,
	PACKETHEAD_PART,

	PACKETHEAD_NULL
}PACKERHEAD;

//协议类型
typedef enum
{
	PROTOCOLTYPE_USERLIST,
	PROTOCOLTYPE_LOGIN,
	PROTOCOLTYPE_LOGINOUT,
	PACKERHEAD_HEART,




	PROTOCOLTYPE_NULL

}PROTOCOLTYPE;

//数据结构

class XPowerManageItem;
#define VEC_POWERMANAGEITEM std::vector<XPowerManageItem*>