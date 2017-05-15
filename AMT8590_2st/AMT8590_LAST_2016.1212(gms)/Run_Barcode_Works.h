#if !defined(AFX_RUN_BARCODE_WORKS_H__138F8A8D_A309_4E11_B8F5_73E60A28051C__INCLUDED_)
#define AFX_RUN_BARCODE_WORKS_H__138F8A8D_A309_4E11_B8F5_73E60A28051C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Run_Barcode_Works.h : header file
//
#include "SrcPart/APartRobot.h"

enum ENUM_BARCODE_ROBOT_INIT
{
	EBCRI_START,
	EBCRI_CHECK_ROBOT_CHK,
	EBCRI_HOMECHK_RBT1_Z1,
	EBCRI_HOMECHK_RBT1_Z2,
	EBCRI_HOMECHK_RBT2_Z1,
	EBCRI_HOMECHK_RBT2_Z2,

	EBCRI_TOP_VACUUM_BWD,
	EBCRI_TOP_VACUUM_BWD_CHK,
	EBCRI_BTM_VACUUM_BWD,
	EBCRI_BTM_VACUUM_BWD_CHK,
	
	EBCRI_VACUUM_ON,
	EBCRI_BARCODE_EMPTY_CHK,
	EBCRI_VACUUM_OFF,
	EBCRI_EJECT_ON,
	EBCRI_EJECT_OFF,

	EBCRI_M1_GUIDE_BWD,
	EBCRI_M1_GUIDE_BWD_CHK,
	EBCRI_M2_GUIDE_BWD,
	EBCRI_M2_GUIDE_BWD_CHK,

//	EBCRI_M1_GUIDE_UP,
//	EBCRI_M1_GUIDE_UP_CHK,
//	EBCRI_M2_GUIDE_UP,
//	EBCRI_M2_GUIDE_UP_CHK,

	
	EBCRI_HOMECHK_RBT1_R1,
	EBCRI_HOMECHK_RBT1_R2,
	EBCRI_HOMECHK_RBT2_R1,
	EBCRI_HOMECHK_RBT2_R2,

	
	EBCRI_HOMECHK_RBT1_X,
	EBCRI_HOMECHK_RBT1_Y,
	EBCRI_HOMECHK_RBT2_X,
	EBCRI_MOVE_SAFETY_RBT1_X,
	EBCRI_MOVE_SAFETY_RBT2_X,
	EBCRI_BOX_SAFETY,
	EBCRI_BOX_SAFETY_CHK,
	EBCRI_BOX_ROTATE,
	EBCRI_BOX_ROTATE_CHK,
	

	EBCRI_FINISH,
};

enum ENUM_BARCODE_ROBOT_RESTORE
{
	EBRR_START,
	EBRR_Z_SAFETY,
	EBRR_VACUUM1_CHK,
	EBRR_VACUUM2_CHK,
	EBRR_VACUUM_OFF,

	EBRR_BLOW_ON,
	EBRR_BLOW_OFF,
	EBRR_CYL_OFF,
	EBRR_CYL_OFF_CHK,
	EBRR_HOMECHK_RBT1_R1,
	EBRR_HOMECHK_RBT1_R2,
	EBRR_HOMECHK_RBT2_R1,
	EBRR_HOMECHK_RBT2_R2,

	EBRR_HOMECHK_RBT1_X,
	EBRR_HOMECHK_RBT2_X,
	
	EBRR_FINISH,
};

enum EPF//Enum picker feeder
{
	EPF_NONE = 0,
	EPF_PICK,
	EPF_PLACE
};


enum ENUM_STEP_ROBOT_PICKFEEDER
{
	ESRPF_PICKER_NONE,
	ESRPF_PICKER_READY,
	ESRPF_PICKER_READY_Z1,
	ESRPF_PICKER_READY_Z1_CHK,
	ESRPF_PICKER_READY_Z2,
	ESRPF_PICKER_READY_Z2_CHK,
	ESRPF_PICKER_READY_X,
	ESRPF_PICKER_READY_X_CHK,
	ESRPF_PICKER_READY_DOWN,
	ESRPF_PICKER_READY_DOWN_CHK,

	ESRPF_PICKER_PICK,
	ESRPF_PICKER_UP,
	ESRPF_PICKER_UP_CHK,
	ESRPF_PICKER_VISPOS,
	ESRPF_PICKER_DOWN,
	ESRPF_PICKER_DOWN_CHK,
	ESRPF_PICKER_UNLOAD_VISION,
	ESRPF_PICKER_VISCHK,//VISION
	ESRPF_PICKER_UNLOAD_WASTE,
	ESRPF_PICKER_UNLOAD,
	ESRPF_PICKER_UNLOAD_WASTE_PICKUP,
	ESRPF_PICKER_UNLOAD_WASTE_FINISH,
	ESRPF_PICKER_FINISH,

	ESRPF_PLACE_READY,
};

enum ENUM_BCR_VACUUM_SITE
{
	EBVS_LEFT = 0,
	EBVS_RIGHT,
};


/////////////////////////////////////////////////////////////////////////////
// CRun_Barcode_Works command target

class CRun_Barcode_Works : public CObject
{
public:
	DECLARE_SERIAL(CRun_Barcode_Works)
	CRun_Barcode_Works();           // protected constructor used by dynamic creation
	virtual ~CRun_Barcode_Works();

// Attributes
public:
	int		mn_InitStep;
	int		mn_RunStep;
	int		mn_RcvyStep1;
	int		mn_RcvyStep2;
	int		mn_RestoreStep;
	DWORD	m_dwTimeInit;
	DWORD	m_dwTime_Robot_1;
	DWORD	m_dwTime_Robot_2;
	DWORD	m_dwTime_Robot1;
	DWORD	m_dwTime_Robot2;
	DWORD	m_dwTime_Recvy[2];
	DWORD	m_dwTimeTact;

	int		mn_mot_flag[2][3];

	int		bcr1_step_old;
	int		bcr2_step_old;

	int     mn_retry_cnt;//2015.0218
	int		mn_bcr_pick_error[2];

private:
	int  m_nReq_Rcvy[2][4];
	double m_dPos_TmpRcvyZ1_1;
	double m_dPos_TmpRcvyZ1_2;
	double m_dPos_TmpRcvyZ2_1;
	double m_dPos_TmpRcvyZ2_2;


// Operations
protected:
	ENUM_STEP_CYL m_step_mrotate_fwdbwd[2];
	EFB			  m_fbmrotatefwdbwd[2];
	DWORD		  m_dwTimeMRotatefwdbwdStart[2];
	DWORD		  m_dwTimeMRotatefwdbwd[2];


	ENUM_STEP_CYL m_step_box_updn;
	EFB			  m_fbboxupdn;
	DWORD		  m_dwTimeBoxupdnStart;
	DWORD		  m_dwTimeBoxupdn;



	ENUM_STEP_CYL m_step_mtopvac[2];//left,right
	EFB			  m_fbmtopvac[2];
	DWORD		  m_dwTimeMTopVacStart[2];
	DWORD		  m_dwTimeMTopVac[2];

	ENUM_STEP_CYL m_step_mbtmvac[2];
	EFB			  m_fbmbtmvac[2];
	DWORD		  m_dwTimeMBtmVacStart[2];
	DWORD		  m_dwTimeMBtmVac[2];

//	ENUM_STEP_CYL m_step_rolling_fwdbwd[3];
//	EFB			  m_fbrollingfwdbwd[3];
//	DWORD		  m_dwTimeRollingFwdBwdStart[3];
//	DWORD		  m_dwTimeRollingFwdBwd[3];
	ENUM_STEP_CYL m_step_rolling_fwdbwd[2]; //bcr1,bcr2 Left,right
	EFB			  m_fbrollingfwdbwd[2]; //bcr1,bcr2 Left,right
	DWORD		  m_dwTimeRollingFwdBwdStart[2]; //bcr1,bcr2 Left,right
	DWORD		  m_dwTimeRollingFwdBwd[2]; //bcr1,bcr2 Left,right

	bool Run_Bcr_Move_Chk1_Jam( stJobPicker job );
	bool Run_Bcr_Move_Chk1_Time();
	bool InTimeRobot1( int iMilliSec );

	bool Run_Bcr_Move_Chk2_Jam( stJobPicker job );
	bool Run_Bcr_Move_Chk2_Time();
	bool InTimeRobot2( int iMilliSec );

	bool Chk_Robot1_vacuum_fwdbwd( int nSite, int iOn );
	bool Chk_Robot2_vacuum_fwdbwd( int nSite, int iOn );
	bool Chk_Robot_rollingfwdbwd( int iOn );

public:
	void ReqMRotateFwdBwd( int nSite, EFB efb);
	void SetMRotateFwdBwd( int nSite, int iOnOff );
	bool CheckMRotateFwdBwd( int nSite, int iOnOff );
	EFB  GetMRotateFwdBwd(int nSite ) { return m_fbmrotatefwdbwd[nSite]; }

	void ReqBoxUpDn( EFB efb);
	EFB  GetBoxUpDn() { return m_fbboxupdn; }
	void SetBoxUpDn( int iOnOff );
	bool CheckBoxUpDn( int iOnOff );

	void ReqMTopVac( int nSite, EFB efb);
	EFB  GetMTopVac( int nSite ) { return m_fbmtopvac[nSite]; }
	void SetMTopVac( int nSite, int iOnOff );
	bool CheckMTopVac( int nSite, int iOnOff );

	void ReqMBtmVac( int nSite, EFB efb );
	EFB	 GetMBtmVac( int nSite ) { return m_fbmbtmvac[nSite];	}
	void SetMBtmVac( int nSIte, int iOnOff );
	bool CheckMBtmVac( int nSite, int iOnOff );


//	void ReqRollingFwdBwd( int nSite, EFB efb);
//	EFB  GetRollingFwdBwd( int nSite ) { return m_fbrollingfwdbwd[nSite]; }
//	void SetRollingFwdBwd( int nSite, int iOnOff );
//	bool CheckRollingFwdBwd( int nSite, int iOnOff );
	void ReqRollingFwdBwd( int pos, EFB efb);
	EFB  GetRollingFwdBwd( int pos ) { return m_fbrollingfwdbwd[pos]; }
	void SetRollingFwdBwd( int pos, int iOnOff );
	bool CheckRollingFwdBwd( int pos, int iOnOff );

	void EBCRI_Check_Rbot_Chk();
	void EBCRI_HomeCheck_Z( int nAxis);
	void EBCRI_VacuumOnOff(int iOnOff);
	void EBCRI_Barcode_Empty_Check();
	void EBCRI_EjectOnOff( int iOnOff );
	void EBCRI_HomeCheck_R( int nAxis);
	void EBCRI_HomeCheck_X( int nAxis);
	void EBCRI_HomeCheck_Y( int nAxis );
	void EBCRI_Move_Safety_X( int nAxis );
	void EBCRI_HomeCheck_BCR_Feeder( int nAxis);

	void EBCRI_Top_Vacuum_Backward();
	void EBCRI_Top_Vacuum_Backward_Check();
	void EBCRI_Btm_Vacuum_Backward();
	void EBCRI_Btm_Vacuum_Backward_Check();


//	void EBCRI_M1_Guide_Up();
//	void EBCRI_M1_Guide_Up_Check();
//	void EBCRI_M2_Guide_Up();
//	void EBCRI_M2_Guide_Up_Check();

	void EBCRI_Finish();

	void EDRR_HomeCheck_R( int nAxis);
	void EDRR_HomeCheck_X( int nAxis);
	

public:
	void Serialize(CArchive &ar);
	void Run_Move1();
	void Run_Move2();
	void Run_Reinstate();
	void Run_Restore();
	void OnRobot_FinalPos();

	void Run_Initial();
	void Thread_Run();
	void Thread_Variable_Initial();

	void Run_Move_Box_UpDn();
	void Run_Move_M_Top_Vacuum( int nSite);
	void Run_Move_M_Btm_Vacuum( int nSite);

	void Run_Move_Bcr_Plate_UpDown( int nSite );

	void Run_Move_M1_Guide_FwdBwd( int nSite);

//	void Run_Move_RollerFwdBwd(int nSite);
	void Run_Move_RollerFwdBwd( int nPos);

	void Run_Move_M_RollerFwdBwd(int nSite);


};
extern CRun_Barcode_Works g_Run_Barcode_Works;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUN_BARCODE_WORKS_H__138F8A8D_A309_4E11_B8F5_73E60A28051C__INCLUDED_)

