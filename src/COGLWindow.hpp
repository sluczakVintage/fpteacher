/**
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief 
*	
*	
*/

#ifndef	COGLWINDOW_H
#define COGLWINDOW_H

class COGLWindow : public CSingleton<COGLWindow>
{
	friend CSingleton<COGLWindow>;

public:
	/// Tworzy okno z podana etykieta
	bool createDisplay(int width = 640, int height = 480, int bpp =  -1, std::string label = "default", bool fullscreen = false);
	/// Niszczy okno (opuszcza SDL)
	void closeDisplay();
	/// Zmienia tryb okno/pelen ekran
	void toggleFullscreen();
	/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz
	void update();
	void clearDisplay(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0, Uint8 alpha = 255);
	void initOpenGL2D();

	/// Zwraca wskaznik na powierzchnie wyswietlana
	/// Zmienic na smartptr
	SDL_Surface* getDisplayPtr();
	/// Zwraca, czy okno zostalo stworzone
	bool isInitialized();
	/// Zwraca szerokosc
	int getDisplayWidth();
	/// Zwraca wysokosc
	int getDisplayHeight();
	/// Zwraca bpp
	int getDisplayDepth();
	/// Zwraca, czy tryb jest pelnoekranowy
	bool isFullscreen();

private:
	COGLWindow();
	~COGLWindow();


	bool sFullscreen_;
	bool sInitialized_;
	string sLabel_;
	SDL_Surface* sScreen_;
};
#endif