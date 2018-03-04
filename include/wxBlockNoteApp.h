/***************************************************************
 * Name:      wxBlockNoteApp.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2018-02-24
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WXBLOCKNOTEAPP_H
#define WXBLOCKNOTEAPP_H

#include <wx/app.h>
#include <wx/filename.h>
#include <utils/wxTranslationHelper.h>

class wxBlockNoteApp : public wxApp
{
    public:
        virtual bool OnInit();
        bool SelectLanguage();
        void RecreateGUI();
        wxFileName* GetAppFileName();
    private:
    wxLocale* m_locale;
    wxTranslationHelper * m_TranslationHelper;
    wxFileName* m_appFileName;
};
wxDECLARE_APP(wxBlockNoteApp);
#endif // WXBLOCKNOTEAPP_H
