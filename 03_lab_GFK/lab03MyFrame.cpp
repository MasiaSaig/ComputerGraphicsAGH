#include "lab03MyFrame.h"

lab03MyFrame::lab03MyFrame(wxWindow* parent)
    :_banana{ false }, _obj{ BIRD }, _inputText{ "Monkey!" }, _hand_position{ 0.0 }, _pickedColor{255,255,255}, MyFrame(parent)
{
    SetTitle(_("Lab 03 - GFK"));
    SetIcon(wxNullIcon);
    SetSize(8, 8, 640, 420);
    Center();

    mid_x = _DrawArea->GetClientSize().x / 2;
    mid_y = _DrawArea->GetClientSize().y / 2;

    _Choice->Append("Słońce");
    _Choice->Append("Ptak");

    _TextInputDraw->SetLabel("Monkey!");
    _handPositionScrollBar->SetScrollbar(1, 15, 115, 15);
    _handPositionScrollBar->Disable();
    _MyImage.AddHandler(new wxPNGHandler);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    //UpdateWindowUI(1000);
}

void lab03MyFrame::_updateDrawArea( wxUpdateUIEvent& event )
{
// TODO: Implement _updateDrawArea
mid_x = _DrawArea->GetClientSize().x / 2;
mid_y = _DrawArea->GetClientSize().y / 2;
Repaint();
}

void lab03MyFrame::_saveOnButtonClick( wxCommandEvent& event )
{
// TODO: Implement _saveOnButtonClick
    wxClientDC MyDC(_DrawArea);

    
    int width = _DrawArea->GetClientSize().x;
    int height = _DrawArea->GetClientSize().y;
    
    // ustawienie bitmapy i memoryDC
    wxMemoryDC memDC;
    wxBitmap test_bitmap(width, height, 32); //ilość pixeli i ich głębokość 32-bity
    memDC.SelectObject(test_bitmap); // przypisanie memoryDC do stworzonej bitmapy
    
    // skopiowanie zawartości okna _DrawArea do memoryDC
    memDC.Blit(0, 0, width, height, &MyDC, 0, 0);
    memDC.SelectObject(wxNullBitmap);
    // przekonwertowanie bitmapy na obrazek
    wxBitmap img = test_bitmap.ConvertToImage();

    wxString filename;
    wxFileDialog WxOpenFileDialog1(this, _("Choose a path"), _(""), _(""), 
        _("*.*"), wxFD_SAVE);
    WxOpenFileDialog1.SetWildcard("PNG files (*.png)|*.png");
    
    if (WxOpenFileDialog1.ShowModal() == wxID_OK){
        filename = WxOpenFileDialog1.GetPath();
        img.SaveFile(filename, wxBITMAP_TYPE_PNG);
    }else {
        wxLogError(_("Nie można zapisać pliku."));
    }
    
}

void lab03MyFrame::_showBananaOnCheck( wxCommandEvent& event )
{
// TODO: Implement _showBananaOnCheck
if (_CheckBoxBanana->IsChecked()) {
_banana = true;
_handPositionScrollBar->Enable(true);
}
else {
_banana = false;
_handPositionScrollBar->Enable(false);
}
}

void lab03MyFrame::_changeHandPosition( wxScrollEvent& event )
{
// TODO: Implement _changeHandPosition
//SetTitle(wxString::Format("%d", _handPositionScrollBar->GetThumbPosition()));
    _hand_position = static_cast<float>(_handPositionScrollBar->GetThumbPosition()) / 100.0f;
    _GaugeMoveHand->SetValue(_handPositionScrollBar->GetThumbPosition());
    Repaint();
}

void lab03MyFrame::_changeStarColor( wxCommandEvent& event )
{
// TODO: Implement _changeStarColor
    wxColourData data;
    data.SetColour(wxColor(255,255,255));
    wxColourDialog dlg(this, &data);
    if (dlg.ShowModal() == wxID_OK) {
        // Colour did change.
        _pickedColor = dlg.GetColourData().GetColour();
    }
}

void lab03MyFrame::_updateText( wxCommandEvent& event )
{
// TODO: Implement _updateText
if (_TextInputDraw) _inputText = _TextInputDraw->GetValue();
}

void lab03MyFrame::_chooseObject( wxCommandEvent& event )
{
// TODO: Implement _chooseObject
    switch (_Choice->GetSelection()) {
    case object::SUN :
            _obj = SUN;
            break;
    case object::BIRD :
        _obj = BIRD;
        break;
    }
}


void lab03MyFrame::Repaint()
{
    wxClientDC windowDC(this);
    windowDC.Clear();
    //wxClientDC MyDC(_DrawArea);
    wxClientDC MyClientDC(_DrawArea);
    wxBufferedDC MyDC(&MyClientDC, _DrawArea->GetClientSize());
    MyDC.SetBackground(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_SOLID));
    MyDC.Clear();

    wxPoint mouth_points[3];
    wxPoint bird_points[5] = {
        wxPoint(mid_x - 100, mid_y - 150), wxPoint(mid_x - 80, mid_y - 130), wxPoint(mid_x - 60, mid_y - 140),
        wxPoint(mid_x - 40, mid_y - 130), wxPoint(mid_x - 20, mid_y - 150)
    };
    MyDC.DrawCircle(mid_x, mid_y - 35, 25);  //glowa
    MyDC.DrawCircle(mid_x - 10, mid_y - 40, 5);    // lewe oko
    MyDC.DrawCircle(mid_x + 10, mid_y - 40, 5);    // prawe oko
    if (_banana) {  //happy
        mouth_points[0] = wxPoint(mid_x - 10, mid_y - 25);
        mouth_points[1] = wxPoint(mid_x, mid_y - 20);
        mouth_points[2] = wxPoint(mid_x + 10, mid_y - 25);
        if (!_MyImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG))
            wxLogError(_("Brak obrazka: banan.png"));
        else
        {
            _MyBitmap = wxBitmap(_MyImage);
            if (_MyBitmap.Ok()) MyDC.DrawBitmap(_MyBitmap, mid_x - 90, mid_y - static_cast<int>(50.0f * _hand_position));
        }
    }
    else {  //sad
        mouth_points[0] = wxPoint(mid_x - 10, mid_y - 20);
        mouth_points[1] = wxPoint(mid_x, mid_y - 25);
        mouth_points[2] = wxPoint(mid_x + 10, mid_y - 20);
    }
    MyDC.DrawSpline(3, mouth_points);    // usta
    MyDC.DrawLine(mid_x, mid_y - 10, mid_x, mid_y + 75); //tulow
    MyDC.DrawLine(mid_x, mid_y + 75, mid_x - 25, mid_y + 100); //lewa noga
    MyDC.DrawLine(mid_x, mid_y + 75, mid_x + 25, mid_y + 100); // prawa nora
    MyDC.DrawLine(mid_x, mid_y, mid_x - 50, mid_y + 25 - static_cast<int>(50.0f * _hand_position)); // lewa reka
    MyDC.DrawLine(mid_x, mid_y, mid_x + 50, mid_y + 25); // prawa reka

    // rysowanie obiektu

    switch (_obj) {
    case object::SUN:
        MyDC.SetBrush(*wxYELLOW_BRUSH); // żółte wypełnienie
        MyDC.DrawCircle(mid_x-80, mid_y - 100, 25);
        break;
    case object::BIRD:
        MyDC.SetBrush(_pickedColor);
        MyDC.DrawPolygon(5, bird_points, -30, 50);
        break;
    }

    MyDC.DrawText(_inputText, mid_x - 50, mid_y + 100);
    MyDC.SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true));
    MyDC.DrawRotatedText(_inputText, mid_x + 50, mid_y + 100, 90);
}
