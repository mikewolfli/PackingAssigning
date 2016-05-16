/***************************************************************
 * Name:      PackingAssigningMain.h
 * Purpose:   Defines Application Frame
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2012-12-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com)
 * License:
 **************************************************************/

#ifndef PACKINGASSIGNINGMAIN_H
#define PACKINGASSIGNINGMAIN_H

//(*Headers(PackingAssigningDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
//*)
#include <wx/log.h>
#include <wx/stream.h>
#include <wx/txtstrm.h>
#include <wx/process.h>

class PackingAssigningDialog: public wxDialog
{
public:

    PackingAssigningDialog(wxWindow* parent,wxWindowID id = -1);
    virtual ~PackingAssigningDialog();

private:

    //(*Handlers(PackingAssigningDialog)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButton1Click(wxCommandEvent& event);
    void OnButton2Click(wxCommandEvent& event);
    void OnButton3Click(wxCommandEvent& event);
    void OnButton4Click(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnButton5Click(wxCommandEvent& event);
    void OnButton2Click1(wxCommandEvent& event);
    void OndebugctrlClick(wxCommandEvent& event);
    void OnButton6Click(wxCommandEvent& event);
    void OnlnwbstxtText(wxCommandEvent& event);
    void OnlnprojtxtText(wxCommandEvent& event);
    void OnlnunittxtText(wxCommandEvent& event);
    void OnlnothertxtText(wxCommandEvent& event);
    void OnlnmaxtxtText(wxCommandEvent& event);
    //*)

    //(*Identifiers(PackingAssigningDialog)
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL1;
    static const long ID_BUTTON1;
    static const long ID_STATICBOX1;
    static const long ID_GAUGE1;
    static const long ID_BUTTON3;
    static const long ID_BUTTON4;
    static const long ID_BUTTON5;
    static const long ID_TEXTCTRL2;
    static const long ID_STATICTEXT2;
    static const long ID_TEXTCTRL3;
    static const long ID_BUTTON2;
    static const long ID_CHECKBOX1;
    static const long ID_STATICTEXT3;
    static const long ID_TEXTCTRL4;
    static const long ID_BUTTON6;
    static const long ID_STATICTEXT4;
    static const long ID_STATICTEXT5;
    static const long ID_STATICTEXT6;
    static const long ID_STATICTEXT7;
    static const long ID_STATICTEXT8;
    static const long ID_TEXTCTRL5;
    static const long ID_TEXTCTRL6;
    static const long ID_TEXTCTRL7;
    static const long ID_TEXTCTRL8;
    static const long ID_TEXTCTRL9;
    //*)

    //(*Declarations(PackingAssigningDialog)
    wxTextCtrl* contractctrl;
    wxButton* Button4;
    wxStaticText* lnunit;
    wxTextCtrl* lnunittxt;
    wxStaticText* lnmax;
    wxStaticText* StaticText2;
    wxTextCtrl* destctrl;
    wxButton* Button1;
    wxTextCtrl* lnothertxt;
    wxStaticText* StaticText1;
    wxTextCtrl* logctrl;
    wxStaticText* StaticText3;
    wxTextCtrl* lnmaxtxt;
    wxStaticBox* StaticBox1;
    wxButton* Button2;
    wxStaticText* lnproject;
    wxButton* Button6;
    wxStaticText* lnwbsno;
    wxButton* Button5;
    wxCheckBox* debugctrl;
    wxButton* Button3;
    wxStaticText* lnother;
    wxTextCtrl* srcctrl;
    wxTextCtrl* lnwbstxt;
    wxGauge* processctrl;
    wxTextCtrl* lnprojtxt;
    //*)
    wxString srcpath;
    wxString destpath;
    wxString conexcelpath;
    wxArrayString m_files;
    void pdftotext(wxString pdffile);
    wxString m_project;
    wxString m_contract;
    wxString m_unit;
    wxString m_wbsno;
    wxString m_other;
    wxString m_newfile;
    wxString m_newfolder;
    wxString findcontract(wxString lwbsno);
    int iproject;
    int iunit;
    int iwbsno;
    int iother;
    int imax;
    bool getnewfilename();
    int cleanfiles(wxString pdffile);
    bool debugmode;
    void showdebugctrl();


    DECLARE_EVENT_TABLE()

};

#endif // PACKINGASSIGNINGMAIN_H
