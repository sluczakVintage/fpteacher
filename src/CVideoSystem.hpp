/**
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

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/tuple/tuple.hpp>

//naglowki OpenGL
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	

//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "CSprite.hpp"
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

	///FESTER
	void drawCSprite(const float x,const float y, const CSprite* sprite ) const;
	
	
private:
	///Konstruktor domyslny
	CVideoSystem();
	///Destruktor
	~CVideoSystem();
};

#endif

//~~CVideoSystem.hpp
