#ifndef SMDDRV_H_INCLUDED
#define SMDDRV_H_INCLUDED

//#include <windows.h>



HINSTANCE hLib = LoadLibrary("C:\\Windows\\SMD004.dll");
typedef bool (__stdcall *_SMD_OpenComPort)(int AComNmbr);
    _SMD_OpenComPort SMD_OpenComPort = (_SMD_OpenComPort) GetProcAddress(hLib, "SMD_OpenComPort");
/*
2.1  ќткрыть Com-порт
‘ункци€ открывает COM-порт, и устанавливает заданный номер порта.
¬ход:  AComNmbr - номер COM-порта. ÷елое число > 0.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_CloseComPort)();
    _SMD_CloseComPort SMD_CloseComPort = (_SMD_CloseComPort)GetProcAddress(hLib, "SMD_CloseComPort");
/*
2.2  «акрыть Com-порт
¬ыход: TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef int (__stdcall *_SMD_GetPortNumber)();
    _SMD_GetPortNumber SMD_GetPortNumber = (_SMD_GetPortNumber)GetProcAddress(hLib, "SMD_GetPortNumber");
/*
2.3  ѕолучить номер COM-порта
¬ыход:  установленный номер COM-порта.
*/


typedef void (__stdcall *_SMD_SetPortNumber)(int Value);
    _SMD_SetPortNumber SMD_SetPortNumber=(_SMD_SetPortNumber) GetProcAddress(hLib, "SMD_SetPortNumber");
/*
2.4  ”становить номер COM-порта
¬ход:  Value - номер COM-порта.
*/


typedef char* (__stdcall *_SMD_ErrMsg)();
    _SMD_ErrMsg SMD_ErrMsg = (_SMD_ErrMsg)GetProcAddress(hLib, "SMD_ErrMsg");
/*
2.5  —ообщение об ошибке
Ќѕ„ѕ ЂTEREXї © ЂSMD-004 DLLї. Ѕиблиотека функций  3
¬ыход:  сообщение об ошибке. ≈cли ошибок нет, возвращаетс€ пуста€ строка.
–екомендуетс€  провер€ть  сообщение  об  ошибке  после  каждого  обращени€  к  процедурам  и
функци€м библиотеки.
*/


typedef bool (__stdcall *_SMD_OnSHD)(int ATrtAddr, int ANumber);
    _SMD_OnSHD SMD_OnSHD = (_SMD_OnSHD)GetProcAddress(hLib, "SMD_OnSHD");
/*
2.6  —тарт двигател€ (команда $00)
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
 ANumber Ц номер двигател€ (0 или 1).
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_OffSHD)(int ATrtAddr, int ANumber);
    _SMD_OffSHD SMD_OffSHD = (_SMD_OffSHD)GetProcAddress(hLib, "SMD_OffSHD");
/*
2.7  ќстановка двигател€ (команда $01)
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
 ANumber Ц номер двигател€ (0 или 1).
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/



typedef bool (__stdcall *_SMD_SetMoveParam)(int ATrtAddr, int ANumber, bool Stop, bool ADirR, unsigned int AStepCount);
    _SMD_SetMoveParam SMD_SetMoveParam = (_SMD_SetMoveParam)GetProcAddress(hLib, "SMD_SetMoveParam");
/*
2.8  ”становка режима вращени€ (команда $02)
function SMD_SetMoveParam(ATrtAddr: int; ANumber: int;
AStop, ADirR: bool;
AStepCount: longword): bool;
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
ANumber Ц номер двигател€ (0 или 1);
AStop Ц TRUE - вращение до концевого выключател€ или команды —“ќѕ;
ADirR Ц TRUE Ц вращение в пр€мом направлении, FALSEЦ в обратном;
AStepCount Ц количество шагов (число в диапазоне от1 до 65535).
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_WriteTactFreq)(int ATrtAddr, int ANumber, int Value);
    _SMD_WriteTactFreq SMD_WriteTactFreq = (_SMD_WriteTactFreq)GetProcAddress(hLib, "SMD_WriteTactFreq");
/*
2.9  ”становка тактовой частоты (команда $03)
stdcall;
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
ANumber Ц номер двигател€ (0 или 1);
Value  Ц  множитель  полупериода  (число  в  диапазоне  от 1  до  255).  Ёто  значение
передаетс€ модулю без изменений.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_OnAllSHD)(int ATrtAddr);
    _SMD_OnAllSHD SMD_OnAllSHD = (_SMD_OnAllSHD)GetProcAddress(hLib, "SMD_OnAllSHD");
/*
2.10  —тарт одновременно двух двигателей
¬ход:  ATrtAddr Ц адрес модул€ SMD-004.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_OffAllSHD)(int ATrtAddr);
    _SMD_OffAllSHD SMD_OffAllSHD = (_SMD_OffAllSHD)GetProcAddress(hLib, "SMD_OffAllSHD");
/*
2.11  ќстановка одновременно двух двигателей
¬ход:  ATrtAddr Ц адрес модул€ SMD-004.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_GetState)(int ATrtAddr, bool SHDOn1, bool EndSensor1_0, bool EndSensor1_8, int Dir1, int StepCount1,
	bool SHDOn2, bool EndSensor2_0, bool EndSensor2_8, int Dir2, int StepCount2);
    _SMD_GetState SMD_GetState = (_SMD_GetState)GetProcAddress(hLib, "SMD_GetState");
/*
2.12  «апрос состо€ни€ двигателей (команда $04)
function SMD_GetState(ATrtAddr: int;
var SHDOn1, EndSensor1_0, EndSensor1_8: bool;
var Dir1: int;
var StepCount1: int;
var SHDOn2, EndSensor2_0, EndSensor2_8: bool;
var Dir2: int;
var StepCount2: int): bool;
¬ход:  ATrtAddr  Ц адрес модул€ SMD-004.
¬ыход:
SHDOn1  Ц TRUE Ц вращаетс€ двигатель, подключенный кканалу 1;
Ќѕ„ѕ ЂTEREXї © ЂSMD-004 DLLї. Ѕиблиотека функций  4
EndSensor1_0  Ц TRUE  Ц  сработал  концевой  выключатель дл€  1-го  канала,  дл€  пр€мого
направлени€;
EndSensor1_8  Ц TRUE  Ц  сработал  концевой  выключатель дл€  1-го  канала,  дл€  обратного
направлени€;
Dir1  Ц 0  Ц  двигатель  на  1м  канале  вращаетс€  в  пр€мом  направлении,  другое
значение Ц в обратном;
StepCount1  -  количество шагов, выполненных двигателем на 1м канале;
SHDOn2  Ц TRUE Ц вращаетс€ двигатель, подключенный кканалу 2;
EndSensor2_0  Ц TRUE  Ц  сработал  концевой  выключатель дл€  2-го  канала,  дл€  пр€мого
направлени€;
EndSensor2_8  Ц TRUE  Ц  сработал  концевой  выключатель дл€  2-го  канала,  дл€  обратного
направлени€;
Dir2  Ц 0 Ц двигатель на 2м канале вращаетс€ в пр€мом направлении;
StepCount2  -  количество шагов, выполненных двигателем на 2-м канале.
*/


typedef bool (__stdcall *_SMD_ClearStep)(int ATrtAddr);
    _SMD_ClearStep SMD_ClearStep = (_SMD_ClearStep)GetProcAddress(hLib, "SMD_ClearStep");
/*
2.13  ќбнуление счетчика шагов (команда $05)
¬ход:  ATrtAddr Ц адрес модул€ SMD-004.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_WriteMulty)(int ATrtAddr, int ANumber, int Value);
    _SMD_WriteMulty SMD_WriteMulty = (_SMD_WriteMulty)GetProcAddress(hLib, "SMD_WriteMulty");
/*
2.14  ”становка множител€ полупериода тактовой частоты (команда $06)
¬ход:  ATrtAddr  Ц адрес модул€ SMD-004;
ANumber  Ц номер двигател€ (0 или 1);
Value  Ц множитель  полупериода  (число  в  диапазоне  от 1  до  255).  Ёто  значение
передаетс€ модулю без изменений.
¬ыход:  TRUE  Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_WriteMarchIHoldICode)(int ATrtAddr, int ANumber, int AMarchI, int AHoldI);
    _SMD_WriteMarchIHoldICode SMD_WriteMarchIHoldICode = (_SMD_WriteMarchIHoldICode)GetProcAddress(hLib, "SMD_WriteMarchIHoldICode");
/*
2.15  ”становка маршевого тока и тока удержани€ (команда $07)
function SMD_WriteMarchIHoldICode(ATrtAddr: int;
ANumber, AMarchI, AHoldI: int): bool;
stdcall;
¬ход:  ATrtAddr  Ц адрес модул€ SMD-004;
ANumber  Ц номер двигател€ (0 или 1);
AMarchI  Ц маршевый ток (код от 0 до 7);
AHoldI  Ц ток удержани€ (код от 0 до 7).
 од  “ок, A
0  0
1  0,4
2  0,8
3  1,2
4  1,6
5  2,0
6  2,5
7  3,0
¬ыход: TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_WritePhaseMode)(int ATrtAddr, int ANumber, byte Value);
    _SMD_WritePhaseMode SMD_WritePhaseMode = (_SMD_WritePhaseMode)GetProcAddress(hLib, "SMD_WritePhaseMode");
/*
2.16  ”становка режима возбуждени€ фаз (команда $08)
stdcall;
¬ход:  ATrtAddr  Ц адрес модул€ SMD-004;
 ANumber  Ц номер двигател€ (0 или 1);
Value  Ц режим возбуждени€ фаз двигател€:
00 Ц волновой режим полного шага;
01 Ц нормальный режим полного шаг;
10 Ц половинный шаг.
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
Ќѕ„ѕ ЂTEREXї © ЂSMD-004 DLLї. Ѕиблиотека функций  5
*/


typedef bool (__stdcall *_SMD_ResetSHD)(int ATrtAddr, bool AShd1, bool AShd2);
    _SMD_ResetSHD SMD_ResetSHD = (_SMD_ResetSHD)GetProcAddress(hLib, "SMD_ResetSHD");
/*
2.17  Cброс контроллеров шаговых двигателей (команда $09)
function SMD_ResetSHD(ATrtAddr: int; AShd1, AShd2: bool):bool;
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
 AShd1  Ц TRUE Ц сбросить дл€ канала 1; FALSE Ц не сбрасывать;
AShd2  Ц TRUE Ц сбросить дл€ канала 2; FALSE Ц не сбрасывать.
¬ыход:  TRUE  Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_SetState)(int ATrtAddr, bool AShd1, bool AShd2);
    _SMD_SetState SMD_SetState = (_SMD_SetState)GetProcAddress(hLib, "SMD_SetState");
/*
2.18  ”правление выходными ключами шаговых двигателей (команда $0A)
function SMD_SetState(ATrtAddr: int; AShd1, AShd2: bool):bool;
¬ход:  ATrtAddr Ц адрес модул€ SMD-004;
 AShd1  Ц TRUE Ц канал 1 включен; FALSE Ц обесточен;
AShd2  Ц TRUE Ц канал 2 включЄн; FALSE Ц обесточен.
¬ыход:  TRUE  Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/


typedef bool (__stdcall *_SMD_GetInform)(char* msg);
    _SMD_GetInform SMD_GetInform = (_SMD_GetInform)GetProcAddress(hLib, "SMD_GetInform");
/*
2.19  ѕолучение информации о модуле SMD (специальна€ команда $00)
‘ункци€ реализует специальную команду $00.
¬ыход:  msg Ц ответ модул€, имеет вид:
SMD004-XXX PRGvY.YY,
где  XXX Ц тип интерфейса (232 дл€ RS-232 и 485 дл€ RS-485);
Y.YY Ц верси€ программы микропроцессора модул€.
*/


typedef int (__stdcall *_SMD_GetAddr)();
    _SMD_GetAddr SMD_GetAddr = (_SMD_GetAddr)GetProcAddress(hLib, "SMD_GetAddr");
/*
2.20  ѕолучение адреса модул€ SMD (специальна€ команда $01)
¬ыход:  адрес  модул€  SMD.  ≈сли  возвращаемое  значение меньше  нул€  Ц  команда  не
выполнена, адрес не определен.
*/


typedef bool (__stdcall *_SMD_SetAddr)(int Value);
    _SMD_SetAddr SMD_SetAddr = (_SMD_SetAddr)GetProcAddress(hLib, "SMD_SetAddr");
/*
2.21  ”становка адреса модул€ SMD (специальна€ команда $02)
¬ход:  Value Ц новый адрес модул€ (число в диапазоне1..255).
¬ыход:  TRUE Ц если операци€ выполнена, FALSE Ц еслиимеютс€ ошибки.
*/

#endif // SMDDRV_H_INCLUDED
