/**@file CAuditorium.cpp
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

#include "CAuditorium.hpp"

const float CAuditorium::MARGIN = 0.0146f;
const float CAuditorium::TAB =  0.0136f;
const float CAuditorium::CUT_OFF = 99.0f/109.0f;

CAuditorium::CAuditorium() 
				: fields_(boost::extents[ROWS][COLUMNS]), teacher_(false)
{
	cout<<"CAuditorium::CAuditorium() tworzenie"<<endl;
}

CAuditorium::~CAuditorium() 
{
	
	cout<<"CAuditorium::~CAuditorium() nieszczenie"<<endl;
}

void CAuditorium::initFromXml()
{
	std::ifstream ifs("..\\res\\XML\\CAuditorium.xml");
    boost::archive::xml_iarchive ia(ifs);
	CAuditorium * ca = CAuditorium::getInstance();
	ia>>BOOST_SERIALIZATION_NVP(ca);
	ifs.close();	
}

void CAuditorium::init(bool teacher)
{
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(55.0, 583.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");	
	CStaticEntity * rows[] ={new CStaticEntity(65.0, 486.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\row1.png"),
							new CStaticEntity(75.0, 390.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\row2.png"),
							new CStaticEntity(84.0, 296.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\row3.png"),
							new CStaticEntity(94.0, 203.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\row4.png"),
							new CStaticEntity(102.0, 108.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\row5.png")
							};
	teacher_ = teacher;
	float currentX;  
	float currentY;
	float currentZ;
	float h;
	float w;
	for(int j = 0; j<ROWS; j++)
	{
		h = rows[j]->getHeight() * CUT_OFF ;
		w = (rows[j]->getWidth() - ((COLUMNS - 1) * TAB + 2 * MARGIN) * rows[j]-> getWidth())/COLUMNS;
		currentX = rows[j]->getX() + MARGIN * rows[j]->getWidth();
		currentY = rows[j]->getY();
		currentZ = rows[j]->getZ();

		for (int i = 0; i<COLUMNS;i++)
		{
			boost::shared_ptr<CField> ptr(new CField(currentX, currentY, currentZ, w, h, j,	i));
			fields_[j][i] = ptr;
			currentX += w +  TAB * rows[j]->getWidth();
		}
	}
	
}
void CAuditorium::saveToXml()
{
	std::ofstream ofs("..\\res\\XML\\CAuditorium.xml");
	boost::archive::xml_oarchive oa(ofs);
	CAuditorium * ca = CAuditorium::getInstance();
	oa<<BOOST_SERIALIZATION_NVP(ca);
	ofs.close();
}

void CAuditorium::loadStaticEntities()
{
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(55.0, 583.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");	
	new CStaticEntity(65.0, 486.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\row1.png");
	new CStaticEntity(75.0, 390.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\row2.png");
	new CStaticEntity(84.0, 296.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\row3.png");
	new CStaticEntity(94.0, 203.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\row4.png");
	new CStaticEntity(102.0, 108.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\row5.png");
							
}

bool CAuditorium::seatNewStudent(int row, int col)
{

//	boost::shared_ptr<CField> cf(fields_[at.first][at.second]);
	boost::shared_ptr<CField> cf(fields_[row][col]);
	if(cf->isFree_)	 
	{
//		if(CTimer::getInstance()->getTime() % 5 < 3)
			new CDynamicEntity(cf->x_,
						cf->y_,
						cf->z_+0.1f,
						"..\\res\\graphics\\sprites\\students\\animset_sit.dat");
/*		else if(CTimer::getInstance()->getTime() % 5 <2)
			new CStaticEntity(cf->x_-10,
						cf->y_,
						cf->z_+0.1f, 
						"..\\res\\graphics\\sprites\\students\\boy2.png");
		else
			new CStaticEntity(cf->x_-5,
						cf->y_,
						cf->z_+0.1f, 
						"..\\res\\graphics\\sprites\\students\\boy3.png");
*/
		cf->isFree_ = false;
		cf->isBusy_ = true;
		return true;
	}

	return false;

}

