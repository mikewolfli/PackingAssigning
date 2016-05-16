/***************************************************************
 * Name:      PackingAssigningApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2012-12-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "PackingAssigningApp.h"

//(*AppHeaders
#include "PackingAssigningMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PackingAssigningApp);

bool PackingAssigningApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PackingAssigningDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
