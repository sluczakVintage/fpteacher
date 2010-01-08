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

#include "CVideoSystem.hpp"
#include "CSpriteMgr.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

/// @TODO DODAC ANIMACJE DO TYLU

class CAnimation
{
	/// Zaprzyjazniona klasa Subsystemu graficznego
	friend class CVideoSystem;
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
	/// Metoda nadajaca nowy tryb odtwarzania animacji
	/// @param enum mode 
	void setAnimMode(const utils::AnimMode& mode );
	/// Metoda zwalniajaca zasoby animacji
	void releaseAnimation();
	/// Metoda nadajaca nowy czas do zmiany ramek
	/// @ param czas do nastepnej zmiany
	/// Resetowanie animacji
	void resetCAnimation();
	/// Start animacji
	void playCAnimation();
	/// Pauza animacji
	void pauseCAnimation();
	/// Pozwala pozyskac nazwe zestawu animacji
	/// @return nazwa zestawu animacji
	const string& getAnimationName() const;

private:
	/// wektor par Sprite'ow skladowych animacji i ich czasow trwania
	vector<  pair< HCSprite, float > > animSet_;
	/// enum opisujacy w jakim trybie ma sie odbywac animacja (statyczna, jednorazowa, ciagla)
	utils::AnimMode animMode_;
	/// nazwa zestawu animacyjnego
	string animSetName_;
	/// flaga mowiaca czy obecnie trwa dana animacja
	utils::AnimState animState_;
	/// obecna klatka animacji
	int currentFrame_;  
	/// czas ostatniej zmiany klatki animacji
	Uint32 lastFrameTime_;
	/// liczba klatek animacji
	int numberOfFrames_;

};

#endif

//~~CAnimation.hpp
