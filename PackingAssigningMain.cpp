/***************************************************************
 * Name:      PackingAssigningMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2012-12-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "PackingAssigningMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(PackingAssigningDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/chartype.h>
#include <wx/dirdlg.h>
#include "pugixml.hpp"
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

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

//(*IdInit(PackingAssigningDialog)
const long PackingAssigningDialog::ID_STATICTEXT1 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL1 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON1 = wxNewId();
const long PackingAssigningDialog::ID_STATICBOX1 = wxNewId();
const long PackingAssigningDialog::ID_GAUGE1 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON3 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON4 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON5 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL2 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT2 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL3 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON2 = wxNewId();
const long PackingAssigningDialog::ID_CHECKBOX1 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT3 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL4 = wxNewId();
const long PackingAssigningDialog::ID_BUTTON6 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT4 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT5 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT6 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT7 = wxNewId();
const long PackingAssigningDialog::ID_STATICTEXT8 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL5 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL6 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL7 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL8 = wxNewId();
const long PackingAssigningDialog::ID_TEXTCTRL9 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PackingAssigningDialog,wxDialog)
    //(*EventTable(PackingAssigningDialog)
    //*)
END_EVENT_TABLE()

PackingAssigningDialog::PackingAssigningDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(PackingAssigningDialog)
    Create(parent, wxID_ANY, _("wxWidgets app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(600,450));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("解析路径"), wxPoint(16,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    srcctrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(88,16), wxSize(240,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button1 = new wxButton(this, ID_BUTTON1, _("..."), wxPoint(352,16), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("操作记录"), wxPoint(24,192), wxSize(552,216), 0, _T("ID_STATICBOX1"));
    processctrl = new wxGauge(this, ID_GAUGE1, 100, wxPoint(24,144), wxSize(552,28), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    Button3 = new wxButton(this, ID_BUTTON3, _("重置操作"), wxPoint(168,96), wxSize(104,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("退出程序"), wxPoint(304,96), wxSize(104,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button5 = new wxButton(this, ID_BUTTON5, _("文件/文件夹解析"), wxPoint(32,96), wxSize(104,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    logctrl = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(48,216), wxSize(520,184), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("目标路径"), wxPoint(16,56), wxSize(56,13), 0, _T("ID_STATICTEXT2"));
    destctrl = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(88,56), wxSize(240,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    Button2 = new wxButton(this, ID_BUTTON2, _("..."), wxPoint(352,56), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    debugctrl = new wxCheckBox(this, ID_CHECKBOX1, _("调试模式"), wxPoint(384,8), wxSize(72,13), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    debugctrl->SetValue(false);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("四位合同号EXCEL文件"), wxPoint(24,424), wxSize(128,13), 0, _T("ID_STATICTEXT3"));
    contractctrl = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(160,416), wxSize(320,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    Button6 = new wxButton(this, ID_BUTTON6, _("..."), wxPoint(504,416), wxSize(48,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    lnwbsno = new wxStaticText(this, ID_STATICTEXT4, _("wbs no行号"), wxPoint(480,16), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    lnwbsno->Hide();
    lnproject = new wxStaticText(this, ID_STATICTEXT5, _("项目名称行号"), wxPoint(464,48), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    lnproject->Hide();
    lnunit = new wxStaticText(this, ID_STATICTEXT6, _("梯号行号"), wxPoint(488,72), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    lnunit->Hide();
    lnother = new wxStaticText(this, ID_STATICTEXT7, _("输出时间行号"), wxPoint(464,96), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    lnother->Hide();
    lnmax = new wxStaticText(this, ID_STATICTEXT8, _("最大读取行号"), wxPoint(464,120), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    lnwbstxt = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxPoint(552,8), wxSize(32,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    lnwbstxt->Hide();
    lnprojtxt = new wxTextCtrl(this, ID_TEXTCTRL6, _("Text"), wxPoint(552,40), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    lnprojtxt->Hide();
    lnunittxt = new wxTextCtrl(this, ID_TEXTCTRL7, _("Text"), wxPoint(552,64), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    lnunittxt->Hide();
    lnothertxt = new wxTextCtrl(this, ID_TEXTCTRL8, _("Text"), wxPoint(552,96), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    lnothertxt->Hide();
    lnmaxtxt = new wxTextCtrl(this, ID_TEXTCTRL9, _("Text"), wxPoint(552,120), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton1Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton3Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton4Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton5Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton2Click1);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OnButton6Click);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PackingAssigningDialog::OnlnwbstxtText);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PackingAssigningDialog::OnlnprojtxtText);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PackingAssigningDialog::OnlnunittxtText);
    Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PackingAssigningDialog::OnlnothertxtText);
    Connect(ID_TEXTCTRL9,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PackingAssigningDialog::OnlnmaxtxtText);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&PackingAssigningDialog::OnInit);
    //*)
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PackingAssigningDialog::OndebugctrlClick);

#if wxUSE_LOG
#ifdef __WXMOTIF__
    // For some reason, we get a memcpy crash in wxLogStream::DoLogStream
    // on gcc/wxMotif, if we use wxLogTextCtl. Maybe it's just gcc?
    delete wxLog::SetActiveTarget(new wxLogStderr);
#else
    // set our text control as the log target
    wxLogTextCtrl *logWindow = new wxLogTextCtrl(logctrl);
    delete wxLog::SetActiveTarget(logWindow);
#endif
#endif // wxUSE_LOG

}

PackingAssigningDialog::~PackingAssigningDialog()
{
    //(*Destroy(PackingAssigningDialog)
    //*)
#if wxUSE_LOG
    delete wxLog::SetActiveTarget(NULL);
#endif // wxUSE_LOG
}

void PackingAssigningDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PackingAssigningDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void PackingAssigningDialog::OnButton1Click(wxCommandEvent& event)
{

    wxDirDialog dlg(this, "选择文件夹", "",
                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);


    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    srcpath   = dlg.GetPath();

    srcctrl->SetValue(srcpath);

    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("srcpath");
        ld_node.text().set(srcpath.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        return;
    }
}

void PackingAssigningDialog::OnButton2Click(wxCommandEvent& event)
{
}

void PackingAssigningDialog::OnButton3Click(wxCommandEvent& event)
{
}

void PackingAssigningDialog::OnButton4Click(wxCommandEvent& event)
{
    Close();
}

void PackingAssigningDialog::OnInit(wxInitDialogEvent& event)
{
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default");
        srcpath = wxString(ld_node.child_value("srcpath"));
        destpath = wxString(ld_node.child_value("destpath"));
        conexcelpath = wxString(ld_node.child_value("conexcel"));
    /*    iproject = ld_node.child("projline").text().as_int();
        iwbsno = ld_node.child("wbsline").text().as_int();
        iunit = ld_node.child("unitline").text().as_int();
        iother = ld_node.child("otherline").text().as_int();*/
        imax = ld_node.child("maxline").text().as_int();
    }
    else
    {
        srcpath= wxT("c:\\");
        destpath = wxT("c:\\");
    }
    debugmode = false;
    srcctrl->SetValue(srcpath);
    destctrl->SetValue(destpath);
    contractctrl->SetValue(conexcelpath);
    debugctrl->SetValue(debugmode);
    logctrl->Clear();

    this->SetTitle(_T("装箱清单整理程序"));

    showdebugctrl();


}

void PackingAssigningDialog::OnButton5Click(wxCommandEvent& event)
{
    wxDir ldir;
    ldir.Open(srcpath);
    wxString errorfile = _T("");
    int ierror = 0, iclean;

    if(ldir.IsOpened())
    {
        ldir.GetAllFiles(srcpath, &m_files, wxT("*.pdf"),wxDIR_FILES);
        int cfile = m_files.GetCount();

        if(cfile ==0)
        {
            wxLogMessage(srcpath+_T("下无PDF文件"));
            return;
        }

        processctrl->SetRange(cfile);
        for( int i=0; i< cfile; i++)
        {
            processctrl->SetValue(i+1);
            pdftotext(m_files.Item(i));
            if(debugmode)
                break;

            if(getnewfilename())
                wxLogMessage(m_files.Item(i)+_T("解析成功!"));
            else
            {
                errorfile = errorfile + m_files.Item(i) + _T(" 错误原因:四位合同号/项目名称/梯号/wbsno为空\n");
                wxLogMessage(m_files.Item(i)+"解析结果四位合同号/项目名称/梯号/wbsno为空!");
                ierror += 1;
                continue;
            }
            iclean = cleanfiles(m_files.Item(i));
            if(iclean==0)
                wxLogMessage(m_files.Item(i)+_T("整理完毕"));
            else if(iclean == 1)
            {
                errorfile = errorfile + m_files.Item(i) + _T(" 错误原因:目标文件被锁定！\n");
                wxLogMessage(m_newfile+"文件被锁定，请先解锁!");
                ierror += 1;
                continue;
            }
            else if(iclean == 2)
            {
                wxLogMessage(m_files.Item(i)+"文件被锁定，无法删除，请解锁后手工删除!");
                continue;
            }

        }

        if(!debugmode)
            wxLogMessage("整理完成！错误%d文件，成功 %d文件！ 错误列表如下：\n"+errorfile, ierror, cfile-ierror);
        else
            wxLogMessage("调试模式下只解析第一个pdf文件，请根据以上内容，重置数据读入行");
        m_files.clear();

    }
    else
    {
        return;
    }

    m_newfile.clear();
    m_newfolder.clear();
    m_project.clear();
    m_unit.clear();
    m_wbsno.clear();
    m_other.clear();

}

void PackingAssigningDialog::OnButton2Click1(wxCommandEvent& event)
{

    wxDirDialog dlg(this, "选择文件夹", "",
                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);


    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    destpath   = dlg.GetPath();

    destctrl->SetValue(destpath);

    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("destpath");
        ld_node.text().set(destpath.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        return;
    }
}

void PackingAssigningDialog::pdftotext(wxString pdffile)
{

    wxProcess* pProcess = new wxProcess();
    pProcess->Redirect();

    wxString cmd = _T("pdftotext.exe -cfg xpdfrc \"")+ pdffile +_T("\" ")+ _T("-");

    int i_pos, i_len,i_end;
    wxString str;

    wxExecute(cmd, wxEXEC_SYNC , pProcess);

    //如果想得到外部控制台程序的屏幕输出，还要用下面的语句得到输入流
    if(pProcess->IsInputAvailable())
    {

        wxInputStream* ResultStream=pProcess->GetInputStream();
        wxString result = _("");

        wxTextInputStream* textresult = new wxTextInputStream(*ResultStream, wxT("\t"), wxConvAuto(wxFONTENCODING_UTF8)/*wxFONTENCODING_UTF8*/);
        wxString temp;
        int i;
        iwbsno=0;
        iunit=0;
        iother=0;
        iproject=0;


        for(i=0; i<imax+1; i++)
        {
            temp = textresult->ReadLine();

            if(temp.Contains(_("产品ID(Product ID):"))&&iwbsno==0)
            {
                iwbsno=i;



                i_pos = temp.Find(wxT("/"));



                m_wbsno = temp.Mid(i_pos-1, 14);
            }



            if(temp.Contains(_("项目名称(Project Name):"))&&iproject==0)
            {
                iproject = i;

                str= _("项目名称(Project Name):");
                i_end = str.Length();

                i_pos = temp.Find(_("项目名称(Project Name):"));
                i_len = temp.Length();
                m_project = temp.Mid(i_pos+i_end,i_len-i_pos-i_end);

                m_project.Replace(wxT("#"),wxT("_"));
                m_project.Replace(wxT("•"),wxT("_"));

            }



            if(temp.Contains(wxT("梯号(UnitID):"))&&iunit==0)
            {
                i_pos = temp.Find(wxT(":"));
                iunit = i;
                i_len = temp.Length();


                m_unit = temp.Mid(i_pos+1,i_len-i_pos-1);
            }

            if(temp.Contains(_("日期Date"))&&iother ==0)
                 iother = i;

            if(i==iother+2)
                m_other=temp;




            if(iunit!=0&&iproject!=0&&iwbsno!=0&&iother!=0)
                break;
/*
            if(iproject== iunit)
            {
               if(i==iwbsno)
                    m_wbsno=temp.Right(14);
                if(i==iunit)
                {
                    i_pos = temp.Find(wxT(" "));
                    ilen = temp.Length();

                    m_unit = temp.Left(i_pos);
                    m_project = temp.Right(ilen-i_pos-1);
                }

                if(i==iother)
                {
                    m_other = temp;
                }

            }
            else
            {


                if(i==iwbsno)
                    m_wbsno=temp.Right(14);
                if(i==iunit)
                    m_unit = temp;
                if(i==iproject)
                    m_project=temp;
                if(i==iother)
                {
                    m_other = temp;
                }
            }*/
            if(debugmode)
                wxLogMessage(_T("line %d:")+temp, i);

        }

        if(debugmode)
        {
            wxLogMessage("合同号:"+m_contract);
            wxLogMessage("wbs no is:"+m_wbsno);
            wxLogMessage("项目名称:"+m_project);
            wxLogMessage("梯号:"+m_unit);
            wxLogMessage("其他信息:"+m_other);
        }
    }

}

int PackingAssigningDialog::cleanfiles(wxString pdffile)
{
    int i=0;
    if(!wxDirExists(m_newfolder))
        wxMkDir(m_newfolder);
//   wxString lfilename = wxFileNameFromPath(pdffile);
    if(!wxCopyFile(pdffile, m_newfile, true))
    {
        i=1;
        return i;
    }

    if(!wxRemoveFile(pdffile))
        i=2;
    return i;


}

bool PackingAssigningDialog::getnewfilename()
{
    if(m_project.IsEmpty()|| m_unit.IsEmpty() || m_wbsno.IsEmpty())
        return false;

    wxString temp;
//   temp = m_wbsno.Mid(3, 8);
//   if(temp.IsNumber())
    //      return false;
/*
    int ipos= m_other.First("Date 2");
    temp = m_other.Mid(ipos+5,15);
    m_other = temp;*/


    m_contract = findcontract(m_wbsno);
    if(m_contract.IsEmpty())
        return false;

    wxLogMessage(m_contract);
    m_other.Replace(".","");
    m_other.Replace(":","");
    m_other.Replace(" ","-");
    m_project.Replace("/","");
    m_project.Replace("\\","");
    m_wbsno.Replace("/","");
//   m_wbsno.Replace(".","_");
    m_unit.Replace("\\","");

    m_other = m_other.Left(12)+_T("0");
    m_newfolder = destpath + _T("\\")+m_contract+_T("_")+m_project+_T("_")+ m_wbsno.Left(9);
    m_newfile = m_newfolder + _T("\\") + m_wbsno + _T("_") + m_project + _T("_") + m_unit+_T("_")+m_contract+_T("_")+m_other+_T(".pdf");

    return true;

}

wxString PackingAssigningDialog::findcontract(wxString lwbsno)
{
    wxString ltemp=lwbsno.Trim().Left(10);
    wxString lstr,lresult;
    wxTextFile ltext(conexcelpath);
    bool b_open = ltext.Open(wxConvAuto());
    if(!b_open)
    {
        wxLogMessage(conexcelpath+_("文件不存在!"));
        return wxEmptyString;
    }
    int i_pos;
    for(lstr = ltext.GetLastLine(); ltext.GetCurrentLine() > 0; lstr = ltext.GetPrevLine() )
    {
        if(lstr.Contains(ltemp))
        {
            i_pos = lstr.Find(ltemp);
            lresult = lstr.Left(i_pos).Trim();
            break;
        }
    }
    ltext.Close();
    return lresult;
}

void PackingAssigningDialog::OndebugctrlClick(wxCommandEvent& event)
{
    if(!event.IsChecked())
    {
//       debugctrl->SetValue(false);
        debugmode=false;
        wxLogMessage(_T("调试模式关闭"));
        this->SetTitle(_T("装箱清单整理程序"));

    }
    else
    {
        //      debugctrl->SetValue(true);
        debugmode=true;
        this->SetTitle(_T("装箱清单整理程序(调试模式)"));
        wxLogMessage(_T("调试模式开启(默认关闭)"));
        wxLogMessage(_T("调试模式下将只解析第一个pdf文件，并列出解析每行的内容,但不整理pdf文件，同时可以编辑配置文件中，读取内容的行标识!"));

    }

    showdebugctrl();

}

void PackingAssigningDialog::OnButton6Click(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open txt file"), "", "",
                     "txt files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);


    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    conexcelpath  = dlg.GetPath();

    contractctrl->SetValue(conexcelpath);

    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("conexcel");
        ld_node.text().set(conexcelpath.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        return;
    }
}


void PackingAssigningDialog::showdebugctrl()
{
  /*  lnwbstxt->Show(debugmode);
    lnunit->Show(debugmode);
    lnwbsno->Show(debugmode);
    lnunittxt->Show(debugmode);
    lnproject->Show(debugmode);
    lnprojtxt->Show(debugmode);
    lnother->Show(debugmode);
    lnothertxt->Show(debugmode);*/
    lnmax->Show(debugmode);
    lnmaxtxt->Show(debugmode);

    if(debugmode)
    {
      /*  lnwbstxt->SetValue(wxString::Format("%d",iwbsno));
        lnunittxt->SetValue(wxString::Format("%d",iunit));
        lnprojtxt->SetValue(wxString::Format("%d",iproject));
        lnothertxt->SetValue(wxString::Format("%d",iother));*/
        lnmaxtxt->SetValue(wxString::Format("%d",imax));
    }
}

void PackingAssigningDialog::OnlnwbstxtText(wxCommandEvent& event)
{
    if(!debugmode)
        event.Skip();

    wxString temp=event.GetString();

    iwbsno = wxAtoi(temp);
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("wbsline");
        ld_node.text().set(temp.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        event.Skip();
    }


}

void PackingAssigningDialog::OnlnprojtxtText(wxCommandEvent& event)
{
    if(!debugmode)
        event.Skip();

    wxString temp=event.GetString();



    iproject= wxAtoi(temp);
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("projline");
        ld_node.text().set(temp.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        event.Skip();
    }


}

void PackingAssigningDialog::OnlnunittxtText(wxCommandEvent& event)
{
    if(!debugmode)
        event.Skip();

    wxString temp=event.GetString();

    iunit= wxAtoi(temp);
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("unitline");
        ld_node.text().set(temp.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        event.Skip();
    }


}

void PackingAssigningDialog::OnlnothertxtText(wxCommandEvent& event)
{

    if(!debugmode)
        event.Skip();


    wxString temp=event.GetString();

    iother= wxAtoi(temp);
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("otherline");
        ld_node.text().set(temp.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        event.Skip();
    }

}

void PackingAssigningDialog::OnlnmaxtxtText(wxCommandEvent& event)
{
    if(!debugmode)
        event.Skip();



    wxString temp=event.GetString();



    imax= wxAtoi(temp);
    pugi::xml_document m_doc;
    pugi::xml_node ld_node;
    pugi::xml_parse_result result;
    result = m_doc.load_file("config.xml");
    if (result)
    {
        pugi::xml_node ld_node = m_doc.child("default").child("maxline");
        ld_node.text().set(temp.mbc_str());
        m_doc.save_file("config.xml");
    }
    else
    {
        event.Skip();
    }

}
