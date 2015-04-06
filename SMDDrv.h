#ifndef SMDDRV_H_INCLUDED
#define SMDDRV_H_INCLUDED

#include "include/PDll.h"


class SMDDll: public PDLL
{
   DECLARE_CLASS(SMDDll);
   DECLARE_FUNCTION1(bool, SMD_OpenComPort, int );
   DECLARE_FUNCTION0(bool, SMD_CloseComPort );
   DECLARE_FUNCTION0(int,  SMD_GetPortNumber );
   DECLARE_FUNCTION1(void, SMD_SetPortNumber, int );
   DECLARE_FUNCTION0(char*, SMD_ErrMsg );
   DECLARE_FUNCTION2(bool, SMD_OnSHD, int , int );
   DECLARE_FUNCTION2(bool, SMD_OffSHD, int , int );
   DECLARE_FUNCTION3(bool, SMD_WriteTactFreq, int , int , int );
   DECLARE_FUNCTION1(bool, SMD_OnAllSHD, int );
   DECLARE_FUNCTION1(bool, SMD_OffAllSHD, int );
   DECLARE_FUNCTION1(bool, SMD_ClearStep, int );
   DECLARE_FUNCTION3(bool, SMD_WriteMulty, int , int , int );
   DECLARE_FUNCTION4(bool, SMD_WriteMarchIHoldICode, int , int , int , int );
   DECLARE_FUNCTION3(bool, SMD_WritePhaseMode, int , int , int );
   DECLARE_FUNCTION3(bool, SMD_ResetSHD, int , bool , bool );
   DECLARE_FUNCTION3(bool, SMD_SetState, int , bool , bool );
   DECLARE_FUNCTION1(bool, SMD_GetInform, char* );
   DECLARE_FUNCTION0(int,  SMD_GetAddr);
   DECLARE_FUNCTION1(bool, SMD_SetAddr, int );
   DECLARE_FUNCTION5(bool, SMD_SetMoveParam, int , int , bool , bool , unsigned int );
   DECLARE_FUNCTION11(bool, SMD_GetState, int , bool& , bool& , bool& , int& , int& , bool& , bool& , bool& , int& , int&  );
};


#endif // SMDDRV_H_INCLUDED
