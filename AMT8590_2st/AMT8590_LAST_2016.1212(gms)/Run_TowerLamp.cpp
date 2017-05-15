// Run_TowerLamp.cpp: implementation of the CRun_TowerLamp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Handler.h"
#include "Run_TowerLamp.h"

#include "Variable.h"				// ���� ���� ���� Class
#include "Public_Function.h"		// Motor �� Cylinder ���� Class
#include "FastechPublic_IO.h"

#include "SrcPart/APartDatabase.h"
#include "ComizoaPublic.h"
#include "SrcPart/APartTray.h"
#include "SrcPart/APartTestSite.h"
#include "AMTLotManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRun_TowerLamp Run_TowerLamp;
CRun_TowerLamp Run_TowerLamp_Manual;

CRun_TowerLamp::CRun_TowerLamp()
{
	MoveStep = 0;
	mn_lamp_step = 0;
	mn_pcb_exist_check = CTL_NO;
}

CRun_TowerLamp::~CRun_TowerLamp()
{

}

void CRun_TowerLamp::Thread_Run()
{
	Run_Move();
}

void CRun_TowerLamp::Run_Move()
{
	int Ret = 0;
	int i = 0, j = 0, k = 0;
	int x = 0, y = 0;

	// **************************************************************************
    // ���� ��µ� ȭ���� I/O ����͸� ȭ������ �˻��Ѵ�                         
	// -> I/O ����� �� Ÿ�� ������ ��� ��µǾ� I/O ���� Ȯ���� ����� ����    
	// -> dSTOP(0)    dRUN(1)    dJAM(2)    dLOTEND(3)   dINIT(4)    dWARNING(5) 
	// -> dLOCK(6)    dSELFCHECK(7)												 
    // **************************************************************************
	if (st_handler.mn_menu_num == 701)  return;
	// **************************************************************************

	if (COMI.mn_run_status == dJAM || COMI.mn_run_status == dWARNING)
	{
	   g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_ON);
	   g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);
	}

	if (COMI.mn_run_status == dINIT)
	{
		switch(mn_lamp_step)
		{
		case 0 :
			// ************************************************************************
			//  RED Ÿ�� ���� ��� �����Ѵ�												
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
			g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_ON);
			// ************************************************************************
			// ************************************************************************
			//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			//  GREEN Ÿ�� ���� ��� �����Ѵ�													
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_alarm_clear_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
			// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
			// ************************************************************************
			ml_lamp_time[0] = GetCurrentTime();
			mn_lamp_step++;
			// ************************************************************************
			break;
		case 1 :
			// ************************************************************************
			// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
			// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
			// ************************************************************************
			ml_lamp_time[1] = GetCurrentTime();
			if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
				mn_lamp_step++;
			else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
			{
				ml_lamp_time[0] = GetCurrentTime();
			}
			// ************************************************************************
			break;
		case 2 :
			// ************************************************************************
			//  RED Ÿ�� ���� ��� �����Ѵ�												
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
			g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_ON);
			// ************************************************************************
			// ************************************************************************
			//  GREEN Ÿ�� ���� ��� �����Ѵ�													
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_alarm_clear_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
			// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
			// ************************************************************************
			ml_lamp_time[0] = GetCurrentTime();
			mn_lamp_step++;
			// ************************************************************************
			break;
		case 3 :
			// ************************************************************************
			// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
			// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
			// ************************************************************************
			ml_lamp_time[1] = GetCurrentTime();
			if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
				mn_lamp_step++;
			else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
			{
				ml_lamp_time[0] = GetCurrentTime();
			}
			// ************************************************************************
			break;
		case 4:
			// ************************************************************************
			//  RED Ÿ�� ���� ��� �����Ѵ�												
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			//  GREEN Ÿ�� ���� ��� �����Ѵ�													
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
			g_ioMgr.set_out_bit(st_io.o_alarm_clear_lamp, IO_ON);
			// ************************************************************************
			// ************************************************************************
			// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
			// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
			// ************************************************************************
			ml_lamp_time[0] = GetCurrentTime();
			mn_lamp_step++;
			// ************************************************************************
			break;
		case 5:
			// ************************************************************************
			// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
			// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
			// ************************************************************************
			ml_lamp_time[1] = GetCurrentTime();
			if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
				mn_lamp_step++;
			else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
			{
				ml_lamp_time[0] = GetCurrentTime();
			}
			// ************************************************************************
			break;
		case 6 :
			// ************************************************************************
			//  RED Ÿ�� ���� ��� �����Ѵ�												
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
			g_ioMgr.set_out_bit(st_io.o_stop_switch_lamp, IO_ON);
			// ************************************************************************
			// ************************************************************************
			//  GREEN Ÿ�� ���� ��� �����Ѵ�													
			// ************************************************************************
			g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
			g_ioMgr.set_out_bit(st_io.o_alarm_clear_lamp, IO_OFF);
			// ************************************************************************
			// ************************************************************************
			// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
			// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
			// ************************************************************************
			ml_lamp_time[0] = GetCurrentTime();
			mn_lamp_step++;
			// ************************************************************************
			break;
		case 7 :
			// ************************************************************************
			// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
			// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
			// ************************************************************************
			ml_lamp_time[1] = GetCurrentTime();
			if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
				mn_lamp_step = 0;
			else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
			{
				ml_lamp_time[0] = GetCurrentTime();
			}
			// ************************************************************************
			break;
		}
	}
	else
	{
		if (st_handler.mn_reinstatement == CTL_YES)	// ���� �����̴�.
		{
			switch(mn_lamp_step)
			{
			case 0 :
				// ************************************************************************
				//  GREEN Ÿ�� ���� ��� �����Ѵ�													
				// ************************************************************************
				g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);	// GREEN Ÿ�� ���� ON
				// ************************************************************************

				g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_ON);		// Start Button ���� ON

				// ************************************************************************
				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
				// ************************************************************************
				ml_lamp_time[0] = GetCurrentTime();
				mn_lamp_step++;
				// ************************************************************************
				break;

			case 1 :
				// ************************************************************************
				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
				// ************************************************************************
				ml_lamp_time[1] = GetCurrentTime();
				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
					mn_lamp_step++;
				else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
				{
					ml_lamp_time[0] = GetCurrentTime();
				}
				// ************************************************************************
				break;
			
			case 2 :
				// ************************************************************************
				//  GREEN Ÿ�� ���� ��� �����Ѵ�											
				// ************************************************************************
				g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);	// GREEN Ÿ�� ���� OFF
				// ************************************************************************

				g_ioMgr.set_out_bit(st_io.o_start_switch_lamp, IO_OFF);			// Start Button ���� OFF

				// ************************************************************************
				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
				// ************************************************************************
				ml_lamp_time[0] = GetCurrentTime();
				mn_lamp_step++;
				// ************************************************************************
				break;

			case 3 :
				// ************************************************************************
				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
				// ************************************************************************
				ml_lamp_time[1] = GetCurrentTime();
				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
					mn_lamp_step = 0;
				else if ((ml_lamp_time[1] - ml_lamp_time[0]) < 0)
				{
					ml_lamp_time[0] = GetCurrentTime();
				}
				// ************************************************************************
				break;
			default:
				mn_lamp_step = 0;
				break;
			}
		}
		else
		{
			if (COMI.mn_run_status != dRUN)
			{
				st_work.mn_tl_status = COMI.mn_run_status;
			}
			else
			{
// 				k = 0;

// 				for (i = BT_REAR_BUFFER; i < BT_CUSTOMER_BUFFER; i++)
// 				{
// 					for (x = 0; x < 3; x++)
// 					{
// 						for (y = 0; y < 100; y++)
// 						{
// 							if (st_buffer_tray[i].nDeviceExistence[0][x][y] == CTL_YES)
// 							{
// 								k++;
// 								break;
// 							}
// 						}
// 					}
// 				}

// 				for( i=0; i<MAX_TRAY; i++ )
// 				{
// 					ATray tray = g_Tray.GetTray( i );
// 					if(	tray.GetPos() == TPOS_REJECT_TO_BIN ||
// 						tray.GetPos() == TPOS_BIN_TO_CONV3 ||
// 						tray.GetTargetPos() == TPOS_NEXT )
// 					{
// 						k++;
// 					}
// 					if( tray.GetPos() == TPOS_REJECT ||
// 						tray.GetPos() == TPOS_BIN1 ||
// 						tray.GetPos() == TPOS_BIN2 ||
// 						tray.GetPos() == TPOS_BIN3)
// 					{
// 						if( g_Tray.GetLoadModuleCnt() > 0 )
// 						{
// 							k++;
// 						}
// 					}
// 					if(k > 0)	break;
// 				}
// 				for( i=0; i<TSITE_SOCKET_CNT; i++ )
// 				{
// 					if(g_site.GetModule(i).IsExist())
// 					{
// 						k++;
// 					}
// 					if(k > 0)	break;
// 				}
// 				
// 				if (k > 0)			// PCB Existence ml_lamp_change_time
// 				{
// 					mn_pcb_exist_check = CTL_NO;
// 					st_work.mn_tl_status = COMI.mn_run_status;
// 				}
// 				else
// 				{
// 					if (mn_pcb_exist_check == CTL_NO)
// 					{
// 						mn_pcb_exist_check = CTL_READY;
// 						ml_lamp_change_time[0] = GetCurrentTime();	
// 					}
// 					else if (mn_pcb_exist_check == CTL_READY)
// 					{
// 						ml_lamp_change_time[1] = GetCurrentTime();
// 						ml_lamp_change_time[2] = ml_lamp_change_time[1] - ml_lamp_change_time[0];
// 						
// 						if (ml_lamp_change_time[2] > st_lamp.mn_lamp_change_time * 1000 * 60)
// 						{
// 							mn_pcb_exist_check = CTL_YES;
// 						}//2012,1220
// 						else if(ml_lamp_change_time[2] < 0)
// 						{
// 							ml_lamp_change_time[0] = GetCurrentTime();
// 						}
// 					}
// 					
// 					if (mn_pcb_exist_check == CTL_YES)
// 					{
// 						st_work.mn_tl_status = dSELFCHECK;
// 					}
// 					else
// 					{
// 						st_work.mn_tl_status = COMI.mn_run_status;
// 					}					
// 					
// 					if( st_timedb.mnTime_Section != st_timedb.mnSectionBuffer )
// 					{
// 						st_timedb.mnTime_Section	= st_timedb.mnSectionBuffer;
// 						st_timedb.mnSectionBuffer = st_work.mn_tl_status;
// 						st_timedb.mole_date		= COleDateTime::GetCurrentTime();
// 						
// 						g_db.DB_Write_Time(st_timedb);
// 					}
// 				}
			}
			
			if( st_handler.mn_chk_lotend == CTL_YES )
			{
				st_work.mn_tl_status = dLOTEND;
			}
			else if( g_lotMgr.GetLotCount() < 1  && COMI.mn_run_status != dRUN)
			{
				if(st_work.mn_tl_status != dSELFCHECK && st_work.mn_run_down == CTL_NO)
				{//2015.0513
					CString strLog;
					strLog.Format(" Run Down");
 					Func.On_LogFile_Add(LOG_EVENT, strLog, 1);
					st_work.mn_run_down = CTL_YES;
				}
				st_work.mn_tl_status = dSELFCHECK;
			}
			else
			{
				if( g_lotMgr.GetLotCount() < 1 )
				{
					if(st_work.mn_tl_status != dSELFCHECK && st_work.mn_run_down == CTL_NO)
					{//2015.0513
						CString strLog;
						strLog.Format(" Run Down");
 						Func.On_LogFile_Add(LOG_EVENT, strLog, 1);
						st_work.mn_run_down = CTL_YES;
					}
					st_work.mn_tl_status = dSELFCHECK;
				}
				else if( st_var.n_next_down == CTL_YES )//2015.0329
				{
					st_work.mn_tl_status = dSELFCHECK;
				}
				else
				{
					if(st_work.mn_run_down == CTL_YES)
					{	
						st_work.mn_run_down = CTL_NO;
						//2015.0513
						CString strLog;
						if(COMI.mn_run_status == dRUN)
						{
							strLog.Format(" Run, Labeller Auto Start");
							Func.On_LogFile_Add(LOG_EVENT, strLog, 1);
						}
					}
					st_work.mn_tl_status = COMI.mn_run_status;
				}
			}
			
			
			switch(mn_lamp_step)
			{
			case 0 :
				// ************************************************************************
				//  RED Ÿ�� ���� ��� �����Ѵ�												
				// ************************************************************************
				if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 1)       // RED Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
				else if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 0)  // RED Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
				else if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 2)  // RED Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
				// ************************************************************************

				// ************************************************************************
				//  GREEN Ÿ�� ���� ��� �����Ѵ�													
				// ************************************************************************
				if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 1)       // GREEN Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
				else if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 0)  // GREEN Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
				else if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 2)  // GREEN Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
				// ************************************************************************

				// ************************************************************************
				//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
				// ************************************************************************
				if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 1)       // YELLOW Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
				else if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 0)  // YELLOW Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
				else if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 2)  // YELLOW Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
				// ************************************************************************

				// ************************************************************************
				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
				// ************************************************************************
				ml_lamp_time[0] = GetCurrentTime();
				mn_lamp_step++;
				// ************************************************************************
				break;
			case 1 :
				// ************************************************************************
				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
				// ************************************************************************
				ml_lamp_time[1] = GetCurrentTime();
				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
					mn_lamp_step++;
				else if(ml_lamp_time[2] < 0)
				{
					ml_lamp_time[0] = GetCurrentTime();
				}
				// ************************************************************************
				break;
			case 2 :
				// ************************************************************************
				//  RED Ÿ�� ���� ��� �����Ѵ�												
				// ************************************************************************
				if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 1)       // RED Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
				else if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 0)  // RED Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
				else if (st_lamp.mn_lamp_r[st_work.mn_tl_status] == 2)  // RED Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
				// ************************************************************************

				// ************************************************************************
				//  GREEN Ÿ�� ���� ��� �����Ѵ�											
				// ************************************************************************
				if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 1)       // GREEN Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
				else if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 0)  // GREEN Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
				else if (st_lamp.mn_lamp_g[st_work.mn_tl_status] == 2)  // GREEN Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
				// ************************************************************************

				// ************************************************************************
				//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
				// ************************************************************************
				if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 1)       // YELLOW Ÿ�� ���� ON
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
				else if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 0)  // YELLOW Ÿ�� ���� OFF
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
				else if (st_lamp.mn_lamp_y[st_work.mn_tl_status] == 2)  // YELLOW Ÿ�� ���� FLICK
					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
				// ************************************************************************

				// ************************************************************************
				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
				// ************************************************************************
				ml_lamp_time[0] = GetCurrentTime();
				mn_lamp_step++;
				// ************************************************************************
				break;
			case 3 :
				// ************************************************************************
				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
				// ************************************************************************
				ml_lamp_time[1] = GetCurrentTime();
				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
					mn_lamp_step = 0;
				else if(ml_lamp_time[2] < 0)
				{
					ml_lamp_time[0] = GetCurrentTime();
				}
				// ************************************************************************
				break;
			default:
				mn_lamp_step = 0;
				break;
			}

			// Original
// 			switch(mn_lamp_step)
// 			{
// 			case 0 :
// 				// ************************************************************************
// 				//  RED Ÿ�� ���� ��� �����Ѵ�												
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 1)       // RED Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
// 				else if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 0)  // RED Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
// 				else if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 2)  // RED Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				//  GREEN Ÿ�� ���� ��� �����Ѵ�													
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 1)       // GREEN Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
// 				else if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 0)  // GREEN Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
// 				else if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 2)  // GREEN Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 1)       // YELLOW Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
// 				else if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 0)  // YELLOW Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
// 				else if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 2)  // YELLOW Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
// 				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
// 				// ************************************************************************
// 				ml_lamp_time[0] = GetCurrentTime();
// 				mn_lamp_step++;
// 				// ************************************************************************
// 				break;
// 			case 1 :
// 				// ************************************************************************
// 				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
// 				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
// 				// ************************************************************************
// 				ml_lamp_time[1] = GetCurrentTime();
// 				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
// 					mn_lamp_step++;
// 				// ************************************************************************
// 				break;
// 			case 2 :
// 				// ************************************************************************
// 				//  RED Ÿ�� ���� ��� �����Ѵ�												
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 1)       // RED Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_ON);
// 				else if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 0)  // RED Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
// 				else if (st_lamp.mn_lamp_r[st_work.mn_run_status] == 2)  // RED Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_red, IO_OFF);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				//  GREEN Ÿ�� ���� ��� �����Ѵ�											
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 1)       // GREEN Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_ON);
// 				else if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 0)  // GREEN Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
// 				else if (st_lamp.mn_lamp_g[st_work.mn_run_status] == 2)  // GREEN Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_green, IO_OFF);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				//  YELLOW Ÿ�� ���� ��� �����Ѵ�											
// 				// ************************************************************************
// 				if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 1)       // YELLOW Ÿ�� ���� ON
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_ON);
// 				else if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 0)  // YELLOW Ÿ�� ���� OFF
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
// 				else if (st_lamp.mn_lamp_y[st_work.mn_run_status] == 2)  // YELLOW Ÿ�� ���� FLICK
// 					g_ioMgr.set_out_bit(st_io.o_towerlamp_yellow, IO_OFF);
// 				// ************************************************************************
// 
// 				// ************************************************************************
// 				// Ÿ�� ���� ON/OFF ���� �����ϱ� ���Ͽ� ���� �ð� ��´�					
// 				// -> ȭ�� ���� �ð���ŭ ON/OFF �ð� �����Ѵ�								
// 				// ************************************************************************
// 				ml_lamp_time[0] = GetCurrentTime();
// 				mn_lamp_step++;
// 				// ************************************************************************
// 				break;
// 			case 3 :
// 				// ************************************************************************
// 				// ȭ�� ���� ���� ON/OFF �ð����� ����Ѵ�									
// 				// -> st_lamp.mn_lamp_wait_time : ���� ON/OFF ���� �ð� ���� ����			
// 				// ************************************************************************
// 				ml_lamp_time[1] = GetCurrentTime();
// 				if ((ml_lamp_time[1] - ml_lamp_time[0]) > st_lamp.mn_lamp_wait_time)
// 					mn_lamp_step = 0;
// 				// ************************************************************************
// 				break;
// 			default:
// 				mn_lamp_step = 0;
// 				break;
// 			}
		}
	}
}

void CRun_TowerLamp::Run_FormChange()
{
	switch (mn_form_step)
	{
	case 100:
		::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 9, 1);  // IO
		ml_form_time[0] = GetCurrentTime();
		mn_form_step = 200;
		break;

	case 200:
		ml_form_time[1] = GetCurrentTime();
		ml_form_time[2] = ml_form_time[1] - ml_form_time[0];

		if (ml_form_time[2] > 100)
		{
			mn_form_step = 300;
		}
		else if(ml_form_time[2] < 0)
		{
			ml_form_time[0] = GetCurrentTime();
		}
		break;

	case 300:
		::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 5, 1);  // XYZ
		ml_form_time[0] = GetCurrentTime();
		mn_form_step = 400;
		break;

	case 400:
		ml_form_time[1] = GetCurrentTime();
		ml_form_time[2] = ml_form_time[1] - ml_form_time[0];
		
		if (ml_form_time[2] > 100)
		{
			mn_form_step = 100;
		}
		else if(ml_form_time[2] < 0)
		{
			ml_form_time[0] = GetCurrentTime();
		}
		break;
	}
}
