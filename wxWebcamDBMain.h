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
#include <mathplot.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/toolbar.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/gbsizer.h>
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

#include "et1255.h"
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

      static wxWebcamDBFrame* singleton() { return m_self; }
      void Init();

      void UpdateStatusBar();
      void UpdateExposureMeter();
      void ClearExposureMeter();
      void syncFiltersFields(int state);
      //void UpdateFWheelMap();
//      void UpdateGuiderTuning();
      void UpdateIncrement();
      void ClearIndPlot();
      ET1255 et1255;
      wxClientDC  *dc;
      wxCoord PowerPointPrevX[4], PowerPointPrevY[4];
      std::vector<double> PD0_yb, PD1_yb, PD2_yb, PD3_yb, PD_xb,
                Ind_p, Ind_vh, Ind_vl, Ind_angle;
      double c_pivot, c_vlow,  c_vhig;
      LONGLONG PowerPointsN;
      wxColour ADCLineColors[4];
	private:
       //static wxWebcamDBFrame* m_self;

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
		//		void OnPickGuideStarClick(wxCommandEvent& event);
		void OnvideoPanelLeftDown(wxMouseEvent& event);
		void OnShowReticleClick(wxCommandEvent& event);
		//		void OnMenuItemGuidingSelected(wxCommandEvent& event);
		//		void OnGuideTelescopeClick(wxCommandEvent& event);
		//		void OnReverseRAClick(wxCommandEvent& event);
		//		void OnReverseDECClick(wxCommandEvent& event);
		//		void OnDecNSChoiceSelect(wxCommandEvent& event);
		//		void OnRaAggrSpinChange(wxSpinEvent& event);
		//		void OnDecAggrSpinChange(wxSpinEvent& event);
		//		void OnAdvancedGuideParamsClick(wxCommandEvent& event);
		void OnUnZoom(wxCommandEvent& event);
		void OnFullFrame(wxCommandEvent& event);
		void OnPauseClick(wxCommandEvent& event);
		void OnIncrementText(wxCommandEvent& event);
		void OnStartBatchButtonClick(wxCommandEvent& event);
		void OnPauseBatchButtonClick(wxCommandEvent& event);
		void OnNotebook1PageChanged(wxNotebookEvent& event);
		void OnMaxFrames_CheckBoxClick(wxCommandEvent& event);
		//		void OnMenuItemOptionsGuiding(wxCommandEvent& event);
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
		void OnSS_PortNSpinChange(wxCommandEvent&  event);
		void OnSS_CurrentAngleChange(wxSpinEvent& event);
		void OnsetFilters_btnClick(wxCommandEvent& event);
		void OnfWheelCheckClick(wxCommandEvent& event);
		void OnsetFWheelList_btnClick(wxCommandEvent& event);
		void OnListBox1Select(wxCommandEvent& event);
		void OnfWheelFiltersGridLabelLeftClick(wxGridEvent& event);
		void OnfWheelPrevClick(wxCommandEvent& event);
		void OnfWheelNextClick(wxCommandEvent& event);
		void OnstepperStopCapture_btnClick(wxCommandEvent& event);
		void OnbacklashCheckClick(wxCommandEvent& event);
		void OnLockFWheelClick(wxCommandEvent& event);
		void OnLockFWheelClick1(wxCommandEvent& event);
		void OnSS_CalibrSpinChange(wxSpinEvent& event);
		void OnSS_AngSpinChange(wxSpinEvent& event);
		void OnStartADCClick(wxCommandEvent& event);
		void OnsetADCDataPathClick(wxCommandEvent& event);
		void OnSS_FrecSliderCmdScroll(wxScrollEvent& event);
		void Ongraph_plotResize(wxSizeEvent& event);
		void OnSS_FrecSpinChange(wxSpinEvent& event);
		void OnReal_PlotResize(wxSizeEvent& event);
		void OnButton2Click(wxCommandEvent& event);

		void OnADC_Int_FrecSelect(wxCommandEvent& event);
		//*)

		void OnGaugeTimer(wxTimerEvent& event);
//		void OnGuideTimer(wxTimerEvent& event);
		void OnStepperCOMTimer(wxTimerEvent& event);
		void OnStepperCaptureTimer(wxTimerEvent& event);
		void OnStepperAfterCaptureTimer(wxTimerEvent& event);
		void OnADCTimer(wxTimerEvent& event);

        void OnStartADC();

		void OnIdle(wxIdleEvent& event);
        void OnUpdateCamData(wxCommandEvent& event); //BM:20090104 added

		// non-event helper functions
		void StartCapture(bool batch);
		void StopCapture();
		void ContinueCapture(bool batch);
		void PauseCapture(bool batch);

		void UpdateLEcontrols();
		void updateExposure();
//		void UpdateBatchControls();
		void ShutdownAll();
        void SetStepperState(bool state){ wxWebcamDBFrame::isStepperConnected = state;};
        //int GetStepperState();{ return Stepper.SMD;};
        bool IsStepperConnected();
        double GetSingleStepAngle();

        double GetStepperAngle(){return StepperAngle;}
        double SetStepperAngle(double ang){return StepperAngle=ang;}
        double UpdateStepperAngle(double ang);
        double ResetStepperAngle(){StepperAngle = 0;  SS_CurrentAngle->SetValue(StepperAngle); return StepperAngle;};
        void UpdateFWheelString();
        void setCurrentFiltersIndex(int index);
        int GetCurrentFilterIndex(){return currentFilterIndex;}
        void fWheelIncrease();
        void fWheelDecrease();

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
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_CHOICE2;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_STATICTEXT5;
		static const long ID_SPINCTRL5;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL6;
		static const long ID_CHOICE3;
		static const long ID_CHOICE4;
		static const long ID_STATICTEXT9;
		static const long ID_CHOICE5;
		static const long ID_SLIDER5;
		static const long ID_SPINCTRL7;
		static const long ID_STATICTEXT11;
		static const long ID_SPINCTRL8;
		static const long ID_BUTTON6;
		static const long ID_SPINCTRL9;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL10;
		static const long ID_CHECKBOX1;
		static const long ID_SPINCTRL1;
		static const long ID_CHECKBOX6;
		static const long ID_BACKLASHSPIN;
		static const long ID_CHECKBOX9;
		static const long ID_PANEL2;
		static const long ID_CHECKBOX3;
		static const long ID_GRID1;
		static const long ID_BUTTON10;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL11;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON4;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX8;
		static const long ID_PANEL4;
		static const long ID_BUTTON11;
		static const long ID_SPINCTRL12;
		static const long ID_SPINCTRL13;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON12;
		static const long ID_CHECKBOX10;
		static const long ID_BUTTON13;
		static const long ID_CHOICE6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_PANEL6;
		static const long ID_NOTEBOOK1;
		static const long ID_CAMERA_PANEL;
		static const long ID_AXIS1;
		static const long ID_AXIS2;
		static const long ID_VECTOR1;
		static const long ID_VECTOR2;
		static const long ID_VECTOR3;
		static const long ID_VECTOR4;
		static const long ID_VECTOR8;
		static const long ID_MATHPLOT1;
		static const long ID_PANEL5;
		static const long ID_AXIS3;
		static const long ID_AXIS4;
		static const long ID_VECTOR5;
		static const long ID_VECTOR6;
		static const long ID_VECTOR7;
		static const long ID_MATHPLOT2;
		static const long ID_PANEL7;
		static const long ID_CHOICE1;
		static const long ID_SPINCTRL2;
		static const long ID_CHECKBOX2;
		static const long ID_PANEL3;
		static const long ID_SLIDER1;
		static const long ID_SLIDER3;
		static const long ID_SLIDER2;
		static const long ID_SLIDER4;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON9;
		static const long ID_BITMAPBUTTON5;
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
//      static const long ID_GUIDE_TIMER1;
      static const long ID_STEPPER_COM_TIMER;
      static const long ID_STEPPER_CAPTURE_TIMER;
      static const long ID_STEPPER_AFTER_CAPTURE_TIMER;
      static const long ID_ADC_TIMER;


		//(*Declarations(wxWebcamDBFrame)
		wxStaticText* StaticText9;
		wxButton* SS_CWiceDirection;
		wxButton* SS_StepperCapture_btn;
		wxBitmapButton* StepperMoveCCWice;
		mpWindow* PowerPlot;
		wxPanel* graph_plot;
		wxMenuItem* MenuItem8;
		wxStaticText* ADCChnl1Val;
		std::vector<float>  PD0_Y;
		wxCheckBox* LE_CheckBox;
		wxMenuItem* MenuItem7;
		wxCheckBox* MaxFrames_CheckBox;
		wxTextCtrl* m_increment;
		std::vector<float>  PD3_X;
		wxNotebook* Notebook1;
		wxButton* m_openStepperCOMPort_btn;
		mpScaleY   *Y_Axis;
		std::vector<float>  PD3_Y;
		std::vector<float>  PD0_X;
		wxStaticText* StaticText2;
		wxCheckBox* backlashCheck;
		wxMenuItem* MenuItem2;
		std::vector<float>  Ind_low_Y;
		wxButton* SetStepperParam;
		wxMenu* Menu3;
		wxChoice* ADC_Int_Frec;
		wxGrid* fWheelFiltersGrid;
		wxBitmapButton* fWheelNext;
		wxStaticText* StaticText6;
		wxChoice* m_stepperIStopChoice;
		mpFXYVector   *Ind_pivot;
		mpFXYVector   *PD1;
		wxMenuItem* MenuItem1;
		std::vector<float>  Ind_high_X;
		wxButton* m_capture_btn;
		wxSpinCtrlDbl* SS_AngSpin;
		wxButton* setFWheelList_btn;
		wxPanel* video_panel;
		wxStaticText* StaticText8;
		std::vector<float>  Ind_pivot_X;
		wxStaticText* ADCChnl2Val;
		std::vector<float>  PD2_X;
		wxSpinCtrl* SS_StepperInterval;
		wxCheckBox* autoFWheelMode;
		wxButton* SS_CCWiceDirection;
		wxPanel* m_record_panel;
		mpScaleY   *Signal_axis;
		wxSpinCtrl* ADCFrec;
		wxSlider* SS_FrecSlider;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		std::vector<float>  PD1_X;
		wxStaticText* ADCChnl3Val;
		wxBoxSizer* BoxSizer2;
		std::vector<float>  PD4_Y;
		wxStaticText* StaticText3;
		wxMenu* Menu1;
		std::vector<float>  Ind_pivot_Y;
		wxBitmapButton* fWheelPrev;
		wxSpinCtrl* SS_FrecSpin;
		wxButton* Button2;
		wxTextCtrl* ADCDataPath;
		wxTextCtrl* currentFiltersField;
		std::vector<float>  PD4_X;
		std::vector<float>  Ind_high_Y;
		wxSpinCtrlDbl* m_meter_scale;
		wxStaticText* CalibrKLabel;
		wxMainToolBar* ToolBar1;
		wxCheckBox* LockFWheel;
		mpFXYVector   *PD3;
		wxCheckBox* fWheelCheck;
		wxMenuItem* MenuItem3;
		mpFXYVector   *Ind_high;
		wxSpinCtrl* ADCAmplif;
		wxButton* StartADC;
		wxSpinCtrlDbl* SS_CalibrSpin;
		std::vector<float>  PD2_Y;
		wxBitmapButton* StepperMoveCWice;
		wxCheckBox* m_activate_exposure_meter;
		std::vector<float>  Ind_low_X;
		wxStaticText* StaticText5;
		mpFXYVector   *PD2;
		wxSpinCtrlDbl* SS_CurrentAngle;
		wxChoice* SS_MotorN;
		wxChoice* m_meter_channel;
		wxPanel* m_stepper_panel;
		wxButton* ResetStepperCounter;
		wxChoice* m_stepperWModeChoice;
		wxSlider* fWheelTopTrigger;
		wxChoice* m_stepperIChoice;
		wxSlider* fWheelPIVOTTrigger;
		wxStatusBarEx* m_statusbar;
		wxBoxSizer* BoxSizer1;
		mpWindow* Ind_Plot;
		wxBitmapButton* stepperCapture2_btn;
		wxSlider* HistMinNaxBalance;
		wxButton* m_pause_btn;
		wxPanel* Real_Plot;
		wxSpinCtrlDbl* backlashSpin;
		wxMenuBar* MenuBar1;
		mpScaleX   *Ang_Axis;
		wxSpinCtrlDbl* LE_SpinCtrl1;
		wxPanel* m_exposure_meter_panel;
		mpFXYVector   *Ind_low;
		mpFXYVector   *PD4;
		wxPanel* Panel2;
		mpFXYVector   *PD0;
		wxStaticBoxSizer* StaticBoxSizer1;
		wxSpinCtrl* SS_PortNSpin;
		wxSpinCtrl* MaxFrames_SpinCtrl;
		wxCheckBox* AutoExposure;
		wxBoxSizer* BoxSizer3;
		wxSlider* fWheelButtomTrigger;
		wxMenu* Menu2;
		wxMenuItem* MenuItem9;
		wxButton* setFilters_btn;
		wxGauge* m_gauge1;
		wxMenuItem* MenuItemGuiding;
		mpScaleX   *X_Axis;
		wxButton* ResetSHD;
		wxStaticText* ADCChnl4Val;
		std::vector<float>  PD1_Y;
		wxSpinCtrl* SS_MultFrecSpin;
		wxCheckBox* SyncCapture;
		wxMenu* Menu4;
		wxSpinCtrlDbl* fWheelCalibrSpin;
		wxButton* setADCDataPath;
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

//      wxTimer     m_guide_timer;     // ** temp solution, the guide timer
//      wxSubFrame  m_guide_subframe;  // the object that handles guiding calculations
//      bool        m_guide_active;    // true when guide commands shall be issued

      ///stepper
      BYTE ATrtAddr;// = 255;
      //int ANumber;// = 0;
      int steps;// = 0;
      double StepperAngle;
      bool isStepperConnected;
      int stepperDirection;
      double fWheelCalibration;// = 360/4;
      int currentFilterIndex;// = 0;
      bool fWheelDirection;// = 0;
      bool auto_exposure;
      wxString fWheelString;
      wxTimer     m_stepperCOM_timer;
      wxTimer     m_stepperCapture_timer;
      wxTimer     m_stepperAfterCapture_timer;
      wxTimer     m_ADC_timer;
      filtersMap fBaseMap;
      wxArrayString filtersArray;
      filtersMap fMap;
      bool StepperExposurePause;

};



#endif // WXWEBCAMDBMAIN_H
