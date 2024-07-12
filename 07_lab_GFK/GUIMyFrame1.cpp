#include "GUIMyFrame1.h"

#include <stdlib.h>
float FunctionData[100][3];
int   NoPoints;

void PrepareData(int fun)
{
    int i;
    float x, y;
    srand(376257);

    switch (fun)
    {
    case 0: NoPoints = 5;
        FunctionData[0][0] = -1.0;	FunctionData[0][1] = 1.0;	FunctionData[0][2] = 0.0;
        FunctionData[1][0] = 1.0;	FunctionData[1][1] = 1.0;	FunctionData[1][2] = 25.0;
        FunctionData[2][0] = 1.0;	FunctionData[2][1] = -1.0;	FunctionData[2][2] = 5.0;
        FunctionData[3][0] = -1.0;	FunctionData[3][1] = -1.0;	FunctionData[3][2] = 25.0;
        FunctionData[4][0] = 0.0;	FunctionData[4][1] = 0.0;	FunctionData[4][2] = 15.0;
        break;
    case 1: NoPoints = 20;
        for (i = 0; i < NoPoints; i++)
        {
            x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            FunctionData[i][0] = x;
            FunctionData[i][1] = y;
            FunctionData[i][2] = 200 * (float(rand()) / RAND_MAX);
        }
        break;
    case 2: NoPoints = 100;
        for (i = 0; i < NoPoints; i++)
        {
            x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            FunctionData[i][0] = x;
            FunctionData[i][1] = y;
            FunctionData[i][2] = x * (2 * x - 7) * (2 * y + 1) + 2 * y;
        }
        break;
    case 3: NoPoints = 10;
        for (i = 0; i < NoPoints; i++)
        {
            x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
            FunctionData[i][0] = x;
            FunctionData[i][1] = y;
            FunctionData[i][2] = x * sin(2 * y);
        }
        break;
    case 4: NoPoints = 100;
        for (i = 0; i < NoPoints; i++)
        {
            x = 2 * (float(rand()) / RAND_MAX) - 1;
            y = 2 * (float(rand()) / RAND_MAX) - 1;
            FunctionData[i][0] = x;
            FunctionData[i][1] = y;
            FunctionData[i][2] = sin(8 * (x * x + y * y));
        }
        break;
    }
}


GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
: color_on{false},
MyFrame1( parent )
{
	SetMinSize({ 530,650 });
    tilt = m_s_tilt->GetValue();
    angle = m_s_rotation->GetValue();
    PrepareData(0);
    Repaint();
}

void GUIMyFrame1::m_button1_click( wxCommandEvent& event )
{
// TODO: Implement m_button1_click
    PrepareData(1);
    Repaint();
}

void GUIMyFrame1::m_button2_click( wxCommandEvent& event )
{
// TODO: Implement m_button2_click
    PrepareData(2);
    Repaint();
}

void GUIMyFrame1::m_button3_click( wxCommandEvent& event )
{
// TODO: Implement m_button3_click
    PrepareData(3);
    Repaint();
}

void GUIMyFrame1::m_button4_click( wxCommandEvent& event )
{
// TODO: Implement m_button4_click
    PrepareData(4);
    Repaint();
}

void GUIMyFrame1::m_cb_color_click( wxCommandEvent& event )
{
// TODO: Implement m_cb_color_click
    color_on = !color_on;
    Repaint();
}

#define PI 3.14159265
void GUIMyFrame1::m_s_rotation_onscroll( wxScrollEvent& event )
{
	m_st_rotation->SetLabel(wxString::Format("Obrot: %d stopni.",m_s_rotation->GetValue()));
    angle = m_s_rotation->GetValue();
    Repaint();
}

void GUIMyFrame1::m_s_tilt_onscroll( wxScrollEvent& event )
{
// TODO: Implement m_s_tilt_onscroll
    tilt = m_s_tilt->GetValue();
    Repaint();
}


double shepard(double x, double y, double functionData[][3]) {
    for (int i = 0; i < NoPoints; ++i) {
        if (x == functionData[i][0] && y == functionData[i][1]) return functionData[i][2];
    }

    double licznik = 0, mianownik = 0;
    double w = 0;
    for (int i = 0; i < NoPoints; ++i) {
        w = 1.0 / (pow(x - functionData[i][0], 2) + pow(y - functionData[i][1], 2));
        if (i != 0) licznik += w * functionData[i][2];
        mianownik += w;
    }
    return licznik / mianownik;
}

static void checkColor(int& color) {
    if (color > 255) color = 255;
    if (color < 0) color = 0;
}

#define PANEL_WIDTH 500
#define PANEL_HEIGHT 500
#define POINTS_X 80
#define POINTS_Y 80
void GUIMyFrame1::Repaint() {
    wxClientDC dc1(m_panel1);
    wxBufferedDC dc(&dc1);
    dc.SetBackground(wxBrush(RGB(255, 255, 255)));
    dc.Clear();

    double width, height;
    width = m_panel1->GetSize().x;
    height = m_panel1->GetSize().y;

#define START_X -2.5
#define START_Y -2.5
    // preparing points, using shepards method

    double cosinus = cos(angle*(2.0*PI)/360);
    double sinus = sin(angle*(2.0*PI)/360);
    auto FunctionData_temp = new double[NoPoints][3];
    for (int i = 0; i < NoPoints; ++i) {
        FunctionData_temp[i][0] = FunctionData[i][0] * cosinus - FunctionData[i][1] * sinus;
        FunctionData_temp[i][1] = FunctionData[i][1] * cosinus + FunctionData[i][0] * sinus;
        FunctionData_temp[i][2] = FunctionData[i][2];
    }

    constexpr double step_x = 5.0 / POINTS_X;
    constexpr double step_y = 5.0 / POINTS_Y;
    auto points = new double[POINTS_X * POINTS_Y][3];
    
    double max_z=-99999, min_z=99999;
    int idx;
    for (int i = 0; i < POINTS_Y; ++i) {
        for (int j = 0; j < POINTS_X; ++j) {
            idx = i * POINTS_X + j;
            points[idx][0] = START_X + step_x * j;
            points[idx][1] = START_Y + step_y * i;
            points[idx][2] = shepard(points[idx][0], points[idx][1], FunctionData_temp);
            if (points[idx][2] < min_z) min_z = points[idx][2];
            if (points[idx][2] > max_z) max_z = points[idx][2];
        }
    }
    

    // drawing voxels
#define TOP_PADDING 100
#define BOTTOM_PADDING 50
#define LEFT_PADDING 100
    constexpr int rectStepX = ((PANEL_WIDTH-LEFT_PADDING) / POINTS_X);
    constexpr int rectStepY = ((PANEL_HEIGHT-TOP_PADDING) / POINTS_Y);
    int color;
    double w_color;
    wxColor curColor;
    for (int i = 0; i < POINTS_Y; ++i) {
        for (int j = 0; j < POINTS_X; ++j) {
            idx = i * POINTS_X + j;
            if (color_on) {
                w_color = (points[idx][2] - min_z) / (max_z - min_z);
                if (w_color > 1) w_color = 1;
                if (w_color < 0) w_color = 0;
                curColor = RGB(255* w_color, 0, 255*(1.0 - w_color));
                dc.SetBrush(wxBrush(curColor)); // color to fill rectangle
                dc.SetPen(wxPen(curColor));
            }
            else {
                color = ((points[idx][2]) / (max_z - min_z)) * 255.0;
                checkColor(color);
                curColor = RGB(color, color, color);
                dc.SetBrush(wxBrush(curColor)); // color to fill rectangle
                dc.SetPen(wxPen(curColor));
            }
            
            
            dc.DrawRectangle((points[idx][0])*((PANEL_WIDTH - LEFT_PADDING) / 5.0) + (width-LEFT_PADDING)/2.0 + ((LEFT_PADDING / POINTS_Y) * (POINTS_Y - i)), 
                            points[idx][1]*((PANEL_HEIGHT - TOP_PADDING-BOTTOM_PADDING-(tilt*2))/5.0) + height/2.0 + TOP_PADDING-BOTTOM_PADDING,
                            rectStepX, -(points[idx][2] / max_z) * rectStepY*15 - 50);
        }
    }

    delete[] points;
}