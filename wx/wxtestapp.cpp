#include "embed.h"
#include "EmbeddingSetup.h"
#include "listener.h"

#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/textfile.h>
//#include <wx/printdlg.h>
//#include "wx/artprov.h"
//#include "wx/aui/aui.h"
//#include "../webconnect/webcontrol.h"

// web control and url combobox ids
const int wxID_WEB = 9001;
const int wxID_URL = 9002;

//debug vars
bool m_StartUpdate = false;

MozView *myMozView;
SampleListener *myMozListener;

class MyApp : public wxApp
{
public:

    bool OnInit()
    {
        // Locate the XULRunner engine; the following call will look for 
        // a directory named "xr"
        //wxString xulrunner_path = FindXulRunner(wxT("xr"));
        /*wxString xulrunner_path = wxT("/home/sk/work/mozilla/sdk/xulrunner-31/");
        if (xulrunner_path.IsEmpty())
        {
            wxMessageBox(wxT("Could not find xulrunner directory"));
            return false;
        }*/
    
        // Locate some common paths and initialize the control with
        // the plugin paths; add these common plugin directories to 
        // MOZ_PLUGIN_PATH
        //wxString program_files_dir;
        //::wxGetEnv(wxT("ProgramFiles"), &program_files_dir);
        //if (program_files_dir.Length() == 0 || program_files_dir.Last() != '\\')
        //    program_files_dir += wxT("\\");

        //wxString dir = program_files_dir;
        //dir += wxT("Mozilla Firefox\\plugins");
        //wxWebControl::AddPluginPath(dir);

        // to install the flash plugin automatically, if it exists, 
        // add a path to the flash location; for example, on windows,
        // if the system directory is given by system_dir, then, we have:
        //
        // wxString dir2 = system_dir;
        // dir2 += wxT("Macromed\\Flash");
        // wxWebControl::AddPluginPath(dir2);

        // Finally, initialize the engine; Calling wxWebControl::InitEngine()
        // is very important and has to be made before using wxWebControl.  
        // It instructs wxWebConnect where the xulrunner directory is.

        //wxString xulrunner_path =  wxString::FromUTF8("");//empty string for default xulrunner path
        //wxWebControl::InitEngine(xulrunner_path); 

       // Create and show the frame
        wxFrame* frame1 = new wxFrame(NULL,
                                     wxID_ANY,
                                     wxT("Gecko Embedding Test"),
                                     wxDefaultPosition,
                                     wxSize(1024, 768));


	    // get base window interface and set its native window
	    #ifdef __WXGTK__
	    //void* native_handle = (void*)m_wxwindow;
	    void* native_handle = (void*)frame1;
	    std::cout << "Using gtk frame for embedding" << std::endl;
	    #else
	    void* native_handle = (void*)frame1->GetHandle();
	    std::cout << "Using native handler from frame for embedding" << std::endl;
	    #endif

		myMozView = new MozView();

	    int res = myMozView->CreateBrowser(native_handle, 0, 0, 1024-50, 600-50, 0);
	    //int res = myMozView->CreateBrowser(g_viewport, 0, 0, 1024-50, 600-50, 0);

	    myMozListener = new SampleListener(myMozView);

	    myMozView->SetListener(myMozListener);

	    //if(argc < 2)
    	//	myMozView->LoadURI("http://www.mozilla.org");
	    //else myMozView->LoadURI(argv[1]);

	//std::cout << "Creating wxWebControl object" << std::endl;
	//wxWebControl *m_browser = new wxWebControl(frame1, wxID_WEB, wxPoint(0,0), wxSize(800,600));

        //wxWindow win1 = this->GetTopWindow();
        //wxWebControl(frame1);

        SetTopWindow(frame1);
        frame1->Show();

	myMozView->LoadURI("www.opennet.ru");
	//m_browser->OpenURI("www.opennet.ru");

/*
        app = wx.App()
        frame = wx.Frame(None, -1, 'Pytho Gecko Test')
        wc = webconnect.wxWebControl(frame)
        wc.OpenURI('www.opennet.ru')
        frame.Show()*/

        return true;
    }
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);
