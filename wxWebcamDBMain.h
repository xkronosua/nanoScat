/***************************************************************
 * Name:      wxWebcamDBMain.h
 * Purpose:   Defines Application Frame
 * Author:    ca ()
 * Created:   2007-04-11
 * Copyright: ca ()
 * License:
 **************************************************************/

#ifndef WXWEBCAMDBMAIN_H
#define WXWEBCAMDBMAIN_H

#include "wxWebcamDBApp.h"

//(*Headers(wxWebcamDBFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include "BatchSetup.h"
#include <wx/spinctrl.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/statusbr.h>
//*)
#include <wx/config.h>
#include "wxWebcam/wxWebcam.h"
#include "wxthings/spinctld.h"
#include "wxcustom/wxStatusBarEx.h"
#include <wx/listimpl.cpp>

#include "wxSubFrame.h"
#include "wxFactory.h"
#include "SMDDrv.h"

class wxPort;
class wxSubFrame;
class wxMainToolBar;

WX_DECLARE_STRING_HASH_MAP( double,     // type of the values
                            filtersMap); // name of the class


class wxWebcamDBFrame: public wxFrame
{
	public:

      wxWebcamDBFrame(wxWindow* parent,wxWindowID id = -1);
      virtual ~wxWebcamDBFrame();

      void Init();

      void UpdateStatusBar();
      void UpdateExposureMeter();
      void ClearExposureMeter();
      void UpdateGuiderTuning();
      void UpdateIncrement();

	private:


	   void ReplaceCamera(wxWindow* old_camera, wxCamera* new_camera);

		//(*Handlers(wxWebcamDBFrame)
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnMenuItemConnect(wxCommandEvent& event);
		void OnMenuItemDisconnect(wxCommandEvent& event);
		void Onm_source_btnClick(wxCommandEvent& event);
		void Onm_format_btnClick(wxCommandEvent& event);
		void Onm_folder_btnClick(wxCommandEvent& event);
		void OnMenuItemSettings(wxCommandEvent& event);
		void OnVideoDeviceProperties(wxCommandEvent& event);
		void OnCaptureClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnLE_CheckBoxClick(wxCommandEvent& event);
		void OnLE_SpinCtrl1Change(wxSpinEvent& event);
		void OnActivateExposureMeterClick(wxCommandEvent& event);
		void OnExposureMeteScaleChange(wxSpinEvent& event);
		void OnMeterChannelSelect(wxCommandEvent& event);
		void OnMenuItemImageHeader(wxCommandEvent& event);
		void OnPickGuideStarClick(wxCommandEvent& event);
		void OnvideoPanelLeftDown(wxMouseEvent& event);
		void OnShowReticleClick(wxCommandEvent& event);
		void OnMenuItemGuidingSelected(wxCommandEvent& event);
		void OnGuideTelescopeClick(wxCommandEvent& event);
		void OnReverseRAClick(wxCommandEvent& event);
		void OnReverseDECClick(wxCommandEvent& event);
		void OnDecNSChoiceSelect(wxCommandEvent& event);
		void OnRaAggrSpinChange(wxSpinEvent& event);
		void OnDecAggrSpinChange(wxSpinEvent& event);
		void OnAdvancedGuideParamsClick(wxCommandEvent& event);
		void OnUnZoom(wxCommandEvent& event);
		void OnFullFrame(wxCommandEvent& event);
		void OnPauseClick(wxCommandEvent& event);
		void OnIncrementText(wxCommandEvent& event);
		void OnStartBatchButtonClick(wxCommandEvent& event);
		void OnPauseBatchButtonClick(wxCommandEvent& event);
		void OnNotebook1PageChanged(wxNotebookEvent& event);
		void OnMaxFrames_CheckBoxClick(wxCommandEvent& event);
		void OnMenuItemOptionsGuiding(wxCommandEvent& event);
		void OnSetStepperParamClick(wxCommandEvent& event);
		void OnOpenStepperCOMPortClick(wxCommandEvent& event);
		void OnStepperMoveCWiceClick(wxCommandEvent& event);
		void OnStepperMoveCCWiceClick(wxCommandEvent& event);
        void OnResetSHDClick(wxCommandEvent& event);
        void OnResetStepperCounterClick(wxCommandEvent& event);
        void OnStepperCaptureClick(wxCommandEvent& event);
        void OnCWStepperDirectionClick(wxCommandEvent&  event);
        void OnCCWStepperDirectionClick(wxCommandEvent&  event);
        void OnSpinCurrentAngleChanged(wxCommandEvent&  event);

		//*)

		void OnGaugeTimer(wxTimerEvent& event);
		void OnGuideTimer(wxTimerEvent& event);
		void OnStepperCOMTimer(wxTimerEvent& event);
		void OnStepperCaptureTimer(wxTimerEvent& event);
		void OnStepperAfterCaptureTimer(wxTimerEvent& event);


		void OnIdle(wxIdleEvent& event);
      void OnUpdateCamData(wxCommandEvent& event); //BM:20090104 added

		// non-event helper functions
		void StartCapture(bool batch);
		void StopCapture();
		void ContinueCapture(bool batch);
		void PauseCapture(bool batch);

		void UpdateLEcontrols();
		void UpdateBatchControls();
		void ShutdownAll();
        void SetStepperState(bool state){ wxWebcamDBFrame::isStepperConnected = state;};
        bool GetStepperState(){ return wxWebcamDBFrame::isStepperConnected;};

        double GetStepperAngle(){return StepperAngle;}
        double SetStepperAngle(double ang){return StepperAngle=ang;}
        double UpdateStepperAngle(double ang){StepperAngle+=ang; SS_CurrentAngle->SetValue( StepperAngle); return StepperAngle;};
        double ResetStepperAngle(){StepperAngle = 0;  SS_CurrentAngle->SetValue(StepperAngle); return StepperAngle;};
        void UpdateFWheelString();

		int Contains(wxArrayString& cameras,const wxString& substr);

		//(*Identifiers(wxWebcamDBFrame)
		static const long ID_DEVICE_PROPERTIES;
		static const long ID_CHECKBOX5;
		static const long ID_CAPTURE;
		static const long ID_GAUGE1;
		static const long ID_BUTTON3;
		static const long ID_TEXTCTRL1;
		static const long ID_CHECKBOX7;
		static const long ID_SPINCTRL4;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICE1;
		static const long ID_PANEL3;
		static const long ID_CHECKBOX2;
		static const long ID_SPINCTRL2;
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX6;
		static const long ID_STATICTEXT9;
		static const long ID_CHOICE2;
		static const long ID_STATICTEXT10;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT12;
		static const long ID_SPINCTRL5;
		static const long ID_BUTTON2;
		static const long ID_PANEL4;
		static const long ID_BATCH_CAPTURE_BTN;
////STEPPER
		static const long ID_SET_STEPPER_PARAM_BTN;
		static const long ID_RESET_STEPPER_BTN;
		static const long ID_RESET_STEPPER_COUNTER_BTN;
		static const long ID_OPEN_STEPPER_COM_PORT_BTN;
		static const long ID_MOVE_STEPPER_CWICE_BTN;
		static const long ID_MOVE_STEPPER_CCWICE_BTN;
		static const long ID_SSANG;
		static const long ID_STEPPER_I_CHOICE;
		static const long ID_STEPPER_I_STOP_CHOICE;
		static const long ID_SSI;
		static const long ID_SSISTOP;
		static const long ID_SSWMODE;
		static const long ID_STEPPER_W_MODE_CHOICE;
		static const long ID_SSFREC;
		static const long ID_SSFRECSPIN;
		static const long ID_SSCALIBR;
		static const long ID_SSCALIBRSPIN;
		static const long ID_SSPORTN;
		static const long ID_SSPORTNSPIN;
		static const long ID_SSMOTORN;
		static const long ID_SSMOTORNSPIN;
		static const long ID_SSMULTFREC;
		static const long ID_SSMULTFRECSPIN;
		static const long ID_SSCWICE_DIRECTION;
		static const long ID_SSCCWICE_DIRECTION;
		static const long ID_SSCURRENTANGLE;
		static const long ID_STEPPER_CAPTURE_BTN;
		static const long ID_STEPPER_INTERVAL;




//////
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT14;
		static const long ID_CUSTOM1;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		static const long ID_CAMERA_PANEL;
		static const long idMenuQuit;
		static const long ID_MENUITEM_CONNECT;
		static const long ID_MENUITEM_DISCONNECT;
		static const long ID_MENUITEM_SETTINGS;
		static const long ID_MENUITEM_GUIDING2;
		static const long ID_MENUITEM_HEADER;
		static const long idMenuAbout;
		static const long ID_STATUSBAR1;
		static const long ID_TOOLBAR1;
		//*)

      static const long ID_GAUGE_TIMER1;
      static const long ID_GUIDE_TIMER1;
      static const long ID_STEPPER_COM_TIMER;
      static const long ID_STEPPER_CAPTURE_TIMER;
      static const long ID_STEPPER_AFTER_CAPTURE_TIMER;


		//(*Declarations(wxWebcamDBFrame)
		wxBoxSizer* BoxSizer6;
		wxPanel* m_batch_panel;
		wxPanel* m_stepper_panel;
		wxBoxSizer* BoxSizer9_1;
		wxMenuItem* MenuItem8;
		wxCheckBox* LE_CheckBox;
		wxMenuItem* MenuItem7;
		wxCheckBox* MaxFrames_CheckBox;
		wxTextCtrl* m_increment;
		BatchSetup* m_batch_setup;
		wxBoxSizer* BoxSizer10;
		wxNotebook* Notebook1;
		wxBoxSizer* BoxSizer7;
		wxStaticText* m_guide_mag;
		wxBoxSizer* BoxSizer8;
		wxMenuItem* MenuItem2;
		wxStaticBoxSizer* StaticBoxSizer4;
		wxCheckBox* m_reverseRA;
		wxMenu* Menu3;
		wxCheckBox* GuideTelescope;
		wxMenuItem* MenuItem1;
		wxButton* m_capture_btn;
		wxPanel* m_record_panel;
		wxChoice* m_decNSChoice;
		wxStaticText* StaticText1;
		wxBoxSizer* BoxSizer2;
		wxMenu* Menu1;
		wxButton* m_batchCapture_btn;
///////////Stepper
		wxButton* m_setStepperParam_btn;
		wxButton* m_resetStepperCounter_btn;
		wxButton* m_resetStepper_btn;
		wxButton* m_openStepperCOMPort_btn;
		wxButton* m_moveStepperCWice_btn;
		wxButton* m_moveStepperCCWice_btn;
		wxStaticText* SS_SetAng;
		wxSpinCtrlDbl* SS_AngSpin;
		wxChoice* m_stepperIChoice;
        wxChoice* m_stepperIStopChoice;
        wxStaticText* SS_IStopText;
        wxChoice* m_stepperWModeChoice;
        wxStaticText* SS_WModeText;
        wxStaticText* SS_FrecText;
        wxSpinCtrl* SS_FrecSpin;
        wxStaticText* SS_CalibrText;
        wxSpinCtrlDbl* SS_CalibrSpin;
        wxStaticText* SS_PortNText;
        wxSpinCtrl* SS_PortNSpin;
        wxStaticText* SS_MotorNText;
        wxSpinCtrl* SS_MotorNSpin;
        wxStaticText* SS_MultFrecText;
        wxSpinCtrl* SS_MultFrecSpin;
        wxButton* SS_CWiceDirection;
        wxButton* SS_CCWiceDirection;
        wxSpinCtrlDbl* SS_CurrentAngle;
        wxSpinCtrl* SS_StepperInterval;
        wxButton* SS_StepperCapture_btn;

///////
		wxStaticBoxSizer* StaticBoxSizer13;
		wxButton* PauseBatchButton;
		wxSpinCtrlDbl* m_meter_scale;
		wxMainToolBar* ToolBar1;
		wxMenuItem* MenuItem3;
		wxSpinCtrlDbl* m_RaAggrSpin;
		wxCheckBox* m_activate_exposure_meter;
		wxStaticText* m_batch_status3;
		wxStaticText* m_batch_status2;
		wxChoice* m_meter_channel;
		wxCheckBox* m_reverseDEC;
		wxStaticText* m_guide_dx;
		wxStaticText* m_batch_status1;
		wxStaticText* LE_Text;
		wxStaticText* SS_IText;
		wxStatusBarEx* m_statusbar;
		wxBoxSizer* BoxSizer1;
		wxBoxSizer* BoxSizer14_1;
		wxBoxSizer* BoxSizer12_1;
		wxButton* m_pause_btn;
		wxButton* PickGuideStar;
		wxMenuBar* MenuBar1;
		wxSpinCtrlDbl* LE_SpinCtrl1;
		wxSpinCtrlDbl* SS_ISpin;
		wxPanel* m_exposure_meter_panel;
		wxStaticBoxSizer* StaticBoxSizer1;
		wxStaticBoxSizer* StaticBoxSizer2_1;
		wxSpinCtrl* MaxFrames_SpinCtrl;
		wxStaticText* m_guide_dy;
		wxMenu* Menu2;
		wxMenuItem* MenuItem9;
		wxGauge* m_gauge1;
		wxPanel* m_guide_panel;
		wxStaticText* m_staticText_RA;
		wxMenuItem* MenuItemGuiding;
		wxMenu* Menu4;
		wxSpinCtrlDbl* m_DecAggrSpin;
		//*)

		DECLARE_EVENT_TABLE()
    private:
      SMDDll Stepper;//(_T("C:\\Windows\\SMD004.dll"));
      wxLocale   m_locale;
      wxFactory  m_factory;

      wxTimer    m_gauge_timer;
      int        m_gdir;


      wxString   m_capture_feedback;
      wxDateTime m_start_capture;

      static wxWebcamDBFrame* m_self;

      // these variables exist because the corresponding
      // controls may not be evaluated while previewing
      bool   m_exposure_meter_active;
      double m_exposure_meter_scale;

      wxTimer     m_guide_timer;     // ** temp solution, the guide timer
      wxSubFrame  m_guide_subframe;  // the object that handles guiding calculations
      bool        m_guide_active;    // true when guide commands shall be issued

      ///stepper
      BYTE ATrtAddr;// = 255;
      //int ANumber;// = 0;
      int steps;// = 0;
      double StepperAngle;
      bool isStepperConnected;
      double fWheelCalibration;// = 360/4;
      int currentFilterIndex;// = 0;
      bool fWheelDirection;// = 0;
      bool auto_exposure;
      wxString fWheelString;
      wxTimer     m_stepperCOM_timer;
      wxTimer     m_stepperCapture_timer;
      wxTimer     m_stepperAfterCapture_timer;
      filtersMap fBaseMap;
      wxArrayString filtersArray;
      filtersMap fMap;
      bool StepperExposurePause;
};



#endif // WXWEBCAMDBMAIN_H
