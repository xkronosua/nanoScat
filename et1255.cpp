
#include "et1255.h"
#include <iostream>
#include <vector>
using namespace std;

ET1255::ET1255()
{
    hHandle = INVALID_HANDLE_VALUE;
}

void ET1255::ET_StopDrv(){
    CloseHandle(hHandle);

}

char* ET1255::ET_StartDrv(){
    char *dwResult = "ET1255:";
//GUID MID;
//LPTSTR CLASS_STR = L"{20CBE45F-F6F7-4f4a-8F2F-DBB6BF82A46C}";
//UuidFromString((RPC_WSTR)CLASS_STR, &MID);
    cout<<"Start...";

     HDEVINFO hDevInfo = SetupDiGetClassDevs( &_GUID_MID, NULL, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT | DIGCF_ALLCLASSES);
         if(hDevInfo == INVALID_HANDLE_VALUE)
         {
             return "ERR_FAIL";
         }

         std::vector<SP_INTERFACE_DEVICE_DATA> interfaces;

         for (DWORD i = 0; true; ++i)
         {
             SP_DEVINFO_DATA devInfo;
             devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
             BOOL succ = SetupDiEnumDeviceInfo(hDevInfo, i, &devInfo);
             if (GetLastError() == ERROR_NO_MORE_ITEMS)
                 break;
             if (!succ) continue;

             SP_INTERFACE_DEVICE_DATA ifInfo;
             ifInfo.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
             if (TRUE != SetupDiEnumDeviceInterfaces(hDevInfo, &devInfo,  &(_GUID_MID), 0, &ifInfo))
             {
                 if (GetLastError() != ERROR_NO_MORE_ITEMS)
                     break;
             }
             interfaces.push_back(ifInfo);
         }

         std::vector<SP_INTERFACE_DEVICE_DETAIL_DATA*> devicePaths;
         for (size_t i = 0; i < interfaces.size(); ++i)
         {
             DWORD requiredSize = 0;
             SetupDiGetDeviceInterfaceDetail(hDevInfo, &(interfaces.at(i)), NULL, 0, &requiredSize, NULL);
             SP_INTERFACE_DEVICE_DETAIL_DATA* data = (SP_INTERFACE_DEVICE_DETAIL_DATA*) malloc(requiredSize);
             //Q_ASSERT(data);
             data->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

             if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &(interfaces.at(i)), data, requiredSize, NULL, NULL))
             {
                 continue;
             }
             devicePaths.push_back(data);
             //QString s;
             //TCHAR* t = data->DevicePath;
             //s = (LPSTR)(t);

             //cout<<"data: "<<t[1];
             hHandle = CreateFile(data->DevicePath,
                                             GENERIC_READ | GENERIC_WRITE,
                                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                                             NULL,
                                             OPEN_EXISTING,
                                             FILE_ATTRIBUTE_NORMAL,
                                             0);
                       if(hHandle == INVALID_HANDLE_VALUE){
                           cout<<GetLastError();
                           //return "ERR";
                       }
                       else{
                         //  QString s = QString::fromWCharArray(data->DevicePath);
                         //  cout<<s;
                           break;
                       }
         }

         //cout<<hHandle;
         return dwResult;
}
//void ET1255:Get_

void ET1255::ET_SetStrob(){
   DWORD BytesReturned = 0;
int result = 0;
   result =  DeviceIoControl(hHandle, ioctl_ADC_STROB,
                             NULL, 0, NULL, 0,
                             &BytesReturned,
                             (LPOVERLAPPED)NULL);
if(!result)
       cout<<"Error in <ET_SetStrob> ="<<GetLastError();

}

float ET1255::ET_ReadADC(){
    int rdata;
    DWORD BytesReturned;

    if(!DeviceIoControl(hHandle, ioctl_ADC_READ, NULL, 0, &rdata, sizeof(rdata), &BytesReturned, (LPOVERLAPPED)NULL))
         {
         cout<<"Error in <ET_ReadADC> ="<<GetLastError();
       // return 0;
    }
         else {
        //cout<<rdata<<" "<<BytesReturned;
        return CodeToVolt(rdata & 0x0FFF);}


}



void ET1255::ET_SetADCChnl(int chnl){
    DWORD BytesReturned = 0;
 int result = 0;
    result =  DeviceIoControl(hHandle, ioctl_ADC_WRITE, &(chnl), sizeof(chnl), NULL, 0, &BytesReturned,  (LPOVERLAPPED)NULL);
if( !result)  cout<<"Error in <ET_SetADCChnl> ="<<GetLastError();

}


float ET1255::CodeToVolt(int w){

  float result = 1;
  int p = 0;
  for (int i=0; i< 11; i++) {

    p = 11 - 2*i;
    if (p>0) result = result + ((w & (1 << i)) << p);
    else     result = result + ((w & (1 << i)) >> abs(p));
  }
    result = (float)(-2.5 + 5 * result / 0xFFF);
    return result;
}

void ET1255::ET_SetScanMode(int ChCount, bool ScanEnable){

  DWORD BytesReturned = 0;
  int wdata;

  if (ChCount>16) ChCount = 16;
  wdata = ChCount;
  if (ScanEnable) wdata = wdata | 0x20;
  if (!DeviceIoControl(hHandle, ioctl_SCAN_WRITE, &wdata, sizeof(wdata), NULL, 0, &BytesReturned, (LPOVERLAPPED)NULL)){
      cout<<"Error in <ET_SetScanMode> ="<<GetLastError();
  }

}

void  ET1255::ET_SetADCMode(int Frq, bool PrgrmStart, bool IntTackt, bool MemEnable){
DWORD BytesReturned = 0;
  WORD wdata = 0;

  if (Frq>3) Frq=3;
  wdata = Frq;
  if (!PrgrmStart) wdata = wdata | 0x04;
  if (!IntTackt)   wdata = wdata | 0x08;
  if (!MemEnable)  wdata = wdata | 0x10;

  if (!DeviceIoControl(hHandle, ioctl_CTRL_WRITE, &wdata, sizeof(wdata), NULL, 0, &BytesReturned, (LPOVERLAPPED)NULL)){
          cout<<"Error in <ET_SetADCMode> ="<<GetLastError();}
}

void ET1255::ET_SetAmplif(int Value){
DWORD BytesReturned = 0;
  if (Value>15) Value = 15;
  if(!DeviceIoControl(hHandle, ioctl_AMPL_SET, &Value, sizeof(Value), NULL, 0, &BytesReturned, (LPOVERLAPPED)NULL)){
     cout<<"Error in <ET_SetAmplif> ="<<GetLastError();
  }
}


int ET1255::ET_MeasEnd(){
DWORD BytesReturned = 0;
  int rdata;



  if(!DeviceIoControl(hHandle, ioctl_CTRL_READ, NULL, 0, &rdata, sizeof(rdata), &BytesReturned, (LPOVERLAPPED)NULL)){
      cout<<"Error in <ET_MeasEnd> ="<<GetLastError();
       return -1;
  }
     else return (rdata & 0x0001) == 0x0001;
}


/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    ET1255 et;
    char* aa = et.ET_StartDrv();


    cout<<"aaa<<"<<aa;
    et.ET_StopDrv();
    aa = et.ET_StartDrv();


    cout<<"aaa<<"<<aa;

    //et.ET_SetStrob();
    //et.ET_SetStrob();
    et.ET_SetADCChnl(0);
    et.ET_SetAmplif(5);
    et.ET_SetScanMode(0, false);
    et.ET_SetADCMode(0, 1, 1, 0);


    float r = 0;
    int ch = 1;
    delay(5000);
    int strob=0;
    for (int i=0; i<20; i++){
        delay(5);
        for (ch=0;ch<1;ch++){
        et.ET_SetADCChnl(ch);
        r = et.ET_ReadADC();
        cout<<r;
        strob = et.ET_MeasEnd();
        if(strob) et.ET_SetStrob();
        }
    }
    et.ET_StopDrv();
    return a.exec();
}*/
