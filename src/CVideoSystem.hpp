/**\file
* @author Sebastian luczak
* @date 2009.12.08
* @version 0.2_draft
* @class CVideoSystem CVideoSystem.hpp
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ow
*	
*/

#ifndef	CVIDEOSYSTEM_H
#define CVIDEOSYSTEM_H

#include <iostream>
#include <string>
#include <cassert>

//naglowki OpenGL
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	

//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CSpriteMgr.hpp"
#include "CSprite.hpp"
#include "CInput.hpp"
#include "utils.hpp"

using namespace std;

class CSprite;

class CVideoSystem : public CSingleton<CVideoSystem>
{
	friend class CSingleton<CVideoSystem>;
	
public:
	///Metoda wiazaca teksture sprite'a z OGL
	/// @param sprite sprite do doczepienia
	void bindTexture(const CSprite& sprite) const;

	///Metoda odrysowuje sprite'a na ekranie
	/// @param x pozycja (wspolrzedna x)
	/// @param y pozycja (wspolrzedna y)
	/// @param sprite wskaznik do sprite'a do odrysowania
	void drawCSprite(const float x, const float y, const CSprite* sprite );
	
	/// Laduje dany kursor jako obecnie wyswietlany
	/// @param filename nazwa pliku z kursorem
	/// @param offset_x przesuniecie w osi x od lewej granicy pliku z kursorem
	/// @param offset_y przesuniecie w osi y od gornej granicy pliku z kursorem
	void loadCursor(const string& filename, float offset_x = 0.f, float offset_y = 0.f);

	/// Odrysowuje zaladowany kursor
	void drawMouseCursor() const;

	/// Ustawia skalowanie na najblizsze odrysowanie
	void setScale(const float scale_ratio); 

	/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
	void update();

private:
	///Konstruktor domyslny
	CVideoSystem();
	///Destruktor
	~CVideoSystem();

	float cursorOffsetX_;
	float cursorOffsetY_;

	float scaleRatio_;

	HCSprite cursor_;
};

#endif

//~~CVideoSystem.hpp
