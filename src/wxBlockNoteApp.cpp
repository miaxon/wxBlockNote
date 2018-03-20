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
#include <wx/log.h>
IMPLEMENT_APP(wxBlockNoteApp);

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
	CreateLogWindow();
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

void wxBlockNoteApp::CreateLogWindow()
{

}

void wxBlockNoteApp::RecreateGUI()
{
	wxWindow * topwindow = GetTopWindow();
	if(topwindow)
	{
		SetTopWindow(NULL);
		topwindow->Destroy();
	}
	wxBlockNoteFrame * frame = new wxBlockNoteFrame(0);
	SetTopWindow(frame);
	frame->Centre();
	frame->Show();
#if LOGGING
	wxFrame* pLogFrame;
    wxLogWindow* m_pLogWindow = new wxLogWindow(frame, wxT("Log") );
    m_pLogWindow->PassMessages(false);
    pLogFrame = m_pLogWindow->GetFrame();
    pLogFrame->SetWindowStyle(wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP);
    pLogFrame->SetSize( wxRect(0,50,400,250) );
    wxLog::SetActiveTarget(m_pLogWindow);
    wxLogDebug("Start logging");
    wxLogWarning("asdasda");
    wxLogError("asdasda");
    wxLogWarning("asdasda");

#endif // LOGGING
}
