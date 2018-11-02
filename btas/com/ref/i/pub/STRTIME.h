/*
����: 	STRTIME.h
�ĵ�:   BTAS2/IRID/01/1.00
����: 	2007-12-20
����: 	ʱ��ṹ����
ϵͳ: 	Windows/Unix
*/

#ifndef  _STRTIME_H_
#define  _STRTIME_H_

#include "BTAS_TYPES.h"

typedef struct _ST_Time
{
    Uint16			                usYear     ;  /* ��    */
    Uint16							usMonth    ;  /* ��    */
    Uint16  						usDay      ;  /* ��    */
    Uint16  						usTemp    ;   /* <optional>Ԥ���ַ� */
    Uint32  						uiSecond   ;  /* �����ۻ���,0.1ms */
}ST_Time;

#endif

