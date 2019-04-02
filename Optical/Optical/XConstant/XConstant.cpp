#include "Stdafx.h"
#include "XConstant.h"


const CString COMPANYNAME											= _T("AVCIT");
const CString APP_NAME												= _T("Optical");
const CString APP_VERSION											= _T("1.0");
const CString APP_REGISTRYKEY										= (APP_NAME + _T(" ") + APP_VERSION);
const CString APP_FONT												= _T("微软雅黑");
const int FONT_SIZE													=11;
const CString APP_ININAME											=_T("App");

const int MAIN_TOPHEIGHT											=130;
const int MAIN_STATUSBARHEIGHT										=30;

const int TITLEBAR_HEIGHT                                           =30;

const int DLG_MINWIDTH												=800;
const int DLG_MINHIGHT												=600;

const int DIS_WIDTH													=10;
const int DIS_HIGHT													=10;




//资源ID
const UINT ID_BEGIN													=35000;
const UINT ID_STATUSBAR												=(ID_BEGIN+1);
const UINT ID_BTN_CLOSE												=(ID_BEGIN+2);
const UINT ID_BTN_SET												=(ID_BEGIN+3);
const UINT ID_BTN_MIN												=(ID_BEGIN+4);
const UINT ID_LANGUAGE_ZH_CN										=(ID_BEGIN+5);
const UINT ID_LANGUAGE_ZH_TW										=(ID_BEGIN+6);
const UINT ID_LANGUAGE_EN											=(ID_BEGIN+7);
const UINT ID_ABOUT													=(ID_BEGIN+8);
const UINT ID_BTN_MESSAGEBOXDLG_1									=(ID_BEGIN+9);
const UINT ID_BTN_MESSAGEBOXDLG_2									=(ID_BEGIN+10);
const UINT ID_BTN_MESSAGEBOXDLG_3									=(ID_BEGIN+11);
const UINT ID_STATIC_MESSAGEBOXDLG_TEXT								=(ID_BEGIN+12);
const UINT ID_TOOLBAR												=(ID_BEGIN+13);
const UINT ID_SETNET												=(ID_BEGIN+14);


//消息ID
const UINT MSG_BEGIN												=WM_USER+100;
const UINT MSG_BTN_LCLICK											=(MSG_BEGIN+1);
const UINT MSG_UDP													=(MSG_BEGIN+2);
const UINT MSG_TOOBAR_ITEMLCLICK									=(MSG_BEGIN+3);