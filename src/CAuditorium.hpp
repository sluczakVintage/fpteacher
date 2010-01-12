/**
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft

* @class CAuditorium CAuditorium.hpp
* @brief klasa CAuditorium przedstawia sale
* 
* klasa CAuditorium przedstawia sale, sklada sie z z pol CField, odpowiedzialna jest za za ladowanie sali na poczatku
*	gry a takze, za dodawanie studentow na sale. Sale mozna serializowac i deserializowac wywolujac metody initFromXml()
*	saveToXml() lub przez archiwa z boost::serializable. Mozna zmienic plik xml opisujacy sale - .\\res\\XML\\CAuditorium.xml
*	klasa jest singletonem 
*
* @todo przemyslec udostpnianie informacji o polach innym klasom
* @todo przemyslec wspolprace z CInput
* @todo stworzyc flage bool initiated blokujaca initFromXml() oraz deserializacje gdy wywolany init(bool teacher) i na odwrot
* @todo dodac sprawdzanie xml - pol CField powinno byc 40 (COLUMNS * ROWS)
* @todo zrobic rozna inicjalizacje grafik dla nauczycieli/studentow
* @todo zrobic jasny  enum do typow studentow dla metody seatNewStudent(int row, int col, int type);
* @todo serializacja/deserializacja parametrow(proporcji) pliku graficznego sali,
*	tak aby calkowita zmiana pliku nie powodowala potrzeby ponownej kompilacji
* @todo dodac wybor bycia studentami/wykladowca
* @todo pozmieniac numery rzedow na uint
*/

#ifndef CAUDITORIUM_H
#define CAUDITORIUM_H

#include <map>
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"
#include "CDynamicEntity.hpp"
#include "boost/multi_array.hpp"
//#include "CField.hpp"
//#include "CTimer.hpp"
#include <boost/serialization/split_member.hpp>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
//#include "CInput.hpp"
#include "CMouseObserver.hpp"
#include "CNetwork.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**
* @author Czarek Zawadka
* @date 2009.12.30
* @version 0.1_draft
* @class CField CAuditorium.hpp
* @brief klasa CField przedstawiajaca miejsce na sali
*
*
* Klasa opisuje jedno miejsce na sali, ktore moze byc zajete przez studenta. Zawiera podstawowe informacje o miejscu - 
* wspolrzedne, oraz to, czy miejsce jest zajete. Klasa moze zostac zserializowana przez archiwa z boost::serializable.
*
*@todo zastanowic sie kto powienien wiedziec ze encja na danym miejscu jest czyms zajeta
*@todo zastanowic sie czy szablon do serializacji nie powinien byc prywarny a klasa boost::serialization::access zaprzyjazniona
*@todo interfejs dla obseratora CField
*@todo przeniesienie logiki w zupelnie inne miejsce
*@todo pozmieniac numery rzedow na uint
*@todo poprawic deserializacje, tak aby dzialala zgodnie z intencjami boost::serialization - uniknac usuwania nowozaalokowanego CAuditorium 
*/

//class CField;
#include "CMouseObserver.hpp"
#include <string>
#include <iostream>
#include "utils.hpp"
#include "CAuditorium.hpp"
#include "CEntity.hpp"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "CMouseEvent.hpp"
#include "CAudioSystem.hpp"
#include "CSoundNetworkEvent.hpp"
#include "CStudentNetworkEvent.hpp"
#include "CTimer.hpp"

class CAuditorium;
class CMouseObserver;
//class CInput;
//class CNetworkEvent;

typedef boost::shared_ptr<CEntity> EntityPtr;

class CField: public CMouseObserver
{
	friend class CAuditorium;
	friend class CInput;
	friend class boost::serialization::access;

public:
	
	///Konstruktor inicjalizujacy wszystkie parametry
	CField(float x,float y,float z, float width, float height,int row, int column);
	
	///Konstruktor domyslny
	CField();

	///Destruktor
	virtual ~CField();

	///metoda zwraca true gdy argumenty sa wewnatrz prostokata pola
	bool isMouseOver(int mouseX, int mouseY);
	
	///@return czy pole jest zajete przez studenta
	bool getIsFree();

	///@return czy student jest zajety przez jakas akcje i nie moze byc aktywowana
	bool getIsBusy();

	///@return wspolrzedna X pola - liczone od lewej
	float getX();

	///@return wspolrzedna Y pola - liczone od gory
	float getY();

	///@return wartosc bufora glebokosci
	float getZ();

	///@return szerokosc pola
	float getWidth();

	///@return pozycja czlowieka, potrzeba do odtwarzania dzwieku 3d
	int getPosition();

	///@return odleglosc czlowieka, potrzebna do odtwarzania dzwieku 3d
	int getDistance();

	///@return wysokosc pola
	float getHeight();

	///@return kopie id_ pola
	std::pair<int, int>& getId(){return id_;};


private:

	///szablon umozliwiajacy serializacje i deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{
	
		ar & BOOST_SERIALIZATION_NVP(id_.first);
		ar & BOOST_SERIALIZATION_NVP(id_.second);
		ar & BOOST_SERIALIZATION_NVP(x_);
		ar & BOOST_SERIALIZATION_NVP(y_);
		ar & BOOST_SERIALIZATION_NVP(z_);
		ar & BOOST_SERIALIZATION_NVP( width_);
		ar & BOOST_SERIALIZATION_NVP(height_);
		ar & BOOST_SERIALIZATION_NVP(isFree_);
		ar & BOOST_SERIALIZATION_NVP(isBusy_);
	}


	///id miejsca jest para int'ow oznaczajaca rzad i miejsce na sali liczone od (0,0) 
	///czyli miejsca po lewej stronie w najnizszym rzedzie patrzac od strony wykladowcy
	std::pair<int, int> id_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

	///szerokosc pola
	float width_;

	///wysokosc pola
	float height_;

	///flaga pokazujaca czy pole jest wolne
	bool isFree_;

	///flaga pokazujaca czys tudent jest zajety,  @ref todo
	bool isBusy_;
	
	///sprytny wskaznik boost::shared_ptr na CEntity ktora jest zwiazana z danym polem
	EntityPtr entPtr_ ; 
	
	///prosty licznik sluzacy do zmiany kwestii wypowiadanej przez studenta
	static int counter_;

	/// metoda wywolywana przez klase CInput gdy zajdzie jakies zdarzenie od myszki
	///odziedziczone po CMouseObserver
	virtual void refresh(CMouseEvent * CMO);
};

//#endif



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//class CAuditorium

class CAuditorium : public CSingleton<CAuditorium>
{
	friend class CSingleton<CAuditorium>;
	friend class boost::serialization::access;

public:
	
	///Inicjalizacja, ktora nie odbywa sie z pliku xml, inicjalizuje pusta sale
	///@param teacher - true gdy ma byc zaladowany widok dla nauczyciela, false, gdy widok dla studenta
	void init(bool teacher = false);
	
	///Inicjalizacja z pliku XML
	void initFromXml();
	
	///Zapis obecnego stanu sali do pliku XML
	void saveToXml();

	///sadza nowego studenta, metoda uzywana przy deserializacji
	///@param row - numer rzedu
	///@param col - numer kolumny
	///@param filename - nazwa pliku do zaczytana
	///@param type - typ studenta - nazwa klasy
	///@return true, jezeli udalo sie posadzic nowego studenta - miejsce bylo wolne
	bool seatNewStudent(int row, int col,string filename, string type);
	
	///sadza nowego studenta
	///@param row - numer rzedu
	///@param col - numer kolumny
	///@param type - typ studenta
	///@return true, jezeli udalo sie posadzic nowego studenta - miejsce bylo wolne
	bool seatNewStudent(int row, int col, int type);
	
	///ilosc rzedow na sali
	const static int ROWS=5;
	
	///ilosc miejsc w rzedzie
	const static int COLUMNS=8;
	
	///stosunek odleglosci pomiedzy krawedzia rzedu a pierwszym miejscem do szerokosci rzedu
	const static float MARGIN;
	
	///stosunek odleglosci miedzy columnami do szerokosci rzedu
	const static float TAB;
	
	///stosunek obszaru zaslonietego przez rzad z przodu do calej wysokosci
	const static float CUT_OFF;

private:

	///szablon umozliwiajacy serializacje klasy
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
				CField  c_field = *(fields_[j][i]);
				ar & BOOST_SERIALIZATION_NVP(c_field); 
				string filename("unknown");
				string type ("unknown");
				
				if(c_field.entPtr_)			
				{
					if (c_field.entPtr_->getFilename().length()>0)
					{
						filename = c_field.entPtr_->getFilename();
					}
					if(c_field.entPtr_->getType().length()>0)
					{
						type = c_field.entPtr_->getType();
					}
				}
				cout<<filename<<type<<endl;
				ar & BOOST_SERIALIZATION_NVP(filename); 
				ar & BOOST_SERIALIZATION_NVP(type); 
				
			}	
		}
	}
	
	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		int k = 0;
		CAuditorium * t = CAuditorium::getInstance();
		ar & BOOST_SERIALIZATION_NVP(teacher_);
		t->teacher_ = this->teacher_; 
		for(int j = 0; j<ROWS; j++)
		{
			for (int i = 0; i<COLUMNS;i++)
			{
				CField * c_field;// = t->fields_[j][i];// = new CField();
				ar & BOOST_SERIALIZATION_NVP(c_field);
				//boost::shared_ptr<CField> ptr(c_field);
				string filename;
				string type ;
				ar & BOOST_SERIALIZATION_NVP(filename); 
				ar & BOOST_SERIALIZATION_NVP(type);
				//t->fields_[j][i] = c_field;
//				cout << "elo elo          " << endl;
				cout<<++k<<endl;
				CInput::getInstance()->addMouseObserver(*c_field);
				t->fields_[j][i] = c_field;
				if(!(c_field->isFree_))
				{
					c_field->isFree_=true;
					t->seatNewStudent(j,i,filename,type);
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

	///kontener - dwuwymiarowa tablica przechowujaca pola CField (sprytne wskazniki na te pola)
	//boost::multi_array<boost::shared_ptr<CField> , 2> fields_;
	boost::multi_array<CField *, 2> fields_;
	
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