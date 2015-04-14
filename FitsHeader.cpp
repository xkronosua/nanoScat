#include "FitsHeader.h"
#include "wxMainToolBar.h"
#include "wxWebcamDBMain.h"
//(*InternalHeaders(FitsHeader)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxFactory.h"

//(*IdInit(FitsHeader)
const long FitsHeader::ID_GRID1 = wxNewId();
const long FitsHeader::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FitsHeader,wxPanel)
	//(*EventTable(FitsHeader)
	//*)
END_EVENT_TABLE()

FitsHeader::FitsHeader(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(FitsHeader)
	Create(parent, id, wxDefaultPosition, wxSize(400,400), wxTAB_TRAVERSAL, _T("id"));
	SetMaxSize(wxSize(-1,400));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	grid = new wxPropGrid(this, ID_GRID1, wxDefaultPosition, wxSize(500,300), wxSIMPLE_BORDER, _T("ID_GRID1"));
	BoxSizer1->Add(grid, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	enptyFits = new wxButton(this, ID_BUTTON1, _("empty"), wxDefaultPosition, wxSize(80,20), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(enptyFits, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	SetSizer(BoxSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FitsHeader::OnEnptyFitsClick);
	//*)

	Init();
}

FitsHeader::~FitsHeader()
{
	//(*Destroy(FitsHeader)
	//*)
}

void FitsHeader::Init()
{
   wxPropGrid::Columns columns;
   columns.push_back(wxT("Keyword"));
   columns.push_back(wxT("Value"));
   columns.push_back(wxT("Comment"));

   // retrieve values from config and pass onto grid
   wxPropGrid::Entries entries;
   wxFactory::singleton()->getFitsHeaderEntries(entries);
   grid->CreateGrid(entries,columns);

   wxArrayString choices;
   choices.Add(wxT("LIGHT"));
   choices.Add(wxT("BIAS"));
   choices.Add(wxT("DARK"));
   choices.Add(wxT("FLAT"));
   grid->CreateChoice(wxT("IMAGETYP"),choices);

   // recompute the control layout
	this->SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
   BoxSizer1->SetSizeHints(this);
   BoxSizer1->Layout();
	Layout();
}

bool FitsHeader::OnApply()
{
   // retrieve values from grid and pass on to config
   wxPropGrid::Entries entries;
   grid->GetCellValues(entries);
   wxFactory::singleton()->saveFitsHeaderEntries(entries);

   wxMainToolBar::singleton()->UpdateType();
   wxMainToolBar::singleton()->UpdateObject();
   wxWebcamDBFrame::singleton()->syncFiltersFields(0);
   return true;
}

void FitsHeader::OnEnptyFitsClick(wxCommandEvent& event)
{
    wxString FitsHeader = wxT("FitsHeader");

   wxConfig *m_config = wxFactory::singleton()->config();
   wxFactory::singleton()->config()->DeleteGroup(FitsHeader);

    wxPropGrid::Entries entries;
  // grid->GetCellValues(entries);
   wxFactory::singleton()->getFitsHeaderEntries(entries);

   wxMainToolBar::singleton()->UpdateType();
   wxMainToolBar::singleton()->UpdateObject();
   wxWebcamDBFrame::singleton()->syncFiltersFields(0);
}
