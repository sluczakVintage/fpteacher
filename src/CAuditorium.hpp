/*
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft
* 
* @brief klasa CAuditorium przedstawia sale
* 
* klasa CAuditorium przedstawia sale, sklada sie z z pol CField, odpowiedzialna jest za za ladowanie sali na poczatku
*	gry a takze, za dodawanie studentow na sale. Sale mozna serializowac i deserializowac wywolujac metody initFromXml()
*	saveToXml() lub przez archiwa z boost::serializable. Mozna zmienic plik xml opisujacy sale - .\res\XML\CAuditorium.xml
*	klasa jest singletonem 
*
* @todo przemyslec udostpnianie informacji o polach innym klasom
* @todo przemysle wspolprace z CInput
* @todo stworzyc flage bool initiated blokujaca initFromXml() oraz deserializacje gdy wywolany init(bool teacher) i na odwrot
* @todo dodac prawdzanie xml - pol CField powinno byc 40 (COLUMNS * ROWS)
* @todo sprawdzic wycieki (dotyczy tez innych klas ;)
* @todo zrobic rozna inicjalizacje grafik dla nauczycieli/studentow
*/

#ifndef CAUDITORIUM_H
#define CAUDITORIUM_H

#include <map>
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"
#include "CDynamicEntity.hpp"
#include "boost/multi_array.hpp"
#include "CField.hpp"
#include "CTimer.hpp"
#include <boost/serialization/split_member.hpp>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class CField;

class CAuditorium : public CSingleton<CAuditorium>
{
	friend CSingleton<CAuditorium>;
	friend class boost::serialization::access;

public:
	
	///Inicjalizacja, ktora nie odbywa sie z pliku xml
	///@param bool teacher - true gdy ma byc zaladowany widok dla nauczyciela, false, gdy widok dla studenta
	void init(bool teacher);
	
	///Inicjalizacja z pliku XML
	void initFromXml();
	
	///Zapis obecnego stanu sali do pliku XML
	void saveToXml();

	//bool seatNewStudent(std::pair<int, int> at);
	bool seatNewStudent(int row, int col);

	///ilosc rzedow na sali
	const static int ROWS=5;
	
	///ilosc miejsc w rzedzie
	const static int COLUMNS=8;
	
	///stosunek odleglosci pomiedzy krawedzia rzedu a pierwszym miejscem do szerokosci rzedu
	const static float MARGIN;
	
	///stosunek odleglosci miedzy rzedami do szerokosci rzedu
	const static float TAB;
	
	///stosunek obszaru zaslonietego przez rzad z przodu do calej wysokosci
	const static float CUT_OFF;

private:

	///szablon umo�liwiajacy serializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
	
		ar & BOOST_SERIALIZATION_NVP(teacher_);
	
		for(int j = 0; j<ROWS; j++)
		{
			for (int i = 0; i<COLUMNS;i++)
			{
				CField c_field = *(fields_[j][i]);
				ar & BOOST_SERIALIZATION_NVP(c_field);
			}
		}
	}
	
	///szablon umo�liwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		CAuditorium * t = CAuditorium::getInstance();
		ar & BOOST_SERIALIZATION_NVP(teacher_);
		t->teacher_ = this->teacher_; 
		for(int j = 0; j<ROWS; j++)
		{
			for (int i = 0; i<COLUMNS;i++)
			{
				CField * c_field = new CField();
				ar & BOOST_SERIALIZATION_NVP(c_field);
				boost::shared_ptr<CField> ptr(c_field);
				t->fields_[j][i] = ptr;
				if(!(t->fields_[j][i]->isFree_))
				{
					t->fields_[j][i]->isFree_=true;
					t->seatNewStudent(j,i);
				}
			}
		}
		t->loadStaticEntities();
		free(this);
	}
	
	///makro oznaczajace, ze zaimplementowano oddzielne funkcje do serializacji i deserializacji
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	
	///flaga true gdy ma byc zaladowany widok dla nauczyciela, false, gdy widok dla studenta
	bool teacher_;

	///kontener - dwuwymiarowa tablica przechowujaca pola CField (sprytne wska�niki na te pola)
	boost::multi_array<boost::shared_ptr<CField> , 2> fields_;
	
	///Konstruktor domyslny
	CAuditorium();
	
	///Destruktor
	~CAuditorium();

	///Metoda ladujaca encje CStaticEntity sali - wywolywana gdy uzywane jest initFromXml() a nie init(bool teacher);
	void loadStaticEntities();

};

///szalbon pozwalajacy samodzielne wywolac odpowiedni konstruktor. Nic sie nie dzieje poniewaz klasa jest singletonem
namespace boost { namespace serialization {

	template<class Archive>
	inline void load_construct_data(
			Archive & ar, CAuditorium * t, const unsigned int file_version
		){
		}

}}

#endif