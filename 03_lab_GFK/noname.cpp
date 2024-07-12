///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* sizerPain;
	sizerPain = new wxBoxSizer( wxVERTICAL );

	_DrawArea = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	_DrawArea->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	sizerPain->Add( _DrawArea, 1, wxEXPAND | wxALL, 5 );


	mainSizer->Add( sizerPain, 1, wxEXPAND, 5 );

	wxBoxSizer* sizerMenu;
	sizerMenu = new wxBoxSizer( wxVERTICAL );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerMenu->Add( m_button1, 0, wxALIGN_CENTER|wxALL, 5 );

	_CheckBoxBanana = new wxCheckBox( this, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerMenu->Add( _CheckBoxBanana, 0, wxALIGN_CENTER|wxALL, 5 );

	m_scrollBar1 = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	sizerMenu->Add( m_scrollBar1, 0, wxALIGN_CENTER|wxALL, 5 );

	_GaugeMoveHand = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	_GaugeMoveHand->SetValue( 0 );
	sizerMenu->Add( _GaugeMoveHand, 0, wxALIGN_CENTER|wxALL, 5 );

	_ButtonColorPicker = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerMenu->Add( _ButtonColorPicker, 0, wxALIGN_CENTER, 5 );

	_TextInputDraw = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMenu->Add( _TextInputDraw, 0, wxALIGN_CENTER|wxALL, 5 );

	wxArrayString _ChoiceChoices;
	_Choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _ChoiceChoices, 0 );
	_Choice->SetSelection( 0 );
	sizerMenu->Add( _Choice, 0, wxALIGN_CENTER|wxALL, 5 );


	mainSizer->Add( sizerMenu, 0, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

MyFrame1::~MyFrame1()
{
}
