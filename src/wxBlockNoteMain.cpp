/***************************************************************
 * Name:      wxBlockNoteMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2018-02-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wxBlockNoteMain.h"
#include "wxBlockNoteApp.h"
#include <wx/msgdlg.h>
#include "images/application_go.xpm"
#include "images/information.xpm"
#include "images/world.xpm"


//(*InternalHeaders(wxBlockNoteFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

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
const long wxBlockNoteFrame::ID_RICHTEXTCTRL = wxNewId();
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
    wxMenuItem* menuItemQuit;

    Create(parent, wxID_ANY, _("wxBlockNote"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    SetFocus();
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_HELP_BOOK")),wxART_FRAME_ICON));
    	SetIcon(FrameIcon);
    }
    richText = new wxRichTextCtrl(this, ID_RICHTEXTCTRL, wxEmptyString, wxPoint(176,168), wxDefaultSize, wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    richText->SetFocus();
    MenuBar = new wxMenuBar();
    menuFile = new wxMenu();
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
    statusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);
    Center();

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnQuit);
    Connect(idMenuLanguage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnLanguageSelect);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxBlockNoteFrame::OnLanguageSelect);
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
