// IO_Manager.cpp: implementation of the IO_Manager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "IO_Manager.h"
#include "FAS_HSSI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "..\common\ShareMem.h"
#include "FastechPublic_IO.h"
#include "Srcbase\ALocalization.h"
#include "SrcPart\APartHandler.h"

st_io_param st_io;
IO_Manager g_ioMgr;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IO_Manager::IO_Manager()
{

}

IO_Manager::~IO_Manager()
{

}

BOOL IO_Manager::Get_In_Bit( int iIoNum )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
	{
		std::string strGet = g_sm.GetData( (SM_TYPE)iIoNum );
		if( strGet == "1" )
			bRtn = TRUE;
	}
	else
	{
		bRtn = FAS_IO.Get_In_Bit( iIoNum );
	}

	return bRtn;
}

int IO_Manager::Get_In_Bit( int iIoNum, int iDummy )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
	{
		std::string strGet = g_sm.GetData( (SM_TYPE)iIoNum );
		if( strGet == "1" )
			bRtn = TRUE;
	}
	else
	{
		bRtn = FAS_IO.Get_In_Bit( iIoNum );
	}

// 	return Get_In_Bit( iIoNum ); //2012,1229
	return bRtn;
}

int IO_Manager::Set_Out_Bit( int nIONo, BOOL bOnOff ) 
{
	int iRtn = CTLBD_RET_GOOD;

	if( st_handler.mn_virtual_mode == 1 )
	{
		std::string strOnOff = "0";
		if( bOnOff == TRUE )
			strOnOff = "1";

		g_sm.SetData( (SM_TYPE)nIONo, strOnOff );
	}
	else
	{
		iRtn = FAS_IO.Set_Out_Bit( nIONo, bOnOff );
	}
	return iRtn;
}

int IO_Manager::Set_IO_PortAutoEnable(int nMasterID, int nPortNo)
{
	int iRtn = CTL_YES;
	if( st_handler.mn_virtual_mode == 1 )
	{

	}
	else
	{
		iRtn = FAS_IO.Set_IO_PortAutoEnable( nMasterID, nPortNo );
	}

	return iRtn;
}

int IO_Manager::Set_IO_SlaveEnable(int nMasterID, int nPortNo, int nSlaveNo, BOOL bEnable)
{
	int iRtn = CTL_YES;
	if( st_handler.mn_virtual_mode == 1 )
	{

	}
	else
	{
		iRtn = FAS_IO.Set_IO_SlaveEnable( nMasterID, nPortNo, nSlaveNo, bEnable );
	}

	return iRtn;
}

BOOL IO_Manager::Get_Out_Bit( int iIoNum )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
	{
		std::string strGet = g_sm.GetData( (SM_TYPE)iIoNum );
		if( strGet == "1" )
			bRtn = TRUE;
	}
	else
	{
		bRtn = FAS_IO.Get_Out_Bit( iIoNum );
	}
	
	return bRtn;	
}

BOOL IO_Manager::Get_Out_Bit( int iIoNum, int iDummy )
{
	return Get_Out_Bit( iIoNum );
}

WORD IO_Manager::Get_In_Word(int nIONo)
{
	WORD wRtn = 0x00;
	if( st_handler.mn_virtual_mode == 1 )
	{
		for( int i=0; i<16; i++ )
		{
			std::string strGet = g_sm.GetData( (SM_TYPE) (nIONo * 100 + i) );
			if( strGet == "1" )
				wRtn |= (1 << i);
		}
	}
	else
	{
		wRtn = FAS_IO.Get_In_Word( nIONo );
	}
	return wRtn;
}

WORD IO_Manager::Get_Out_Word(int nIONo)
{
	WORD wRtn = 0x00;
	if( st_handler.mn_virtual_mode ==  1 )
	{
		for( int i=0; i<16; i++ )
		{
			std::string strGet = g_sm.GetData( (SM_TYPE) (nIONo * 100 + i) );
			if( strGet == "1" )
				wRtn |= (1 << i);
		}
	}
	else
	{
		wRtn = FAS_IO.Get_Out_Word( nIONo );
	}
	return wRtn;
}


int IO_Manager::set_out_bit( int nIONo, BOOL bOnOff )
{
	int iRtn = 0;
	if( st_handler.mn_virtual_mode == 1 )
		iRtn = Set_Out_Bit( nIONo, bOnOff );
	else
		iRtn = FAS_IO.set_out_bit( nIONo, bOnOff );

	return iRtn;
}

BOOL IO_Manager::get_in_bit( int iIoNum, int iDummy )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
		bRtn = Get_In_Bit( iIoNum, iDummy );
	else
		bRtn = FAS_IO.get_in_bit( iIoNum, iDummy );

	return bRtn;
}

BOOL IO_Manager::get_in_bit( int iIoNum, int opt, int iDummy )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
		bRtn = Get_In_Bit( iIoNum, iDummy );
	else
		bRtn = FAS_IO.Get_In_Bit( iIoNum, iDummy );
	
	return bRtn;
}

BOOL IO_Manager::get_in_bit( int iIoNum )
{
	BOOL bRtn = FALSE;
	int iDummy = IO_OFF;
	if( st_handler.mn_virtual_mode == 1 )
		bRtn = Get_In_Bit( iIoNum, iDummy );
	else
		bRtn = FAS_IO.get_in_bit( iIoNum, iDummy );

	return bRtn;
}

BOOL IO_Manager::get_out_bit( int iIoNum, int iDummy )
{
	BOOL bRtn = FALSE;
	if( st_handler.mn_virtual_mode == 1 )
		bRtn = Get_Out_Bit( iIoNum, iDummy );
	else
		bRtn = FAS_IO.get_out_bit( iIoNum, iDummy );

	return bRtn;
}

st_io_param::st_io_param()
{
	int i=0,j=0,k=0;

	//ASS'Y  : LOB BUFFER
	st_io.o_density_f1_lockunlock_switch_lamp							= 0;				//S0000								
	st_io.o_density_f2_lockunlock_switch_lamp							= 1;								
	st_io.o_density_f3_lockunlock_switch_lamp							= 2;								
	st_io.o_density_f4_lockunlock_switch_lamp							= 3;								
	st_io.o_density_f5_lockunlock_switch_lamp							= 4;								
	st_io.o_density_f6_lockunlock_switch_lamp							= 5;								
	
	st_io.i_density_f1_lockunlock_switch_chk							= 8;										
	st_io.i_density_f2_lockunlock_switch_chk							= 9;									
	st_io.i_density_f3_lockunlock_switch_chk							= 10;									
	st_io.i_density_f4_lockunlock_switch_chk							= 11;									
	st_io.i_density_f5_lockunlock_switch_chk							= 12;									
	st_io.i_density_f6_lockunlock_switch_chk							= 13;
	
	
	for ( i = 0; i < 6; i++)
	{
		st_io.o_density_lock_switch[i]									= 0 + i;
		st_io.i_density_lock_switch_chk[i]								= 8 + i;
	}


	st_io.o_density_f1_lockunlock										= 100;											
	st_io.o_density_f2_lockunlock										= 101;											
	st_io.o_density_f3_lockunlock										= 102;											
	st_io.o_density_f4_lockunlock										= 103;											
	st_io.o_density_f5_lockunlock										= 104;											
	st_io.o_density_f6_lockunlock										= 105;											

	st_io.i_density_left_label_limit1_chk								= 108;
	st_io.i_density_right_label_limit2_chk								= 109;

	st_io.i_density_f1_lock_chk											= 200;												
	st_io.i_density_f1_unlock_chk										= 201;											
	st_io.i_density_f2_lock_chk											= 202;												
	st_io.i_density_f2_unlock_chk										= 203;											
	st_io.i_density_f3_lock_chk											= 204;												
	st_io.i_density_f3_unlock_chk										= 205;											
	st_io.i_density_f4_lock_chk											= 206;												
	st_io.i_density_f4_unlock_chk										= 207;											
	st_io.i_density_f5_lock_chk											= 208;												
	st_io.i_density_f5_unlock_chk										= 209;											
	st_io.i_density_f6_lock_chk											= 210;												
	st_io.i_density_f6_unlock_chk										= 211;											

	for ( i = 0; i < 6; i++)
	{
		st_io.o_density_lockunlock[i]									= 100 + i;
		st_io.i_density_lock_chk[i]										= 200 + i*2;
		st_io.i_density_unlock_chk[i]									= 201 + i*2;
	}

	st_io.o_density_lable1_start										= 300;
	st_io.o_density_lable2_start										= 301;
	st_io.o_density_lable3_start										= 302;
	st_io.o_density_lable4_start										= 303;
	st_io.o_density_lable5_start										= 304;
	st_io.o_density_lable6_start										= 305;

	st_io.o_density_lable1_pickon										= 306;
	st_io.o_density_lable2_pickon										= 307;
	st_io.o_density_lable3_pickon										= 308;
	st_io.o_density_lable4_pickon										= 309;
	st_io.o_density_lable5_pickon										= 310;
	st_io.o_density_lable6_pickon										= 311;
	st_io.o_density_lable1_length1										= 312;
	st_io.o_density_lable1_length2										= 313;
	st_io.o_density_lable2_length1										= 314;
	st_io.o_density_lable2_length2										= 315;

	for ( i = 0; i < 6; i++)
	{
		st_io.o_density_lable_start[i]									= 300 + i;
		st_io.o_density_lable_pickon[i]									= 306 + i;
	}
	for ( i = 0; i < 2; i++)
	{
		st_io.o_density_lable_length1[i]								= 312 + (i*2);
		st_io.o_density_lable_length2[i]								= 313 + (i*2);
	}

	st_io.o_density_lable3_length1										= 400;
	st_io.o_density_lable3_length2										= 401;
	st_io.o_density_lable4_length1										= 402;
	st_io.o_density_lable4_length2										= 403;
	st_io.o_density_lable5_length1										= 404;
	st_io.o_density_lable5_length2										= 405;
	st_io.o_density_lable6_length1										= 406;
	st_io.o_density_lable6_length2										= 407;

	for ( i = 2; i < 6; i++)
	{
		st_io.o_density_lable_length1[i]								= 400 + ((i-2)*2);
		st_io.o_density_lable_length2[i]								= 400 + ((i-2)*2);
	}

	st_io.i_density_f1_position_chk										= 408;
	st_io.i_density_f2_position_chk										= 409;
	st_io.i_density_f3_position_chk										= 410;
	st_io.i_density_f4_position_chk										= 411;
	st_io.i_density_f5_position_chk										= 412;
	st_io.i_density_f6_position_chk										= 413;
	st_io.i_density_label1_error_chk									= 414;
	st_io.i_density_label2_error_chk									= 415;
	
	for ( i = 0; i < 6; i++)
	{
		st_io.i_density_position_chk[i]									= 408 + i;
	}

	for ( i = 0; i < 2; i++)
	{
		st_io.i_density_label_error_chk[i]								= 414 + i;
	}


	st_io.i_density_label3_error_chk									= 500;
	st_io.i_density_label4_error_chk									= 501;
	st_io.i_density_label5_error_chk									= 502;
	st_io.i_density_label6_error_chk									= 503;
	for ( i = 2; i < 6; i++)
	{
		st_io.i_density_label_error_chk[i]								= 500 + (i-2);
	}

	st_io.i_density_label1_ready_chk									= 504;
	st_io.i_density_label2_ready_chk									= 505;
	st_io.i_density_label3_ready_chk									= 506;
	st_io.i_density_label4_ready_chk									= 507;
	st_io.i_density_label5_ready_chk									= 508;
	st_io.i_density_label6_ready_chk									= 509;
	st_io.i_density_label1_complete_chk									= 510;
	st_io.i_density_label2_complete_chk									= 511;
	st_io.i_density_label3_complete_chk									= 512;
	st_io.i_density_label4_complete_chk									= 513;
	st_io.i_density_label5_complete_chk									= 514;
	st_io.i_density_label6_complete_chk									= 515;

	for ( i = 0; i < 6; i++)
	{
		st_io.i_density_label_ready_chk[i]								= 504 + i;
		st_io.i_density_label_complete_chk[i]							= 510 + i;
	}

	st_io.o_density_rbt_left_vacuum1									= 600;
	st_io.o_density_rbt_right_vacuum1									= 601;

	st_io.o_density_rbt_left_blow1										= 602;
	st_io.o_density_rbt_right_blow1										= 603;


	st_io.i_density_rbt_left_vacuum1_chk								= 608;
	st_io.i_density_rbt_right_vacuum1_chk								= 609;

	st_io.o_distribute_p1_lockunlock_switch_lamp						= 700;
	st_io.o_distribute_p2_lockunlock_switch_lamp						= 701;
	st_io.o_distribute_p3_lockunlock_switch_lamp						= 702;
	st_io.o_distribute_p4_lockunlock_switch_lamp						= 703;
	
	st_io.i_distribute_p1_lockunlock_switch_chk							= 708;
	st_io.i_distribute_p2_lockunlock_switch_chk							= 709;
	st_io.i_distribute_p3_lockunlock_switch_chk							= 710;
	st_io.i_distribute_p4_lockunlock_switch_chk							= 711;


	for ( i = 0; i < 4; i++)
	{
		st_io.o_distribute_lockunlock_switch_lamp[i]					= 700 + i;
		st_io.i_distribute_lockunlock_switch_chk[i]						= 708 + i;
	}

	st_io.o_distribute_p1_lock											= 1000;
	st_io.o_distribute_p2_lock											= 1001;
	st_io.o_distribute_p3_lock											= 1002;
	st_io.o_distribute_p4_lock											= 1003;

	st_io.i_distribute_p1_lock_chk										= 1004;
	st_io.i_distribute_p1_unlock_chk									= 1005;
	st_io.i_distribute_p1_lock_position_chk								= 1006;
	st_io.i_distribute_p2_lock_chk										= 1007;
	st_io.i_distribute_p2_unlock_chk									= 1008;
	st_io.i_distribute_p2_lock_position_chk								= 1009;
	st_io.i_distribute_p3_lock_chk										= 1010;
	st_io.i_distribute_p3_unlock_chk									= 1011;
	st_io.i_distribute_p3_lock_position_chk								= 1012;
	st_io.i_distribute_p4_lock_chk										= 1013;
	st_io.i_distribute_p4_unlock_chk									= 1014;
	st_io.i_distribute_p4_lock_position_chk								= 1015;

	for ( i = 0; i < 4; i++ )
	{
		st_io.o_distribute_p_lock[i]									= 1000 + i;//2014.1018 (i*3) -> i;
		st_io.i_distribute_lock_chk[i]									= 1004 + (i*3);
		st_io.i_distribute_unlock_chk[i]								= 1005 + (i*3);
		st_io.i_distribute_lock_position_chk[i]							= 1006 + (i*3);
	}

	st_io.o_distribute_p1_plate_updown									= 1100;
	st_io.o_distribute_p2_plate_updown									= 1101;
	st_io.o_distribute_p3_plate_updown									= 1102;
	st_io.o_distribute_p4_plate_updown									= 1103;

	st_io.i_distribute_p1_plate_up_chk									= 1104;
	st_io.i_distribute_p1_plate_down_chk								= 1105;
	st_io.i_bcr_label1_chk												= 1106;

	st_io.i_distribute_p2_plate_up_chk									= 1107;
	st_io.i_distribute_p2_plate_down_chk								= 1108;
	st_io.i_bcr_label2_chk												= 1109;

	st_io.i_distribute_p3_plate_up_chk									= 1110;
	st_io.i_distribute_p3_plate_down_chk								= 1111;
	st_io.i_bcr_label3_chk												= 1112;

	st_io.i_distribute_p4_plate_up_chk									= 1113;
	st_io.i_distribute_p4_plate_down_chk								= 1114;
	st_io.i_bcr_label4_chk												= 1115;

	for ( i = 0; i < 4; i++ )
	{
		st_io.o_distribute_plate_updown[i]								= 1100 + i;
		st_io.i_distribute_plate_up_chk[i]								= 1104 + (i*3);
		st_io.i_distribute_plate_down_chk[i]							= 1105 + (i*3);
		st_io.i_bcr_label_chk[i]										= 1106 + (i*3);
	}

	st_io.o_distribute_p1_plate_vacuum									= 1200;
	st_io.o_distribute_p2_plate_vacuum									= 1201;
	st_io.o_distribute_p3_plate_vacuum									= 1202;
	st_io.o_distribute_p4_plate_vacuum									= 1203;
	st_io.o_distribute_p1_eject_vacuum									= 1204;
	st_io.o_distribute_p2_eject_vacuum									= 1205;
	st_io.o_distribute_p3_eject_vacuum									= 1206;
	st_io.o_distribute_p4_eject_vacuum									= 1207;
	st_io.i_distribute_p1_plate_vacuum_chk								= 1208;
	st_io.i_distribute_p2_plate_vacuum_chk								= 1209;
	st_io.i_distribute_p3_plate_vacuum_chk								= 1210;
	st_io.i_distribute_p4_plate_vacuum_chk								= 1211;

	for ( i = 0; i < 4; i++ )
	{
		st_io.o_distribute_plate_vacuum[i]								= 1200 + i;
		st_io.o_distribute_eject_vacuum[i]								= 1204 + i;
		st_io.i_distribute_plate_vacuum_chk[i]							= 1208 + i;
	}

///////////////////////
	st_io.o_distribute_rbt_left_box_rotator_fwd_cylinder				= 1300;
	st_io.o_distribute_rbt_left_box_rotator_bwd_cylinder				= 1301;
	st_io.o_distribute_rbt_right_box_rotator_fwd_cylinder				= 1302;
	st_io.o_distribute_rbt_right_box_rotator_bwd_cylinder				= 1303;





	st_io.i_distribute_rbt_left_box_rotator_fwd_chk						= 1306;
	st_io.i_distribute_rbt_left_box_rotator_bwd_chk						= 1307;
	st_io.i_distribute_rbt_right_box_rotator_fwd_chk					= 1308;
	st_io.i_distribute_rbt_right_box_rotator_bwd_chk					= 1309;
	
	
	for ( i = 0;i < 2; i++)
	{
		st_io.o_distribute_rbt_box_rotator_fwd_cylinder[i]    			= 1300 + (i*2);
		st_io.o_distribute_rbt_box_rotator_bwd_cylinder[i]    			= 1301 + (i*2);
		st_io.i_distribute_rbt_box_rotator_fwd_chk[i]    				= 1306 + (i*2);
		st_io.i_distribute_rbt_box_rotator_bwd_chk[i]    				= 1307 + (i*2);
	}

///////////////////////



	st_io.o_distribute_rbt_left_top_vacuum_fwdback						= 1400;
	st_io.o_distribute_rbt_left_btm_vacuum_fwdback						= 1401;

	st_io.o_distribute_rbt_right_top_vacuum_fwdback						= 1404;
	st_io.o_distribute_rbt_right_btm_vacuum_fwdback						= 1405;

	st_io.o_distribute_rbt_left_top_vacuum								= 1408;
	st_io.o_distribute_rbt_left_top_eject								= 1409;
	st_io.o_distribute_rbt_left_btm_vacuum								= 1410;
	st_io.o_distribute_rbt_left_btm_eject								= 1411;
	st_io.o_distribute_rbt_right_top_vacuum								= 1412;
	st_io.o_distribute_rbt_right_top_eject								= 1413;
	st_io.o_distribute_rbt_right_btm_vacuum								= 1414;
	st_io.o_distribute_rbt_right_btm_eject								= 1415;


	st_io.i_distribute_rbt_left_top_vacuum_bwd_chk						= 1500;
	st_io.i_distribute_rbt_left_btm_vacuum_bwd_chk						= 1501;

	st_io.i_distribute_rbt_left_top_vacuum_chk							= 1503;
	st_io.i_distribute_rbt_left_btm_vacuum_chk							= 1504;
	
	st_io.i_distribute_rbt_right_top_vacuum_bwd_chk						= 1505;
	st_io.i_distribute_rbt_right_btm_vacuum_bwd_chk						= 1506;

	st_io.i_distribute_rbt_right_top_vacuum_chk							= 1508;
	st_io.i_distribute_rbt_right_btm_vacuum_chk							= 1509;
	////
	

	for ( i = 0;i < 2; i++)
	{
		st_io.o_distribute_rbt_top_vacuum_fwdback[i]					= 1400 + (i*4);//left,right
		st_io.o_distribute_rbt_btm_vacuum_fwdback[i]					= 1401 + (i*4);

		st_io.o_distribute_rbt_top_vacuum[i]							= 1408 + (i*4);
		st_io.o_distribute_rbt_top_eject[i]								= 1409 + (i*4);
		st_io.o_distribute_rbt_btm_vacuum[i]							= 1410 + (i*4);
		st_io.o_distribute_rbt_btm_eject[i]								= 1411 + (i*4);
		

		st_io.i_distribute_rbt_top_vacuum_bwd_chk[i]					= 1500 + (i*5);
		st_io.i_distribute_rbt_btm_vacuum_bwd_chk[i]					= 1501 + (i*5);
		st_io.i_distribute_rbt_top_vacuum_chk[i]						= 1503 + (i*5);
		st_io.i_distribute_rbt_btm_vacuum_chk[i]						= 1504 + (i*5);
	}

	st_io.i_distribute_rbt_left_remove_detect_sensor_chk				= 1511;
	st_io.i_distribute_rbt_right_remove_detect_sensor_chk				= 1512;

	
	st_io.o_reject_rbt_updown											= 1600;
	st_io.o_reject_rbt_vacuum											= 1601;
	st_io.o_reject_rbt_eject											= 1602;

	st_io.o_density_vision_trigger_onoff								= 1604;
	st_io.o_distribute_vision_trigger_onoff								= 1605;
	st_io.o_top_vision_trigger_onoff									= 1606;
	st_io.o_btm_vision_trigger_onoff									= 1607;

	st_io.i_reject_rbt_up_chk											= 1608;
	st_io.i_reject_rbt_down_chk											= 1609;
	st_io.i_reject_rbt_vacuum_chk										= 1610;
	st_io.i_reject_cv_full_chk											= 1611;
	st_io.i_reject_cv_1step_pos_chk										= 1612;
	st_io.i_reject_cv_full_pos_chk										= 1613;

	st_io.o_uld_rbt_left_updown											= 1700;
	st_io.o_uld_rbt_left_vacuum											= 1701;
	st_io.o_uld_rbt_right_updown										= 1702;
	st_io.o_uld_rbt_right_vacuum										= 1703;
	st_io.o_uld_rbt_left_eject											= 1704;
	st_io.o_uld_rbt_right_eject											= 1705;

	st_io.i_uld_rbt_left_up_chk											= 1708;
	st_io.i_uld_rbt_left_down_chk										= 1709;
	st_io.i_uld_rbt_left_vacuum_chk										= 1710;
	st_io.i_uld_rbt_right_up_chk										= 1711;
	st_io.i_uld_rbt_right_down_chk										= 1712;
	st_io.i_uld_rbt_right_vacuum_chk									= 1713;

	for ( i = 0;i < 2; i++)
	{
		st_io.o_uld_rbt_picker[i]										= 1700 + (i*2);
		st_io.o_uld_rbt_vacuum[i]										= 1701 + (i*2);
		st_io.i_uld_rbt_pickerup_chk[i]									= 1708 + (i*3);
		st_io.i_uld_rbt_pickerdn_chk[i]									= 1709 + (i*3);
		st_io.i_uld_rbt_vacuum_chk[i]									= 1710 + (i*3);
		st_io.o_uld_rbt_eject[i]										= 1704 + i;
	}

	
	st_io.o_out_rear_cv_motor_onoff										= 2000;
	st_io.o_out_mute_on_lamp											= 2001;
	st_io.o_out_mute_off_lamp											= 2002;

	st_io.i_uld_cv_left_box_chk											= 2004;
	st_io.i_uld_cv_right_box_chk										= 2005;
	st_io.i_uld_cv_box_out_chk											= 2006;
    st_io.i_uld_cv_box_full_chk											= 2007;

	st_io.i_out_cv_box1_chk												= 2008;
	st_io.i_out_cv_box2_chk												= 2009;
	st_io.i_out_cv_box3_chk												= 2010;
	st_io.i_out_cv_box4_chk												= 2011;
	
	st_io.i_out_mute_on_check											= 2012;
	st_io.i_out_mute_off_check											= 2013;
	st_io.i_out_area													= 2014;

	for( i = 0; i < 4; i++)
	{
		st_io.i_uld_cv_box[i]											= 2004 + i;
		st_io.i_out_cv_box[i]											= 2008 + i;
	}

	st_io.o_top_idbuffer_ld1_shifter_hook_fwd							= 2100;
	st_io.o_top_idbuffer_ld1_shifter_hook_bwd							= 2101;
	st_io.o_top_idbuffer_ld1_shifter_hook_clamp							= 2102;
	st_io.o_top_idbuffer_ld1_shifter_hook_unclamp						= 2103;
	st_io.o_top_idbuffer_ld2_shifter_left_hook_clamp					= 2104;
	st_io.o_top_idbuffer_ld2_shifter_left_hook_unclamp					= 2105;
	st_io.o_top_idbuffer_ld2_shifter_right_hook_clamp					= 2106;
	st_io.o_top_idbuffer_ld2_shifter_right_hook_unclamp					= 2107;
	st_io.i_top_idbuffer_ld1_shifter_hook_fwd_chk						= 2108;
	st_io.i_top_idbuffer_ld1_shifter_hook_bwd_chk						= 2109;
	st_io.i_top_idbuffer_ld1_shifter_hook_clamp_chk						= 2110;
	st_io.i_top_idbuffer_ld1_shifter_hook_unclamp_chk					= 2111;
	st_io.i_top_idbuffer_ld2_shifter_left_hook_clamp_chk				= 2112;
	st_io.i_top_idbuffer_ld2_shifter_left_hook_unclamp_chk				= 2113;
	st_io.i_top_idbuffer_ld2_shifter_right_hook_clamp_chk				= 2114;
	st_io.i_top_idbuffer_ld2_shifter_right_hook_unclamp_chk				= 2115;


	st_io.o_top_idbuffer_ld2_shifter_hook_fwd							= 2200;
	st_io.o_top_idbuffer_ld2_shifter_hook_bwd							= 2201;
	st_io.o_top_idbuffer12_clamp										= 2202;
	st_io.o_top_idbuffer12_unclamp										= 2203;
	st_io.o_top_idbuffer34_clamp										= 2204;
	st_io.o_top_idbuffer34_unclamp										= 2205;
	st_io.o_top_idbuffer56_clamp										= 2206;
	st_io.o_top_idbuffer56_unclamp										= 2207;
	st_io.o_top_idbuffer78_clamp										= 2208;
	st_io.o_top_idbuffer78_unclamp										= 2209;

	st_io.i_top_idbuffer_ld2_shifter_hook_fwd_chk						= 2300;
	st_io.i_top_idbuffer_ld2_shifter_hook_bwd_chk						= 2301;
	st_io.i_top_idbuffer12_clamp_chk									= 2302;
	st_io.i_top_idbuffer12_unclamp_chk									= 2303;
	st_io.i_top_idbuffer1_chk											= 2304;
	st_io.i_top_idbuffer2_chk											= 2305;
	st_io.i_top_idbuffer_box1_chk										= 2306;
	st_io.i_top_idbuffer_box2_chk										= 2307;
	st_io.i_top_idbuffer34_clamp_chk									= 2308;
	st_io.i_top_idbuffer34_unclamp_chk									= 2309;
	st_io.i_top_idbuffer3_chk											= 2310;
	st_io.i_top_idbuffer4_chk											= 2311;
	st_io.i_top_idbuffer_box3_chk										= 2312;
	st_io.i_top_idbuffer_box4_chk										= 2313;
	
	st_io.i_top_idbuffer_shifter_hook_fwd[0]							= 2108;
	st_io.i_top_idbuffer_shifter_hook_bwd[0]							= 2109;
	st_io.i_top_idbuffer_shifter_hook_fwd[1]							= 2300;
	st_io.i_top_idbuffer_shifter_hook_bwd[1]							= 2301;


	st_io.i_top_idbuffer56_clamp_chk									= 2400;
	st_io.i_top_idbuffer56_unclamp_chk									= 2401;
	st_io.i_top_idbuffer5_chk											= 2402;
	st_io.i_top_idbuffer6_chk											= 2403;
	st_io.i_top_idbuffer_box5_chk										= 2404;
	st_io.i_top_idbuffer_box6_chk										= 2405;
	st_io.i_top_idbuffer78_clamp_chk									= 2406;
	st_io.i_top_idbuffer78_unclamp_chk									= 2407;
	st_io.i_top_idbuffer7_chk											= 2408;
	st_io.i_top_idbuffer8_chk											= 2409;
	st_io.i_top_idbuffer_box7_chk										= 2410;
	st_io.i_top_idbuffer_box8_chk										= 2411;

	st_io.o_rolling_pusher_fwdback_left									= 2500;
	st_io.o_rolling_pusher_fwdback_right								= 2501;
	st_io.o_top_box_supportup_clamp										= 2502;
	st_io.o_top_box_supportdn_clamp										= 2503;

	st_io.o_top_box_up_clamp											= 2502;
	st_io.o_top_box_dn_clamp											= 2503;

	st_io.i_rolling1_pusher_left_fwd_chk								= 2508;
	st_io.i_rolling1_pusher_left_back_chk								= 2509;
	st_io.i_rolling1_pusher_right_fwd_chk								= 2510;
	st_io.i_rolling1_pusher_right_back_chk								= 2511;
	st_io.i_top_box_supportup_chk										= 2512;
	st_io.i_top_box_supportdn_chk										= 2513;

	st_io.i_top_box_up_clamp_chk										= 2512;
	st_io.i_top_box_dn_clamp_chk										= 2513;

	
	for ( i = 0; i<2; i++ )
	{
		st_io.o_rolling_push_fwdback[i]									= 2500 + i;
		st_io.i_rolling_push_fwd_chk[i]									= 2508 + (i*2);
		st_io.i_rolling_push_bwd_chk[i]									= 2509 + (i*2);
	}

	for ( i = 0; i < 2; i++ )
	{
		st_io.o_top_idbuffer_shifter_hook_fwd[i]						= 2100 + (i*100);
		st_io.o_top_idbuffer_shifter_hook_bwd[i]						= 2101 + (i*100);
	}
	
	for ( i = 0; i < HOOKCLAMP_CNT; i++)
	{
		st_io.o_top_idbuffer_shifter_hook_clamp[i]						= 2102 + (i*2);
		st_io.o_top_idbuffer_shifter_hook_unclamp[i]					= 2103 + (i*2);
		st_io.i_top_idbuffer_shifter_hook_clamp[i]						= 2110 + (i*2);
		st_io.i_top_idbuffer_shifter_hook_unclamp[i]					= 2111 + (i*2);
	}
	
	for ( i = 0; i < 4; i++)
	{
		st_io.o_top_idbuffer_clamp[i]									= 2202 + (i*2);
		st_io.o_top_idbuffer_unclamp[i]									= 2203 + (i*2);
	}
	for ( i = 0; i < 2; i++)
	{
		st_io.i_top_idbuffer_clamp[i]									= 2302 + (i*6);
		st_io.i_top_idbuffer_unclamp[i]									= 2303 + (i*6);
		st_io.i_top_idbuffer_chk[i][0]									= 2304 + (i*6);
		st_io.i_top_idbuffer_chk[i][1]									= 2305 + (i*6);
		st_io.i_top_idbuffer_box[i][0]									= 2306 + (i*6);
		st_io.i_top_idbuffer_box[i][1]									= 2307 + (i*6);
	}
	for ( i = 2; i < 4; i++)
	{
		st_io.i_top_idbuffer_clamp[i]									= 2400 + ((i-2)*6);
		st_io.i_top_idbuffer_unclamp[i]									= 2401 + ((i-2)*6);
		st_io.i_top_idbuffer_chk[i][0]									= 2402 + ((i-2)*6);
		st_io.i_top_idbuffer_chk[i][1]									= 2403 + ((i-2)*6);
		st_io.i_top_idbuffer_box[i][0]									= 2404 + ((i-2)*6);
		st_io.i_top_idbuffer_box[i][1]									= 2405 + ((i-2)*6);
	}




	st_io.o_idbuffer_elv_hook_clamp										= 2600;
	st_io.o_idbuffer_elv_hook_unclamp									= 2601;
	st_io.o_idbuffer_elv_pusher_fwd										= 2602;
	st_io.o_idbuffer_elv_pusher_bwd										= 2603;


	st_io.i_idbuffer_elv_hook_clamp_chk									= 2608;
	st_io.i_idbuffer_elv_hook_unclamp_chk								= 2609;
	st_io.i_idbuffer_elv_idbuffer1_chk									= 2610;
	st_io.i_idbuffer_elv_idbuffer2_chk									= 2611;
	st_io.i_idbuffer_elv_box1_chk										= 2612;
	st_io.i_idbuffer_elv_box2_chk										= 2613;
	st_io.i_idbuffer_elv_pusher_fwd_chk									= 2614;
	st_io.i_idbuffer_elv_pusher_bwd_chk									= 2615;

	st_io.o_btm_idbuffer_uld1_shifter_hook_fwd							= 2700;
	st_io.o_btm_idbuffer_uld1_shifter_hook_back							= 2701;
	st_io.o_btm_idbuffer12_clamp										= 2702;
	st_io.o_btm_idbuffer12_unclamp										= 2703;
	st_io.o_btm_idbuffer_uld2_shifter_hook_fwd							= 2704;
	st_io.o_btm_idbuffer_uld2_shifter_hook_back							= 2705;
	st_io.i_btm_idbuffer_uld1_shifter_hook_fwd_chk						= 2706;
	st_io.i_btm_idbuffer_uld1_shifter_hook_back_chk						= 2707;
	////2014,1203
	st_io.i_btm_idbuffer_uld1_shifter_buffer1_chk						= 2708;
	st_io.i_btm_idbuffer_uld1_shifter_buffer2_chk						= 2709;
	////


	st_io.i_btm_idbuffer12_clamp_chk									= 2710;
	st_io.i_btm_idbuffer12_unclamp_chk									= 2711;
	st_io.i_btm_idbuffer1_chk											= 2712;
	st_io.i_btm_idbuffer2_chk											= 2713;
// 	st_io.i_top_right_box_supportup_chk									= 3314;
// 	st_io.i_top_right_box_supportdn_chk									= 3315;

//	st_io.i_btm_idbuffer_uld2_shifter_hook_fwd1							= 3312;
//	st_io.i_btm_idbuffer_uld2_shifter_hook_back1						= 3313;
//	st_io.i_btm_idbuffer_uld2_shifter_hook_fwd2							= 3314;
//	st_io.i_btm_idbuffer_uld2_shifter_hook_back2						= 3315;

	st_io.o_btm_idbuffer34_clamp										= 3000;
	st_io.o_btm_idbuffer34_unclamp										= 3001;
	st_io.o_btm_idbuffer_stopper_updown									= 3002;

	st_io.i_btm_idbuffer_uld2_shifter_hook_fwd1_chk						= 3004;
	st_io.i_btm_idbuffer_uld2_shifter_hook_back1_chk					= 3005;
	st_io.i_btm_idbuffer_uld2_shifter_hook_fwd2_chk						= 3006;
	st_io.i_btm_idbuffer_uld2_shifter_hook_back2_chk					= 3007;
	st_io.i_btm_idbuffer34_clamp_chk									= 3008;
	st_io.i_btm_idbuffer34_unclamp_chk									= 3009;
	st_io.i_btm_idbuffer3_chk											= 3010;
	st_io.i_btm_idbuffer4_chk											= 3011;
	st_io.i_btm_idbuffer_stopper_up_chk									= 3012;
	st_io.i_btm_idbuffer_stopper_down_chk								= 3013;
	st_io.i_btm_idbuffer_stopper_buffer_chk								= 3014;
	st_io.i_btm_idbuffer_8480_hook_in_chk								= 3015;

	st_io.i_btm_idbuffer_chk[0][0]										= 2712;
	st_io.i_btm_idbuffer_chk[0][1]										= 2713;
	st_io.i_btm_idbuffer_chk[1][0]										= 3010;
	st_io.i_btm_idbuffer_chk[1][1]										= 3011;
	for ( i = 0; i < 2; i++ )
	{
		st_io.o_btm_idbuffer_shifter_hook_fwd[i]						= 2700 + (i*4);
		st_io.o_btm_idbuffer_shifter_hook_bwd[i]						= 2701 + (i*4);


// 		st_io.i_top_box_up_clamp_chk[i]									= 3312 + (i*2);
// 		st_io.i_top_box_dn_clamp_chk[i]									= 3313 + (i*2);
	}
	st_io.i_btm_idbuffer_shifter_hook_fwd[0]							= 2706;
	st_io.i_btm_idbuffer_shifter_hook_bwd[0]							= 2707;
	for (i = 1; i < 3; i++)
	{
		st_io.i_btm_idbuffer_shifter_hook_fwd[i]						= 3004 + ((i-1)*2);
		st_io.i_btm_idbuffer_shifter_hook_bwd[i]						= 3005 + ((i-1)*2);
	}
	st_io.o_btm_idbuffer_clamp[0]										= 2702;
	st_io.o_btm_idbuffer_unclamp[0]										= 2703;
	st_io.o_btm_idbuffer_clamp[1]										= 3000;
	st_io.o_btm_idbuffer_unclamp[1]										= 3001;

//	st_io.i_btm_idbuffer_shifter_clamp									= 3306;
//	st_io.i_btm_idbuffer_shifter_unclamp								= 3307;
//	st_io.i_btm_idbuffer_shifter_clamp[1]								= 3312;
//	st_io.i_btm_idbuffer_shifter_unclamp[1]								= 3313;
//	st_io.i_btm_idbuffer_shifter_clamp[2]								= 3314;
//	st_io.i_btm_idbuffer_shifter_unclamp[2]								= 3315;

	st_io.i_btm_idbuffer_clamp[0]										= 2710;
	st_io.i_btm_idbuffer_unclamp[0]										= 2711;
	st_io.i_btm_idbuffer_clamp[1]										= 3008;
	st_io.i_btm_idbuffer_unclamp[1]										= 3009;



	st_io.i_top_idbuffer_exist_sensor_check[0] = st_io.i_top_idbuffer1_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[1] = st_io.i_top_idbuffer2_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[2] = st_io.i_top_idbuffer3_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[3] = st_io.i_top_idbuffer4_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[4] = st_io.i_top_idbuffer5_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[5] = st_io.i_top_idbuffer6_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[6] = st_io.i_top_idbuffer7_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[7] = st_io.i_top_idbuffer8_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[8] = st_io.i_idbuffer_elv_idbuffer1_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[9] = st_io.i_idbuffer_elv_idbuffer2_chk;
				
	st_io.i_top_idbuffer_exist_sensor_check[10] = st_io.i_top_idbuffer_box1_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[11] = st_io.i_top_idbuffer_box2_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[12] = st_io.i_top_idbuffer_box3_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[13] = st_io.i_top_idbuffer_box4_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[14] = st_io.i_top_idbuffer_box5_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[15] = st_io.i_top_idbuffer_box6_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[16] = st_io.i_top_idbuffer_box7_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[17] = st_io.i_top_idbuffer_box8_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[18] = st_io.i_idbuffer_elv_box1_chk;				
	st_io.i_top_idbuffer_exist_sensor_check[19] = st_io.i_idbuffer_elv_box2_chk;	

	st_io.i_btm_idbuffer_exist_sensor_check[0] = st_io.i_btm_idbuffer1_chk;
	st_io.i_btm_idbuffer_exist_sensor_check[1] = st_io.i_btm_idbuffer2_chk;
	st_io.i_btm_idbuffer_exist_sensor_check[2] = st_io.i_btm_idbuffer3_chk;
	st_io.i_btm_idbuffer_exist_sensor_check[3] = st_io.i_btm_idbuffer4_chk;

	//2014,1205
	st_io.i_btm_idbuffer_exist_sensor_check[4] = st_io.i_btm_idbuffer_uld1_shifter_buffer1_chk;
	st_io.i_btm_idbuffer_exist_sensor_check[5] = st_io.i_btm_idbuffer_uld1_shifter_buffer2_chk;



	//S'Y  : TL & DOOR
	st_io.o_start_switch_lamp											= 3100;									
	st_io.o_stop_switch_lamp											= 3101;										
	st_io.o_alarm_clear_lamp											= 3102;										
	st_io.o_buzzer_off_lamp												= 3103;										
	st_io.o_reject_cv_motor_onoff										= 3104;
	st_io.o_uld_cv_motor_onoff											= 3105;

	st_io.i_start_switch_chk											= 3108;										
	st_io.i_stop_switch_chk												= 3109;										
	st_io.i_alarm_clear_switch_chk										= 3110;								
	st_io.i_buzzer_switch_chk											= 3111;									
	////2014,1203
	st_io.i_auto_mode_switch_chk										= 3112;									
	st_io.i_manual_mode_switch_chk										= 3113;								
	////
	st_io.i_front_select_switch_chk										= 3114;								
	st_io.i_rear_select_switch_chk										= 3115;								

	//st_io.o_switch_lamp[4];

	//S'Y  : MC & EMO
	st_io.o_main_air													= 3200;												
	st_io.o_towerlamp_green												= 3201;										
	st_io.o_towerlamp_yellow											= 3202;										
	st_io.o_towerlamp_red												= 3203;										
	st_io.o_buzzer_1													= 3204;												
	st_io.o_buzzer_2													= 3205;												
	st_io.o_buzzer_3													= 3206;
	st_io.o_door_lock													= 3207;											
	st_io.i_main_air_chk												= 3208;											
	
	st_io.i_mc1_chk														= 3211;												
	st_io.i_emo_1_chk													= 3212;											
	st_io.i_emo_2_chk													= 3213;											
	st_io.i_emo_3_chk													= 3214;											
	st_io.i_emo_4_chk													= 3215;											

	st_io.i_door1_chk													= 3300;											
	st_io.i_door2_chk													= 3301;											
	st_io.i_door3_chk													= 3302;											
	st_io.i_door4_chk													= 3303;											
	st_io.i_door5_chk													= 3304;											
	st_io.i_door6_chk													= 3305;											
	st_io.i_door7_chk													= 3306;											
	st_io.i_door8_chk													= 3307;											
	st_io.i_door9_chk													= 3308;									
	st_io.i_door10_chk													= 3309;									
	st_io.i_recycle_zone_door_chk										= 3310;//2014,1203

	st_io.i_bottom_door1												= 3312;
	st_io.i_bottom_door2												= 3313;
	st_io.i_bottom_door3												= 3314;
	st_io.i_bottom_door4												= 3315;

	for ( i = 0; i < 3; i++ )
	{
		st_io.o_buzzer[i] = st_io.o_buzzer_1 + i;
	}
	for ( i = 0; i < 10; i++ )
	{
		st_io.i_door_chk[i]	= st_io.i_door1_chk + i;
	}
	for ( i = 0; i < 4; i++ )
	{
		st_io.i_emo_chk[i] = st_io.i_emo_1_chk + i;
	}

	//ASS'Y  : MC/EMO/SMEMA
	st_io.o_front_top_machine_enter_signal								= 3400;						
	st_io.o_front_top_machine_transfer_signal							= 3401;					
	st_io.o_front_btm_machine_ready_signal								= 3402;						
	st_io.o_front_btm_machine_stop_signal								= 3403;	
	st_io.o_rear_ready_signal											= 3404;
	st_io.o_rear_enter_signal											= 3405;

	st_io.i_front_top_machine_ready_signal_chk							= 3408;					
	st_io.i_front_top_machine_stop_signal_chk							= 3409;					
	st_io.i_front_btm_machine_request_signal_chk						= 3410;					
	st_io.i_front_btm_machine_transfer_signal_chk						= 3411;				
	st_io.i_rear_req_signal_chk											= 3412;				
	st_io.i_rear_transfer_signal_chk									= 3413;				

}

int IO_Manager::IO_Board_Initialize()
{
	INT HSSI_speed = 0;
	int Ret = 0;
	INT pMasterNo;
	
	if( !st_handler.mn_virtual_mode &&
		FAS_IO.Set_IO_BoardOpen(&pMasterNo, START_NOTHING) != STATUS_SUCCESS )
		return FALSE;
	
	if( IO_Port_AutoEnable( 0, 0 ) == FALSE )		return FALSE;
	if( IO_Port_AutoEnable( 0, 1 ) == FALSE )		return FALSE;
	if( IO_Port_AutoEnable( 0, 2 ) == FALSE )		return FALSE;
	if( IO_Port_AutoEnable( 0, 3 ) == FALSE )		return FALSE;
// 	if( IO_Port_AutoEnable( 1, 0 ) == FALSE )		return FALSE;
	
	
	if( IO_SlaveEnable( 0, 0, 8, TRUE ) == FALSE )	return FALSE;
	if( IO_SlaveEnable( 0, 1, 8, TRUE ) == FALSE )	return FALSE;
	if( IO_SlaveEnable( 0, 2, 8, TRUE ) == FALSE )	return FALSE;
	if( IO_SlaveEnable( 0, 3, 8, TRUE ) == FALSE )	return FALSE;
	
	
// 	if( IO_SlaveEnable( 1, 0, 8, TRUE ) == FALSE )  return FALSE;
	////
	
	for (int i = 0; i < 4; i++)
	{
		Ret = FAS_IO.Set_IO_HSSISpeed(0, i, PORT_SPEED_10);
		Ret = FAS_IO.Get_IO_HSSISpeed(0, i, &HSSI_speed);
	}
// 	Ret = FAS_IO.Set_IO_HSSISpeed(1, 0, PORT_SPEED_10);
// 	Ret = FAS_IO.Get_IO_HSSISpeed(1, 0, &HSSI_speed);
// 
	
	FAS_IO.Set_IO_DefineWord(0, 0, 0, 0x00ff); // 0번 Master, 0번 포트, 0번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 1, 0x00ff); // 0번 Master, 0번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 2, 0x0000); // 0번 Master, 0번 포트, 2번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 3, 0xffff); // 0번 Master, 0번 포트, 3번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 4, 0x00ff); // 0번 Master, 0번 포트, 4번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 5, 0x0000); // 0번 Master, 0번 포트, 5번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 6, 0x00ff); // 0번 Master, 0번 포트, 6번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 0, 7, 0x00ff); // 0번 Master, 0번 포트, 7번 슬레이브 , 16bit 셋팅
	
	FAS_IO.Set_IO_DefineWord(0, 1, 0, 0x000f); // 0번 Master, 1번 포트, 0번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 1, 1, 0x000f); // 0번 Master, 1번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 1, 2, 0x00ff); // 0번 Master, 1번 포트, 2번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 1, 3, 0x003f); // 0번 Master, 1번 포트, 3번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 1, 4, 0xffff); // 0번 Master, 1번 포트, 4번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 1, 5, 0x0000); // 0번 Master, 1번 포트, 5번 슬레이브 , 16bit 셋팅 //2014,1203 0x0000 - > 0xf000 
	FAS_IO.Set_IO_DefineWord(0, 1, 6, 0x00ff); // 0번 Master, 1번 포트, 6번 슬레이브 , 16bit 셋팅 //2014,1203 0x0000 - > 0xf000 
	FAS_IO.Set_IO_DefineWord(0, 1, 7, 0x00ff); // 0번 Master, 1번 포트, 7번 슬레이브 , 16bit 셋팅
	
	FAS_IO.Set_IO_DefineWord(0, 2, 0, 0x000f); // 0번 Master, 2번 포트, 0번 슬레이브 , 16bit 셋팅 //2014,1203 0x0000 - > 0xf000
	FAS_IO.Set_IO_DefineWord(0, 2, 1, 0x00ff); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅 //2014,1203 0x0000 - > 0xf000 
	FAS_IO.Set_IO_DefineWord(0, 2, 2, 0xffff); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 2, 3, 0x0000); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 2, 4, 0x0000); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 2, 5, 0x00ff); // 0번 Master, 1번 포트, 5번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 2, 6, 0x00ff); // 0번 Master, 1번 포트, 6번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 2, 7, 0x003f); // 0번 Master, 1번 포트, 7번 슬레이브 , 16bit 셋팅

	FAS_IO.Set_IO_DefineWord(0, 3, 0, 0x000f); // 0번 Master, 2번 포트, 0번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 3, 1, 0x00ff); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 3, 2, 0x00ff); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 3, 3, 0x0000); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅
	FAS_IO.Set_IO_DefineWord(0, 3, 4, 0x00ff); // 0번 Master, 2번 포트, 1번 슬레이브 , 16bit 셋팅

// 	FAS_IO.Set_IO_DefineWord(1, 0, 0, 0x00ff); // 0번 Master, 2번 포트, 0번 슬레이브 , 16bit 셋팅
	SetIOBoardInit( true );
	
	return TRUE;
}

void IO_Manager::OnSet_IO_Out_Port_Clear()
{
	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_buzzer_2, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_buzzer_3, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_alarm_clear_lamp, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_buzzer_off_lamp, IO_OFF);

	
	g_ioMgr.set_out_bit(st_io.o_main_air, IO_ON);
	
	if (g_ioMgr.Get_In_Bit(st_io.i_main_air_chk) != IO_ON)
	{
		g_ioMgr.set_out_bit(st_io.o_main_air, IO_OFF);
		
		Sleep(300);
		
		g_ioMgr.set_out_bit(st_io.o_main_air, IO_ON);
	}
	g_ioMgr.Set_Out_Bit(st_io.o_uld_cv_motor_onoff, IO_OFF);

	//smema
	g_ioMgr.set_out_bit(st_io.o_front_top_machine_enter_signal, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_front_top_machine_transfer_signal, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_front_btm_machine_ready_signal, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_front_btm_machine_stop_signal, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_rear_ready_signal, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_rear_enter_signal, IO_OFF);
}


int IO_Manager::IO_Port_AutoEnable( int iMasterID, int iPortNo )
{
	int nRtn = Set_IO_PortAutoEnable(iMasterID, iPortNo);
	if ( nRtn != CTL_YES)
	{
		if (st_handler.cwnd_list != NULL)  // 리스트 바 화면 존재
		{
			sprintf(st_msg.c_abnormal_msg, "%d Port, not enable", iPortNo);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
		}

		SetIOBoardInit( false );
		return FALSE;
	}

	return TRUE;
}

int IO_Manager::IO_SlaveEnable(int nMasterID, int nPortNo, int nSlaveCnt, BOOL bEnable)
{
	int nFailCnt = 0;
	for (int i = 0; i < nSlaveCnt; i++)
	{
		int nRet = Set_IO_SlaveEnable( nMasterID, nPortNo, i, bEnable);
		
		if (nRet != CTL_YES)
		{
			if (st_handler.cwnd_list != NULL)  // 리스트 바 화면 존재
			{
				sprintf(st_msg.c_abnormal_msg, "Slave #%d, not enable", i);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
			}
			i = -1;
			
			if (nFailCnt < 3)
			{
				nFailCnt++;
			}
			else
			{
				SetIOBoardInit( false );
				return FALSE;
			}
			continue;
		}
		
		if (st_handler.cwnd_list != NULL)  // 리스트 바 화면 존재
		{
			sprintf(st_msg.c_normal_msg, "Slave #%d, enable success", i);
			st_handler.cwnd_list->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // 동작 성공 출력 요청
		}
		Sleep(100);
	}

	return TRUE;
}

void IO_Manager::set_out_reverse( int nIONo )
{
	BOOL bOn = get_out_bit( nIONo, IO_ON );

	if( bOn == IO_ON )
	{
//		if( nIONo == st_io.o_bin_stacker1_rail_guide_fwdbwd &&
//			g_ioMgr.get_in_bit( st_io.i_bin_stacker1_tray_chk ) == IO_ON )
//		{
//			if ( g_local.GetLocalType() == LOCAL_ENG )//20131029
//			{
//				DoModal_Msg( "Tray Check." );
//			}
//			else
//			{
//				DoModal_Msg( "트레이가 있습니다." );
//			}
//			return;
//		}
//		else if( nIONo == st_io.o_bin_stacker2_rail_guide_fwdbwd &&
//			g_ioMgr.get_in_bit( st_io.i_bin_stacker2_tray_chk ) == IO_ON )
//		{
//			if ( g_local.GetLocalType() == LOCAL_ENG )//20131029
//			{
//				DoModal_Msg( "Tray Check." );
//			}
//			else
//			{
//				DoModal_Msg( "트레이가 있습니다." );
//			}
//			return;
//		}
//		else if( nIONo == st_io.o_bin_stacker3_rail_guide_fwdbwd &&
//			g_ioMgr.get_in_bit( st_io.i_bin_stacker3_tray_chk ) == IO_ON )
//		{
//			if ( g_local.GetLocalType() == LOCAL_ENG )//20131029
//			{
//				DoModal_Msg( "Tray Check." );
//			}
//			else
//			{
//				DoModal_Msg( "트레이가 있습니다." );
//			}
//			return;
//		}
	}
	
	set_out_bit( nIONo, !bOn );
}

void IO_Manager::set_out_reverse( int nFwd, int nBwd )
{
	BOOL bFwd = get_out_bit( nFwd, IO_ON );
	BOOL bBwd = get_out_bit( nBwd, IO_ON );

	if( bFwd && !bBwd )
	{
		set_out_bit( nFwd, IO_OFF );
		set_out_bit( nBwd, IO_ON );
	}
	else
	{
		set_out_bit( nFwd, IO_ON );
		set_out_bit( nBwd, IO_OFF );
	}
}
