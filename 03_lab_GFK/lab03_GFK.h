///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
	private:

	protected:
		wxPanel* _DrawArea;
		wxButton* m_button1;
		wxCheckBox* _CheckBoxBanana;
		wxScrollBar* _handPositionScrollBar;
		wxGauge* _GaugeMoveHand;
		wxButton* _ButtonColorPicker;
		wxTextCtrl* _TextInputDraw;
		wxChoice* _Choice;

		// Virtual event handlers, override them in your derived class
		virtual void _updateDrawArea( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void _saveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _showBananaOnCheck( wxCommandEvent& event ) { event.Skip(); }
		virtual void _changeHandPosition( wxScrollEvent& event ) { event.Skip(); }
		virtual void _changeStarColor( wxCommandEvent& event ) { event.Skip(); }
		virtual void _updateText( wxCommandEvent& event ) { event.Skip(); }
		virtual void _chooseObject( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 612,386 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame();

};

