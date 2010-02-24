/** @file CAnimator.hpp
* @author Sebastian luczak
* @date 2010.01.08
* @version 0.6
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

#include <vector>
#include <list>
//naglowki boost
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
//naglowki klas aplikacji
#include "CVideoSystem.hpp"
#include "CAudioSystem.hpp"
#include "CAnimationMgr.hpp"
#include "utils.hpp"
#include "CLogic.hpp"



using namespace std;

class CAnimator
{
	/// pair_si konretyzacja pary string, int
	typedef boost::tuple<string, string, int> tuple_sai;
	/// pair_hi konretyzacja pary uchwyt do zestawu animacji, int
	typedef boost::tuple<HCAnimation, string, int> tuple_hai;

public:

	/// Konstruktor domyslny
	CAnimator();	
	
	/// Destruktor domyslny
	~CAnimator();

	/// Metoda otwiera plik o nazwie podanej jako parametr
	/// @param filename nazwa pliku (string)
	/// @return wartosc logiczna opisujaca powodzenie operacji
	bool openFile(string filename, bool object = false);

	/// Metoda wypelniajaca na nowo animator animacjami z listy
	/// @param anim_names lista par string, int (nazwa zestawu i priorytet)
	void refillCAnimator(const list< tuple_sai > anim_names);

	/// Metoda wypelniajaca na nowo animator animacjami z listy i ustawiajaca konkretny tryb animacji
	/// @param anim_names lista par string, int (nazwa zestawu i priorytet)
	/// @param mode enum AnimMode okreslajacy w jakim trybie maja sie zmieniac zestawy animacji w sekwencji
	void refillCAnimator(const list< tuple_sai > anim_names, const utils::AnimMode& mode );

	/// Metoda dodajaca do wektora nowa animacje
	/// @param filename nazwa zestawu
	/// @param priority priorytet zestawu w sekwencji
	void addAnimation(const string filename, const string audioname, const int priority);

	/// Metoda oprozniajaca wektor animacji
	void clearCAnimator();

	/// Metoda nadajaca nowy tryb odtwarzania animacji
	/// @param mode enum AnimMode okreslajacy w jakim trybie maja sie zmieniac zestawy animacji w sekwencji
	void setAnimMode(const utils::AnimMode& mode );

	/// Reset animacji
	void resetCAnimator();

	/// Start animacji
	void playAnimation();

	/// Pauza animacji
	void pauseAnimation();

	/// Ulatwia dostep do obiektu animsetu
	/// @param animation_handle uchwyt do zestawu animacji
	/// @return CAnimation wskaznik do zestawu animacji
	CAnimation* accessAnimation(const HCAnimation animation_handle) const;

	/// Metoda ustawia parametry dzwiekowe animatora
	/// @param position pozycja dzwieku
	/// @param distance odleglosc od sluchacza
	void setAudioParam(const int position, const int distance);	

	/// Podsystem animacyjny, podejmuje decyzje o animowaniu sekwencji i zmianie zestawow
	/// @param x wspolrzedna x animowanej sekwencji
	/// @param y wspolrzedna y animowanej sekwencji
	/// @return nazwa zestawu animacji
	void animate(const float x, const float y);

private:

	/// Metoda wypelniajaca na nowo animator pojedyncza animacja (uzywane przy default)
	/// @param anim_name nazwa zestawu
	/// @param priority priorytet zestawu w sekwencji
	void refillCAnimatorDefault();

	/// wektor uchwytow do animacji
	vector< tuple_hai  > animSetHandles_;
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
	/// numer kana³u
	int soundChannel_;
	
	int location_;
	int volume_;


};

#endif

//~~CAnimator.hpp
