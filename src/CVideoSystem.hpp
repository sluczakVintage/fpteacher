/**
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ów
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

//naglowki OpenGL
#include <windows.h>
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
	friend CSingleton<CVideoSystem>;

public:
	void bindTexture(const CSprite& sprite) const;
	void drawCSprite(float x, float y, const CSprite& sprite ) const;
	
private:
	CVideoSystem();
	~CVideoSystem();
};

#endif