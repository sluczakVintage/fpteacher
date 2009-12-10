/**
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa ENgine odpowiada za poprawne dzia�anie silnika gry
*	
*		
*/
#ifndef CENGINE
#define CENGINE

#include "globals.hpp"

using namespace std;
 

class CEngine : public CSingleton<CEngine>
{
	friend CSingleton<CEngine>;
public:
	CEngine();

	~CEngine();

	void init();

	void start();

	void end();

private:

	
	
};

#endif