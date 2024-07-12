#include "GUIMyFrame1.h"
#include <stdlib.h>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 // TO DO: Konwersja do skali 
	Img_Cpy = Img_Org.ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
 // TO DO: Rozmywanie obrazu (blur)
	Img_Cpy = Img_Org.Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
 // TO DO: Odbicie lustrzane
	Img_Cpy = Img_Org.Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
 // TO DO: Zamiana kolorow 
	Img_Cpy = Img_Org;
	Img_Cpy.Replace(254,0,0,  0,0,255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
 // TO DO: Zmiana rozmiarow do 320x240
	wxClientDC dc(m_scrolledWindow);
	dc.Clear();

	Img_Cpy = Img_Org;
	Img_Cpy = Img_Cpy.Rescale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
 // TO DO: Obrot o 30 stopni
	wxClientDC dc(m_scrolledWindow);
	dc.Clear();

	Img_Cpy = Img_Org.Rotate(30, { Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2 });
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
 // TO DO: Przesuniecie Hue o 180 stopni
	Img_Cpy = Img_Org;
	Img_Cpy.RotateHue(0.5);	// 1.0 == 360
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
 // TO DO: Ustawienie maski obrazu
	wxClientDC dc(m_scrolledWindow);
	dc.Clear();

	Img_Cpy = Img_Org;
	if (!Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0)) {
		wxMessageBox(_("Blad ustawienia maski"));
	}
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}


static int prewittSum(const unsigned char* data, const int& row, int x, int y){
	return -data[row*(y - 1) + x - (3)] -
		data[row*y + x - (3)] -
		data[row*(y + 1) + x - (3)] +
		data[row*(y - 1) + x + (3)] +
		data[row*y + x + (3)] +
		data[row*(y + 1) + x + (3)];
}


static inline void checkColor(int& col) {
	if (col > 255) col = 255;
	else if (col < 0) col = 0;
}
void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
/*unsigned char* data = new unsigned char[(row+2)*(Img_Org.GetHeight()+2)];
for (int i = 0; i < row+6; ++i) { data[i] = 0; }
for (int i = row* (Img_Org.GetHeight()+1); i < row+6; ++i) { data[i] = 0; }
for (int i = 0; i < Img_Org.GetHeight() * row; i += row + 3) { data[i], data[i+1], data[i+2] = 0; }
for (int i = row+3; i < Img_Org.GetHeight() * row; i += row + 6) { data[i], data[i + 1], data[i + 2] = 0; }*/
 // TO DO: Pionowa maska Prewitta
	//Img_Cpy = Img_Org;
	////const unsigned char* data_src = Img_Org.GetData();
	//unsigned char* data_dst = Img_Cpy.GetData();
	//int row = Img_Org.GetWidth()*3;

	//unsigned char* data = new unsigned char[row * Img_Org.GetHeight()];
	//memcpy(data, data_dst, sizeof(unsigned char));

	//int r, g, b;
	//for (int y = 1; y < Img_Org.GetHeight()-1; ++y) {
	//	for (int x = 3; x < row-3; x+=3) {
	//		r = prewittSum(data, row, x, y);
	//		g = prewittSum(data, row, x + 1, y);
	//		b = prewittSum(data, row, x + 2, y);
	//		r = abs(r);
	//		g = abs(g);
	//		b = abs(b);
	//		checkColor(r);
	//		checkColor(g);
	//		checkColor(b);
	//		data_dst[y * row + x] = r;
	//		data_dst[y * row + x+1] = g;
	//		data_dst[y * row + x+2] = b;
	//	}
	//}
	//delete [] data;
	
	int r, g, b;
	//Img_Cpy = Img_Org;
	wxImage Img_temp = Img_Org;
	
	double val = 259.0 * (static_cast<double>(-50.0 * 2.5) + 255.0) / (255.0 * (259.0 - static_cast<double>(-50.0 * 2.5)));
	for (int y = 0; y < Img_Org.GetHeight(); ++y) {
		for (int x = 0; x < Img_Org.GetWidth(); ++x) {
			r = static_cast<double>(Img_temp.GetRed(x, y) - 128.0) * (val)+128.0;
			g = static_cast<double>(Img_temp.GetGreen(x, y) - 128.0) * (val)+128.0;
			b = static_cast<double>(Img_temp.GetBlue(x, y) - 128.0) * (val)+128.0;
			checkColor(r);
			checkColor(g);
			checkColor(b);

			Img_temp.SetRGB(x, y, r, g, b);
		}
	}



	// uciêcie na brzegach
	for (int y = 1; y < Img_Org.GetHeight()-1; ++y) {
		for (int x = 1; x < Img_Org.GetWidth()-1; ++x) {
			r = -Img_temp.GetRed(x - 1, y - 1) -
				Img_temp.GetRed(x - 1, y) -
				Img_temp.GetRed(x - 1, y + 1) +
				Img_temp.GetRed(x + 1, y - 1) +
				Img_temp.GetRed(x + 1, y) +
				Img_temp.GetRed(x + 1, y + 1);

			g = -Img_temp.GetGreen(x - 1, y - 1) -
				Img_temp.GetGreen(x - 1, y) -
				Img_temp.GetGreen(x - 1, y + 1) +
				Img_temp.GetGreen(x + 1, y - 1) +
				Img_temp.GetGreen(x + 1, y) +
				Img_temp.GetGreen(x + 1, y + 1);

			b = -Img_temp.GetBlue(x - 1, y - 1) -
				Img_temp.GetBlue(x - 1, y) -
				Img_temp.GetBlue(x - 1, y + 1) +
				Img_temp.GetBlue(x + 1, y - 1) +
				Img_temp.GetBlue(x + 1, y) +
				Img_temp.GetBlue(x + 1, y + 1);

			r = abs(r);
			g = abs(g);
			b = abs(b);
			checkColor(r);
			checkColor(g);
			checkColor(b);

			Img_Cpy.SetRGB(x, y, r, g, b);
		}
	}
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
	Img_Cpy = Img_Org;
	int r, g, b;
	for (int y = 0; y < Img_Org.GetHeight(); ++y) {
		for (int x = 0; x < Img_Org.GetWidth(); ++x) {
			r = Img_Cpy.GetRed(x, y) > 128 ? 255 : 0;
			g = Img_Cpy.GetGreen(x, y) > 128 ? 255 : 0;
			b = Img_Cpy.GetBlue(x, y) > 128 ? 255 : 0;

			Img_Cpy.SetRGB(x, y, r, g, b);
		}
	}
}

void GUIMyFrame1::Contrast(int value)
{
 // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od (-100 do 100) 0 do 200
	Img_Cpy = Img_Org;
	//unsigned char* data = Img_Cpy.GetData();
	int r, g, b;
	double val = 259.0 * (static_cast<double>(value*2.5) + 255.0) / (255.0 * (259.0 - static_cast<double>(value*2.5)));
	for (int y = 0; y < Img_Org.GetHeight(); ++y) {
		for (int x = 0; x < Img_Org.GetWidth(); ++x) {
			r = static_cast<double>(Img_Cpy.GetRed(x, y) - 128.0) * (val) + 128.0;
			g = static_cast<double>(Img_Cpy.GetGreen(x, y) - 128.0) * (val) + 128.0;
			b = static_cast<double>(Img_Cpy.GetBlue(x, y) - 128.0) * (val) + 128.0;
			checkColor(r);
			checkColor(g);
			checkColor(b);

			Img_Cpy.SetRGB(x, y, r, g, b);
		}
	}
}

void GUIMyFrame1::Brightness(int value)
{
 // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org;
	//unsigned char* data = Img_Cpy.GetData();
	//unsigned int pixelCount = Img_Cpy.GetHeight() * Img_Cpy.GetWidth();
	int r, g, b;
	/*for (int i = 0; i < pixelCount; ++i) {
		r = data[0] + value;
		g = data[1] + value;
		b = data[2] + value;
		checkColor(r);
		checkColor(g);
		checkColor(b);
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data += 3;
	}*/



	//// fade to white, can be changed to fade towards other colors
	//wxColor fadeto = wxColor(255, 255, 255);

	////change this factor to your needs, 0 will give the original image, 255 a complete white image
	//unsigned int fade_factor = value;

	//unsigned int fade_r = fadeto.Red() * fade_factor;
	//unsigned int fade_g = fadeto.Green() * fade_factor;
	//unsigned int fade_b = fadeto.Blue() * fade_factor;
	//unsigned int fade_complement = 255 - fade_factor;

	//unsigned int pixelcount = Img_Cpy.GetHeight() * Img_Cpy.GetWidth();
	//unsigned char* data = Img_Cpy.GetData();
	//for (unsigned int i = 0; i < pixelcount; i++) {
	//	// could be optimized by using three 256-byte lookup tables
	//	data[0] = (data[0] * fade_complement + fade_r) >> 8;
	//	data[1] = (data[1] * fade_complement + fade_g) >> 8;
	//	data[2] = (data[2] * fade_complement + fade_b) >> 8;
	//	data += 3;
	//}



	for (int y = 0; y < Img_Org.GetHeight(); ++y) {
		for (int x = 0; x < Img_Org.GetWidth(); ++x) {
			r = Img_Cpy.GetRed(x, y) + value;
			g = Img_Cpy.GetGreen(x, y) + value;
			b = Img_Cpy.GetBlue(x, y) + value;
			checkColor(r);
			checkColor(g);
			checkColor(b);

			Img_Cpy.SetRGB(x, y, r, g, b);
		}
	}
}




void GUIMyFrame1::Repaint()
{
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
	m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}
