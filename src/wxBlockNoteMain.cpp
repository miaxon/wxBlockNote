/***************************************************************
 * Name:      wxBlockNoteMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2018-02-24
 * Copyright:  ()
 * License:
 **************************************************************/




//(*InternalHeaders(wxBlockNoteFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)


#include <wxBlockNoteMain.h>
#include <wxBlockNoteApp.h>
#include <images/application_go.xpm>
#include <images/information.xpm>
#include <images/world.xpm>
#include <images/page_green.xpm>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
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

//(*IdInit(wxBlockNoteFrame)
const long wxBlockNoteFrame::ID_TEXTCTRL = wxNewId();
const long wxBlockNoteFrame::idMenuOpen = wxNewId();
const long wxBlockNoteFrame::idMenuQuit = wxNewId();
const long wxBlockNoteFrame::idMenuLanguage = wxNewId();
const long wxBlockNoteFrame::idMenuAbout = wxNewId();
const long wxBlockNoteFrame::ID_STATUSBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxBlockNoteFrame,wxFrame)
    //(*EventTable(wxBlockNoteFrame)
    //*)
END_EVENT_TABLE()

wxBlockNoteFrame::wxBlockNoteFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxBlockNoteFrame)
    wxMenu* menuFile;
    wxMenu* menuHelp;
    wxMenu* menuView;
    wxMenuBar* MenuBar;
    wxMenuItem* menuItemAbout;
    wxMenuItem* menuItemLanguage;
    wxMenuItem* menuItemOpen;
    wxMenuItem* menuItemQuit;

    Create(parent, wxID_ANY, _("wxBlockNote"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    SetFocus();
    {
    wxIcon FrameIcon;
    FrameIcon.CopyFromBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_HELP_BOOK")),wxART_FRAME_ICON));
    SetIcon(FrameIcon);
    }
    textCtrl = new wxTextCtrl(this, ID_TEXTCTRL, wxEmptyString, wxPoint(632,400), wxDefaultSize, wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL"));
    MenuBar = new wxMenuBar();
    menuFile = new wxMenu();
    menuItemOpen = new wxMenuItem(menuFile, idMenuOpen, _("Open\tCtrl+O"), _("Open file"), wxITEM_NORMAL);
    menuItemOpen->SetBitmap(wxBitmap(page_green));
    menuFile->Append(menuItemOpen);
    menuItemQuit = new wxMenuItem(menuFile, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    menuItemQuit->SetBitmap(wxBitmap(application_go));
    menuFile->Append(menuItemQuit);
    MenuBar->Append(menuFile, _("&File"));
    menuView = new wxMenu();
    menuItemLanguage = new wxMenuItem(menuView, idMenuLanguage, _("Language"), _("Select language"), wxITEM_NORMAL);
    menuItemLanguage->SetBitmap(wxBitmap(world));
    menuView->Append(menuItemLanguage);
    MenuBar->Append(menuView, _("View"));
    menuHelp = new wxMenu();
    menuItemAbout = new wxMenuItem(menuHelp, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    menuItemAbout->SetBitmap(wxBitmap(information));
    menuHelp->Append(menuItemAbout);
    MenuBar->Append(menuHelp, _("Help"));
    SetMenuBar(MenuBar);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);

    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnOpenSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnQuit);
    Connect(idMenuLanguage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnLanguageSelect);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnAbout);
    //*)
}

wxBlockNoteFrame::~wxBlockNoteFrame()
{
    //(*Destroy(wxBlockNoteFrame)
    //*)
}

void wxBlockNoteFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxBlockNoteFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg =  wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxBlockNoteFrame::OnLanguageSelect(wxCommandEvent& event)
{
    if(wxGetApp().SelectLanguage())
	{
		wxGetApp().RecreateGUI();
	}
}

void wxBlockNoteFrame::OnOpenSelected(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
		_("Text files (*.txt)|*.txt|C++ Source Files (*.cpp, *.cxx)|*.cpp;*.cxx|C Source files (*.c)|*.c|C header files (*.h)|*.h"),
		wxFD_OPEN, wxDefaultPosition);

	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		//CurrentDocPath = OpenDialog->GetPath();
		// Sets our current document to the file the user selected
		wxLogDebug(OpenDialog->GetPath());
		textCtrl->LoadFile(OpenDialog->GetPath()); //Opens that file
		textCtrl->Refresh();
		SetTitle(wxString(_("Edit - ")) << OpenDialog->GetFilename()); // Set the Title to reflect the file open
	}

	// Clean up after ourselves
	OpenDialog->Destroy();
}
