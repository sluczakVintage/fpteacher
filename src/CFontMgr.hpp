/** @file CFontMgr.hpp
* @author Sebastian £uczak
* @date 2010.02.20
* @version 0.2
* @brief klasa CFontMgr
*	
*		
*/

#ifndef	CFONTMGR_H
#define CFONTMGR_H


#include <string>
#include <map>
#include <math.h>	

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>

//naglowki OpenGL
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	
//naglowki aplikacji
#include "CSingleton.hpp"
#include "CSpriteMgr.hpp"
#include "utils.hpp"

typedef map<string, std::pair<int, GLuint>, utils::string_less> FontsMap;

class CFontMgr : public CSingleton<CFontMgr>
{
	friend class CSingleton<CFontMgr>;

public:

	GLvoid buildFont(const string filename, int size = 16);

	GLvoid killFont(const string filename);

	GLvoid printText(const GLint x, const GLint y, const string text, const string set);

private:

	CFontMgr();

	~CFontMgr();

	GLuint CFontMgr::loadFont(const string filename);

	int callListOffset_;
	FontsMap fonts_;
	

};


#endif

//~~CFontMgr.hpp

