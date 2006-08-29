/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp,v 1.81.2.1 2005/11/30 20:48:19 MW Exp $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if wxUSE_CLIPBOARD
    #include "wx/dataobj.h"
    #include "wx/clipbrd.h"
#endif

#if wxUSE_FILE
    #include "wx/file.h"
#endif

// We test for wxUSE_DRAG_AND_DROP also, because data objects may not be
// implemented for compilers that can't cope with the OLE parts in
// wxUSE_DRAG_AND_DROP.
#if !wxUSE_DRAG_AND_DROP
    #undef wxUSE_CLIPBOARD
    #define wxUSE_CLIPBOARD 0
#endif

#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"

#include "wx/rawbmp.h"
#include "wx/dynlib.h"
#include <wx/tokenzr.h>
#include "../texgen/tg_shared.h"

#ifdef _WINDOWS
#define TEXGEN_LIB_NAME "texgen.dll"
#else
#define TEXGEN_LIB_NAME "texgen.so"
#endif

enum
{
    TEXT_QUIT = wxID_EXIT,
    TEXT_ABOUT = wxID_ABOUT,
    TEXT_LOAD = 101,
    TEXT_SAVE,
    TEXT_CLEAR,

    TEXT_END
};

void MyLogError(const char *format, ...)
{
}

void MyLogMessage(const char *format, ...)
{
}

void *MyMalloc(int size)
{
    return malloc(size);
}

//----------------------------------------------------------------------
// class definitions
//----------------------------------------------------------------------

#define SMALL_SIZE 256

class MyRawBitmapFrame : public wxPanel
{
public:
    void OnPaint(wxPaintEvent& WXUNUSED(event))
    {
        wxPaintDC dc(this);
        dc.DrawBitmap(m_bitmap, 0, 0, false /* use mask */);
    }

    void UploadData(unsigned char *incomming)
    {
        typedef wxAlphaPixelData Data;
        unsigned char *in = incomming;

        Data data(m_bitmap, wxPoint(0, 0) , wxSize(SMALL_SIZE, SMALL_SIZE));
        //data.UseAlpha();

        Data::Iterator p(data);
        for(int y=0; y<SMALL_SIZE; y++)
        {
            Data::Iterator row = p;
            for(int x=0; x<SMALL_SIZE; x++)
            {
                p.Red() = *in++;
                p.Green() = *in++;
                p.Blue() = *in++;
                //p.Alpha() = 
                in++;
                ++p;
            }

            p = row;
            p.OffsetY(data, 1);
        }

        Refresh();
    }

private:
    wxBitmap m_bitmap;

public:
    MyRawBitmapFrame(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0) , wxSize(SMALL_SIZE, SMALL_SIZE)), m_bitmap(SMALL_SIZE, SMALL_SIZE, 32)
    {
        SetClientSize(SMALL_SIZE, SMALL_SIZE);
    }

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyRawBitmapFrame, wxPanel)
    EVT_PAINT(MyRawBitmapFrame::OnPaint)
END_EVENT_TABLE()

DECLARE_EVENT_TYPE(wxEVT_UPDATE_CODE, -1)
DEFINE_EVENT_TYPE(wxEVT_UPDATE_CODE)

class MyPanel: public wxPanel
{
public:
	bool SaveCode(void)
	{
        wxFileDialog saveDialog(this);

        saveDialog.SetStyle(wxSAVE | wxFILE_MUST_EXIST);
        saveDialog.SetDirectory(lastDir);

        if(saveDialog.ShowModal() == wxID_OK)
        {
            lastDir = saveDialog.GetDirectory();
            return m_code->SaveFile(saveDialog.GetPath());
        }
        return false;
	}
	bool LoadCode(void)
	{
        wxFileDialog loadDialog(this);

        loadDialog.SetStyle(wxOPEN);
        loadDialog.SetDirectory(lastDir);

        if(loadDialog.ShowModal() == wxID_OK)
        {
            lastDir = loadDialog.GetDirectory();
            return m_code->LoadFile(loadDialog.GetPath());
        }
        return false;
	}
    long GetCodeLine(void)
    {
        long y;
        m_code->PositionToXY(m_code->GetInsertionPoint(), NULL, &y);
        return y;
    }
    long GetCodeLine(long pos)
    {
        long y;
        m_code->PositionToXY(pos, NULL, &y);
        return y;
    }
    bool CodeEditChange(void)
    {
        if(m_code->IsModified())
            return true;
        m_code->DiscardEdits();

        return m_code_old_y != GetCodeLine();
    }
    void OnCharEvent(wxKeyEvent& event)
    {
        event.Skip();

        long keycode = event.GetKeyCode();
        wxCommandEvent delay(wxEVT_UPDATE_CODE);
        switch ( keycode )
        {
            case WXK_PRIOR:
            case WXK_NEXT:
            case WXK_END:
            case WXK_HOME:
            case WXK_LEFT:
            case WXK_UP:
            case WXK_RIGHT:
            case WXK_DOWN:
                m_code_old_y = GetCodeLine();
                AddPendingEvent(delay);
            default:
                break;
        }
    }
    void OnMouseEvent(wxMouseEvent& event)
    {
        event.Skip();

        m_code_old_y = GetCodeLine();

        wxCommandEvent delay(wxEVT_UPDATE_CODE);
        AddPendingEvent(delay);
    }
    void OnTextEvent(wxCommandEvent& event)
    {
        event.Skip();

        m_code_old_y = -1;

        wxCommandEvent delay(wxEVT_UPDATE_CODE);
        AddPendingEvent(delay);
    }

    void OnUpdateCode(wxCommandEvent& WXUNUSED(event))
    {
        if(!CodeEditChange())
            return;

        tgi.newPainting(SMALL_SIZE, SMALL_SIZE);

        bool lineUploaded = false, stageUploaded = false, stageSelected = false;
        unsigned char *data;
        int lastPos = 0;

        wxStringTokenizer tkz(m_code->GetValue(), wxT("\n\t"));
        while (tkz.HasMoreTokens())
        {
            wxStringTokenizer lineTkz(tkz.GetNextToken(), wxT(" "));
            wxString token = lineTkz.GetNextToken();

            if(token[0] == '/' && token[1] == '/')
            {
                while(lineTkz.HasMoreTokens()) token = lineTkz.GetNextToken();
                continue;
            }

            if(token.Last() == ':')
            {
                token.Last() = 0;

                if(!stageUploaded && stageSelected)
                {
                    if(tkz.GetPosition() > m_code->GetInsertionPoint())
                    {
                        tgi.getImage(TG_COLOR, TG_BYTE, (void **)&data);
                        m_finalStage->UploadData(data);
                        free(data);
                        stageUploaded = true;
                    }
                }

                tgi.bind(token.mb_str(wxConvUTF8));
                stageSelected = true;
                continue;
            }

            int i = 0;
            wxString tokens[64];
            tokens[i++] = token;
            while(lineTkz.HasMoreTokens()) tokens[i++] = lineTkz.GetNextToken();

            if(i == 2)
            {
                if(token == _T("seed"))
                {
                    int seed = atoi(tokens[1].mb_str(wxConvUTF8));
                    tgi.seed(seed);
                }
                if(token == _T("gaussian"))
                {
                    float pixels = atof(tokens[1].mb_str(wxConvUTF8));
                    tgi.gaussian(pixels);
                }
            }
            if(i == 4)
            {
                if(token == _T("colornoise"))
                {
                    int grid = atoi(tokens[1].mb_str(wxConvUTF8));
                    float min = atof(tokens[2].mb_str(wxConvUTF8));
                    float max = atof(tokens[3].mb_str(wxConvUTF8));
                    tgi.colorNoise(grid, min, max);
                }
                if(token == _T("bumpnoise"))
                {
                    int grid = atoi(tokens[1].mb_str(wxConvUTF8));
                    float min = atof(tokens[2].mb_str(wxConvUTF8));
                    float max = atof(tokens[3].mb_str(wxConvUTF8));
                    tgi.bumpNoise(grid, min, max);
                }
                if(token == _T("noisemask"))
                {
                    int grid = atoi(tokens[1].mb_str(wxConvUTF8));
                    float min = atof(tokens[2].mb_str(wxConvUTF8));
                    float max = atof(tokens[3].mb_str(wxConvUTF8));
                    tgi.noiseMask(grid, min, max);
                }
                if(token == _T("combinemask"))
                {
                    const char *bottom = tokens[1].mb_str(wxConvUTF8);
                    const char *top = tokens[2].mb_str(wxConvUTF8);
                    const char *mask = tokens[3].mb_str(wxConvUTF8);
                    tgi.combineMask(bottom, top, mask);
                }
            }
            if(i == 5)
            {
                if(token == _T("brickmask"))
                {
                    float brickwidth_ = atof(tokens[1].mb_str(wxConvUTF8));
                    float brickheight_ = atof(tokens[2].mb_str(wxConvUTF8));
                    float mortarthickness_ = atof(tokens[3].mb_str(wxConvUTF8));
                    float bevelthickness_ = atof(tokens[4].mb_str(wxConvUTF8));
                    tgi.brickMask(brickwidth_, brickheight_, mortarthickness_, bevelthickness_);
                }
            }
            if(i == 6)
            {
                if(token == _T("clear"))
                {
                    float cr = atof(tokens[1].mb_str(wxConvUTF8));
                    float cg = atof(tokens[2].mb_str(wxConvUTF8));
                    float cb = atof(tokens[3].mb_str(wxConvUTF8));
                    float ca = atof(tokens[4].mb_str(wxConvUTF8));
                    float cd = atof(tokens[5].mb_str(wxConvUTF8));
                    tgi.clear(cr, cg, cb, ca, cd);
                }
            }
            if(i == 7)
            {
                if(token == _T("light"))
                {
                    float light[3];
                    float color[3];

                    light[0] = atof(tokens[1].mb_str(wxConvUTF8));
                    light[1] = atof(tokens[2].mb_str(wxConvUTF8));
                    light[2] = atof(tokens[3].mb_str(wxConvUTF8));
                    color[0] = atof(tokens[4].mb_str(wxConvUTF8));
                    color[1] = atof(tokens[5].mb_str(wxConvUTF8));
                    color[2] = atof(tokens[6].mb_str(wxConvUTF8));

                    tgi.light(light, color);
                }
            }
            if(i == 13)
            {
                if(token == _T("watererode"))
                {
                    float count = atof(tokens[1].mb_str(wxConvUTF8));
                    float length = atof(tokens[2].mb_str(wxConvUTF8));
                    float erode = atof(tokens[3].mb_str(wxConvUTF8));
                    float size = atof(tokens[4].mb_str(wxConvUTF8));
                    float minx = atof(tokens[5].mb_str(wxConvUTF8));
                    float miny = atof(tokens[6].mb_str(wxConvUTF8));
                    float maxx = atof(tokens[7].mb_str(wxConvUTF8));
                    float maxy = atof(tokens[8].mb_str(wxConvUTF8));

                    float color[4];
                    color[0] = atof(tokens[ 9].mb_str(wxConvUTF8));
                    color[1] = atof(tokens[10].mb_str(wxConvUTF8));
                    color[2] = atof(tokens[11].mb_str(wxConvUTF8));
                    color[3] = atof(tokens[12].mb_str(wxConvUTF8));

                    tgi.waterErode(count, length, erode, size, minx, miny, maxx, maxy, color);
                }
            }

            if(tgi.getString(TG_ERRORSTRING))
            {
                return;
            }
            lastPos = tkz.GetPosition();

            if(!lineUploaded)
            {
                if(GetCodeLine(lastPos) == GetCodeLine())
                {
                    tgi.getImage(TG_COLOR, TG_BYTE, (void **)&data);
                    m_currentCommand->UploadData(data);
                    free(data);
                    lineUploaded = true;
                }
            }
        }

        if(!stageUploaded)
        {
            tgi.getImage(TG_COLOR, TG_BYTE, (void **)&data);
            m_finalStage->UploadData(data);
            free(data);
        }

        tgi.bind("output");
        tgi.getImage(TG_COLOR, TG_BYTE, (void **)&data);
        m_finalTexture->UploadData(data);
        free(data);
    }

private:
	wxDynamicLibrary	*tgLibrary;
	tg_interface_t		tgi;

    int                 m_code_old_y;
    wxString            lastDir;
	wxTextCtrl			*m_code;
    wxTextCtrl			*m_log;
    wxLog				*m_logOld;

	MyRawBitmapFrame	*m_finalStage;
	MyRawBitmapFrame	*m_currentCommand;
	MyRawBitmapFrame	*m_finalTexture;

public:
    virtual ~MyPanel()
    {
        delete wxLog::SetActiveTarget(m_logOld);
    }
	MyPanel(wxFrame *frame, int x, int y, int w, int h) : wxPanel(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h))
	{
		m_log = new wxTextCtrl( this, wxID_ANY, _T("This is the log window.\n"), wxPoint(5,260), wxSize(630,100), wxTE_MULTILINE | wxTE_READONLY/* | wxTE_RICH */);
		m_logOld = wxLog::SetActiveTarget( new wxLogTextCtrl( m_log ) );

		tgi.Error = MyLogError;
		tgi.Print = MyLogMessage;
        tgi.Malloc = MyMalloc;

		tgLibrary = new wxDynamicLibrary(TEXGEN_LIB_NAME);
        if(tgLibrary->IsLoaded())
        {
    		PFNTEXGENLIBEXPORTPROC TexgenLibExport = (PFNTEXGENLIBEXPORTPROC)(tgLibrary->GetSymbol(_T("TexgenLibExport")));
		    TexgenLibExport(&tgi);
        }

		m_code = new wxTextCtrl(this, wxID_ANY, _T(""), wxPoint(450, 10), wxSize(200, 230), wxTE_RICH | wxTE_MULTILINE | wxTE_PROCESS_TAB);
        m_finalStage = new MyRawBitmapFrame(this);
        m_currentCommand = new MyRawBitmapFrame(this);
        m_finalTexture = new MyRawBitmapFrame(this);

		// lay out the controls
		wxBoxSizer *picSizer = new wxBoxSizer(wxHORIZONTAL);
        picSizer->Add(m_finalStage, 0, wxALL, 5);
        picSizer->Add(m_currentCommand, 0, wxALL, 5);
        picSizer->Add(m_finalTexture, 0, wxALL, 5);

		wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
		topSizer->Add(m_code, 4, wxALL | wxEXPAND, 5);
        topSizer->Add(picSizer, 0, wxALL | wxEXPAND, 5);
		topSizer->Add(m_log, 1, wxALL | wxEXPAND, 5);

		SetAutoLayout( true );
		SetSizer(topSizer);

        m_code->Connect(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED, wxTextEventHandler(MyPanel::OnTextEvent), NULL, this);
        m_code->Connect(wxID_ANY, wxEVT_CHAR, wxCharEventHandler(MyPanel::OnCharEvent), NULL, this);
        m_code->Connect(wxID_ANY, wxEVT_LEFT_DOWN, wxMouseEventHandler(MyPanel::OnMouseEvent), NULL, this);
        Connect(wxID_ANY, wxEVT_UPDATE_CODE, wxCommandEventHandler(MyPanel::OnUpdateCode), NULL, this);

        lastDir = wxString(_T(""));
	}
};

class MyFrame: public wxFrame
{
public:
	void OnQuit (wxCommandEvent& WXUNUSED(event) )
	{
		Close(true);
	}
	void OnAbout( wxCommandEvent& WXUNUSED(event) )
	{
		wxBeginBusyCursor();

		wxMessageDialog dialog(this,
		  _T("This is a text control sample. It demonstrates the many different\n")
		  _T("text control styles, the use of the clipboard, setting and handling\n")
		  _T("tooltips and intercepting key and char events.\n")
		  _T("\n")
			_T("Copyright (c) 1999, Robert Roebling, Julian Smart, Vadim Zeitlin"),
			_T("About wxTextCtrl Sample"),
			wxOK | wxICON_INFORMATION);

		dialog.ShowModal();

		wxEndBusyCursor();
	}
	void OnFileSave(wxCommandEvent& WXUNUSED(event))
	{
		if(m_panel->SaveCode())
			wxLogStatus(this, _T("Successfully saved file"));
		else
			wxLogStatus(this, _T("Couldn't save the file"));
	}
	void OnFileLoad(wxCommandEvent& WXUNUSED(event))
	{
		if(m_panel->LoadCode())
			wxLogStatus(this, _T("Successfully loaded file"));
		else
			wxLogStatus(this, _T("Couldn't load the file"));
	}

private:
    MyPanel *m_panel;

public:
	MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h) : wxFrame(frame, wxID_ANY, title, wxPoint(x, y), wxSize(w, h) )
	{
		CreateStatusBar(2);

		m_panel = new MyPanel( this, 10, 10, 300, 100 );
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(TEXT_QUIT,   MyFrame::OnQuit)
    EVT_MENU(TEXT_ABOUT,  MyFrame::OnAbout)
    EVT_MENU(TEXT_SAVE,   MyFrame::OnFileSave)
    EVT_MENU(TEXT_LOAD,   MyFrame::OnFileLoad)
END_EVENT_TABLE()

//----------------------------------------------------------------------
// main()
//----------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    bool MyApp::OnInit()
	{
		// Create the main frame window
		MyFrame *frame = new MyFrame((wxFrame *) NULL, _T("tgEditor - one shop for all your images, someday"), 50, 50, 700, 550);
		frame->SetSizeHints( 500, 400 );

		wxMenuBar *menu_bar = new wxMenuBar( wxMB_DOCKABLE );

		wxMenu *file_menu = new wxMenu;
		file_menu->Append(TEXT_SAVE, _T("&Save file\tCtrl-S"), _T("Save the text control contents to file"));
		file_menu->Append(TEXT_LOAD, _T("&Load file\tCtrl-O"), _T("Load the sample file into text control"));
		file_menu->AppendSeparator();
		file_menu->Append(TEXT_ABOUT, _T("&About\tAlt-A"));
		file_menu->AppendSeparator();
		file_menu->Append(TEXT_QUIT, _T("E&xit\tAlt-X"), _T("Quit this sample"));

		menu_bar->Append(file_menu, _T("&File"));

		frame->SetMenuBar(menu_bar);
		frame->Show(true);

		SetTopWindow(frame);

		// report success
		return true;
	}
};

IMPLEMENT_APP(MyApp)
