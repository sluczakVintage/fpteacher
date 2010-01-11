/** @file CAnimator.hpp
* @author Sebastian luczak
* @date 2010.01.08
* @version 0.2_draft
* @class CAnimator CAnimator.hpp
* @brief Klasa animatora, czyli minisystemu zarzadzajacego sekwencja animacji
*  
*		Dzialanie animatora:\n w trybie ONCE - wyswietlany jest jednorazowo caly wektor animset'ow \n
							w trybie LOOP - sekwencja animset'ow jest powtarzana \n
							w trybie RANDOM - sekwencja animset'ow jest odtwarzana losowo, w trybie ciaglym \n
							w trybie NONE - animacja nie jest wykonywana \n
*/

#ifndef CANIMATOR_H
#define CANIMATOR_H

//naglowki boost
#include <boost/foreach.hpp>

#include "CVideoSystem.hpp"
#include "CAnimationMgr.hpp"
#include "utils.hpp"

#include <vector>
#include <list>

using namespace std;

class CAnimator
{
	/// Deklaracje typow par
	typedef pair<string, int> pair_si;
	typedef pair<HCAnimation, int> pair_hi;

public:
	/// Konstruktor domyslny
	CAnimator();	
	/// Metoda otwiera plik o nazwie podanej jako parametr
	/// @param filename nazwa pliku (string)
	/// @return wartosc logiczna opisujaca powodzenie operacji
	bool openFile(string filename);
	/// Destruktor domyslny
	~CAnimator();
	/// @todo Loader z pliku!!
	/// Metoda wypelniajaca na nowo animator animacjami z listy
	void refillCAnimator(const list< pair_si > anim_names);
	/// Metoda wypelniajaca na nowo animator animacjami z listy i ustawiajaca konkretny tryb animacji
	void refillCAnimator(const list< pair_si > anim_names, const utils::AnimMode& mode );
	/// Metoda wypelniajaca na nowo animator pojedyncza animacja
	void refillCAnimator(const string anim_name, const int priority);
	/// Metoda dodajaca do wektora nowa animacje
	void addAnimation(const string filename, const int priority);
	/// Metoda oprozniajaca wektor animacji
	void clearCAnimator();
	/// Metoda nadajaca nowy tryb odtwarzania animacji
	/// @param mode 
	void setAnimMode(const utils::AnimMode& mode );
	/// Reset animacji
	void resetCAnimator();
	/// Start animacji
	void playAnimation();
	/// Pauza animacji
	void pauseAnimation();
	/// Ulatwia dostep do obiektu animsetu
	CAnimation* accessAnimation(const HCAnimation animation_handle) const;
	/// Pozwala pozyskac nazwe zestawu animacji
	/// @return nazwa zestawu animacji
	void animate(const float x, const float y);

private:
	/// wektor uchwytow do animacji
	vector< pair_hi > animSetHandles_;
	/// enum opisujacy w jakim trybie ma sie odbywac animacja (statyczna, jednorazowa, ciagla, losowa)
	utils::AnimMode animMode_;
	/// flaga mowiaca czy obecnie trwa dana animacja
	utils::AnimState animState_;
	/// aktualny animset
	int currentAnimSet_;
	/// obecna klatka animacji
	int currentFrame_;  
	/// czas ostatniej zmiany klatki animacji
	Uint32 lastFrameTime_;
	/// suma priorytetow
	int prioritySum_;


};

#endif

//~~CAnimator.hpp
