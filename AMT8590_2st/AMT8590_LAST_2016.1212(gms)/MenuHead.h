// Copyright (C) 2002 AMT Corporation
// All rights reserved.
//
// DIVISION    : A.M.T. Coporation
// MODIFIED BY : ViboX Kim
// REVISION    :
//     2011. 02. 19 : Modified by ViboX Kim
//

#ifndef _STRUCT_H_
#define _STRUCT_H_

// *****************************************************************************
// ȭ�� �� Ŭ���� �߰� �κ�
// *****************************************************************************
#include "Screen_Main.h"				// ���� ȭ�� Ŭ���� �߰� 
#include "Screen_Lock.h"				// System Locking ȭ�� Ŭ���� �߰� 
#include "Screen_Initial.h"				// �ʱ�ȭ ���� ȭ�� Ŭ���� �߰� 

#include "Screen_Basic.h"				// ������ ���� ȭ�� Ŭ���� �߰� 

#include "Screen_Set_Maintenance.h"		// ����Ʈ ���� ȭ�� Ŭ���� �߰� 
#include "Screen_Wait_Time.h"			// ��� �ð� ���� ���� ȭ�� Ŭ���� �߰� 
#include "Screen_File_Editor.h"			// File Editor ȭ�� Ŭ���� �߰� 
 
#include "Screen_Motor.h"
#include "Screen_Motor_Speed.h"			// ���� ���ǵ� ȭ�� Ŭ���� �߰�.
#include "Screen_List_Operation.h"		// Operation ���� ��� ȭ�� Ŭ���� �߰� 
#include "Screen_List_Data_View.h"
#include "Screen_IO.h"					// I/O ���� ���� ��� ȭ�� Ŭ���� �߰� 
#include "Screen_Set_Barcode.h"
#include "Screen_Admin.h"				// Administrator ��� ȭ�� Ŭ���� �߰� 

// *****************************************************************************

// *****************************************************************************
// ȭ�� �� Ŭ���� ID ���� �κ�
// *****************************************************************************
#define IDW_SCREEN_MAIN					101
#define IDW_SCREEN_LOCK					102
#define IDW_SCREEN_INIT					103
	
#define IDW_SCREEN_BASIC		 		201

#define IDW_SCREEN_SET_MAINTENANCE		301
#define IDW_SCREEN_SET_BARCODE          302
#define IDW_SCREEN_SET_NETWORK          303

#define IDW_SCREEN_WAIT_TIME			401

#define IDW_SCREEN_MOTOR_TEACH			501
#define IDW_SCREEN_MOTOR_SPEED			502

#define IDW_SCREEN_LIST_OPERATION		601
#define IDW_SCREEN_LIST_DATA_VIEW		602
#define IDW_SCREEN_LIST_STEP			603

#define IDW_SCREEN_IO					701

#define IDW_SCREEN_ADMINISTRATOR		801
#define IDW_SCREEN_FILE_EDITOR			802
#define IDW_SCREEN_ECSERVER				803

#define IDW_SCREEN_PGM_INFO				1700

// *****************************************************************************

#endif