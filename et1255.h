#ifndef ET1255_H_INCLUDED
#define ET1255_H_INCLUDED

#include <windows.h>
#include <winioctl.h>
//#include <hidsdi.h>
#include <SetupAPI.h>




#define Get_CTL_CODE(Function) (CTL_CODE(FILE_DEVICE_UNKNOWN, Function, METHOD_BUFFERED, FILE_ANY_ACCESS))
#define ioctl_ADC_WRITE    Get_CTL_CODE(0x801)
#define ioctl_ADC_READ     Get_CTL_CODE(0x802)
#define ioctl_SCAN_WRITE   Get_CTL_CODE(0x803)
#define ioctl_SCAN_READ    Get_CTL_CODE(0x804)
#define ioctl_CTRL_WRITE   Get_CTL_CODE(0x805)
#define ioctl_CTRL_READ    Get_CTL_CODE(0x806)
#define ioctl_ADC_STROB    Get_CTL_CODE(0x807)
#define ioctl_MEM_START_WRITE   Get_CTL_CODE(0x808)
#define ioctl_AMPL_SET     Get_CTL_CODE(0x809)
#define ioctl_DAC_WRITE    Get_CTL_CODE(0x810)
#define ioctl_DGT_WRITE    Get_CTL_CODE(0x811)
#define ioctl_DGT_READ     Get_CTL_CODE(0x812)



const GUID _GUID_MID =
{
   0x20CBE45F,0xF6F7,0x4f4a,{0x8F,0x2F,0xDB,0xB6,0xBF,0x82,0xA4,0x6C}
};
/*
//c671678c-82c1-43f3-d700-0049433e9a4b
const GUID _GUID_MID =
{
   0xc671678c,0x82c1,0x43f3,{0xd7,0x00,0x00,0x49,0x43,0x3e,0x9a,0x4b}
};
*/


class ET1255
{
HDEVINFO hdev;
GUID GUID_ET1255;
HANDLE hHandle;
public:
    ET1255();
    ET1255(LPTSTR MONITOR_CLASS_STR);
    char* ET_StartDrv();
    void ET_SetStrob();
    float ET_ReadADC();
    void ET_StopDrv();
    void ET_SetADCChnl(int chnl);
    float CodeToVolt(int w);
    void ET_SetScanMode(int ChCount, bool ScanEnable);
    void ET_SetADCMode(int Frq, bool PrgrmStart, bool IntTackt, bool MemEnable);
    void ET_SetAmplif(int Value);
    int ET_MeasEnd();

    //unsigned Get_CTL_CODE(int code);
};





#endif // ET1255_H
