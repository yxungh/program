#pragma once


extern const CString APP_DATAFILENAME;
extern const CString APP_ININAME;
extern const CString APP_FONT;

extern const UINT MSG_UDP;
extern const UINT MSG_UPDATESHOW;
extern const UINT MSG_BTN_LCLICK;
extern const UINT MSG_ADDDOCUMENT;
extern const UINT MSG_NEWSCENE;

extern const int INPUTSIGNALPANE_DATAVERSION;

extern const int VIDEOPREVIEWPANE_DATAVERSION;

extern const int USERMANAGE_DATAVERSION;

extern const int SCENEPANE_DATAVERSION;

extern const int SM_DATAVERSION;

extern const int DRAWDISTANCE_X;
extern const int DRAWDISTANCE_Y;


extern unsigned int m_signalID;
extern unsigned int m_signalGroupID;

extern HWND gHandle;


//资源ID

#define ID_BEGIN 35000
#define ID_ADDINPUTSIGNALEXPAND			(ID_BEGIN + 100)
#define IDC_STATIC_MESSAGEBOXDLG_TEXT	(ID_BEGIN + 101)
#define IDC_BTN_MESSAGEBOXDLG_1			(ID_BEGIN + 102)
#define IDC_BTN_MESSAGEBOXDLG_2			(ID_BEGIN + 103)
#define IDC_BTN_MESSAGEBOXDLG_3			(ID_BEGIN + 104)
#define ID_EDITINPUTSIGNALEXPAND		(ID_BEGIN + 105)
#define ID_DELINPUTSIGNALEXPAND			(ID_BEGIN + 106)
#define ID_COMBO_LANGUAGE				(ID_BEGIN + 107)
#define ID_COMBO_SCALE					(ID_BEGIN + 108)
#define ID_BTN_OPENNET					(ID_BEGIN + 111)
#define ID_BTN_CLOSENET					(ID_BEGIN + 112)
#define ID_INPUTSIGNAL_TREECTRL			(ID_BEGIN + 115)
#define ID_INPUTSIGNALPANE				(ID_BEGIN + 116)
#define ID_EDIT_DEVICEIP				(ID_BEGIN + 117)
#define ID_EDIT_DEVICEPORT				(ID_BEGIN + 118)
#define ID_SCREEN_CLOSESIGNAL			(ID_BEGIN + 120)
#define ID_BTN_DELETEALLSIGNAL			(ID_BEGIN + 122)
#define ID_SETOSD						(ID_BEGIN + 123)
#define ID_SCREEN_SEPARATE				(ID_BEGIN + 124)
#define ID_SCREEN_NOSEPARATE			(ID_BEGIN + 125)
#define ID_SETINPUTSIGNALDEFAULTEXPAND	(ID_BEGIN + 126)
#define ID_EDIT_TEMPERATURE				(ID_BEGIN + 127)
#define ID_BTN_TEMPERATURE				(ID_BEGIN + 128)
#define ID_BTN_SENDALLSIGNAL			(ID_BEGIN + 129)
#define ID_BTN_ABOUT					(ID_BEGIN + 130)
#define ID_UDPWATCHPANE					(ID_BEGIN + 131)
#define ID_VIDEOPREVIEWPANE				(ID_BEGIN + 132)
#define ID_CHANGEINPUTRES    			(ID_BEGIN + 133)
#define ID_CHANGERTSPADDR				(ID_BEGIN + 134)
#define ID_EDIT_INPUTCOUNT				(ID_BEGIN + 135)
#define ID_EDIT_OUTPUTCOUNTH			(ID_BEGIN + 136)
#define ID_EDIT_OUTPUTCOUNTV			(ID_BEGIN + 137)
#define ID_BTN_LOGIN					(ID_BEGIN + 138)
#define ID_BTN_LOGOUT					(ID_BEGIN + 139)
#define ID_BTN_USERMANAGE				(ID_BEGIN + 140)
#define ID_BTN_POWERMANAGE				(ID_BEGIN + 141)
#define ID_BTN_SETSIGNALTOP				(ID_BEGIN + 142)
#define ID_BTN_SETSIGNALBOTTOM			(ID_BEGIN + 143)
#define ID_BTN_SETSIGNALSHIFTUP			(ID_BEGIN + 144)
#define ID_BTN_SETSIGNALSHIFTDOWN		(ID_BEGIN + 145)
#define ID_BTN_SETSIGNALEXPAND		    (ID_BEGIN + 146)
#define ID_BTN_SAVESCENCE               (ID_BEGIN + 147)
#define ID_BTN_OPENSCENCE               (ID_BEGIN + 148)
#define ID_INPUTSIGNALCUT               (ID_BEGIN + 149)
#define ID_CHANGEINPUT                  (ID_BEGIN + 150)
#define ID_BORDEROVERLAT                (ID_BEGIN + 151)
#define ID_BTN_SETMOVEPARAMATER         (ID_BEGIN + 152)
#define ID_EDID                         (ID_BEGIN + 153)
#define ID_ATTRIBUTE_SIGNAL             (ID_BEGIN + 154)
#define ID_ATTRIBUTE_SCREEN             (ID_BEGIN + 155)
#define ID_TIMEDPOLLING                 (ID_BEGIN + 156)
#define ID_SETANOTHERNAME               (ID_BEGIN + 157)
#define ID_BTN_DELETESCENE              (ID_BEGIN + 158)
#define ID_BTN_SETSCREENRESULATION      (ID_BEGIN + 159)
#define ID_BTN_OLDORDER                 (ID_BEGIN + 160)
#define ID_BTN_PAN                      (ID_BEGIN + 161)
#define ID_BTN_CHIP                     (ID_BEGIN + 162)
#define ID_SCREENCHANGE                 (ID_BEGIN + 163)
#define ID_BTN_NEWVIEW                  (ID_BEGIN + 164)
#define ID_COMBO_VIEW                   (ID_BEGIN + 165)
#define ID_BTN_CLOSEVIEW                (ID_BEGIN + 166)
#define ID_BTN_PREVIEW                  (ID_BEGIN + 167)
#define ID_BTN_FRONT                    (ID_BEGIN + 168)
#define ID_BTN_BACK                     (ID_BEGIN + 169)
#define ID_SELECTCHENAL                 (ID_BEGIN + 167)
#define ID_SECNEPANE                    (ID_BEGIN + 168)
#define ID_BTNNEWSCENCE                 (ID_BEGIN + 169)
#define ID_BTNOPENSCENE                 (ID_BEGIN + 170)
#define ID_BTNSAVESCENE                 (ID_BEGIN + 171)
#define ID_BTNDELETESCENE               (ID_BEGIN + 172)
#define ID_SETSCREENNUM                 (ID_BEGIN + 173)
#define ID_SETSCREENINDEX               (ID_BEGIN + 174)
#define ID_SETINPUTURTAL                (ID_BEGIN + 175)
#define ID_SETINPUTOSD                  (ID_BEGIN + 176)
#define ID_SETSCREENMENU                (ID_BEGIN + 177)
#define ID_SAVESCENEMENU                (ID_BEGIN + 178)
#define ID_IPSTREAMADDR                 (ID_BEGIN + 179)
#define ID_SETPANENET                   (ID_BEGIN + 180)
#define ID_SETPREVIEWNET                (ID_BEGIN + 181)
#define ID_SETBITRATE                   (ID_BEGIN + 182)
#define ID_CHANGEANOTHERNAME            (ID_BEGIN + 183)
#define ID_SCENETREE                    (ID_BEGIN + 184)
#define ID_SCENE_DELETE                 (ID_BEGIN + 185)
#define ID_DELFROMGROUP                 (ID_BEGIN + 186)
#define ID_ADDGROUP                     (ID_BEGIN + 187)
#define ID_GROUP_DELETE                 (ID_BEGIN + 188)
#define ID_GROUP_CHANGE                 (ID_BEGIN + 189)
#define ID_INPUTGROUP_CHANGE            (ID_BEGIN + 190)
#define ID_INPUTGROUP_DELETE            (ID_BEGIN + 191)
#define ID_BTN_NAMAL                    (ID_BEGIN + 192)
#define ID_BTN_FOUR                     (ID_BEGIN + 193)
#define ID_BTN_FULL                     (ID_BEGIN + 194)
#define ID_SCREEN_RESULATIONOFMATRIX    (ID_BEGIN + 195)
#define ID_SCENE_RENAME                 (ID_BEGIN + 196)
#define ID_SCENE_REMOVE                 (ID_BEGIN + 197)   
#define ID_SCENE_DELETEGROUP            (ID_BEGIN + 198)
#define ID_SCENE_RENAMEGROUP            (ID_BEGIN + 199)
#define ID_BTN_INTER                    (ID_BEGIN + 200)
#define ID_BTN_TIPMODEL                 (ID_BEGIN + 201)
#define ID_BTN_UPMODEL                  (ID_BEGIN + 202)
#define ID_BTN_DOWNMODEL                (ID_BEGIN + 203)
#define ID_BTN_ALLSCENE                 (ID_BEGIN + 204)
#define ID_BTN_COPY                     (ID_BEGIN + 205)
#define ID_COPYORDER                    (ID_BEGIN + 206)
#define ID_SIGNLESCENE                  (ID_BEGIN + 207)
#define ID_SETROWDPI                    (ID_BEGIN + 208)
#define ID_SETCOLDPI                    (ID_BEGIN + 209)
#define ID_MENU_NET						(ID_BEGIN + 210)
#define ID_MENU_BITRATE					(ID_BEGIN + 211)




#define ID_BTNCHECKBOX                  (ID_BEGIN + 1000)
#define ID_SPLITBTN                     (ID_BEGIN + 2000)


enum XEQUIPMENTTYPE
{
	EQUIPMENTTYPE_INPUT=1,

	EQUIPMENTTYPE_OUTPUT=2
};

enum XDATATYPE//数据类型
{
	XDATATYPE_ALL,

	XDATATYPE_LANGUAGENAME,//语言名称
	XDATATYPE_SCALE,//显示比例
	XDATATYPE_DEVICEIP,//设备IP
	XDATATYPE_DEVICEPORT,//设备Port
	XDATATYPE_INPUTCOUNT,//输入个数
	XDATATYPE_OUTPUTCOUNTH,//水平输出个数
	XDATATYPE_OUTPUTCOUNTV,//垂直输出个数
	XDATATYPE_VIEW,//选择视图

	XDATATYPE_NULL
};

enum LANGUAGETYPE//语言类型
{
	LANGUAGETYPE_ZH_CN,
	LANGUAGETYPE_ZH_TW,
	LANGUAGETYPE_EN,

	LANGUAGETYPE_NULL
};

enum OPERATETYPE//操作类型
{
	OPERATETYPE_NEWVIEW,//新建视图
	OPERATETYPE_CLOSEVIEW,//关闭视图
	//////////////////////////////////////////////////////////////////////////

	OPERATETYPE_PREVIEW,//视频预览
	//////////////////////////////////////////////////////////////////////////
	OPERATETYPE_OPENNET,
	OPERATETYPE_CLOSENET,
	OPERATETYPE_RELOADINTERFACE,//重载界面
	OPERATETYPE_SCREENCLOSESIGNAL,//屏幕删除信号
	OPERATETYPE_DELETEALLSIGNAL,//删除所有信号
	OPERATETYPE_SETSCREENRESULATION,//设置全部分辨率
	OPERATETYPE_RUNOLDORDER,//执行旧指令
	//////////////////////////////////////////////////////////////////////////

	OPERATETYPE_SAVESCENCE,//保存场景
	OPERATETYPE_OPENSCENCE,//打开场景
	OPERATETYPE_DELETESCENCE,//删除场景

	OPERATETYPE_SCREENMOVE,//滚动画面
	OPERATETYPE_TIMEDPOLLING,//定时轮询间隔
	OPERATETYPE_SETSIGNALTOP,//信号置顶
	OPERATETYPE_SETSIGNALBOTTOM,//信号置底
	OPERATETYPE_SETSIGNALSHIFTUP,//信号上移
	OPERATETYPE_SETSIGNALSHIFTDOWN,//信号下移
	OPERATETYPE_SETSIGNALEXPAND,//信号扩展
	OPERATETYPE_CHANGEINPUT,//切换输入源

	//////////////////////////////////////////////////////////////////////////
	OPERATETYPE_SCREENSEPARATE,//屏幕高清分割
	OPERATETYPE_SCREENRESULATION,//屏幕分辨率
	OPERATETYPE_SCREENATTRIBUTE,//屏幕属性
	OPERATETYPE_DEVICESTATUS,//获取设备状态
	OPERATETYPE_SETDEVICESTATUS,
	OPERATETYPE_CHANGESCREEN,//交换屏幕

	OPERATETYPE_REFRESHDEVICESTATUS,//检查设备状态

	OPERATETYPE_REFRESHPAN,//刷新板卡
	OPERATETYPE_REFRESHCHIP,//刷新芯片

	OPERATETYPE_SETTEMPERATURE,//设置温度
	OPERATETYPE_RESETTEMPERATURE,//重置温度
	//////////////////////////////////////////////////////////////////////////

	OPERATETYPE_GETSIGNALPARAMATER,//获取信号信息
	OPERATETYPE_GETSCREENPARAMATER,//获取屏幕信息
	OPERATETYPE_SETSIGNALPARAMATER,//设置信号参数
	OPERATETYPE_SETSCREENPARAMATER,//设置屏幕信息
	OPERATETYPE_GETWINDOWPARAMATER,//获取窗口配置
	OPERATETYPE_SETWINDOWPARAMATER,//设置窗口信息
	OPERATETYPE_GETSCREENMOVEASK,//获取屏幕滚动应答
	OPERATETYPE_GETSCENEINDEX,//获取场景序号
	OPERATETYPE_SETSCENEINDEX,//设置场景序号
	OPERATETYPE_SETSCENEINDEX1,
	OPERATETYPE_SETSCREENPARAMATEROFMATRIX,
	
	
	OPERATETYPE_SETSIGNALICON,//刷新输入信号图标
	OPERATETYPE_SETSCREENINDEXRGB,//刷新屏幕序号颜色
	OPERATETYPE_GETSIGNALCUT,//获取信号裁剪
	OPERATETYPE_SETSIGNALCUT,//获取信号裁剪

	OPERATETYPE_GETINPUTNUM,//获取信号序号
	OPERATETYPE_SETINPUTNUM,//设置信号序号

	OPERATETYPE_MATRIXOUTPUT,//获取矩阵窗口配置

	//////////////////////////////////////////////////////////////////////////
	OPERATETYPE_NEWSCENE,
	OPERATETYPE_MENUSCREENSET,
	OPERATETYPE_MENUSAVESCENE,
	//////////////////////////////////////////////////////////////////////////

	OPERATETYPE_ABOUT,//关于
	OPERATETYPE_GETSCREENSYN,//获取屏幕同步
	OPERATETYPE_HANDLESCREENSYN,//处理屏幕同步
	OPERATETYPE_HANDLESCREENSYNBYVIDEOPREVIEW,//根据视频预览处理屏幕同步
	OPERATETYPE_LOGIN,//登陆
	OPERATETYPE_LOGOUT,//注销
	OPERATETYPE_USERMANAGE,//用户管理
	OPERATETYPE_POWERMANAGE,//权限管理
	OPERATETYPE_ADDTEXTTOTITLE,//添加文字到标题栏
	OPERATETYPE_RESETUSERNODEPOWER,//重置用户节点权限

	//////////////////////////////////////////////////////////////////////////
	OPERATETYPE_GETPANEIPADDR,//获取板卡IP
	OPERATETYPE_GETSTREAMADDR,//获取视频流

	OPERATETYPE_GETBITRATE,//获取码率

	OPERATETYPE_GETMATRIXOUTPUT,

	OPERATETYPE_GETPREVIEWNET,//

	OPERATETYPE_SPLITNETSET,
	OPERATETYPE_SPLITBITRATE,

	OPERATETYPE_NORMAL,//普通模式
	OPERATETYPE_FULL,//全屏模式
	OPERATETYPE_FOUR,
	OPERATETYPE_INTER,

	OPERATETYPE_TIPMODEL,
	OPERATETYPE_UPMODEL,
	OPERATETYPE_DOWNMODEL,

	OPERATETYPE_SAVEALLSECNE,
	OPERATETYPE_SINGLESCENE,

	OPERATETYPE_COPYMODEL,

	OPERATETYPE_SETROWDPI,
	OPERATETYPE_SETCOLDPI,



	OPERATETYPE_SCREENRESULATIONOFMATRIX,

	OPERATETYPE_NULL
};

enum CMDUITYPE
{
	CMDUITYPE_OPENNET,
	CMDUITYPE_CLOSENET,
	CMDUITYPE_LOGIN,//登陆
	CMDUITYPE_LOGOUT,//注销
	CMDUITYPE_USERMANAGE,//用户管理
	CMDUITYPE_POWERMANAGE,//权限管理
	CMDUITYPE_INPUTCOUNT,//输入个数
	CMDUITYPE_OUTPUTCOUNTH,//水平输出个数
	CMDUITYPE_OUTPUTCOUNTV,//垂直输出个数
	CMDUITYPE_DEVICEIP,//设备IP
	CMDUITYPE_DEVICEPORT,//设备Port
	CMDUITYPE_SAVESCENCE,//保存场景
	CMDUITYPE_OPENSCENCE,//打开场景
	CMDUITYPE_DELETESCENCE,//删除场景
	CMDUITYPE_SCREENMOVE,//屏幕拼接滚动
	CMDUITYPE_TIMEDPOLLING,//轮询间隔
	CMDUITYPE_SETSCREENRESULATION,//整体设置屏幕分辨率
	CMDUITYPE_RUNOLDORDER,//执行旧指令
	CMDUITYPE_PAN,
	CMDUITYPE_CHIP,
	CMDUITYPE_NEWVIEW,//新建视图
	CMDUITYPE_CLOSEVIEW,//关闭视图
	CMDUITYPE_PREVIEW,//视频预览

	CMDUITYPE_DELETEALLSIGNAL,//删除所有信号


	CMDUITYPE_NORMAL,
	CMDUITYPE_FULL,
	CMDUITYPE_FOUR,
	CMDUITYPE_INTER,
	CMDUITYPE_TIPMODEL,
	CMDUITYPE_UPMODEL,
	CMDUITYPE_DOWNMODEL,

	CMDUITYPE_SAVEALLSCENE,

	CMDUITYPE_COPYMODEL,

	CMDUITYPE_NULL
};

enum SHOWTYPE//显示类型
{
	SHOWTYPE_SHOW,//显示
	SHOWTYPE_HIDE,//隐藏

	SHOWTYPE_NULL
};

typedef enum POWERTYPE_//权限类型
{
	POWERTYPE_ADMIN = 1,

	POWERTYPE_NORMAL = 0,

	POWERTYPE_NULL = -1,

}POWERTYPE;

enum POSITIONTYPE//位置类型
{
	POSITIONTYPE_LT,
	POSITIONTYPE_RT,
	POSITIONTYPE_LB,
	POSITIONTYPE_RB,
	POSITIONTYPE_L,
	POSITIONTYPE_R,
	POSITIONTYPE_T,
	POSITIONTYPE_B,

	POSITIONTYPE_NULL,
};

enum CURSORTYPE//鼠标类型
{
	CURSORTYPE_NORMAL,//普通
	CURSORTYPE_MOVE,//移动
	CURSORTYPE_NESW,//双箭头指向东北和西南
	CURSORTYPE_NS,//双箭头指向南北
	CURSORTYPE_NWSE,//双箭头指向西北和东南
	CURSORTYPE_WE,//双箭头指向东西

	CURSORTYPE_NULL,
};

enum SIGNALPOSTYPE//信号位置类型
{
	SIGNALPOSTYPE_1,
	SIGNALPOSTYPE_2,
	SIGNALPOSTYPE_3,
	SIGNALPOSTYPE_4,

	SIGNALPOSTYPE_NULL,
};

enum HYITEMTYPE//树项类型
{
	HYITEMTYPE_LAYER,
	HYITEMTYPE_CLASS,
	HYITEMTYPE_DEVICE,

	HYITEMTYPE_NULL
};

enum ORDERNUM//命令编号
{
	ORDERNUM_SAVESCENE,//保存场景
	ORDERNUM_OPENSCENE,//打开场景
	ORDERNUM_GETINPUT,//输入状态
	ORDERNUM_SETOUTPUT,//获取输出状态
	ORDERNUM_GETOUTPUT,//设置输出
	ORDERNUM_OPERATOR,//操作编号
	ORDERNUM_SIGNAL,//窗口配置
	ORDERNUM_RESIGNAL,//获取窗口配置
	ORDERNUM_DELETEALL,//删除所有
	ORDERNUM_FINISH,//配置完成
	ORDERNUM_DATATRANS,//数据传输
	ORDERNUM_OSD,//OSD
	ORDERNUM_BORDEROVERLAY,//边框叠加
	ORDERNUM_SETSIGNALCUT,//信号裁剪
	ORDERNUM_GETSIGNALCUT,//获取信号裁剪参数
	ORDERNUM_TIMEDPOLLING,//定时轮询间隔
	ORDERNUM_SCREENMOVEASK,//询问是否能发送
	ORDERNUM_SCREENMOVE,//滚动画面
	ORDERNUM_SCENEINDEX,//场景序号
	ORDERNUM_DELETESCENE,//删除场景
	ORDERNUM_OLDORDER,//执行旧指令
	ORDERNUM_DEVICESTATUS,//设备状态
	ORDERNUM_CHANGECHENAL,//切换通道
	ORDERNUM_GETSIGNALNUM,//获取信号序号

	ORDERNUM_IPSTREAM,//IP输入卡
	ORDERNUM_PANEIPSET,//板卡网络设置

	ORDERNUM_GETPANEIP,//获取板卡网络
	ORDERNUM_GETSTREAMADDR,//获取视频流

	ORDERNUM_SETPREVIEWNET,
	ORDERNUM_GETPREVIEWNET,

	ORDERNUM_SETBITRATE,//设置码率
	ORDERNUM_GETBITRATE,//获取码率

	ORDERNUM_MATRIX,//矩阵切换\

	ORDERNUM_MATRIXRESULATION,

	ORDERNUM_CLOSEMATRIX,

	ORDERNUM_GETMTRIXPARA,



	ORDERNUM_NULL
};

enum ADDRESSTYPE//命令地址类型
{
	ADDRESSTYPE_INPUT,//输入信号
	ADDRESSTYPE_OUTPUT,//输出到屏幕
	ADDRESSTYPE_OPERATOR,//操作(置顶。。)
	ADDRESSTYPE_PANEL,//面板
	ADDRESSTYPE_BROADCAST,//广播
	ADDRESSTYPE_WINDOW,//kauchuang
	ADDRESSTYPE_TWOOPERATOR,//两路操作

	ADDRESSTYPE_NULL
};

enum ORDERTYPE//命令形式
{
	ORDERTYPE_INPUT,//输入
	ORDERTYPE_OUTPUT,//输出
	ORDERTYPE_WINDOWS,//窗口配置
	OEDERTYPE_SCENE,//场景序号
	OEDERTYPE_SCREEN,
	ORDERTYPE_DEVICESTATUS,//设备状态
	ORDERTYPE_SIGNALNUM,

	ORDERTYPE_NODATA,

	ORDERTYPE_GETPANEIP,//获取板卡网络
	ORDERTYPE_GETSTREAMADDR,//获取视频流

	ORDERTYPE_SETPREVIEWNET,
	ORDERTYPE_GETPREVIEWNET,

	ORDERTYPE_SETBITRATE,//设置码率
	ORDERTYPE_GETBITRATE,//获取码率

	ORDERTYPE_MATRIXWINDOWS,


	ORDERTYPE_NULL
};

enum BTNSTATUS//按钮状态
{
	BTNSTATUS_FRONTDISABLE,//向前
	BTNSTATUS_BACKDISABLE,//向后
	BTNSTATUS_BOTHDISABLE,//两者

	BTNSTATUS_FRONTENABLE,//向前
	BTNSTATUS_BACKENABLE,//向后
	BTNSTATUS_BOTHENABLE,//两者

	BTNSTATUS_NULL

};

enum ITEMTYPE//树节点状态
{
	ITEMTYPE_INPUTGROUP,

	ITEMTYPE_INPUTSIGNAL,

	ITEMTYPE_EXPAND,

	ITEMTYPE_ROOT,

	ITEMTYPE_CHILD,

	ITEMTYPE_CHILDCHILD,

	ITEMTYPE_NULL
};

typedef enum
{
	SCREENMODEL_MATRIX=1,

	SCREENMODEL_SPLIC=2,

	SCREENMODEL_DEV=3,

	SCREENMODEL_FLAG,

	SCREENMODEL_NULL

}SCREENMODEL;

enum DRAGSTATUS
{
	DRAGSTATUS_NORMAL,

	DRAGSTATUS_FULL,

	DRAGSTATUS_FOUR,

	DRAGSTATUS_INTER,

	DRAGSTATUS_COPY,


	DRAGSTATUS_NULL
};

enum DRAGMODEL
{

	DRAGMODEL_TIPMODEL,

	DRAGMODEL_UPMODEL,

	DRAGMODEL_DOWNMODEL,

	//DRAGMODEL_COPY,

	DRAGMODEL_NULL
};

enum BOARDTYPE
{
	BOARDTYPE_SIGNALSPLICE,//单路拼接

	BOARDTYPE_MULTISPLICE,//两路拼接

	BOARDTYPE_MATRIX,//矩阵

	BOARDTYPE_PREVIEW,//预览卡

	BOARDTYPE_NOPANE,//没有板卡

	BOARDTYPE_NULL
};

enum INPUTTYPE
{
	INPUTTYPE_2K,

	INPUTTYPE_4K,

	INPUTTYPE_VGA,

	INPUTTYPE_SDI,

	INPUTTYPE_AV,

	INPUTTYPE_IP2K,

	INPUTTYPE_IP4K,

	INPUTTYPE_NOPANE,

	INPUTTYPE_NULL,
};

enum CORRPSCREENNUM
{
	CORRPSCREENNUM_ONE,

	CORRPSCREENNUM_TWO,

	CORRPSCREENNUM_FOUR,

	CORRPSCREENNUM_NULL
};

enum ITEMSCENETYPE
{
	ITEM_SCENEROOT,
	ITEM_SCENECHILD,
	ITEM_SCENEGROUP,
	ITEM_SCENE,
	ITEM_SCENEVIEWNAME,

	ITEM_MATRIX,
	ITEM_SPLIC,
	ITEM_DEV,
	ITEM_SIGNAL,

	ITEM_NULL
};


typedef enum
{
	CTRLSTATUS_NOMAL,
	CTRLSTATUS_CHANGE,

	CTRLSTATUS_NULL
}CTRLSTATUS;

typedef enum
{
	SAVETYPE_RCUT,
	SAVETYPE_BCUT,
	SAVETYPE_ALL,

	SAVETYPE_NULL
}SAVETYPE;

//集合
#define RECTF	Gdiplus::RectF
#define POINTF  Gdiplus::PointF
#define SIZEF   Gdiplus::SizeF

class XBaseScreenManage;
#define VEC_BASESCREENMANAGE std::vector<XBaseScreenManage*>
#define VEC_BASETEMP std::vector<XBaseScreenManage*>


class XVideoPreviewPane;
#define VEC_VIDEOPREVIEWPANE std::vector<XVideoPreviewPane*>

class XVideoPreviewPane;
#define VEC_VIDEOPREVIEWPANETEMP std::vector<XVideoPreviewPane*>

class XScreen;
#define VEC_SCREEN std::vector<XScreen*>

class XSignal;
#define VEC_SIGNAL std::vector<XSignal*>

class XInputSignal;
#define VEC_INPUTSIGNAL std::vector<XInputSignal*>

class XInputSignalExpand;
#define VEC_INPUTSIGNALEXPAND std::vector<XInputSignalExpand*>

class XScreenSynInfo;
#define MAP_SCREENSYNINFO std::map<int, XScreenSynInfo*>

class XVideoPreviewFrame;
#define VEC_VIDEOPREVIEWFRAME std::vector<XVideoPreviewFrame*>

class XDeviceInfo;
#define VEC_FRONTDEVICEINFO std::vector<XDeviceInfo*>

class XDeviceInfo;
#define VEC_BACKDEVICEINFO std::vector<XDeviceInfo*>

class XDeviceInfo;
#define VEC_DEVICEINFO std::vector<XDeviceInfo*>

class XUserInfo;
#define VEC_USERINFO std::vector<XUserInfo*>

class HYXTreeNodeItem;
#define HYVEC_TREENODEITEM std::vector<HYXTreeNodeItem*>
#define HYMAP_TREENODEITEM std::map<DWORD, HYXTreeNodeItem*>

class HYXVTreeNodeItem;
#define HYVEC_VTREENODEITEM std::vector<HYXVTreeNodeItem*>

class HYXGridItem;
#define HYVEC_GRIDITEM std::vector<HYXGridItem*>
#define HYMAP_GRIDITEM std::map<DWORD, HYXGridItem*>

class HYXGridRow;
#define HYMAP_GRIDROW std::map<DWORD, HYXGridRow*>
#define HYVEC_GRIDROW std::vector<HYXGridRow*>

#define HYVEC_NUM std::vector<int>

class XNodePowerInfo;
#define MAP_NODEPOWERINFO std::map<unsigned int, XNodePowerInfo*>

#define VEC_CHAR std::vector<char*>

#define VEC_UCHAR std::vector<unsigned char>

class XSendData;
#define VEC_SENDDATA std::vector<XSendData*>

#define VEC_RECTF std::vector<RECTF>

#define VEC_RECT std::vector<CRect>

#define VEC_CSTRING std::vector<CString>

#define VEC_UNINT std::vector<unsigned int>

class XEquipmentWnd;
#define VEC_EQUIPMENT std::vector<XEquipmentWnd*>

class XEquipmentInput;
#define VEC_EQUIPMENTINPUT std::vector<XEquipmentInput*>

class XEquipmentOutput;
#define VEC_EQUIPMENTOUTPUT std::vector<XEquipmentOutput*>

class XScreenData;
#define VEC_SCREENDATA std::vector<XScreenData*>

class XScreenInfo;
#define VEC_SCREENINFO std::vector<XScreenInfo*>

#define MAP_NUMOFSCREEN std::map<int,int>

class XOutputInfo;
#define VEC_OUTPUTINFO std::vector<XOutputInfo*>

class XScreenNumInfo;
#define MULTIMAP_NUMOFSCREEN std::multimap<int,XScreenNumInfo*>

class XAnotherNameInfo;
#define VEC_NAMEINFO std::vector<XAnotherNameInfo*>

class XScreenDataInfo;
#define VEC_SCREENDATAINFO std::vector<XScreenDataInfo*>

class XBoardNetInfo;
#define MAP_BOARDNETINFO std::map<int,XBoardNetInfo*>

#define VEC_RTSP std::vector<CString>

//class XPreviewRTSPInfo;
//#define MAP_INPUTRTSP std::map<int,XPreviewRTSPInfo*>

class XScreenRetInfo;
#define MAP_SCREENRETINFO std::map<int,XScreenRetInfo*>

#define MAP_MATRIX std::map<int,int>

#define MAP_NUMOFMATRIXSCREEN std::map<int,MAP_MATRIX>

#define MAP_NUM std::map<int,int>

class XSceneInfo;
#define MAP_SCENE std::map<CString,XSceneInfo*>

#define MAP_ITEM std::map<int,HTREEITEM>

#define MAP_ITEMNAME std::map<CString,HTREEITEM>

class XInputGroup;
#define MAP_GROUP std::map<CString,XInputGroup*>

class XTempInputInfo;
#define MAP_TEMPINPUT std::map<int,XTempInputInfo*>

class XInputInfoInGroup;
#define VEC_INPUTINFOINGROUP std::vector<XInputInfoInGroup*>

class XPreviewBoardInfo;
#define VEC_PREVIEWBOARDINFO std::vector<XPreviewBoardInfo*>

class XPreviewBoard;
#define VEC_PREVIEWBOARD std::vector<XPreviewBoard*>

class XSelectBoardInfo;
#define MAP_SELECTBOARD std::map<int,XSelectBoardInfo*>

#define MAP_PREVIEWTEMP std::map<int,int>

class HYXText;
#define VEC_PREVIEWTEXT std::vector<HYXText*>

#define VEC_VIEWTEXT std::vector<HYXText*>

#define MAP_BOARDTYPE std::map<int,int>

class XInputType;
#define MAP_INPUTTYPE std::map<int,XInputType*>

class XSceneGroupInfo;
#define MAP_SCENEGROUP std::map<CString,XSceneGroupInfo*>

class XExpandInfo;
#define VEC_EXPANDINFO std::vector<XExpandInfo*>

#define MAP_RERTSPADDR std::map<CString,int>

#define MAP_GROUPID std::map<unsigned int,int>

#define MAP_SELSCENE std::map<int,CString>

#define MAP_SCENETEMP std::map<CString,int>

#define MAP_TABLABLE std::map<CString,CString>

class XScreenColInfo;
class XScreenRowInfo;
#define MAP_ROWINFO std::map<int,XScreenRowInfo*>
#define MAP_COLINFO std::map<int,XScreenColInfo*>


typedef enum hiPIC_SIZE_E
{
	PIC_QCIF = 0,
	PIC_CIF,     
	PIC_2CIF,    
	PIC_HD1, 	 
	PIC_D1,		 
	PIC_960H,
	PIC_1280H,
	PIC_1440H,

	PIC_QVGA,    /* 320 * 240 */
	PIC_VGA,     /* 640 * 480 */    
	PIC_XGA,     /* 1024 * 768 */   
	PIC_SXGA,    /* 1400 * 1050 */    
	PIC_UXGA,    /* 1600 * 1200 */    
	PIC_QXGA,    /* 2048 * 1536 */

	PIC_WVGA,    /* 854 * 480 */
	PIC_WSXGA,   /* 1680 * 1050 */      
	PIC_WUXGA,   /* 1920 * 1200 */
	PIC_WQXGA,   /* 2560 * 1600 */

	PIC_HD720,   /* 1280 * 720 */
	PIC_HD1080,  /* 1920 * 1080 */
	PIC_qHD,     /*960 * 540*/

	PIC_UHD4K,   /* 3840*2160 */

	PIC_BUTT
}PIC_SIZE_E;
