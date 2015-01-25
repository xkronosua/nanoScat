#ifndef SMDDRV_H_INCLUDED
#define SMDDRV_H_INCLUDED

//#include <windows.h>



HINSTANCE hLib = LoadLibrary("C:\\Windows\\SMD004.dll");
typedef bool (__stdcall *_SMD_OpenComPort)(int AComNmbr);
    _SMD_OpenComPort SMD_OpenComPort = (_SMD_OpenComPort) GetProcAddress(hLib, "SMD_OpenComPort");
/*
2.1  ������� Com-����
������� ��������� COM-����, � ������������� �������� ����� �����.
����:  AComNmbr - ����� COM-�����. ����� ����� > 0.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_CloseComPort)();
    _SMD_CloseComPort SMD_CloseComPort = (_SMD_CloseComPort)GetProcAddress(hLib, "SMD_CloseComPort");
/*
2.2  ������� Com-����
�����: TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef int (__stdcall *_SMD_GetPortNumber)();
    _SMD_GetPortNumber SMD_GetPortNumber = (_SMD_GetPortNumber)GetProcAddress(hLib, "SMD_GetPortNumber");
/*
2.3  �������� ����� COM-�����
�����:  ������������� ����� COM-�����.
*/


typedef void (__stdcall *_SMD_SetPortNumber)(int Value);
    _SMD_SetPortNumber SMD_SetPortNumber=(_SMD_SetPortNumber) GetProcAddress(hLib, "SMD_SetPortNumber");
/*
2.4  ���������� ����� COM-�����
����:  Value - ����� COM-�����.
*/


typedef char* (__stdcall *_SMD_ErrMsg)();
    _SMD_ErrMsg SMD_ErrMsg = (_SMD_ErrMsg)GetProcAddress(hLib, "SMD_ErrMsg");
/*
2.5  ��������� �� ������
���� �TEREX� � �SMD-004 DLL�. ���������� �������  3
�����:  ��������� �� ������. �c�� ������ ���, ������������ ������ ������.
�������������  ���������  ���������  ��  ������  �����  �������  ���������  �  ����������  �
�������� ����������.
*/


typedef bool (__stdcall *_SMD_OnSHD)(int ATrtAddr, int ANumber);
    _SMD_OnSHD SMD_OnSHD = (_SMD_OnSHD)GetProcAddress(hLib, "SMD_OnSHD");
/*
2.6  ����� ��������� (������� $00)
����:  ATrtAddr � ����� ������ SMD-004;
 ANumber � ����� ��������� (0 ��� 1).
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_OffSHD)(int ATrtAddr, int ANumber);
    _SMD_OffSHD SMD_OffSHD = (_SMD_OffSHD)GetProcAddress(hLib, "SMD_OffSHD");
/*
2.7  ��������� ��������� (������� $01)
����:  ATrtAddr � ����� ������ SMD-004;
 ANumber � ����� ��������� (0 ��� 1).
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/



typedef bool (__stdcall *_SMD_SetMoveParam)(int ATrtAddr, int ANumber, bool Stop, bool ADirR, unsigned int AStepCount);
    _SMD_SetMoveParam SMD_SetMoveParam = (_SMD_SetMoveParam)GetProcAddress(hLib, "SMD_SetMoveParam");
/*
2.8  ��������� ������ �������� (������� $02)
function SMD_SetMoveParam(ATrtAddr: int; ANumber: int;
AStop, ADirR: bool;
AStepCount: longword): bool;
����:  ATrtAddr � ����� ������ SMD-004;
ANumber � ����� ��������� (0 ��� 1);
AStop � TRUE - �������� �� ��������� ����������� ��� ������� ����;
ADirR � TRUE � �������� � ������ �����������, FALSE� � ��������;
AStepCount � ���������� ����� (����� � ��������� ��1 �� 65535).
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_WriteTactFreq)(int ATrtAddr, int ANumber, int Value);
    _SMD_WriteTactFreq SMD_WriteTactFreq = (_SMD_WriteTactFreq)GetProcAddress(hLib, "SMD_WriteTactFreq");
/*
2.9  ��������� �������� ������� (������� $03)
stdcall;
����:  ATrtAddr � ����� ������ SMD-004;
ANumber � ����� ��������� (0 ��� 1);
Value  �  ���������  �����������  (�����  �  ���������  �� 1  ��  255).  ���  ��������
���������� ������ ��� ���������.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_OnAllSHD)(int ATrtAddr);
    _SMD_OnAllSHD SMD_OnAllSHD = (_SMD_OnAllSHD)GetProcAddress(hLib, "SMD_OnAllSHD");
/*
2.10  ����� ������������ ���� ����������
����:  ATrtAddr � ����� ������ SMD-004.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_OffAllSHD)(int ATrtAddr);
    _SMD_OffAllSHD SMD_OffAllSHD = (_SMD_OffAllSHD)GetProcAddress(hLib, "SMD_OffAllSHD");
/*
2.11  ��������� ������������ ���� ����������
����:  ATrtAddr � ����� ������ SMD-004.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_GetState)(int ATrtAddr, bool SHDOn1, bool EndSensor1_0, bool EndSensor1_8, int Dir1, int StepCount1,
	bool SHDOn2, bool EndSensor2_0, bool EndSensor2_8, int Dir2, int StepCount2);
    _SMD_GetState SMD_GetState = (_SMD_GetState)GetProcAddress(hLib, "SMD_GetState");
/*
2.12  ������ ��������� ���������� (������� $04)
function SMD_GetState(ATrtAddr: int;
var SHDOn1, EndSensor1_0, EndSensor1_8: bool;
var Dir1: int;
var StepCount1: int;
var SHDOn2, EndSensor2_0, EndSensor2_8: bool;
var Dir2: int;
var StepCount2: int): bool;
����:  ATrtAddr  � ����� ������ SMD-004.
�����:
SHDOn1  � TRUE � ��������� ���������, ������������ ������� 1;
���� �TEREX� � �SMD-004 DLL�. ���������� �������  4
EndSensor1_0  � TRUE  �  ��������  ��������  ����������� ���  1-��  ������,  ���  �������
�����������;
EndSensor1_8  � TRUE  �  ��������  ��������  ����������� ���  1-��  ������,  ���  ���������
�����������;
Dir1  � 0  �  ���������  ��  1�  ������  ���������  �  ������  �����������,  ������
�������� � � ��������;
StepCount1  -  ���������� �����, ����������� ���������� �� 1� ������;
SHDOn2  � TRUE � ��������� ���������, ������������ ������� 2;
EndSensor2_0  � TRUE  �  ��������  ��������  ����������� ���  2-��  ������,  ���  �������
�����������;
EndSensor2_8  � TRUE  �  ��������  ��������  ����������� ���  2-��  ������,  ���  ���������
�����������;
Dir2  � 0 � ��������� �� 2� ������ ��������� � ������ �����������;
StepCount2  -  ���������� �����, ����������� ���������� �� 2-� ������.
*/


typedef bool (__stdcall *_SMD_ClearStep)(int ATrtAddr);
    _SMD_ClearStep SMD_ClearStep = (_SMD_ClearStep)GetProcAddress(hLib, "SMD_ClearStep");
/*
2.13  ��������� �������� ����� (������� $05)
����:  ATrtAddr � ����� ������ SMD-004.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_WriteMulty)(int ATrtAddr, int ANumber, int Value);
    _SMD_WriteMulty SMD_WriteMulty = (_SMD_WriteMulty)GetProcAddress(hLib, "SMD_WriteMulty");
/*
2.14  ��������� ��������� ����������� �������� ������� (������� $06)
����:  ATrtAddr  � ����� ������ SMD-004;
ANumber  � ����� ��������� (0 ��� 1);
Value  � ���������  �����������  (�����  �  ���������  �� 1  ��  255).  ���  ��������
���������� ������ ��� ���������.
�����:  TRUE  � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_WriteMarchIHoldICode)(int ATrtAddr, int ANumber, int AMarchI, int AHoldI);
    _SMD_WriteMarchIHoldICode SMD_WriteMarchIHoldICode = (_SMD_WriteMarchIHoldICode)GetProcAddress(hLib, "SMD_WriteMarchIHoldICode");
/*
2.15  ��������� ��������� ���� � ���� ��������� (������� $07)
function SMD_WriteMarchIHoldICode(ATrtAddr: int;
ANumber, AMarchI, AHoldI: int): bool;
stdcall;
����:  ATrtAddr  � ����� ������ SMD-004;
ANumber  � ����� ��������� (0 ��� 1);
AMarchI  � �������� ��� (��� �� 0 �� 7);
AHoldI  � ��� ��������� (��� �� 0 �� 7).
���  ���, A
0  0
1  0,4
2  0,8
3  1,2
4  1,6
5  2,0
6  2,5
7  3,0
�����: TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_WritePhaseMode)(int ATrtAddr, int ANumber, byte Value);
    _SMD_WritePhaseMode SMD_WritePhaseMode = (_SMD_WritePhaseMode)GetProcAddress(hLib, "SMD_WritePhaseMode");
/*
2.16  ��������� ������ ����������� ��� (������� $08)
stdcall;
����:  ATrtAddr  � ����� ������ SMD-004;
 ANumber  � ����� ��������� (0 ��� 1);
Value  � ����� ����������� ��� ���������:
00 � �������� ����� ������� ����;
01 � ���������� ����� ������� ���;
10 � ���������� ���.
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
���� �TEREX� � �SMD-004 DLL�. ���������� �������  5
*/


typedef bool (__stdcall *_SMD_ResetSHD)(int ATrtAddr, bool AShd1, bool AShd2);
    _SMD_ResetSHD SMD_ResetSHD = (_SMD_ResetSHD)GetProcAddress(hLib, "SMD_ResetSHD");
/*
2.17  C���� ������������ ������� ���������� (������� $09)
function SMD_ResetSHD(ATrtAddr: int; AShd1, AShd2: bool):bool;
����:  ATrtAddr � ����� ������ SMD-004;
 AShd1  � TRUE � �������� ��� ������ 1; FALSE � �� ����������;
AShd2  � TRUE � �������� ��� ������ 2; FALSE � �� ����������.
�����:  TRUE  � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_SetState)(int ATrtAddr, bool AShd1, bool AShd2);
    _SMD_SetState SMD_SetState = (_SMD_SetState)GetProcAddress(hLib, "SMD_SetState");
/*
2.18  ���������� ��������� ������� ������� ���������� (������� $0A)
function SMD_SetState(ATrtAddr: int; AShd1, AShd2: bool):bool;
����:  ATrtAddr � ����� ������ SMD-004;
 AShd1  � TRUE � ����� 1 �������; FALSE � ���������;
AShd2  � TRUE � ����� 2 �������; FALSE � ���������.
�����:  TRUE  � ���� �������� ���������, FALSE � ����������� ������.
*/


typedef bool (__stdcall *_SMD_GetInform)(char* msg);
    _SMD_GetInform SMD_GetInform = (_SMD_GetInform)GetProcAddress(hLib, "SMD_GetInform");
/*
2.19  ��������� ���������� � ������ SMD (����������� ������� $00)
������� ��������� ����������� ������� $00.
�����:  msg � ����� ������, ����� ���:
SMD004-XXX PRGvY.YY,
���  XXX � ��� ���������� (232 ��� RS-232 � 485 ��� RS-485);
Y.YY � ������ ��������� ��������������� ������.
*/


typedef int (__stdcall *_SMD_GetAddr)();
    _SMD_GetAddr SMD_GetAddr = (_SMD_GetAddr)GetProcAddress(hLib, "SMD_GetAddr");
/*
2.20  ��������� ������ ������ SMD (����������� ������� $01)
�����:  �����  ������  SMD.  ����  ������������  �������� ������  ����  �  �������  ��
���������, ����� �� ���������.
*/


typedef bool (__stdcall *_SMD_SetAddr)(int Value);
    _SMD_SetAddr SMD_SetAddr = (_SMD_SetAddr)GetProcAddress(hLib, "SMD_SetAddr");
/*
2.21  ��������� ������ ������ SMD (����������� ������� $02)
����:  Value � ����� ����� ������ (����� � ���������1..255).
�����:  TRUE � ���� �������� ���������, FALSE � ����������� ������.
*/

#endif // SMDDRV_H_INCLUDED
