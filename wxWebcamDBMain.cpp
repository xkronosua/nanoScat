/***************************************************************
 * Name:      wxWebcamDBMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ca ()
 * Created:   2007-04-11
 * Copyright: ca ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxWebcamDBMain.h"
#include "wx/dirdlg.h"
#include "SettingsDialog.h"
#include "ImageHeaderDialog.h"
///#include "OptionsGuiding.h"     /// OLD Options guiding
#include "wxGuidingOptions.h"   /// NEW Options guiding
#include "wxWebcamProps.h"
#include "AdvancedGuidingParams.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/aboutdlg.h>
#include <wx/tokenzr.h>

// version.h defines program version number as "MyAppVer" string
#include "version.h"
#include "wxIO/wxLongExpoPort.h"
#include "wxIO/wxGuiderPort.h"
#include "wxGuidingConfig.h"
#include "wxGuider.h"
#include "wxMainToolBar.h"

#include "wxMessageArea.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(_WXMSW_)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*InternalHeaders(wxWebcamDBFrame)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxWebcam/wxCamera.h"
#include "wxWebcam/wxWebcam.h"
#include "wxWebcam/wxArtcam.h"

#define SPC900NC_ICON 1
#define CROSS_HAIR_ICON 1
#include "wxWebcam_icons.h"



//(*IdInit(wxWebcamDBFrame)
const long wxWebcamDBFrame::ID_DEVICE_PROPERTIES = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX5 = wxNewId();
const long wxWebcamDBFrame::ID_CAPTURE = wxNewId();
const long wxWebcamDBFrame::ID_GAUGE1 = wxNewId();
const long wxWebcamDBFrame::ID_BUTTON3 = wxNewId();
const long wxWebcamDBFrame::ID_TEXTCTRL1 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX7 = wxNewId();
const long wxWebcamDBFrame::ID_SPINCTRL4 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX1 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT1 = wxNewId();
const long wxWebcamDBFrame::ID_SPINCTRL1 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT2 = wxNewId();
const long wxWebcamDBFrame::ID_CHOICE1 = wxNewId();
const long wxWebcamDBFrame::ID_PANEL3 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX2 = wxNewId();
const long wxWebcamDBFrame::ID_SPINCTRL2 = wxNewId();
const long wxWebcamDBFrame::ID_PANEL1 = wxNewId();
const long wxWebcamDBFrame::ID_BUTTON1 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT3 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT4 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT5 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT6 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT7 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT8 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX3 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX4 = wxNewId();
const long wxWebcamDBFrame::ID_CHECKBOX6 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT9 = wxNewId();
const long wxWebcamDBFrame::ID_CHOICE2 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT10 = wxNewId();
const long wxWebcamDBFrame::ID_SPINCTRL3 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT12 = wxNewId();
const long wxWebcamDBFrame::ID_SPINCTRL5 = wxNewId();
const long wxWebcamDBFrame::ID_BUTTON2 = wxNewId();
const long wxWebcamDBFrame::ID_PANEL4 = wxNewId();
const long wxWebcamDBFrame::ID_BATCH_CAPTURE_BTN = wxNewId();
///Stepper
const long wxWebcamDBFrame::ID_SET_STEPPER_PARAM_BTN = wxNewId();
const long wxWebcamDBFrame::ID_RESET_STEPPER_BTN = wxNewId();
const long wxWebcamDBFrame::ID_RESET_STEPPER_COUNTER_BTN = wxNewId();
const long wxWebcamDBFrame::ID_OPEN_STEPPER_COM_PORT_BTN = wxNewId();
const long wxWebcamDBFrame::ID_MOVE_STEPPER_CWICE_BTN = wxNewId();
const long wxWebcamDBFrame::ID_MOVE_STEPPER_CCWICE_BTN = wxNewId();
const long wxWebcamDBFrame::ID_SSANG = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_CAPTURE_BTN = wxNewId();

const long wxWebcamDBFrame::ID_STEPPER_I_CHOICE = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_I_STOP_CHOICE = wxNewId();
const long wxWebcamDBFrame::ID_SSI = wxNewId();
const long wxWebcamDBFrame::ID_SSISTOP = wxNewId();
const long wxWebcamDBFrame::ID_SSWMODE = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_W_MODE_CHOICE = wxNewId();
const long wxWebcamDBFrame::ID_SSFRECSPIN = wxNewId();
const long wxWebcamDBFrame::ID_SSFREC = wxNewId();
const long wxWebcamDBFrame::ID_SSCALIBRSPIN = wxNewId();
const long wxWebcamDBFrame::ID_SSCALIBR = wxNewId();
const long wxWebcamDBFrame::ID_SSPORTNSPIN= wxNewId();
const long wxWebcamDBFrame::ID_SSMOTORNSPIN = wxNewId();
const long wxWebcamDBFrame::ID_SSMULTFRECSPIN = wxNewId();
const long wxWebcamDBFrame::ID_SSPORTN= wxNewId();
const long wxWebcamDBFrame::ID_SSMOTORN = wxNewId();
const long wxWebcamDBFrame::ID_SSMULTFREC = wxNewId();
const long wxWebcamDBFrame::ID_SSCURRENTANGLE = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_INTERVAL = wxNewId();
const long wxWebcamDBFrame::ID_SSCWICE_DIRECTION = wxNewId();
const long wxWebcamDBFrame::ID_SSCCWICE_DIRECTION = wxNewId();
//sTEPPER

const long wxWebcamDBFrame::ID_BUTTON5 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT13 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT11 = wxNewId();
const long wxWebcamDBFrame::ID_STATICTEXT14 = wxNewId();
const long wxWebcamDBFrame::ID_CUSTOM1 = wxNewId();
const long wxWebcamDBFrame::ID_PANEL2 = wxNewId();
const long wxWebcamDBFrame::ID_NOTEBOOK1 = wxNewId();
const long wxWebcamDBFrame::ID_CAMERA_PANEL = wxNewId();
const long wxWebcamDBFrame::idMenuQuit = wxNewId();
const long wxWebcamDBFrame::ID_MENUITEM_CONNECT = wxNewId();
const long wxWebcamDBFrame::ID_MENUITEM_DISCONNECT = wxNewId();
const long wxWebcamDBFrame::ID_MENUITEM_SETTINGS = wxNewId();
const long wxWebcamDBFrame::ID_MENUITEM_GUIDING2 = wxNewId();
const long wxWebcamDBFrame::ID_MENUITEM_HEADER = wxNewId();
const long wxWebcamDBFrame::idMenuAbout = wxNewId();
const long wxWebcamDBFrame::ID_STATUSBAR1 = wxNewId();
const long wxWebcamDBFrame::ID_TOOLBAR1 = wxNewId();
//*)

wxWebcamDBFrame* wxWebcamDBFrame::m_self=NULL;

//SMD_OpenComPort(5);

const long ID_MENUITEM_DD= wxNewId();

const long wxWebcamDBFrame::ID_GAUGE_TIMER1 = wxNewId();
const long wxWebcamDBFrame::ID_GUIDE_TIMER1 = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_COM_TIMER = wxNewId();
const long wxWebcamDBFrame::ID_STEPPER_CAPTURE_TIMER = wxNewId();

static const int gauge_ms = 1000; // refresh rate for gauge in [ms]

static const wxBrush histo_bkg(wxColour(128,128,128));

//BM:20090104 - added Command Events from Camera timers
DEFINE_EVENT_TYPE(wxEVT_WXAC_TIMER)
DEFINE_EVENT_TYPE(wxEVT_WXAC_FRAME)

BEGIN_EVENT_TABLE(wxWebcamDBFrame,wxFrame)
	//(*EventTable(wxWebcamDBFrame)
	//*)
	EVT_TIMER(ID_GAUGE_TIMER1,wxWebcamDBFrame::OnGaugeTimer)
	EVT_TIMER(ID_GUIDE_TIMER1,wxWebcamDBFrame::OnGuideTimer)
	EVT_TIMER(ID_STEPPER_COM_TIMER,wxWebcamDBFrame::OnStepperCOMTimer)
	EVT_TIMER(ID_STEPPER_CAPTURE_TIMER,wxWebcamDBFrame::OnStepperCaptureTimer)
	EVT_IDLE(wxWebcamDBFrame::OnIdle)
	EVT_COMMAND(ID_CAMERA_PANEL, wxEVT_WXAC_TIMER, wxWebcamDBFrame::OnUpdateCamData)
	EVT_COMMAND(ID_CAMERA_PANEL, wxEVT_WXAC_FRAME, wxWebcamDBFrame::OnUpdateCamData)
END_EVENT_TABLE()

wxWebcamDBFrame::wxWebcamDBFrame(wxWindow* parent,wxWindowID WXUNUSED(id))
: m_factory()
, m_gauge_timer(this,ID_GAUGE_TIMER1)
, m_gdir(1)
, m_guide_timer(this,ID_GUIDE_TIMER1)
, m_stepperCOM_timer(this, ID_STEPPER_COM_TIMER)
, m_stepperCapture_timer(this, ID_STEPPER_CAPTURE_TIMER)
, Stepper("C:\\Windows\\SMD004.dll")
{

	//(*Initialize(wxWebcamDBFrame)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer5;
	wxStaticText* StaticText2;
	wxBoxSizer* BoxSizer13;
	wxButton* Button1;
	wxFlexGridSizer* FlexGridSizer3;
	wxStaticText* StaticText19;
	wxPanel* video_panel;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxBoxSizer* BoxSizer12;
	wxButton* Button5;
	wxBoxSizer* BoxSizer14;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxStaticText* StaticText7;
	wxBoxSizer* BoxSizer17;
	wxBoxSizer* BoxSizer9;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer1_1;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxStaticText* StaticText17;
	wxStaticText* StaticText4;
	wxBoxSizer* BoxSizer25;
	wxCheckBox* ShowReticle;

	Create(parent, wxID_ANY, _("wxAstroCapture - Windows linuX Astronomy Capture"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVEBORDER));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(200,-1), wxNB_MULTILINE, _T("ID_NOTEBOOK1"));
	m_record_panel = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, m_record_panel, _("Video Device"));
	Button1 = new wxButton(m_record_panel, ID_DEVICE_PROPERTIES, _("Properties ..."), wxDefaultPosition, wxSize(-1,-1), 0, wxDefaultValidator, _T("ID_DEVICE_PROPERTIES"));
	Button1->SetToolTip(_("Adjust camera gain, brightness etc."));
	StaticBoxSizer1->Add(Button1, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	ShowReticle = new wxCheckBox(m_record_panel, ID_CHECKBOX5, _("Show Reticle"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	ShowReticle->SetValue(false);
	ShowReticle->SetToolTip(_("Show crosshair reticle overlay"));
	StaticBoxSizer1->Add(ShowReticle, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
	m_capture_btn = new wxButton(m_record_panel, ID_CAPTURE, _("Capture"), wxDefaultPosition, wxSize(68,-1), 0, wxDefaultValidator, _T("ID_CAPTURE"));
	m_capture_btn->SetToolTip(_("Press button to start/stop capture"));
	BoxSizer17->Add(m_capture_btn, 1, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_gauge1 = new wxGauge(m_record_panel, ID_GAUGE1, 10, wxDefaultPosition, wxSize(56,-1), 0, wxDefaultValidator, _T("ID_GAUGE1"));
	m_gauge1->SetToolTip(_("Activity indicates ongoing capture"));
	BoxSizer17->Add(m_gauge1, 1, wxTOP|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer17, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	m_pause_btn = new wxButton(m_record_panel, ID_BUTTON3, _("Pause"), wxDefaultPosition, wxSize(68,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	m_pause_btn->Disable();
	m_pause_btn->SetToolTip(_("Press button to pause/resume capture"));
	BoxSizer16->Add(m_pause_btn, 1, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_increment = new wxTextCtrl(m_record_panel, ID_TEXTCTRL1, _("1"), wxDefaultPosition, wxSize(56,-1), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	m_increment->SetToolTip(_("Frame number. Initial value to be \nused with next capture (FITS only)."));
	BoxSizer16->Add(m_increment, 1, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer16, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer15->Add(5,-1,0, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	MaxFrames_CheckBox = new wxCheckBox(m_record_panel, ID_CHECKBOX7, _("Max#"), wxDefaultPosition, wxSize(60,-1), 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	MaxFrames_CheckBox->SetValue(true);
	MaxFrames_CheckBox->SetToolTip(_("Enable Max number of frames"));
	BoxSizer15->Add(MaxFrames_CheckBox, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	BoxSizer15->Add(5,-1,1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	MaxFrames_SpinCtrl = new wxSpinCtrl(m_record_panel, ID_SPINCTRL4, _T("1"), wxDefaultPosition, wxSize(70,-1), 0, 1, 10000, 1, _T("ID_SPINCTRL4"));
	MaxFrames_SpinCtrl->SetValue(_T("1"));
	//MaxFrames_SpinCtrl->Disable();
	MaxFrames_SpinCtrl->SetToolTip(_("Max number of frames to capture"));
	BoxSizer15->Add(MaxFrames_SpinCtrl, 0, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer15, 1, wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	FlexGridSizer1->Add(-1,5,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, m_record_panel, _("Long exposures"));
	BoxSizer12 = new wxBoxSizer(wxVERTICAL);
	LE_CheckBox = new wxCheckBox(m_record_panel, ID_CHECKBOX1, _("Long exposure"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	LE_CheckBox->SetValue(false);
	LE_CheckBox->SetToolTip(_("Check to enable webcam long exposure"));
	BoxSizer12->Add(LE_CheckBox, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
	LE_Text = new wxStaticText(m_record_panel, ID_STATICTEXT1, _("[sec]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer14->Add(LE_Text, 1, wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);

	BoxSizer14->Add(LE_SpinCtrl1, 0, wxTOP|wxLEFT|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 4);
	BoxSizer12->Add(BoxSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticBoxSizer2->Add(BoxSizer12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_record_panel->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(m_record_panel);
	FlexGridSizer1->SetSizeHints(m_record_panel);
	m_guide_panel = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, m_guide_panel, _("Guide star tracking"));
	PickGuideStar = new wxButton(m_guide_panel, ID_BUTTON1, _("Pick guide star"), wxDefaultPosition, wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBoxSizer4->Add(PickGuideStar, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxVERTICAL);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(m_guide_panel, ID_STATICTEXT3, _("Ra:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer7->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	m_guide_dx = new wxStaticText(m_guide_panel, ID_STATICTEXT4, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer7->Add(m_guide_dx, 2, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6->Add(BoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(m_guide_panel, ID_STATICTEXT5, _("Dec:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	BoxSizer8->Add(StaticText4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	m_guide_dy = new wxStaticText(m_guide_panel, ID_STATICTEXT6, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	BoxSizer8->Add(m_guide_dy, 2, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6->Add(BoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	StaticText7 = new wxStaticText(m_guide_panel, ID_STATICTEXT7, _("Mag:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	BoxSizer10->Add(StaticText7, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	m_guide_mag = new wxStaticText(m_guide_panel, ID_STATICTEXT8, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	BoxSizer10->Add(m_guide_mag, 2, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6->Add(BoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	StaticBoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer5->Add(StaticBoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(-1,10,0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, m_guide_panel, _("Guiding commands"));
	GuideTelescope = new wxCheckBox(m_guide_panel, ID_CHECKBOX3, _("Guide telescope"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	GuideTelescope->SetValue(true);
	StaticBoxSizer5->Add(GuideTelescope, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, m_guide_panel, _("Reverse"));
	m_reverseRA = new wxCheckBox(m_guide_panel, ID_CHECKBOX4, _("RA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	m_reverseRA->SetValue(false);
	StaticBoxSizer6->Add(m_reverseRA, 1, wxTOP|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	m_reverseDEC = new wxCheckBox(m_guide_panel, ID_CHECKBOX6, _("DEC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	m_reverseDEC->SetValue(false);
	StaticBoxSizer6->Add(m_reverseDEC, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticBoxSizer5->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText17 = new wxStaticText(m_guide_panel, ID_STATICTEXT9, _("Dec"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer3->Add(StaticText17, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_decNSChoice = new wxChoice(m_guide_panel, ID_CHOICE2, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	m_decNSChoice->Append(_("None"));
	m_decNSChoice->Append(_("N and S"));
	m_decNSChoice->Append(_("N+ only"));
	m_decNSChoice->Append(_("S- only"));
	FlexGridSizer3->Add(m_decNSChoice, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	StaticBoxSizer5->Add(FlexGridSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer5->Add(StaticBoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(-1,10,0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer13 = new wxStaticBoxSizer(wxVERTICAL, m_guide_panel, _("Aggressiveness"));
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	m_staticText_RA = new wxStaticText(m_guide_panel, ID_STATICTEXT10, _("RA (k)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	BoxSizer13->Add(m_staticText_RA, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_RaAggrSpin = new wxSpinCtrlDbl(m_guide_panel, ID_SPINCTRL3, _T("1.0"), wxDefaultPosition, wxSize(70,-1), 0, 0, 100, 1, _T("ID_SPINCTRL3"));
	m_RaAggrSpin->SetValue(_T("1.0"));
	BoxSizer13->Add(m_RaAggrSpin, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer13->Add(BoxSizer13, 1, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
	StaticText19 = new wxStaticText(m_guide_panel, ID_STATICTEXT12, _("DEC (k)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	BoxSizer25->Add(StaticText19, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_DecAggrSpin = new wxSpinCtrlDbl(m_guide_panel, ID_SPINCTRL5, _T("1.0"), wxDefaultPosition, wxSize(70,-1), 0, 0, 100, 1, _T("ID_SPINCTRL5"));
	m_DecAggrSpin->SetValue(_T("1.0"));
	BoxSizer25->Add(m_DecAggrSpin, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer13->Add(BoxSizer25, 1, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button5 = new wxButton(m_guide_panel, ID_BUTTON2, _("Advanced..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer13->Add(Button5, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(StaticBoxSizer13, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_guide_panel->SetSizer(BoxSizer5);
	BoxSizer5->Fit(m_guide_panel);
	BoxSizer5->SetSizeHints(m_guide_panel);
	m_batch_panel = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer9 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxVERTICAL, m_batch_panel, _("Batch Processing"));
	m_batchCapture_btn = new wxButton(m_batch_panel, ID_BATCH_CAPTURE_BTN, _("Start Batch"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_BATCH_CAPTURE_BTN"));
	StaticBoxSizer7->Add(m_batchCapture_btn, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PauseBatchButton = new wxButton(m_batch_panel, ID_BUTTON5, _("Pause Batch"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	PauseBatchButton->Disable();
	StaticBoxSizer7->Add(PauseBatchButton, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(StaticBoxSizer7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, m_batch_panel, _("Status"));
	m_batch_status1 = new wxStaticText(m_batch_panel, ID_STATICTEXT13, _("Batch not running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	StaticBoxSizer8->Add(m_batch_status1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_batch_status2 = new wxStaticText(m_batch_panel, ID_STATICTEXT11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticBoxSizer8->Add(m_batch_status2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_batch_status3 = new wxStaticText(m_batch_panel, ID_STATICTEXT14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	StaticBoxSizer8->Add(m_batch_status3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(StaticBoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer11 = new wxBoxSizer(wxVERTICAL);
	m_batch_setup = new BatchSetup(m_batch_panel,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize);
	BoxSizer11->Add(m_batch_setup, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(BoxSizer11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_batch_panel->SetSizer(BoxSizer9);
	BoxSizer9->Fit(m_batch_panel);
	BoxSizer9->SetSizeHints(m_batch_panel);
/////////STEPPER

	m_stepper_panel = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer1_1 = new wxFlexGridSizer(40, 2,0,0);


    m_openStepperCOMPort_btn = new wxButton(m_stepper_panel, ID_OPEN_STEPPER_COM_PORT_BTN, _("Open"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_OPEN_STEPPER_COM_PORT_BTN"));
	m_openStepperCOMPort_btn->SetBackgroundColour(wxColor("green"));
	FlexGridSizer1_1->Add(m_openStepperCOMPort_btn,0,0,0,0);

	m_setStepperParam_btn = new wxButton(m_stepper_panel, ID_SET_STEPPER_PARAM_BTN, _("Set"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_SET_STEPPER_PARAM_BTN"));
	FlexGridSizer1_1->Add(m_setStepperParam_btn,0,0,0,0);
	SS_PortNText = new wxStaticText(m_stepper_panel, ID_SSPORTN, _("Port:"));
	FlexGridSizer1_1->Add(SS_PortNText, 0,0,0,0);
    SS_PortNSpin = new wxSpinCtrl(m_stepper_panel, ID_SSPORTNSPIN, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 255, 0, _T("ID_SSPORTNSPIN"));
	SS_PortNSpin->SetToolTip(_("COMPort for Stepper"));
	FlexGridSizer1_1->Add(SS_PortNSpin, 0, wxMINIMIZE);
	SS_MotorNText = new wxStaticText(m_stepper_panel, ID_SSMOTORN, _("Motor:"));
	FlexGridSizer1_1->Add(SS_MotorNText, 0, wxMINIMIZE);
    SS_MotorNSpin = new wxSpinCtrl(m_stepper_panel, ID_SSMOTORNSPIN, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 255, 0, _T("ID_SSMOTORNSPIN"));
	SS_MotorNSpin->SetToolTip(_("Stepper index"));
	FlexGridSizer1_1->Add(SS_MotorNSpin, 0, wxMINIMIZE);
	m_resetStepperCounter_btn = new wxButton(m_stepper_panel, ID_RESET_STEPPER_COUNTER_BTN, _("ResetC"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_RESET_STEPPER_COUNTER_BTN"));
	FlexGridSizer1_1->Add(m_resetStepperCounter_btn,0, wxMINIMIZE);
	m_resetStepper_btn = new wxButton(m_stepper_panel, ID_RESET_STEPPER_BTN, _("ResetM"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_RESET_STEPPER_BTN"));
	FlexGridSizer1_1->Add(m_resetStepper_btn,0, wxMINIMIZE);
	m_moveStepperCWice_btn = new wxButton(m_stepper_panel, ID_MOVE_STEPPER_CWICE_BTN, _("<<<"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_MOVE_STEPPER_CWICE_BTN"));
	FlexGridSizer1_1->Add(m_moveStepperCWice_btn,0, wxMINIMIZE);
	m_moveStepperCCWice_btn = new wxButton(m_stepper_panel, ID_MOVE_STEPPER_CCWICE_BTN, _(">>>"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_MOVE_STEPPER_CCWICE_BTN"));
	FlexGridSizer1_1->Add(m_moveStepperCCWice_btn,0, wxMINIMIZE);

	SS_CalibrText = new wxStaticText(m_stepper_panel, ID_SSCALIBR, _("CalibrK:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSCALIBR"));
	FlexGridSizer1_1->Add(SS_CalibrText, 0, wxMINIMIZE);
    SS_CalibrSpin = new wxSpinCtrlDbl(m_stepper_panel, ID_SSCALIBRSPIN, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0.000000001, 999999, 200, _T("ID_SSCALIBRSPIN"));
	SS_CalibrSpin->SetToolTip(_("Calibration of Stepping"));
	FlexGridSizer1_1->Add(SS_CalibrSpin, 0, wxMINIMIZE);

	SS_SetAng = new wxStaticText(m_stepper_panel, ID_SSANG, _("Ang.[deg]:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSANG"));
	FlexGridSizer1_1->Add(SS_SetAng, 0, wxMINIMIZE);
	SS_AngSpin = new wxSpinCtrlDbl(m_stepper_panel, ID_SSANG, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0.000001, 10000, 1, _T("ID_SSANG"));
	SS_AngSpin->SetToolTip(_("Angle for Stepping"));
	FlexGridSizer1_1->Add(SS_AngSpin, 0, wxMINIMIZE);
    SS_IText = new wxStaticText(m_stepper_panel, ID_SSI, _("I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSI"));
	FlexGridSizer1_1->Add(SS_IText, 0, wxMINIMIZE);
	m_stepperIChoice = new wxChoice(m_stepper_panel, ID_STEPPER_I_CHOICE, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_STEPPER_I_CHOICE"));
	m_stepperIChoice->Append(_("0"));
	m_stepperIChoice->Append(_("0.4"));
	m_stepperIChoice->Append(_("0.8"));
	m_stepperIChoice->Append(_("1.2"));
	m_stepperIChoice->Select(1);
	FlexGridSizer1_1->Add(m_stepperIChoice,0, wxMINIMIZE);
    SS_IStopText = new wxStaticText(m_stepper_panel, ID_SSISTOP, _("I_Stop:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSISTOP"));
	FlexGridSizer1_1->Add(SS_IStopText, 0, wxMINIMIZE);
    m_stepperIStopChoice = new wxChoice(m_stepper_panel, ID_STEPPER_I_STOP_CHOICE, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_STEPPER_I_STOP_CHOICE"));
	m_stepperIStopChoice->Append(_("0"));
	m_stepperIStopChoice->Append(_("0.4"));
	m_stepperIStopChoice->Append(_("0.8"));
	m_stepperIStopChoice->Append(_("1.2"));
	m_stepperIStopChoice->Select(0);
	FlexGridSizer1_1->Add(m_stepperIStopChoice,0, wxMINIMIZE);
    SS_WModeText = new wxStaticText(m_stepper_panel, ID_SSWMODE, _("W_Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSWMODE"));
	FlexGridSizer1_1->Add(SS_WModeText, 0, wxMINIMIZE);
    m_stepperWModeChoice = new wxChoice(m_stepper_panel, ID_STEPPER_W_MODE_CHOICE, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_STEPPER_W_MODE_CHOICE"));
	m_stepperWModeChoice->Append(_("Wave"));
	m_stepperWModeChoice->Append(_("Full"));
	m_stepperWModeChoice->Append(_("1/2"));
	m_stepperWModeChoice->Select(0);
	FlexGridSizer1_1->Add(m_stepperWModeChoice,0, wxMINIMIZE);
    SS_FrecText = new wxStaticText(m_stepper_panel, ID_SSFREC, _("Frec:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SSFREC"));
	FlexGridSizer1_1->Add(SS_FrecText, 0, wxMINIMIZE);
    SS_FrecSpin = new wxSpinCtrl(m_stepper_panel, ID_SSFRECSPIN, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 1, 255, 200, _T("ID_SSFRECSPIN"));
	SS_FrecSpin->SetToolTip(_("Frec. of Stepping"));
	FlexGridSizer1_1->Add(SS_FrecSpin, 0, wxMINIMIZE);

	SS_MultFrecText = new wxStaticText(m_stepper_panel, ID_SSMULTFREC, _("MultF:"));
	FlexGridSizer1_1->Add(SS_MultFrecText, 0, wxMINIMIZE);
    SS_MultFrecSpin = new wxSpinCtrl(m_stepper_panel, ID_SSMULTFRECSPIN, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 1, 255, 1, _T("ID_SSMULTFRECSPIN"));
	SS_MultFrecSpin->SetToolTip(_("Frec. Multypl."));
	FlexGridSizer1_1->Add(SS_MultFrecSpin, 0, wxMINIMIZE);

    SS_StepperInterval = new wxSpinCtrl(m_stepper_panel, ID_STEPPER_INTERVAL, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 1, 10000000, 100000, _T("ID_STEPPER_INTERVAL"));
	SS_StepperInterval->SetToolTip(_("Interval btw. steps"));
	FlexGridSizer1_1->Add(SS_StepperInterval);

    SS_StepperCapture_btn = new wxButton(m_stepper_panel, ID_STEPPER_CAPTURE_BTN, _("Capture"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_STEPPER_CAPTURE_BTN"));
	FlexGridSizer1_1->Add(SS_StepperCapture_btn,0, wxMINIMIZE);

	SS_CWiceDirection = new wxButton(m_stepper_panel, ID_SSCWICE_DIRECTION, _("<<"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_SSCWICE_DIRECTION"));
	FlexGridSizer1_1->Add(SS_CWiceDirection);
	SS_CCWiceDirection = new wxButton(m_stepper_panel, ID_SSCCWICE_DIRECTION, _(">>"), wxDefaultPosition, wxSize(-1,25), 0, wxDefaultValidator, _T("ID_SSCCWICE_DIRECTION"));
	FlexGridSizer1_1->Add(SS_CCWiceDirection);

	SS_CurrentAngle = new wxStaticText(m_stepper_panel, ID_SSCURRENTANGLE, _("0.0 deg."));
	FlexGridSizer1_1->Add(SS_CurrentAngle, 2, wxTOP|wxALIGN_LEFT, 4);



	//StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, m_stepper_panel, _("Exposure Meter"));
	//BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	//FlexGridSizer1_1->Add(StaticText1);
	m_meter_channel = new wxChoice(m_stepper_panel, ID_CHOICE1, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	m_meter_channel->Append(_("L"));
	m_meter_channel->Append(_("R"));
	m_meter_channel->Append(_("G"));
	m_meter_channel->Append(_("B"));
	m_meter_channel->SetToolTip(_("Select colour channel for histogram"));
	FlexGridSizer1_1->Add(m_meter_channel);
	m_exposure_meter_panel = new wxPanel(m_stepper_panel, ID_PANEL3, wxDefaultPosition, wxSize(128,64), 0, _T("ID_PANEL3"));
	m_exposure_meter_panel->SetMaxSize(wxSize(128,64));
	m_exposure_meter_panel->SetToolTip(_("Live histogram"));
    //StaticText1 = new wxStaticText(m_stepper_panel, ID_STATICTEXT2, _("Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    LE_SpinCtrl1 = new wxSpinCtrlDbl(m_exposure_meter_panel, ID_SPINCTRL1, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	LE_SpinCtrl1->SetToolTip(_("Length of long exposure in seconds"));
	FlexGridSizer1_1->Add(LE_SpinCtrl1);






	//BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	m_activate_exposure_meter = new wxCheckBox(m_stepper_panel, ID_CHECKBOX2, _("Enable "), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	m_activate_exposure_meter->SetValue(false);
	m_activate_exposure_meter->SetToolTip(_("Check to enable live histogram"));
	FlexGridSizer1_1->Add(m_activate_exposure_meter);
	m_meter_scale = new wxSpinCtrlDbl(m_stepper_panel, ID_SPINCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL2"));
	m_meter_scale->SetToolTip(_("Scale factor for histogram"));
	FlexGridSizer1_1->Add(m_meter_scale);
    //FlexGridSizer1_1->Add(m_exposure_meter_panel);

    //FlexGridSizer1_1->SetVGap(0);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4->Add(FlexGridSizer1_1);
    BoxSizer4->Add(m_exposure_meter_panel);
    m_stepper_panel->SetSizer(BoxSizer4);
	FlexGridSizer1_1->Fit(m_stepper_panel);
	FlexGridSizer1_1->SetSizeHints(m_stepper_panel);

/////////sTEPPER
	Notebook1->AddPage(m_record_panel, _("Rec"), false);
	Notebook1->AddPage(m_guide_panel, _("Guide"), false);
	Notebook1->AddPage(m_batch_panel, _("Batch"), false);
	Notebook1->AddPage(m_stepper_panel, _("Stepper"), false);
	BoxSizer1->Add(Notebook1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	video_panel = new wxPanel(this, ID_CAMERA_PANEL, wxDefaultPosition, wxSize(655,495), wxTAB_TRAVERSAL, _T("ID_CAMERA_PANEL"));
	video_panel->SetMinSize(wxSize(-1,-1));
	video_panel->SetMaxSize(wxSize(-1,-1));
	BoxSizer2->Add(video_panel, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1->Add(BoxSizer2, 64, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	SetSizer(BoxSizer1);
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Exit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&File"));
	Menu2 = new wxMenu();
	MenuItem2 = new wxMenuItem(Menu2, ID_MENUITEM_CONNECT, _("Connect"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(MenuItem2);
	MenuItem3 = new wxMenuItem(Menu2, ID_MENUITEM_DISCONNECT, _("Disconnect"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(MenuItem3);
	Menu2->AppendSeparator();
	MenuBar1->Append(Menu2, _("Camera"));
	Menu3 = new wxMenu();
	MenuItem7 = new wxMenuItem(Menu3, ID_MENUITEM_SETTINGS, _("Settings..."), wxEmptyString, wxITEM_NORMAL);
	Menu3->Append(MenuItem7);
	MenuItemGuiding = new wxMenuItem(Menu3, ID_MENUITEM_GUIDING2, _("Guiding..."), wxEmptyString, wxITEM_NORMAL);
	Menu3->Append(MenuItemGuiding);
	MenuItem9 = new wxMenuItem(Menu3, ID_MENUITEM_HEADER, _("FITS Header..."), wxEmptyString, wxITEM_NORMAL);
	Menu3->Append(MenuItem9);
	MenuBar1->Append(Menu3, _("Options"));
	Menu4 = new wxMenu();
	MenuItem8 = new wxMenuItem(Menu4, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
	Menu4->Append(MenuItem8);
	MenuBar1->Append(Menu4, _("Help"));
	SetMenuBar(MenuBar1);
	m_statusbar = new wxStatusBarEx(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
	int __wxStatusBarWidths_1[3] = { -30, -40, -50 };
	int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
	m_statusbar->SetFieldsCount(3,__wxStatusBarWidths_1);
	m_statusbar->SetStatusStyles(3,__wxStatusBarStyles_1);
	SetStatusBar(m_statusbar);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_DEVICE_PROPERTIES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnVideoDeviceProperties);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnShowReticleClick);
	Connect(ID_CAPTURE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnCaptureClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnPauseClick);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxWebcamDBFrame::OnIncrementText);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMaxFrames_CheckBoxClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnLE_CheckBoxClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxWebcamDBFrame::OnLE_SpinCtrl1Change);
	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMeterChannelSelect);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnActivateExposureMeterClick);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxWebcamDBFrame::OnExposureMeteScaleChange);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnPickGuideStarClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnGuideTelescopeClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnReverseRAClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnReverseDECClick);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnDecNSChoiceSelect);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxWebcamDBFrame::OnRaAggrSpinChange);
	Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxWebcamDBFrame::OnDecAggrSpinChange);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnAdvancedGuideParamsClick);
	Connect(ID_BATCH_CAPTURE_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnStartBatchButtonClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnPauseBatchButtonClick);
	Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&wxWebcamDBFrame::OnNotebook1PageChanged);
	video_panel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&wxWebcamDBFrame::OnvideoPanelLeftDown,0,this);
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnQuit);
	Connect(ID_MENUITEM_CONNECT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMenuItemConnect);
	Connect(ID_MENUITEM_DISCONNECT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMenuItemDisconnect);
	Connect(ID_MENUITEM_SETTINGS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMenuItemSettings);
	Connect(ID_MENUITEM_GUIDING2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMenuItemOptionsGuiding);
	Connect(ID_MENUITEM_HEADER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnMenuItemImageHeader);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::OnAbout);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wxWebcamDBFrame::OnClose);
	///Stepper
	Connect(ID_SET_STEPPER_PARAM_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnSetStepperParamClick);
	Connect(ID_OPEN_STEPPER_COM_PORT_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnOpenStepperCOMPortClick);
	Connect(ID_MOVE_STEPPER_CWICE_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnStepperMoveCWiceClick);
	Connect(ID_MOVE_STEPPER_CCWICE_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnStepperMoveCCWiceClick);
	Connect(ID_RESET_STEPPER_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnResetSHDClick);
	Connect(ID_RESET_STEPPER_COUNTER_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnResetStepperCounterClick);
    Connect(ID_STEPPER_CAPTURE_BTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxWebcamDBFrame::OnStepperCaptureClick);
    Connect(ID_SSCWICE_DIRECTION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)& wxWebcamDBFrame::OnCWStepperDirectionClick);
    Connect(ID_SSCCWICE_DIRECTION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)& wxWebcamDBFrame::OnCCWStepperDirectionClick);

	///sTEPPER
	//*)

    /* ======================================================================== */
    /* =============Manual initialisation ===================================== */
    /* ======================================================================== */

	ToolBar1 = new wxMainToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	SetToolBar(ToolBar1);

   // recompute the size after adding the toolbar
   BoxSizer1->Fit(this);
   BoxSizer1->SetSizeHints(this);

#if defined(_WXMSW_)
   {
      // Due to a bug in wxSmith, the following is coded manually
      // this bug was reported fixed in CB 4749
      // wxSmith: Fixed bug #12596 - Code generates "new wxMenuItem()" instead of "new wxMenu()"
      const long ID_MENUITEM_FORMAT = wxNewId();
      const long ID_MENUITEM_SOURCE = wxNewId();
      wxMenu* DriverMenu = new wxMenu();
      wxMenuItem* FormatItem = new wxMenuItem(DriverMenu, ID_MENUITEM_FORMAT, _("Format"), wxEmptyString, wxITEM_NORMAL);
      DriverMenu->Append(FormatItem);
      wxMenuItem* SourceItem = new wxMenuItem(DriverMenu, ID_MENUITEM_SOURCE, _("Source"), wxEmptyString, wxITEM_NORMAL);
      DriverMenu->Append(SourceItem);
      Menu2->Append(ID_MENUITEM_DD, _("Driver Dialogs"), DriverMenu, wxEmptyString);
      Connect(ID_MENUITEM_FORMAT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::Onm_format_btnClick);
      Connect(ID_MENUITEM_SOURCE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWebcamDBFrame::Onm_source_btnClick);
      Menu2->Enable(ID_MENUITEM_DD,false);
   }
#endif

   // set the window positio to what it used to be last time
   long frame_x=0,frame_y=0;
   if(m_factory.config()->Read(_T("FramePos_x"),&frame_x)
   && m_factory.config()->Read(_T("FramePos_y"),&frame_y)) {
      Move(wxPoint(frame_x,frame_y));
   }

   // we really want C locale, but it seems not available, so try english instead
   // The purpose is to make sure all numbers are formatted using full stop
   // instead of comma when the users locale is something different than C locale.
   // This brute force seems like the only way.
   m_locale.Init(wxLANGUAGE_ENGLISH_US);
   //CA m_locale.Init(wxLocale::GetSystemLanguage());

   wxIconBundle icons;
   icons.AddIcon(wxIcon(&spcn00nc_16x16_xpm[0]));
   icons.AddIcon(wxIcon(&spcn00nc_64x64_xpm[0]));
   SetIcons(icons);

 //  m_statusbar->SetStatusWidths(3,m_statusbar__widths);

   m_self = this;

   // replace the dummy video_panel with the webcam window
   // The dummy panel is there to allow wxWidgets calculate the main frame size properly
   m_factory.setWebcam(wxWebcam::Construct(this,ID_CAMERA_PANEL));
//   m_factory.ConstructLEport();
   ReplaceCamera(video_panel,m_factory.webcam());


// Sample use of wxMessageSink

//   wxArrayString messages;
//   messages.Add(wxT("This is a modeless dialog, owned by the application"));
//   messages.Add(wxT("This is the second line"));
//   messages.Add(wxT("This is the third line"));
//   messages.Add(wxString::Format(wxT("Line: %i, File %s "),__LINE__,wxT(__FILE__)));
//   wxMessageSink(messages,wxT("MessageSink Example"));


   Init();





}

void wxWebcamDBFrame::ReplaceCamera(wxWindow* old_camera, wxCamera* new_camera)
{

   if(wxCamera* camera = dynamic_cast<wxCamera*>(old_camera)) {
      bool show_reticle = camera->isReticleEnabled();
      camera->DisconnectCamera();
      new_camera->EnableReticle(show_reticle);
   }

   m_factory.setCamera(new_camera);
   new_camera->SetBackgroundStyle(wxBG_STYLE_CUSTOM); // used with double buffered drawing (see manual)
//   BoxSizer2->Replace(old_camera,new_camera);

   // we have to detach the old camera and add the new one instead of a simple replace,
   // because otherwise the styles are not propely maintained
   long style = wxEXPAND; //wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP;
   if(new_camera->IsWebcam())style = style;//!20080907BM NOT LONGER |wxSHAPED;
   BoxSizer2->Detach(old_camera);
   BoxSizer2->Add(new_camera,1,style,0);
   old_camera->Destroy();
   BoxSizer2->Layout();
	Layout();
}

void wxWebcamDBFrame::Init()
{

fWheelCalibration = 0.5;
wxString comment_val;
auto_exposure = wxF()->getFitsHeaderValue(wxT("COMMENT"), comment_val);
fWheelDirection = 0;

   fBaseMap[_T("OP06")] = 0.251188643150958;
   fBaseMap[_T("OP09")] = 0.12589254117941673;
   fBaseMap[_T("OP18")] = 0.015848931924611134;


wxF()->getFitsHeaderValue(wxT("FILTMAP"), fWheelString);

   wxStringTokenizer tokenizer(fWheelString, ";");
        while ( tokenizer.HasMoreTokens() )
        {
            wxString token = tokenizer.GetNextToken();
            filtersArray.Add(token);
            }
currentFilterIndex = filtersArray.size();


for (int i=0; i<filtersArray.size(); i++){
    double fres = 1;

    wxStringTokenizer tokenizer(filtersArray[i], ", ");
        while ( tokenizer.HasMoreTokens() )
        {
            wxString token = tokenizer.GetNextToken();
            fres *= fBaseMap[token];
            }

    fMap[filtersArray[i]] = fres;
}


   ResetStepperAngle();
   LE_SpinCtrl1->SetRange(0.001,3600.0);
   LE_SpinCtrl1->SetValue(0.6);
   LE_SpinCtrl1->SetIncrement(0.1);
   UpdateLEcontrols();

   //SS_FrecSpin->SetValue(78);
   SS_PortNSpin->SetValue(5);
   SS_CCWiceDirection->Enable(0);
   m_exposure_meter_panel->SetBackgroundStyle(wxBG_STYLE_CUSTOM); // used with double buffered drawing (see manual)
   m_meter_scale->SetRange(0.0,10.0);
   m_meter_scale->SetValue(0.1);
   m_meter_scale->SetIncrement(0.01);
   m_meter_channel->SetSelection(0);

   m_exposure_meter_active = m_activate_exposure_meter->IsChecked();

   m_exposure_meter_scale = m_meter_scale->GetValue();

   m_guide_active = true;

   bool reverseRA,reverseDEC;
   wxGuidingConfig::DECguiding dec;
   wxGuidingConfig::getGuidingOptions(reverseRA,reverseDEC,dec);

   m_reverseRA->SetValue(reverseRA);
   m_reverseDEC->SetValue(reverseDEC);
   m_decNSChoice->SetSelection(dec);

   m_RaAggrSpin->SetRange(0.0,100.0);
   m_RaAggrSpin->SetIncrement(0.5);

   m_DecAggrSpin->SetRange(0.0,100.0);
   m_DecAggrSpin->SetIncrement(0.5);

   UpdateGuiderTuning();
   ATrtAddr = 255;
   isStepperConnected = false;
}

void wxWebcamDBFrame::UpdateGuiderTuning()
{
   // skip this update if camera is artemis
   wxArtcam* artcam = wxF()->artcam();
   if(artcam)return;

   if(wxGuider* guider = wxF()->guider()) {
      m_RaAggrSpin->SetValue(guider->raK());
      m_DecAggrSpin->SetValue(guider->decK());
   }
}

void wxWebcamDBFrame::UpdateIncrement()
{
   // update increment control if different from policy value
   long p_incr = wxF()->getNamePolicyFile()->GetIncrement();
   long c_incr = 0;
   wxString label = m_increment->GetValue();
   if(label.ToLong(&c_incr)) {
      if(p_incr != c_incr) {
         m_increment->SetValue(wxString::Format(wxT("%d"),p_incr));
      }
   }

   // control enabling of the increment field
   bool enabled = false;
   wxCamera* cam = wxF()->cam();
   bool avi_container =  wxF()->containerFormat() == ECF_AVI;
   if(cam->IsConnected()) {
      if(avi_container || cam->IsCapturing() || cam->IsCapturePausing() ) enabled = false;
      else enabled = true;
   }

   if(m_increment->IsEnabled() != enabled) m_increment->Enable(enabled);
}


void wxWebcamDBFrame::OnIncrementText(wxCommandEvent& event)
{
    wxString label = event.GetString();
    long incr = 0;
    if(label.ToLong(&incr)) {
       size_t increment = (size_t)incr;
       wxF()->getNamePolicyFile()->SetIncrement(increment);
    }
}

void wxWebcamDBFrame::UpdateStatusBar()
{
   wxCamera* cam = wxF()->cam();
   if(cam->IsCapturing()) {
      wxTimeSpan span = wxDateTime::UNow() -  m_start_capture;
      wxLongLong msec = span.GetMilliseconds();
      double sec = msec.ToDouble()/1000.;
      int nframes = cam->FramesCaptured();
      double fps = nframes/sec;
      wxString captured;

      if(MaxFrames_CheckBox->IsChecked()) {
         if(nframes >= MaxFrames_SpinCtrl->GetValue()) {
            StopCapture();
         }
      }

      if (cam->IsWebcam()) {
         wxLongExpoPort* le = wxF()->webcam()->LongExpoPort();
         if(le && le->IsLXmodeOn()) {
            captured.Printf(_T("Frames captured %d, (%d s)"),nframes ,int(sec));
         }
         else {
            captured.Printf(_T("Frames captured %d, (%.1f s, %.1f fps)"),nframes ,sec,fps);
         }
      }
      else {
         // non streaming cam (single frame only)
         captured.Printf(_T("Frames captured %d, (%d s)"),nframes ,int(sec));
      }
      m_statusbar->SetStatusText(captured, 1);
   }

   m_statusbar->SetStatusText(wxFactory::singleton()->captureFolder(), 0);
   // no need to repeat camera name here, it is in the window title
   m_statusbar->SetStatusText(cam->CameraStatus(), 2);

}

void wxWebcamDBFrame::OnActivateExposureMeterClick(wxCommandEvent& WXUNUSED(event))
{
   m_exposure_meter_active = m_activate_exposure_meter->IsChecked();
   ClearExposureMeter();
}

void wxWebcamDBFrame::OnExposureMeteScaleChange(wxSpinEvent& WXUNUSED(event))
{
   m_exposure_meter_scale = m_meter_scale->GetValue();
}

void wxWebcamDBFrame::OnMeterChannelSelect(wxCommandEvent& event)
{
   wxHistogram::FrameChannel channel = (wxHistogram::FrameChannel)event.GetInt();
   wxF()->cam()->Histogram().SetChannel(channel);
}

void wxWebcamDBFrame::ClearExposureMeter()
{
   //BM: using double buffer to avoid flickering
   wxClientDC ndc(m_exposure_meter_panel);  // outside paint event use wxClientDC !!!
   PrepareDC(ndc);
   wxCoord w, h;
   ndc.GetSize(&w, &h);
   wxBufferedDC dc(&ndc,wxSize(w,h));  // outside OnPaint events

   dc.SetFont(ndc.GetFont());
   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(histo_bkg);
   dc.DrawRectangle(0,0,w,h);
   dc.SetTextForeground(wxColour(150,0,0));
   dc.GetTextExtent(wxT("X"),&w,&h);
   if(!m_exposure_meter_active){
      dc.DrawText(wxT("Histogram"), 30,25-h/2);
      dc.DrawText(wxT("(disabled)"), 30,25+h/2);
   }
}

void wxWebcamDBFrame::UpdateFWheelString()
{
    wxString tmpfMap;
    wxF()->getFitsHeaderValue(wxT("FILTMAP"), tmpfMap);
if (tmpfMap != fWheelString){
   filtersArray.empty();
    wxStringTokenizer tokenizer(fWheelString, ";");
        while ( tokenizer.HasMoreTokens() )
        {
            wxString token = tokenizer.GetNextToken();
            filtersArray.Add(token);
            }

            }
}
void wxWebcamDBFrame::UpdateExposureMeter()
{
   if(!m_exposure_meter_active){
      ClearExposureMeter();
      return;
   }

//   wxWebcam* webcam = wxFactory::singleton()->webcam();
   wxCamera* cam = wxF()->cam();
   if(cam->IsConnected()) {
      if(cam->Histogram().OK()) {
         //BM: using double buffer to avoid flickering
         wxClientDC ndc(m_exposure_meter_panel);  // outside paint event use wxClientDC !!!
         PrepareDC(ndc);
         wxCoord w, h;
         ndc.GetSize(&w, &h);
         wxBufferedDC dc(&ndc,wxSize(w,h));  // outside OnPaint events
         dc.SetFont(ndc.GetFont());

         // draw the background
         dc.SetPen(*wxBLACK_PEN);
         dc.SetBrush(histo_bkg);
         dc.DrawRectangle(0,0,w,h);

         // draw the actual histogram using a colour matching the channel
         wxHistogram::FrameChannel channel = cam->Histogram().Channel();
         switch(channel) {
            case wxHistogram::Rchan: { dc.SetPen(wxPen(wxColour(128,0,0))); break;}
            case wxHistogram::Gchan: { dc.SetPen(wxPen(wxColour(0,128,0))); break;}
            case wxHistogram::Bchan: { dc.SetPen(wxPen(wxColour(0,0,128))); break;}
            default:                 { dc.SetPen(*wxBLACK_PEN); break;}
         }
         /// GETTING MIN MAX WOULD BE:
      //   unsigned short minE = cam->Histogram().MinExposure(channel);
      //   unsigned short maxE = cam->Histogram().MaxExposure(channel);

         wxHistogram& histogram = cam->Histogram();
         double size_scale = histogram.SizeScaleFactor();
         double display_scale = m_exposure_meter_scale*size_scale;

         int hs = histogram.Size();
         for(int i=0; i<hs; i++) {
            int count = int(display_scale*histogram.Value(i));
            if(count>0)dc.DrawLine(i,h,i,h-count);
         }

         if(cam->IsWebcam() && !histogram.MonoImage()) {
            // if camera provides white balance info, display it
            unsigned short maxR = histogram.MaxExposure(wxHistogram::Rchan);
            unsigned short maxG = histogram.MaxExposure(wxHistogram::Gchan);
            unsigned short maxB = histogram.MaxExposure(wxHistogram::Bchan);

            int cw = GetCharWidth();
            dc.SetTextForeground(wxColour(200,0,0));
            dc.DrawText(wxString::Format(wxT("%i"),maxR),2,0);
            dc.SetTextForeground(wxColour(0,255,0));
            dc.DrawText(wxString::Format(wxT("%i"),maxG),w/2-cw,0);
            dc.SetTextForeground(wxColour(0,0,128));
#ifdef _WXMSW_
            dc.DrawText(wxString::Format(wxT("%i"),maxB),w-4*cw-2,0);
#else
            dc.DrawText(wxString::Format(wxT("%i"),maxB),w-3*cw-2,0);
#endif
         }
      }
   }
}

wxWebcamDBFrame::~wxWebcamDBFrame()
{
   wxBusyCursor busy;
   ShutdownAll();
   m_self = NULL;
	//(*Destroy(wxWebcamDBFrame)
	//*)
}

void wxWebcamDBFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
   wxBusyCursor busy;
   ShutdownAll();

   // close application
   Close();
}

void wxWebcamDBFrame::ShutdownAll()
{
   // make sure capture is switched off
   StopCapture();
   // make sure LE mode is switched off
   if(wxWebcam* webcam = wxF()->webcam()) {
      webcam->SwitchLE(false);
   }
   // disconnect camera
   wxF()->cam()->DisconnectCamera();
   // disconnect stepper
   Stepper.SMD_CloseComPort();
   Stepper.~SMDDll();
}

void wxWebcamDBFrame::OnClose(wxCloseEvent& event)
{
   int fx(0),fy(0);
   GetScreenPosition(&fx,&fy);
   if(fx > -1 && fy > -1) {
      long framepos_x(fx),framepos_y(fy);
      wxF()->config()->Write(_T("FramePos_x"),framepos_x);
      wxF()->config()->Write(_T("FramePos_y"),framepos_y);
   }
   event.Skip();
}

void wxWebcamDBFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(_("wxAstroCapture"));
    info.SetVersion(_(MyAppVer));
    info.SetDescription(wxbuildinfo(long_f));

    info.AddDeveloper(_("Martin Burri, Switzerland"));
#if defined(_WXMSW_)
    info.AddDeveloper(_("\nCarsten Arnholm, Norway"));// must force line feed on windows
#else
    info.AddDeveloper(_("Carsten Arnholm, Norway"));
#endif

    info.SetCopyright(_T("(C) 2007,2008,2009,2010 Carsten Arnholm & Martin Burri"));
    info.SetWebSite(_T("http://arnholm.org/astro/software/wxAstroCapture/"));
    wxAboutBox(info);
}

int wxWebcamDBFrame::Contains(wxArrayString& cameras,const wxString& substr)
{
   for(size_t i=0; i<cameras.Count(); i++) {
      const wxString& camera = cameras[i];
      if(camera.Contains(substr))return int(i);
   }
   return -1;
}

void wxWebcamDBFrame::OnMenuItemConnect(wxCommandEvent& WXUNUSED(event))
{
   wxArrayString cameras;
   wxFactory::CameraTypeVector ctypes;
   if(wxF()->EnumerateCameras(this,cameras,ctypes)>0) {
      wxString selected = cameras[0]; // default selection when only one
      ECType ctype      = ctypes[0];  // selected camera type: webcam, artemis etc.
      if(cameras.size() > 1) {
         // More than one camera available
         // Ask user to choose which one

         wxSingleChoiceDialog dialog(this,_("Please select camera"),_("Camera chooser"),cameras);

         // expand the dialog width by 30% to enable long camera descriptions
         wxSize dsize = dialog.GetBestSize();
         dsize.SetWidth(dsize.GetWidth()*1.3);
         dialog.SetSize(dsize);

         // prefer cameras offering 640x480 resolution
         int idx_default = Contains(cameras,wxT("640x480"));
         if(idx_default > 0) {
            dialog.SetSelection(idx_default);
         }
         if(wxID_OK == dialog.ShowModal()) {
            selected = dialog.GetStringSelection();
            ctype = ctypes[dialog.GetSelection()];

         }
         else {
            selected = wxT(""); // nothing selected
         }
      }

      if(selected.length() > 0) {

         wxBusyCursor busy;

         // install a new camera of correct type
         wxCamera* old_camera = wxF()->cam();
         wxCamera* new_camera = wxCamera::Construct(ctype,this,ID_CAMERA_PANEL);
         ReplaceCamera(old_camera,new_camera);
         if (new_camera->IsWebcam()) {
            if(wxF()->lePort()->IsInitialised() ) {
               // nothing to do, but the side effect is that the LE port is
               // initialised before the camera is connected
            }
         }

         bool enable_guiding = true;

         // connect to the selected instance
         bool camOK = false;

         if(new_camera) {

            // pre-load exposure value to camera (especially for Artemis)
            double exposure = LE_SpinCtrl1->GetValue();
            new_camera->SetLEduration((unsigned long)(exposure*1000.0) );

            // connect to camera
            camOK = new_camera->ConnectCamera(selected);
            if(camOK) {
               SetTitle(new_camera->CameraName() + wxT(" - wxAstroCapture"));
            }
            else {
               SetTitle(wxT("wxAstroCapture - Warning: Camera failed to connect"));
            }

            //  ToolBar1->CamEnable();
            ToolBar1->InitToolBar();
            // disable guide tab when camera does not support it
            enable_guiding = new_camera->SupportsGuiding();
         }

         #if defined(_WXMSW_)
            // mask the Driver Dialog menu item when the feature is not supported on this platform
            // or not by this camera
            Menu2->Enable(ID_MENUITEM_DD,new_camera->HasDriverDialogs());
         #endif

         m_batch_setup->Init();

         m_guide_panel->Enable(enable_guiding);
      }

      // always start in short exposure mode
      LE_CheckBox->SetValue(false);
      UpdateLEcontrols();
      UpdateBatchControls();

      ClearExposureMeter();
   }

}

void wxWebcamDBFrame::OnMenuItemDisconnect(wxCommandEvent& WXUNUSED(event))
{
   wxBusyCursor busy;
   StopCapture();
   wxF()->cam()->DisconnectCamera();
   SetTitle(_("wxAstroCapture - Windows linuX Astronomy Capture"));

  // ToolBar1->CamEnable();
   ToolBar1->InitToolBar();

   // re-enable guide panel on disconnect in case it was disabled
   m_guide_panel->Enable(true);

   // we can close the LE port here
   wxF()->lePortRelease(true);
}

void wxWebcamDBFrame::Onm_source_btnClick(wxCommandEvent& WXUNUSED(event))
{
   wxF()->cam()->ShowSourceDialog();
}

void wxWebcamDBFrame::Onm_format_btnClick(wxCommandEvent& WXUNUSED(event))
{
   wxF()->cam()->ShowFormatDialog();
}


void wxWebcamDBFrame::OnGaugeTimer(wxTimerEvent& WXUNUSED(event))
{


    if(wxF()->cam()->IsCapturing()) {
       /* if(isStepperConnected){
            m_gauge_timer.Stop();
            double angle = SS_AngSpin->GetValue();
            double calibr = SS_CalibrSpin->GetValue();
            if(Stepper.SMD_SetMoveParam(255, 0, FALSE, FALSE, (LONG32)(angle*calibr)) &&
                    Stepper.SMD_OnSHD(255, 0) &&
                Stepper.SMD_ClearStep(255)){
            m_gauge_timer.Start(gauge_ms);
            }
        }*/

       int gv = m_gauge1->GetValue();
       if(gv+m_gdir > m_gauge1->GetRange())m_gdir *= -1;
       if(gv+m_gdir < 0                  )m_gdir *= -1;
       m_gauge1->SetValue(gv+m_gdir);


    }
    else {
       m_gauge_timer.Stop();
       m_gauge1->SetValue(0);
    }
}

void wxWebcamDBFrame::OnUpdateCamData(wxCommandEvent& event)
{
   if (event.GetEventType()==wxEVT_WXAC_TIMER) {
      UpdateStatusBar();
      UpdateBatchControls();
   }
   else if (event.GetEventType()==wxEVT_WXAC_FRAME) {
      UpdateStatusBar();
      UpdateBatchControls();
   }
   else {
      event.Skip();
   }
}

//BM:2
void wxWebcamDBFrame::OnIdle(wxIdleEvent& WXUNUSED(event))
{
   UpdateStatusBar();
   UpdateExposureMeter();
   UpdateGuiderTuning();
   UpdateIncrement();
   ToolBar1->UpdateToolBar();
}

void wxWebcamDBFrame::OnMenuItemSettings(wxCommandEvent& WXUNUSED(event))
{
   SettingsDialog dialog(this);
   dialog.ShowModal();

   UpdateLEcontrols();
}



void wxWebcamDBFrame::OnMenuItemImageHeader(wxCommandEvent& WXUNUSED(event))
{
    ImageHeaderDialog dialog(this);
    dialog.ShowModal();
}


void wxWebcamDBFrame::UpdateLEcontrols()
{
   bool leSpinText = false;
   bool leCheckBox = false;

   wxCamera* camera = wxF()->cam();

   if (wxWebcam* webcam = wxF()->webcam()) {
      leCheckBox = true;
      leSpinText = true;

      if(!webcam->IsLExposing()) {
         // Do NOT check the lePort at this stage, because it prevents
         // dual instances of the program on Linux
         wxF()->webcam()->SwitchLE(false);
      }

   }
   else if ( camera->IsArtcam() ) {
      leSpinText = true;
   }

   if (!leCheckBox) LE_CheckBox->SetValue(leCheckBox);
   LE_CheckBox->Enable(leCheckBox);
   LE_Text->Enable(leSpinText);
   LE_SpinCtrl1->Enable(leSpinText);
}

void wxWebcamDBFrame::UpdateBatchControls()
{
   BatchJobManager* bjm = wxF()->batchJobManager();
   if(bjm && bjm->active()) {
      if(bjm->JobAvailable()) {
         int njob = bjm->active_size();
         int ijob = 1 + njob - bjm->remaining();
         BatchJob& batch_job = bjm->ActiveJob();
         wxString txt2 = wxString::Format(_T("Job %d of %d (%5.2fs )"),ijob,njob,batch_job.ExpoTime());
         int nframe = batch_job.NumFrames();
         int iframe = 1 + nframe - batch_job.FramesRemaining();
         wxString txt3 = wxString::Format(_T("Frame %d of %d"),iframe,nframe);

         wxCamera* cam = wxF()->cam();
         if(cam && cam->IsCapturePausing()) m_batch_status1->SetLabel(_T("Batch paused"));
         else m_batch_status1->SetLabel(_T("Batch active"));
         m_batch_status2->SetLabel(txt2);
         m_batch_status3->SetLabel(txt3);
      }
      else {
         m_batchCapture_btn->SetLabel(_T("Start Batch"));
         PauseBatchButton->SetLabel(_T("Pause Batch"));
         PauseBatchButton->Disable();
         m_batch_status1->SetLabel(_T("Batch completed"));
         m_batch_status2->SetLabel(_T(" "));
         m_batch_status3->SetLabel(_T(" "));
         bjm->setActive(false);
      }
   }
   else {
      m_batch_status1->SetLabel(_T("Batch not running"));
      if(wxCamera* cam = wxF()->cam()) {
         if(!cam->IsConnected()){
            m_batch_status2->SetLabel(wxT("No camera."));
         }
         else {
            // there is a camera

            if(cam->IsConnected()) {
               if(!cam->IsCapturing()) {
                  m_capture_btn->Enable(true);
                  m_capture_btn->SetLabel(wxT("Capture"));
                  m_pause_btn->SetLabel(wxT("Pause"));
                  m_pause_btn->Enable(false);
               }
            }

            if (wxWebcam* webcam = wxF()->webcam()) {
               if(webcam->IsConnected()) {
                  if(!webcam->IsLExposing()) m_batch_status2->SetLabel(wxT("long Exp. DISABLED"));
                  else m_batch_status2->SetLabel(wxT("long Exp. OK"));
               }
            }
         }
      }
      m_batch_status3->SetLabel(_T(" "));
   }
}

void wxWebcamDBFrame::OnVideoDeviceProperties(wxCommandEvent& WXUNUSED(event))
{
   // wxWebcamProps is also used for Artemis
   wxWebcamProps* dialog = wxWebcamProps::singleton();
   if(!dialog) {
      dialog = new wxWebcamProps(m_record_panel);
   }
   dialog->Show();
}


void wxWebcamDBFrame::OnMenuItemGuidingSelected(wxCommandEvent& WXUNUSED(event))
{
   /// THIS IS THE OLD DIALOG, no longer used
/*
    OptionsGuiding* dialog = OptionsGuiding::singleton();
    if(!dialog) {
       dialog = new OptionsGuiding(m_record_panel);
    }
    dialog->Show();
*/
}

void wxWebcamDBFrame::OnMenuItemOptionsGuiding(wxCommandEvent& WXUNUSED(event))
{
   wxGuidingOptions* dialog = wxGuidingOptions::singleton();
   if(!dialog) {
      dialog = new wxGuidingOptions(m_record_panel);
   }
   dialog->Show();
}

void wxWebcamDBFrame::OnShowReticleClick(wxCommandEvent& event)
{
   bool show_reticle = event.IsChecked();
   if(wxCamera* camera = wxF()->cam()) {
       camera->EnableReticle(show_reticle);
   }
}

void wxWebcamDBFrame::OnCaptureClick(wxCommandEvent&  WXUNUSED(event))
{
   bool batch = false;
   wxCamera* cam = wxF()->cam();
   if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturing()) {

            // delegate to helperdll

            // delegate to helper
            StopCapture();
         }
         else {
            // delegate to helper
            StartCapture(batch);
         }
      }
      else {
         wxMessageBox(_T("Please connect to the camera first"));
         //m_capture_btn->SetValue(false);
      }
   }

}

void wxWebcamDBFrame::OnPauseClick(wxCommandEvent& WXUNUSED(event))
{
   bool batch = false;
   wxCamera* cam = wxF()->cam();
   if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturePausing()) {

            // delegate to helper
            ContinueCapture(batch);
         }
         else {
            // delegate to helper
            PauseCapture(batch);
         }
      }
      else {
        wxMessageBox(_T("Please connect to the camera first"));
         //m_capture_btn->SetValue(false);
      }
   }
}

void wxWebcamDBFrame::StartCapture(bool batch)
{

   wxCamera* cam = wxF()->cam();
   if(cam){
      wxString folder = wxF()->captureFolder();
      EVideoSampleFormat sformat = wxF()->sampleFormat();
      EContainerFormat cformat = wxF()->containerFormat();

      if(cam->IsConnected()) {

         wxNamePolicyFile* policy = wxF()->getNamePolicyFile();
         if(policy->GetAutoResetIncrement()) {
            policy->SetIncrement(1);
         }

         if(batch) {

            // prepare and start batch capture
            BatchJobManager::BatchList batch_list;
            m_batch_setup->GetValue(batch_list);
            wxF()->batchJobManager()->DefineBatchJobs(batch_list);
            if(cam->RunBatchCapture()) {   // CA 20090411: Check for successful start of batch capture
                PauseBatchButton->Enable(true);
                m_batchCapture_btn->SetLabel(_T("Stop Batch"));
                m_start_capture = wxDateTime::UNow();

                m_capture_btn->Enable(false); // CA 20090331: disable normal capture during batch capture
            }
            else {
                // something failed when attempting to start batch capture, so reset normal exposure
                double exposure = LE_SpinCtrl1->GetValue();
                if(wxCamera* cam = wxF()->cam()) {
                   cam->SetLEduration((unsigned long)(exposure*1000.0) );
                }
            }
         }
         else {
            // ordinary capture

            // CA20090331: enforce exposure length from main tab again here.
            // We may be coming from bach capture and then the
            // exposure length will be wrong
            double exposure = LE_SpinCtrl1->GetValue();
            if(wxCamera* cam = wxF()->cam()) {
               cam->SetLEduration((unsigned long)(exposure*1000.0) );
            }

            // CA 20090331 Looks like we have to restart exposure here to get the correct
            // exposure length after coming from batch capture
            cam->RestartExposure();

            if(cam->StartCapture(folder,sformat,cformat)) {
               m_capture_btn->SetLabel(_T("Stop"));
               m_pause_btn->Enable(true);
               m_increment->Enable(false);
               m_batchCapture_btn->Enable(false);  // CA 20090331: disable batch capture during normal capture
               m_gauge1->SetValue(0);
               m_gdir = 1;

               //m_gauge_timer.Start(gauge_ms);

               m_start_capture = wxDateTime::UNow();
            }
         }
      }
   }
}

void wxWebcamDBFrame::StopCapture()
{
  wxCamera* cam = wxF()->cam();
  if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturing()) {
            cam->StopCapture();

            // batch job
            wxF()->batchJobManager()->setActive(false);
            m_batchCapture_btn->Enable(true); // CA 20090331: re-enable batch capture
            PauseBatchButton->Enable(false);
            m_batchCapture_btn->SetLabel(_T("Start Batch"));

            m_capture_btn->Enable(true); // CA 20090331: re-enable normal capture
            m_capture_btn->SetLabel(_T("Capture"));
            m_pause_btn->SetLabel(_T("Pause"));
            m_pause_btn->Enable(false);
            if(wxF()->containerFormat() == ECF_AVI)m_increment->Enable(false);
            else                                   m_increment->Enable(true);
            m_gauge_timer.Stop();
            m_gauge1->SetValue(0);
            m_gdir = 1;
         }
      }
  }
}

void wxWebcamDBFrame::ContinueCapture(bool batch)
{
  wxCamera* cam = wxF()->cam();
  if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturePausing()) {
            cam->ContinueCapture();
            if(batch){
               PauseBatchButton->SetLabel(_T("Pause Batch"));
            }
            else {
               m_pause_btn->SetLabel(_T("Pause"));
               m_increment->Enable(false);
            }
            m_gauge_timer.Start(gauge_ms);
         }
      }
  }
}

void wxWebcamDBFrame::PauseCapture(bool batch)
{
  wxCamera* cam = wxF()->cam();
  if(cam){
      if(cam->IsConnected()) {
         if(!cam->IsCapturePausing()) {
            cam->PauseCapture();
            if(batch){
               PauseBatchButton->SetLabel(_T("Continue Batch"));
            }
            else {
               m_pause_btn->SetLabel(_T("Continue"));
               m_increment->Enable(false);
            }
            m_gauge_timer.Stop();
         }
      }
  }
}

void wxWebcamDBFrame::OnLE_CheckBoxClick(wxCommandEvent& event)
{
   bool LE_active = event.IsChecked();
   double exposure = LE_SpinCtrl1->GetValue();

   if (wxWebcam* webcam = wxF()->webcam()) {
      if(wxF()->lePort()->IsInitialised() ) {

         webcam->SwitchLE(LE_active);
         if (LE_active) webcam->SetLEduration((unsigned long)(exposure*1000.0) ); //BM: set duration

      }
      else {
         webcam->SwitchLE(false);
      }
   }
}

void wxWebcamDBFrame::OnLE_SpinCtrl1Change(wxSpinEvent& WXUNUSED(event))
{
   double exposure = LE_SpinCtrl1->GetValue();
   if(wxCamera* cam = wxF()->cam()) {
      cam->SetLEduration((unsigned long)(exposure*1000.0) );
   }

   if(     exposure < 0.05)LE_SpinCtrl1->SetIncrement(0.001,3,wxSpinCtrlDbl::lf_fmt);
   else if(exposure <  0.5)LE_SpinCtrl1->SetIncrement( 0.01,2,wxSpinCtrlDbl::lf_fmt);
   else if(exposure <   10)LE_SpinCtrl1->SetIncrement(  0.1,5,wxSpinCtrlDbl::lg_fmt);
   else if(exposure <   30)LE_SpinCtrl1->SetIncrement(  1.0,10,wxSpinCtrlDbl::lg_fmt);
   else                    LE_SpinCtrl1->SetIncrement( 10.0,10,wxSpinCtrlDbl::lg_fmt);
}



void wxWebcamDBFrame::OnPickGuideStarClick(wxCommandEvent& WXUNUSED(event))
{
   // stop any ongoing guiding
   m_guide_timer.Stop();

   // set up the event to handle the mouse click in the video frame
   if (!wxF()->cam()->IsWebcam()) return;

   wxGuider* guider = wxF()->guider();

   // Make sure there is a valid guideport
   wxGuiderPort*  guideport = wxF()->guidePort();

   if(guider->interface_type() == wxGuider::PORT_INTERFACE) {
      if(!guideport || !guideport->IsInitialised() ) {
         wxMessageBox(wxT("Guide port is not available or not usable."));
         return;
      }
   }

   //20080825:CA Zoomed guiding not supported
   //20080826:CA Subframed guiding not supported
   if(wxCamera* camera = wxF()->cam()) {
      camera->unZoom();
      camera->SetFullFrame();
   }
      // make sure the on/off flag reflects the gui setting
   m_guide_active = GuideTelescope->GetValue();

   wxWebcam* camera =  wxF()->webcam();
   wxImage* image = camera->liveImage();

   if(!camera->isGuiding() && image->IsOk()) {
      camera->Connect(ID_CAMERA_PANEL,wxEVT_LEFT_DOWN,wxMouseEventHandler(wxWebcamDBFrame::OnvideoPanelLeftDown),0,this);

      // make a white 32x32 cross hair cursor with centereed hot spot
#ifdef _WXMSW_
      wxImage cimage(cross_hair_32x32_xpm);
      cimage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X,cimage.GetWidth()/2);
      cimage.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y,cimage.GetHeight()/2);
      camera->wxWindow::SetCursor(wxCursor(cimage));
#else
      // using stock cursor on Linux, as the MSW code makes a black crosshair and vice versa!!
      camera->wxWindow::SetCursor(wxCursor(wxCURSOR_BULLSEYE));
#endif

      // make sure guide port is open
      if(guider->interface_type() == wxGuider::PORT_INTERFACE) {
         if(guideport)guideport->ReopenPort();
      }

      // make sure guide sequence is started
      if(guider) guider->guideStart();

   }
   else {
      // cancel the guiding
      camera->cancelGuideBox();
      PickGuideStar->SetLabel(wxT("Pick Guide Star"));

      m_guide_dx->SetLabel(wxT("N/A"));
      m_guide_dy->SetLabel(wxT("N/A"));
      m_guide_mag->SetLabel(wxT("N/A"));

      // terminate the guider also, even if the m_guide_active is false
      if(wxGuider* guider = wxF()->guider()) guider->guideEnd();

      // release the port again
      guideport->ReleasePort();
   }

   // this will handle enbling and disabling of zooming in toolbar
   ToolBar1->InitToolBar();
}

void wxWebcamDBFrame::OnvideoPanelLeftDown(wxMouseEvent& event)
{
   wxWebcam* camera =  wxF()->webcam();
   if (!camera) return;

   wxImage* image = camera->liveImage();
   if(!image->IsOk())return;

   int guideBoxSize,bacgroundCutoff,guideInterval;
   double imageScale, cameraAngle;
   wxGuidingConfig::getGuidingConfig(guideBoxSize,bacgroundCutoff,guideInterval,imageScale,cameraAngle);

   m_guide_subframe.setCameraAngle(cameraAngle);
   m_guide_subframe.setImageScale(imageScale);
   m_guide_subframe.setCutoffLimit(bacgroundCutoff);

   // get position and guide box size
   wxPoint DC_point = event.GetPosition();
   wxSize subsiz(guideBoxSize,guideBoxSize);

   // convert to image coordinates and enable the guide box display
   wxRealPoint imagePoint(DC_point.x,DC_point.y);
  // camera->imagePointfromDC(DC_point,imagePoint);  //20080825:CA Zoomed guiding not supported
   camera->setGuideBox(imagePoint,imagePoint,subsiz);
   PickGuideStar->SetLabel(wxT("Stop Tracking"));

   // init the subframe
   wxSize fullsize(image->GetWidth(),image->GetHeight());
   m_guide_subframe.setFrameInfo(fullsize,subsiz,imagePoint);
   bool inverted = camera->liveImageInverted();

   // lock onto the guidestar
   bool locked = false;
   if(image && m_guide_subframe.copySubFrame(*image,inverted)) {

      // lock on the selected guide star
      wxStar offset_star;
      if(m_guide_subframe.guide(offset_star)) {

         // just a simple timer loop for now to drive the guiding
         // maybe a thread with a timer later
         m_guide_timer.Start(guideInterval);

         if(wxGuider* guider =  wxF()->guider()) {
            // set actual guider interval
            guider->setGuideInterval(guideInterval);
         }
         locked = true;
      }
   }

   // disable the video mouse click event
   camera->Disconnect(ID_CAMERA_PANEL,wxEVT_LEFT_DOWN);
 	camera->wxWindow::SetCursor(*wxSTANDARD_CURSOR);

 	if(!locked) {
 	   wxMessageBox(wxT("Could not lock onto the selected guide star"));
 	}
}


void wxWebcamDBFrame::OnGuideTimer(wxTimerEvent& WXUNUSED(event))
{
   if (!wxF()->cam()->IsWebcam()) return;

   wxWebcam* camera =  wxF()->webcam();
   wxImage* image = camera->liveImage();
   bool inverted = camera->liveImageInverted();

   // extract guiding subframe from fullframe
   if(image && m_guide_subframe.copySubFrame(*image,inverted)) {

      // compute the star offset
      wxStar offset_star;
      if(m_guide_subframe.guide(offset_star)) {

         bool reverseRA,reverseDEC;
         wxGuidingConfig::DECguiding dec_opt;
         wxGuidingConfig::getCachedGuidingOptions(reverseRA,reverseDEC,dec_opt);

         double ra  = (reverseRA)?  -offset_star.x() : offset_star.x();
         double dec = (reverseDEC)? -offset_star.y() : offset_star.y();

         double realdec = dec;
         bool   decupd = false;
         switch(dec_opt) {
            case wxGuidingConfig::NoDecGuiding: { dec = 0.0;             decupd=true; break; }
            case wxGuidingConfig::NorthOnly:    { if(dec<0.0) dec = 0.0; decupd=true; break; }
            case wxGuidingConfig::SouthOnly:    { if(dec>0.0) dec = 0.0; decupd=true; break; }
            default: {}
         };

         // do not send guider commands unless it has been enabled
         if(m_guide_active) {
            if(wxGuider* guider = wxF()->guider()) {
               // wxBell();
               guider->guideError(m_guide_subframe.timestamp_ms(),ra,dec);
            }
         }

        // update numbers in GUI
         m_guide_dx->SetLabel(wxString::Format(wxT("%.1f"),ra));
         if(decupd)m_guide_dy->SetLabel(wxString::Format(wxT("%.1f  (%.1f)"),dec,realdec));
         else      m_guide_dy->SetLabel(wxString::Format(wxT("%.1f"),dec));
         m_guide_mag->SetLabel(wxString::Format(wxT("%.0f"),offset_star.mag()));

         // update camera guide box overlay
         wxRealPoint curcen = m_guide_subframe.centre();
         camera->setGuideBox(m_guide_subframe.lockpos(),curcen,m_guide_subframe.size());
       }
   }
}



void wxWebcamDBFrame::OnGuideTelescopeClick(wxCommandEvent& event)
{
   // Just set the flag here, nothing else
   m_guide_active = event.IsChecked();
}

void wxWebcamDBFrame::OnReverseRAClick(wxCommandEvent& event)
{
   bool reverseRA,reverseDEC;
   wxGuidingConfig::DECguiding dec;
   wxGuidingConfig::getGuidingOptions(reverseRA,reverseDEC,dec);
   reverseRA = event.IsChecked();
   wxGuidingConfig::saveGuidingOptions(reverseRA,reverseDEC,dec);
}

void wxWebcamDBFrame::OnReverseDECClick(wxCommandEvent& event)
{
   bool reverseRA,reverseDEC;
   wxGuidingConfig::DECguiding dec;
   wxGuidingConfig::getGuidingOptions(reverseRA,reverseDEC,dec);
   reverseDEC = event.IsChecked();
   wxGuidingConfig::saveGuidingOptions(reverseRA,reverseDEC,dec);
}

void wxWebcamDBFrame::OnDecNSChoiceSelect(wxCommandEvent& event)
{
   bool reverseRA,reverseDEC;
   wxGuidingConfig::DECguiding dec;
   wxGuidingConfig::getGuidingOptions(reverseRA,reverseDEC,dec);
   dec = (wxGuidingConfig::DECguiding )event.GetInt();
   wxGuidingConfig::saveGuidingOptions(reverseRA,reverseDEC,dec);
}



void wxWebcamDBFrame::OnRaAggrSpinChange(wxSpinEvent& WXUNUSED(event))
{
   double ra_k = m_RaAggrSpin->GetValue();
   if(wxGuider* guider = wxF()->guider()) {
      guider->setRaK(ra_k);
   }
}

void wxWebcamDBFrame::OnDecAggrSpinChange(wxSpinEvent& WXUNUSED(event))
{
   double dec_k = m_DecAggrSpin->GetValue();
   if(wxGuider* guider = wxF()->guider()) {
      guider->setDecK(dec_k);
   }
}

void wxWebcamDBFrame::OnAdvancedGuideParamsClick(wxCommandEvent& WXUNUSED(event))
{
   if(AdvancedGuidingParams* dlg = AdvancedGuidingParams::singleton(m_staticText_RA)) {
      dlg->Show();
   }
}

void wxWebcamDBFrame::OnUnZoom(wxCommandEvent& WXUNUSED(event))
{
   if(wxCamera* camera = wxF()->cam()) {
      camera->unZoom();
   }
}

void wxWebcamDBFrame::OnFullFrame(wxCommandEvent& WXUNUSED(event))
{
   if(wxArtcam* camera = wxF()->artcam()) {
      camera->SetFullFrame();
   }
}


void wxWebcamDBFrame::OnStartBatchButtonClick(wxCommandEvent& WXUNUSED(event))
{
   bool batch = true;
   wxCamera* cam = wxF()->cam();
   if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturing()) {

            // delegate to helper
            StopCapture();
         }
         else {
            // delegate to helper
            StartCapture(batch);
         }
      }
      else {
         wxMessageBox(_T("Please connect to the camera first"));
      }
   }
}

void wxWebcamDBFrame::OnPauseBatchButtonClick(wxCommandEvent& WXUNUSED(event))
{
   bool batch = true;
   wxCamera* cam = wxF()->cam();
   if(cam){
      if(cam->IsConnected()) {
         if(cam->IsCapturePausing()) {

            // delegate to helper
            ContinueCapture(batch);
         }
         else {
            // delegate to helper
            PauseCapture(batch);
         }
      }
      else {
        wxMessageBox(_T("Please connect to the camera first"));
         //m_capture_btn->SetValue(false);
      }
   }
}

void wxWebcamDBFrame::OnNotebook1PageChanged(wxNotebookEvent& WXUNUSED(event))
{
   UpdateBatchControls();
}

void wxWebcamDBFrame::OnMaxFrames_CheckBoxClick(wxCommandEvent& WXUNUSED(event))
{
   MaxFrames_SpinCtrl->Enable(MaxFrames_CheckBox->IsChecked());
}


///Stepper
void wxWebcamDBFrame::OnSetStepperParamClick(wxCommandEvent&  WXUNUSED(event))
{



if(wxWebcamDBFrame::GetStepperState()){
BYTE ATrtAddr = (BYTE)wxWebcamDBFrame::ATrtAddr;
INT32 ANumber = (INT32)SS_MotorNSpin->GetValue();
INT32 COMPortNumber = (INT32)SS_PortNSpin->GetValue();

INT32 I = m_stepperIChoice->GetCurrentSelection();
INT32 I_stop = m_stepperIStopChoice->GetCurrentSelection();

INT32 PhaseMode = m_stepperWModeChoice->GetCurrentSelection();
INT32 Frec = SS_FrecSpin->GetValue();
INT32 FrecMulty = SS_MultFrecSpin->GetValue();

INT32 steps = 0;
byte FMode[] = {00,01, 10};

//SMD_ClearStep(ATrtAddr);
Stepper.SMD_OffAllSHD(ATrtAddr);

Stepper.SMD_WriteTactFreq(ATrtAddr, ANumber, Frec);
//SMD_SetPortNumber(COMPortNumber);
Stepper.SMD_WritePhaseMode(ATrtAddr, ANumber, FMode[PhaseMode]);
//SMD_SetPortNumber(COMPortNumber);
Stepper.SMD_WriteMarchIHoldICode(ATrtAddr, ANumber, I, I_stop);
Stepper.SMD_WriteMulty(255, ANumber, FrecMulty);
Stepper.SMD_SetPortNumber(COMPortNumber);



}
else {
    wxMessageBox(_T("Stepper is not connected"));
}
}

void wxWebcamDBFrame::OnOpenStepperCOMPortClick(wxCommandEvent&  WXUNUSED(event))
{
    if(!wxWebcamDBFrame::GetStepperState()){
    INT32 COMPortNumber = (INT32)SS_PortNSpin->GetValue();
    bool b = Stepper.SMD_OpenComPort(COMPortNumber);
    wxWebcamDBFrame::SetStepperState(b);
    if(b){
            wxMessageBox(wxString::Format("1Stepper:%d;\n%d", COMPortNumber, b));
            m_openStepperCOMPort_btn->SetBackgroundColour(wxColor("red"));
            SS_PortNSpin->Enable(false);
             m_openStepperCOMPort_btn->SetLabel("Close");
             m_stepperCOM_timer.Start(5000);
    }
    else         {
            wxMessageBox(wxString::Format("2Stepper error %d", b));
            m_openStepperCOMPort_btn->SetBackgroundColour(wxColor("green"));
            m_openStepperCOMPort_btn->SetLabel("Open");
    }
    }
    else{
            Stepper.SMD_OffAllSHD(255);
            bool b = Stepper.SMD_CloseComPort();
            wxMessageBox(wxString::Format("3Stepper:%d", b));
            wxWebcamDBFrame::SetStepperState(!b);
            m_openStepperCOMPort_btn->SetBackgroundColour(wxColor("green"));
            m_openStepperCOMPort_btn->SetLabel("Open");
            SS_PortNSpin->Enable(true);
    }
}

void wxWebcamDBFrame::OnStepperMoveCWiceClick(wxCommandEvent&  WXUNUSED(event))
{
BYTE ATrtAddr = wxWebcamDBFrame::ATrtAddr;
INT32 ANumber = (INT32)SS_MotorNSpin->GetValue();
INT32 COMPortNumber = (INT32)SS_PortNSpin->GetValue();

double angle = SS_AngSpin->GetValue();
double calibr = SS_CalibrSpin->GetValue();
Stepper.SMD_SetMoveParam(255, ANumber, FALSE, TRUE, (LONG32)(angle*calibr));
Stepper.SMD_OnSHD(255, ANumber);
//Stepper.SMD_ClearStep(255);
int direction = 1;//(SS_CWiceDirection->IsEnabled())? -1 : 1;
wxWebcamDBFrame::UpdateStepperAngle(angle*direction);
}

void wxWebcamDBFrame::OnStepperMoveCCWiceClick(wxCommandEvent&  WXUNUSED(event))
{

//BYTE ATrtAddr = wxWebcamDBFrame::ATrtAddr;
INT32 ANumber = (INT32)SS_MotorNSpin->GetValue();
//INT32 COMPortNumber = (INT32)SS_PortNSpin->GetValue();

double angle = SS_AngSpin->GetValue();
double calibr = SS_CalibrSpin->GetValue();
Stepper.SMD_SetMoveParam(255, ANumber, FALSE, FALSE, (LONG32)(angle*calibr));
Stepper.SMD_OnSHD(255, ANumber);
//Stepper.SMD_ClearStep(255);
int direction = -1;//(SS_CWiceDirection->IsEnabled())? -1 : 1;
wxWebcamDBFrame::UpdateStepperAngle(angle*direction);
}

void wxWebcamDBFrame::OnResetStepperCounterClick(wxCommandEvent&  WXUNUSED(event))
{
ResetStepperAngle();
Stepper.SMD_ClearStep(255);
}

void wxWebcamDBFrame::OnResetSHDClick(wxCommandEvent&  WXUNUSED(event))
{
Stepper.SMD_ResetSHD(255,TRUE,TRUE);
}


void wxWebcamDBFrame::OnStepperCOMTimer(wxTimerEvent& WXUNUSED(event))
{
    if(wxWebcamDBFrame::isStepperConnected) {
     //  Stepper.SMD_OpenComPort((INT32)SS_PortNSpin->GetValue());
     //char p;
     //Stepper.SMD_GetInform(p);

    }
    else {
       m_stepperCOM_timer.Stop();
}
}


void wxWebcamDBFrame::OnStepperCaptureClick(wxCommandEvent&  WXUNUSED(event))
{
if(!(m_stepperCapture_timer.IsRunning())){
wxCamera* cam = wxF()->cam();
       if (cam){
           if(cam->IsConnected() && wxWebcamDBFrame::isStepperConnected){
           int m_stepper_capture_interval = SS_StepperInterval->GetValue();
           m_stepperCapture_timer.Start(m_stepper_capture_interval);
           SS_StepperCapture_btn->SetLabel(_("Stop"));
           }}
           else{
            m_stepperCapture_timer.Stop();
            SS_StepperCapture_btn->SetLabel(_("Capture"));
           }
}
else {
     m_stepperCapture_timer.Stop();
     SS_StepperCapture_btn->SetLabel(_("Capture"));
     StopCapture();
}
}


void wxWebcamDBFrame::OnStepperCaptureTimer(wxTimerEvent& WXUNUSED(event))
{
    m_stepperCapture_timer.Stop();
    wxCamera* cam = wxF()->cam();
    wxString FitsAngle, FitsCalibr, FitsObject, FitsExposure;
    if (cam->IsConnected() && wxWebcamDBFrame::isStepperConnected){
    if (!cam->IsCapturing()){
        StartCapture(true);
        double angle = SS_AngSpin->GetValue();
        double calibr = SS_CalibrSpin->GetValue();
        ///////////////////////////////////////Direction/////////////////
        int direction = (SS_CWiceDirection->IsEnabled())? -1 : 1;
        bool dir = (SS_CWiceDirection->IsEnabled())? FALSE : TRUE;
        float exposure = LE_SpinCtrl1->GetValue();
        double current_ang = UpdateStepperAngle(angle*direction);

        if (Stepper.SMD_SetMoveParam(255, 0, FALSE, dir, (LONG32)(angle*calibr)) &&
                    Stepper.SMD_OnSHD(255, 0) &&
                    Stepper.SMD_ClearStep(255))
                    {

                    wxF()->getFitsHeaderValue(wxT("OBJECT"), FitsObject);
                    FitsAngle = wxT(wxString::Format("%s_%f", FitsObject, current_ang));
                    wxF()->saveFitsHeaderValue(wxT("ANGLE"), FitsAngle);


                    wxF()->getFitsHeaderValue(wxT("ANGLE"), FitsAngle);
                    FitsAngle = wxT(wxString::Format("%f", current_ang));
                    wxF()->saveFitsHeaderValue(wxT("ANGLE"), FitsAngle);
                    wxF()->getFitsHeaderValue(wxT("STEPPERC"), FitsCalibr);
                    FitsCalibr = wxT(wxString::Format("%f", calibr));
                    wxF()->saveFitsHeaderValue(wxT("STEPPERC"), FitsCalibr);
                    wxF()->getFitsHeaderValue(wxT("EXPOSURE"), FitsExposure);
                    FitsExposure = wxT(wxString::Format("%f", exposure));
                    wxF()->saveFitsHeaderValue(wxT("EXPOSURE"), FitsExposure);

                       m_stepperCapture_timer.Start(SS_StepperInterval->GetValue());
                    }
    }
    else m_stepperCapture_timer.Start(1000);
    }


    else {

     SS_StepperCapture_btn->SetLabel(_("Capture"));
     StopCapture();

    }
/*
wxString comment_val;
int m_stepper_capture_interval = SS_StepperInterval->GetValue();
auto_exposure = wxF()->getFitsHeaderValue(wxT("COMMENT"), comment_val);

//постійно пробудження двигунів
  Stepper.SMD_OpenComPort((INT32)SS_PortNSpin->GetValue());
m_stepperCapture_timer.Stop();
       wxCamera* cam = wxF()->cam();
if (cam && cam->IsConnected() && !(cam->IsCapturing())){


               double angle = SS_AngSpin->GetValue();
               double calibr = SS_CalibrSpin->GetValue();
               ///////////////////////////////////////Direction/////////////////
               int direction = (SS_CWiceDirection->IsEnabled())? -1 : 1;
               bool dir = (SS_CWiceDirection->IsEnabled())? FALSE : TRUE;
               float exposure = LE_SpinCtrl1->GetValue();







   unsigned short pivot, vlow,  vhig,  Max;
   wxF()->cam()->Histogram().PivotDev(pivot, vlow,  vhig,  Max);
   double pivot_ = (double)pivot;
   double vhig_ = (double)vhig;
   double vlow_ = (double)vlow;
   double Max_ = (double)Max;
   wxString captured;
   captured.Printf(_T("pivot: %f; vlow: %f; vhig: %f; max: %f;"), double(pivot), double(vlow),  double(vhig),  double(Max));

bool tmp_exposure = 0;
if(auto_exposure){

    //double filterWheelAngle = fWheelCalibration*360/filtersArray.size();
   // int tmpfIndex = currentFilterIndex;
    UpdateExposureMeter();
     if (vhig_ > Max_*0.9){


           // exposure = LE_SpinCtrl1->GetValue();
     if (exposure > 0.1) {
            exposure*=0.9;
            LE_SpinCtrl1->SetValue(exposure);
tmp_exposure = true;
            }

   //         UpdateFWheelString();
   //         if ( currentFilterIndex >0 ){
   // //wxMessageBox(wxString::Format(_T("pivot: %f; vlow: %f; vhig: %f; max: %f;"), double(pivot), double(vlow),  double(vhig),  double(Max)));
   // Stepper.SMD_SetMoveParam(255, 1, FALSE, FALSE, (LONG32)(filterWheelAngle));
   // Stepper.SMD_OnSHD(255, 1);
   // currentFilterIndex -= 1;
            }


     else if (vhig_ < Max_*0.001){
  //          UpdateFWheelString();
  //          if ( currentFilterIndex < filtersArray.size()){
  //  //wxMessageBox(wxString::Format(_T("pivot: %f; vlow: %f; vhig: %f; max: %f;"), double(pivot), double(vlow),  double(vhig),  double(Max)));
  //  Stepper.SMD_SetMoveParam(255, 1, FALSE, TRUE, (LONG32)(filterWheelAngle));
  //  Stepper.SMD_OnSHD(255, 1);
  // currentFilterIndex += 1;

         // UpdateExposureMeter();

     if (exposure < 4) {
            exposure*=1.1;
            LE_SpinCtrl1->SetValue(exposure);
            }
            tmp_exposure = true;
     }
         // UpdateExposureMeter();
     }

wxString FitsAngle, FitsCalibr, FitsObject, FitsExposure;

if (!tmp_exposure)
{


wxF()->getFitsHeaderValue(wxT("EXPOSURE"), FitsExposure);
                    FitsExposure = wxT(wxString::Format("%f", exposure));
                    wxF()->saveFitsHeaderValue(wxT("EXPOSURE"), FitsExposure);

m_stepperCapture_timer.Start(m_stepper_capture_interval);

}
else{
    StartCapture(false);



               //переробити
               if( wxWebcamDBFrame::isStepperConnected && Stepper.SMD_SetMoveParam(255, 0, FALSE, dir, (LONG32)(angle*calibr)) &&
                    Stepper.SMD_OnSHD(255, 0) &&
                    Stepper.SMD_ClearStep(255))
                    {
                    double current_ang = UpdateStepperAngle(angle*direction);



                    wxF()->getFitsHeaderValue(wxT("OBJECT"), FitsObject);
                    FitsAngle = wxT(wxString::Format("%s_%f", FitsObject, current_ang));
                    wxF()->saveFitsHeaderValue(wxT("ANGLE"), FitsAngle);


                    wxF()->getFitsHeaderValue(wxT("ANGLE"), FitsAngle);
                    FitsAngle = wxT(wxString::Format("%f", current_ang));
                    wxF()->saveFitsHeaderValue(wxT("ANGLE"), FitsAngle);
                    wxF()->getFitsHeaderValue(wxT("STEPPERC"), FitsCalibr);
                    FitsCalibr = wxT(wxString::Format("%f", calibr));
                    wxF()->saveFitsHeaderValue(wxT("STEPPERC"), FitsCalibr);


m_stepperCapture_timer.Start(m_stepper_capture_interval);
*/
/*
    if (tmpfIndex != currentFilterIndex){
     wxString FitsFilter;

                    wxF()->getFitsHeaderValue(wxT("FILTER"), FitsFilter);
                    FitsFilter = wxT(wxString::Format("%s", filtersArray[currentFilterIndex]));
                    wxF()->saveFitsHeaderValue(wxT("FILTER"), FitsFilter);
    }
    else{*/

                     //StartCapture(false);

   // }




              //      }
    //    }


                  //  m_statusbar->SetStatusText(captured, 1);

/*
            }
             else {
       m_stepperCapture_timer.Stop();
SS_StepperCapture_btn->SetLabel(_("Capture"));
     StopCapture();
    }
     }   //}
    //}

}
else{

}
 m_stepperCapture_timer.Start(m_stepper_capture_interval);

 */
 }


void wxWebcamDBFrame::OnCWStepperDirectionClick(wxCommandEvent&  WXUNUSED(event))
{
SS_CCWiceDirection->Enable(1);
SS_CWiceDirection->Enable(0);

}

void wxWebcamDBFrame::OnCCWStepperDirectionClick(wxCommandEvent&  WXUNUSED(event))
{
SS_CCWiceDirection->Enable(0);
SS_CWiceDirection->Enable(1);
}

///sTEPPER
