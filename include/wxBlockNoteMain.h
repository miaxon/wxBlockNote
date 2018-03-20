/***************************************************************
 * Name:      wxBlockNoteMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-02-24
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WXBLOCKNOTEMAIN_H
#define WXBLOCKNOTEMAIN_H

//(*Headers(wxBlockNoteFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)



class wxBlockNoteFrame: public wxFrame
{
    public:

        wxBlockNoteFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxBlockNoteFrame();

    private:

        //(*Handlers(wxBlockNoteFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnLanguageSelect(wxCommandEvent& event);
        void OnOpenSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxBlockNoteFrame)
        static const long ID_TEXTCTRL;
        static const long idMenuOpen;
        static const long idMenuQuit;
        static const long idMenuLanguage;
        static const long idMenuAbout;
        static const long ID_STATUSBAR;
        //*)

        //(*Declarations(wxBlockNoteFrame)
        wxStatusBar* StatusBar;
        wxTextCtrl* textCtrl;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXBLOCKNOTEMAIN_H
