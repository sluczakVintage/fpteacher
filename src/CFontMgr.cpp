/** @file CFontMgr.cpp
* @author Sebastian £uczak
* @date 2010.02.20
* @version 0.2
* @brief klasa CFontMgr
*	
*		
*/

#include "CFontMgr.hpp"
using namespace logging;

CFontMgr::CFontMgr() : callListOffset_(0)
{

	CLog::getInstance()->sss << "CFontMgr::CFontMgr: konstruktor CFontMgr" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CFontMgr::~CFontMgr()
{
	FontsMap::iterator i, begin = fonts_.begin(), end = fonts_.end();
    for ( i = begin ; i != end ; ++i )
    {
		glDeleteLists(i->second.first,128);						
    }
	fonts_.clear();
	CLog::getInstance()->sss << "CFontMgr::CFontMgr: zniszczony" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

GLuint CFontMgr::loadFont(const string filename)
{
	HCSprite temp_sprite_handle;

	temp_sprite_handle = CSpriteMgr::getInstance()->getCSprite(utils::PATH_FONTS+filename);

	CLog::getInstance()->sss << "CFontMgr::loadFont: zaladowano czcionke z pliku " << filename << endl;
	logs(CLog::getInstance()->sss.str(), INFO);

	return CSpriteMgr::getInstance()->getCSpritePtr(temp_sprite_handle)->getTexID();

}

GLvoid CFontMgr::buildFont(const string filename, int size)								// Build Our Font Display List
{
	GLfloat	cx;											// Holds Our X Character Coord
	GLfloat	cy;											// Holds Our Y Character Coord
	GLuint texID;
	GLuint loop;
	float interval = 1/static_cast<float>(size);

	texID = loadFont(filename);

	callListOffset_ = glGenLists(128);								// Creating 128 Display Lists	
	
	glBindTexture(GL_TEXTURE_2D, texID);			// Select Our Font Texture
	for (loop=0; loop<128; loop++)						// Loop Through All 128 Lists
	{
		cx=static_cast<GLfloat>(loop%size)/static_cast<float>(size);						// X Position Of Current Character
		cy=static_cast<GLfloat>(loop/size)/static_cast<float>(size);						// Y Position Of Current Character

		glNewList(callListOffset_+loop,GL_COMPILE);				// Start Building A List
			glBegin(GL_TRIANGLE_STRIP);							// Use A Quad For Each Character
				glTexCoord2f(cx,cy);			// Texture Coord (Bottom Left)  /// ROZKMNINIC
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+interval,cy);	// Texture Coord (Bottom Right)
				glVertex2i(size,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx,cy+(interval));			// Texture Coord (Top Right)
				glVertex2i(0,size);						// Vertex Coord (Top Right)
				glTexCoord2f(cx+interval,cy+(interval));					// Texture Coord (Top Left)
				glVertex2i(size,size);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(16,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}	
	fonts_.insert( std::make_pair(filename, std::make_pair(callListOffset_, texID)));

	CLog::getInstance()->sss << "CFontMgr::buildFont: zbudowano czcionke z pliku " << filename << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

GLvoid CFontMgr::killFont(const string fontname)									// Delete The Font From Memory
{
	string name = fontname;
	if(name.find(".png") == -1)
		name = name+ ".png";
	FontsMap::iterator font = fonts_.find(name);
	if(font != fonts_.end() )
	{
		glDeleteLists(fonts_.find(name)->second.first,128);						
		fonts_.erase(name);
	}
	CLog::getInstance()->sss << "CFontMgr::killFont: usunieto font z managera " << fontname << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

GLvoid CFontMgr::printText(const GLint x,const GLint y, const string text, const string fontname)	// Where The Printing Happens
{
	string name = fontname;
	if(name.find(".png") == -1)
		name = name+ ".png";
	FontsMap::iterator font = fonts_.find(name);
	if(font != fonts_.end() )
	{
		//Dobierz barwe wyswietlania
		glColor4ub(255,255,255,255); 
		//Wlacz mieszanie barw
		glEnable(GL_BLEND);
		//Wylacz test ZBufora
		glDisable(GL_DEPTH_TEST);
		//Ustaw funkcje mieszania barw z kanalem alpha (przezroczystosc)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//doczep teksture
		glBindTexture(GL_TEXTURE_2D, font->second.second );			// Select Our Font Texture
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();										// Store The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
		glTranslatef(static_cast<float>(x),static_cast<float>(y),0);								// Position The Text (0,0 - Bottom Left)
		glListBase(font->second.first-32);	
		glCallLists(text.length(),GL_BYTE, text.c_str());			// Write The Text To The Screen
		glPopMatrix();										// Restore The Old Projection Matrix
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glColor4ub(255,255,255,255);
	}
}

//~~CFontMgr.hpp
