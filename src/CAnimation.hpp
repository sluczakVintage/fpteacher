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

// naglowki boost
#include <boost/smart_ptr.hpp>

#include "CSprite.hpp"
#include "CVideoSystem.hpp"
#include "utils.hpp"

#include <vector>

using namespace std;

/// @TODO DODAC ANIMACJE DO TYLU
class CSprite;
class CAnimation
{
	friend class CVideoSystem;
public:
	CAnimation(const string filename );
	~CAnimation();

	bool openFile(const string filename );
	void setAnimMode(const utils::AnimMode& mode );
	void setTimeToNextFrame(const int time);

	void resetCAnimation();
	void playCAnimation();
	void pauseCAnimation();

	

private:
	/// Prywatny konstruktor domyslny (nie ma takiej mozliwosci)
	CAnimation();
	/// wektor par Sprite'ow skladowych animacji i ich czasow trwania
	vector<  pair< boost::shared_ptr<CSprite> , int > > animSet_;
	/// enum opisujacy w jakim trybie ma sie odbywac animacja (statyczna, jednorazowa, ciagla)
	utils::AnimMode animMode_;
	/// nazwa zestawu animacyjnego, poki co nie obslugiwana --> manager animacji
	string animSetName_;
	/// flaga mowiaca czy obecnie trwa dana animacja
	utils::AnimState animState_;
	/// obecna klatka animacji
	int currentFrame_;  
	/// czas do nastepnej klatki animacji
	int timeToNextFrame_;
	/// liczba klatek animacji
	int numberOfFrames_;

};

#endif

//~~CAnimation.hpp
