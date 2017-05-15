// Run_Smema_Ctl.h: interface for the CRun_Smema_Ctl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUN_SMEMA_CTL_H__C8AA743E_82B4_4C7D_8EE1_E9C32D9B2B1F__INCLUDED_)
#define AFX_RUN_SMEMA_CTL_H__C8AA743E_82B4_4C7D_8EE1_E9C32D9B2B1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRun_Smema_Ctl  
{
public:
	int mn_top_run_step;
	int mn_btm_run_step;

	int mn_network_limit_time;
	int mn_smema_max_retry_num;
	int mn_smema_netwotk_retry[5]; //2014.1107
	DWORD dw_smema_network_retry_waittime[5][3];
	///////////////////////////////////////////
	
	int mn_retry_cnt;

	
	char mc_jamcode[10];
	int  mn_smema_io_onoff_flag[10]; //2012.0815 4���� smema ����� �����Ѵ� 
	long ml_smema_io_onoff_wait[10][3]; //2012.0815 4���� smema ����� ��


	int top_idbuffer_datainfo_shift(int n_mde, int n_shift_site);
	int top_idbuffer_sensor_flag_status_check(int n_mode, int n_check_site); //������ �÷��װ� Ʋ���� ���� 

	int btm_idbuffer_datainfo_shift(int n_mode, int n_shift_site);


	void smema_process_top_8580(int n_mode);

	CRun_Smema_Ctl();
	virtual ~CRun_Smema_Ctl();

};
extern CRun_Smema_Ctl  Run_Smema_Ctl;

#endif // !defined(AFX_RUN_SMEMA_CTL_H__C8AA743E_82B4_4C7D_8EE1_E9C32D9B2B1F__INCLUDED_)
