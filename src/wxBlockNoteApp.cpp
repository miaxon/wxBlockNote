/***************************************************************
 * Name:      wxBlockNoteApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2018-02-24
 * Copyright:  ()
 * License:
 **************************************************************/



//(*AppHeaders
#include <wxBlockNoteApp.h>
#include <wxBlockNoteMain.h>
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxBlockNoteApp);
wxLocale* locale;
long language;

bool wxBlockNoteApp::OnInit()
{
    //(*AppInitialize
    wxImage::AddHandler(new wxPNGHandler);
    m_appFileName = new wxFileName(argv[0]);
	m_appFileName->Normalize(wxPATH_NORM_DOTS|wxPATH_NORM_ABSOLUTE|wxPATH_NORM_TILDE);
	m_TranslationHelper = new wxTranslationHelper(*this, m_appFileName->GetPath() +	wxFileName::GetPathSeparator() + wxT("lang"), false);
	wxString path = m_appFileName->GetPath() + wxFileName::GetPathSeparator() + wxT("conf.ini");
	m_TranslationHelper->SetConfigPath(path);
	m_TranslationHelper->Load();
	RecreateGUI();
    //*)
    return true;

}
wxFileName* wxBlockNoteApp::GetAppFileName()
{
    return m_appFileName;

}
bool wxBlockNoteApp::SelectLanguage()
{
	wxArrayString names;
	wxArrayLong identifiers;
	m_TranslationHelper->GetInstalledLanguages(names, identifiers);
	bool res = m_TranslationHelper->AskUserForLanguage(names, identifiers);
	return res;
}

void wxBlockNoteApp::RecreateGUI()
{
	wxWindow * topwindow = GetTopWindow();
	if(topwindow)
	{
		SetTopWindow(NULL);
		topwindow->Destroy();
	}
	wxLog::SetActiveTarget(new wxLogWindow(NULL,"Logs"));
	wxBlockNoteFrame * frame = new wxBlockNoteFrame(0);
	SetTopWindow(frame);
	frame->Centre();
	frame->Show();
}
