
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "../log/log.h"
#include "mainwork.h"
using namespace std;

TCHAR szServiceName[] = _T("EarlyStartService");
//定义全局函数变量
void Init();//初始化函数
void WINAPI ServiceMain();//服务的主函数
void WINAPI ServiceStrl(DWORD dwOpcode);//服务控制函数


BOOL bInstall;
SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS status;
DWORD dwThreadID;

//*********************************************************
//Functiopn:           main
//Description:         主函数入口
//*********************************************************
int APIENTRY WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
        LPSTR     lpCmdLine,
int       nCmdShow)
{
Init();


dwThreadID = ::GetCurrentThreadId();

SERVICE_TABLE_ENTRY st[] =
        {
                { szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
                { NULL, NULL }
        };




if (!::StartServiceCtrlDispatcher(st))
{
    LogMessage(L"Register Service Main Function Error!");
}


return 0;
}

//*********************************************************
//Functiopn:               Init
//Description:            初始化
//*********************************************************
void Init()
{
    hServiceStatus = NULL;
    status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState = SERVICE_STOPPED;
    status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    status.dwWin32ExitCode = 0;
    status.dwServiceSpecificExitCode = 0;
    status.dwCheckPoint = 0;
    status.dwWaitHint = 0;
}

//*********************************************************
//Function:            ServiceMain
//Description:            服务主函数，这里进行控制对服务控制的注册
//*********************************************************
void WINAPI ServiceMain()
{
    // Register the control request handler
    hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
    if (hServiceStatus == NULL)
    {
        LogMessage(L"Handler not installed");
        return;
    }

    // Initialize service status
    status.dwCurrentState = SERVICE_START_PENDING;
    SetServiceStatus(hServiceStatus, &status);

    // Now that the handler is registered, we can proceed to start the service
    status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hServiceStatus, &status);

    dwThreadID = ::GetCurrentThreadId(); // Move this here

    // Keep the service running
    while (1)
    {
        if(status.dwCurrentState == SERVICE_RUNNING)
        {
            if(workmain())
            {
                break;
            }

        }
        else
        {
            break;
        }

    }


    // Stop the service logic
    status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(hServiceStatus, &status);
    LogMessage(L"Service stopped");
}


//*********************************************************
//Functiopn:			 ServiceStrl
//Description: 			服务控制主函数，这里实现对服务的控制，
//                      当在服务管理器上停止或其它操作时，将会运行此处代码
//*********************************************************
void WINAPI ServiceStrl(DWORD dwOpcode)
{
switch (dwOpcode)
{
case SERVICE_CONTROL_STOP:
status.dwCurrentState = SERVICE_STOP_PENDING;
SetServiceStatus(hServiceStatus, &status);
PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
break;
case SERVICE_CONTROL_PAUSE:
break;
case SERVICE_CONTROL_CONTINUE:
break;
case SERVICE_CONTROL_INTERROGATE:
break;
case SERVICE_CONTROL_SHUTDOWN:
break;
default:
    LogMessage(L"Bad service request");
}
}




