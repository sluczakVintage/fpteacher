/**
* @author Sebastian Luczak
* @date 2009.12.30
* @version 0.4
* @class CAnimation CAnimation.hpp
* @brief klasa CAnimation opakowuje animacje, odwolania do niej zwiazane sa z odtwarzaniem animacji
*	
*		
*/
#ifndef CANIMATION_H
#define CANIMATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
//naglowki klas aplikacji
#include "CSpriteMgr.hpp"

using namespace std;


class CAnimation
{
public:
	/// Konstruktor domyslny
	CAnimation();

	/// Konstruktor z pliku
	/// @param filename nazwa pliku (string)
	CAnimation(const string filename );

	/// Destruktor
	~CAnimation() 
	{
		releaseAnimation();
		cout<<"CAnimation::~CAnimation: Destruktor CAnimation" <<endl;
	}

	/// Metoda otwierajaca dany plik
	/// @param filename nazwa pliku (string)
	/// @return wartosc logiczna, czy otwarcie pliku sie powiodlo
	bool openFile(const string filename );

	/// Metoda ladujaca domyslnego CSprite'a
	void loadDefault();

	/// Metoda zwalniajaca zasoby animacji
	void releaseAnimation();

	/// Pobiera opoznienie danej klatki
	/// @ param frame numer ramki
	/// @ return opoznienie danej ramki (float)
	float getDelayOf(int frame) const;

	/// Zwraca nazwe animacji
	/// @ return nazwa animacji (string)
	const string& getAnimationName() const;

	/// Metoda zwraca liczbe ramek animacji
	/// @ return liczba klatek animacji
	int getNoOfAnimationFrames() const;

	/// Zwraca referencje do animSet_
	/// @return wektor par uchwyt do sprite i odstep miedzy klatkami
	const vector< pair< HCSprite, float > >& getAnimSet() const;

private:
	/// wektor par Sprite'ow skladowych animacji i ich czasow trwania
	vector<  pair< HCSprite, float > > animSet_;
	/// nazwa zestawu animacyjnego
	string animSetName_;
	/// liczba klatek animacji
	int numberOfFrames_;

};

#endif

//~~CAnimation.hpp
