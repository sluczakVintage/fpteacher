/**
* @author Sebastian Luczak
* @date 2009.12.30
* @version 0.1_draft
* @brief klasa CAnimation opakowuje animacjê, odwo³ania do niej zwi¹zane s¹ z odtwarzaniem animacji
*	
*		
*/
#ifndef CANIMATION_H
#define CANIMATION_H

#include "CSpriteMgr.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;


class CAnimation
{
public:
	/// Konstruktor domyslny
	CAnimation();
	/// Konstruktor z pliku
	/// @param nazwa pliku (string)
	CAnimation(const string filename );

	/// Destruktor
	~CAnimation() 
	{
		releaseAnimation();
		cout<<"CAnimation::~CAnimation: Destruktor CAnimation" <<endl;
	}

	/// Metoda otwierajaca dany plik
	/// @param nazwa pliku (string)
	/// @return wartosc logiczna, czy otwarcie pliku sie powiodlo
	bool openFile(const string filename );
	/// Metoda zwalniajaca zasoby animacji
	void releaseAnimation();
	/// Pobiera opoznienie danej klatki
	/// @ param numer ramki
	/// @ return opoznienie danej ramki (float)
	float getDelayOf(int frame) const;
	/// Zwraca nazwe animacji
	/// @ return nazwa animacji (string)
	const string& getAnimationName() const;
	/// Metoda zwraca liczbe ramek animacji
	/// @ return liczba klatek animacji
	int getNoOfAnimationFrames() const;
	/// Zwraca referencje do animSet_
	/// @return wektor par uchwyt do sprite i odstepu miedzy klatkami
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
