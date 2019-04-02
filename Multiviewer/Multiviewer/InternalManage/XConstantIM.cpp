#include "StdAfx.h"
#include "XConstantIM.h"



const CString APP_DATAFILENAME				= _T("App");
const CString APP_ININAME					= _T("App");
const CString APP_FONT						= _T("宋体");

const int INPUTSIGNALPANE_DATAVERSION		= 1;//输入信号面板数据版本

const int VIDEOPREVIEWPANE_DATAVERSION		= 1;//视频预览面板数据版本

const int USERMANAGE_DATAVERSION			= 1;//用户管理数据版本

const int SCENEPANE_DATAVERSION             = 1;//场景面板数据版本

const int SM_DATAVERSION					= 1;//屏幕管理数据版本
const int DRAWDISTANCE_X					= 100;//绘图水平间隔
const int DRAWDISTANCE_Y					= 100;//绘图垂直间隔

unsigned int m_signalID                     =(GetTickCount()*10000)%0x80000000;

unsigned int m_signalGroupID                =(GetTickCount()*10000)%0x80000000+1000;

HWND gHandle                                =NULL;


//消息ID
const UINT MSG_BEGIN						= WM_USER + 100;
const UINT MSG_UDP							=(MSG_BEGIN + 1);
const UINT MSG_UPDATESHOW                   =(MSG_BEGIN + 2);
const UINT MSG_BTN_LCLICK                   =(MSG_BEGIN + 3);
const UINT MSG_ADDDOCUMENT                  =(MSG_BEGIN + 4);
const UINT MSG_NEWSCENE                     =(MSG_BEGIN + 5);





