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
#include <wx/richtext/richtextctrl.h>
#include <wx/statusbr.h>
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
        //*)

        //(*Identifiers(wxBlockNoteFrame)
        static const long ID_RICHTEXTCTRL;
        static const long idMenuQuit;
        static const long idMenuLanguage;
        static const long idMenuAbout;
        static const long ID_STATUSBAR;
        //*)

        //(*Declarations(wxBlockNoteFrame)
        wxRichTextCtrl* richText;
        wxStatusBar* statusBar;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXBLOCKNOTEMAIN_H
