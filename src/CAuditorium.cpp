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
* @todo rozna inicjalizacje grafik dla nauczycieli/studentow
* @todo serializacja/deserializacja parametrow(proporcji) pliku graficznego sali,
*	tak aby calkowita zmiana pliku nie powodowala potrzeby ponownej kompilacji
*/

#include "CAuditorium.hpp"

const float CAuditorium::MARGIN = 0.029897f;
const float CAuditorium::TAB =  0.02887f;
const float CAuditorium::CUT_OFF = 1.0f;

CAuditorium::CAuditorium() 
				: fields_(boost::extents[ROWS][COLUMNS]), teacher_(false)
{
	cout<<"CAuditorium::CAuditorium() tworzenie"<<endl;
}

CAuditorium::~CAuditorium() 
{
	for(int j = 0; j<ROWS; j++)
	{
		for (int i = 0; i<COLUMNS;i++)
		{
			delete(fields_[j][i]);
		}
	}
	cout<<"CAuditorium::~CAuditorium() nieszczenie"<<endl;
}
 
void CAuditorium::initFromXml()
{
	std::ifstream ifs("../res/XML/CAuditorium.xml");
    boost::archive::xml_iarchive ia(ifs);
	CAuditorium * ca = CAuditorium::getInstance();
	ia>>BOOST_SERIALIZATION_NVP(ca);
	ifs.close();	   
}

void CAuditorium::init(bool teacher)
{
/*		// TUTAJ JEST NOWA SALA
	new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/students/main.png");
	new CStaticEntity(30.0, 736.0, 60.0, "../res/graphics/sprites/auditorium/students/bottom.png");	
	CStaticEntity * rows[] = {new CStaticEntity(45.0, 696.0, 50.0, "../res/graphics/sprites/auditorium/students/row1.png"),
	new CStaticEntity(62.0, 661.0, 40.0, "../res/graphics/sprites/auditorium/students/row2.png"),
	new CStaticEntity(77.0, 626.0, 30.0, "../res/graphics/sprites/auditorium/students/row3.png"),
	new CStaticEntity(92.0, 595.0, 20.0, "../res/graphics/sprites/auditorium/students/row4.png")
	};
*/

	new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/teacher/main.png");
	new CStaticEntity(9.0, 585.0, 60.0, "../res/graphics/sprites/auditorium/teacher/bottom.png");	
	CStaticEntity * rows[] ={new CStaticEntity(28.0, 471.0, 50.0, "../res/graphics/sprites/auditorium/teacher/row1.png"),
							new CStaticEntity(46.0, 366.0, 40.0, "../res/graphics/sprites/auditorium/teacher/row2.png"),
							new CStaticEntity(63.0, 269.0, 30.0, "../res/graphics/sprites/auditorium/teacher/row3.png"),
							new CStaticEntity(79.0, 179.0, 20.0, "../res/graphics/sprites/auditorium/teacher/row4.png"),
							new CStaticEntity(95.0, 96.0, 10.0, "../res/graphics/sprites/auditorium/teacher/row5.png")
							};
	teacher_ = teacher;
	float currentX;  
	float currentY; 
	float currentZ;
	float h;
	float w; 
	for(int j = 0; j<ROWS; j++)
	{
		//h = rows[j]->getHeight() * CUT_OFF ;
		h = 90.0f;
		w = (rows[j]->getWidth() - ((COLUMNS - 1) * TAB + 2 * MARGIN) * rows[j]-> getWidth())/COLUMNS;
		
		currentX = rows[j]->getX() + TAB * rows[j]->getWidth();
		currentY = rows[j]->getY() + rows[j]->getHeight() - 90.0f;
		//currentY = rows[j]->getY();
		currentZ = rows[j]->getZ();

		for (int i = 0; i<COLUMNS;i++)
		{
			//boost::shared_ptr<CField> ptr(new CField(currentX, currentY, currentZ, w, h, j,	i));
			CField * ptr = (new CField(currentX, currentY, currentZ, w, h, j,	i));
			fields_[j][i] = ptr;
			
		//	new CStaticEntity(currentX, currentY, currentZ, "../res/graphics/sprites/auditorium/kwadrat.png");
		//	new CStaticEntity(currentX + w - 10.0f, currentY + h - 10.0f, 120.0f, "../res/graphics/sprites/auditorium/kwadrat1.png");
			currentX += w +  TAB * rows[j]->getWidth();
		}
	}
	
}
void CAuditorium::saveToXml()
{ 
	std::ofstream ofs("../res/XML/CAuditorium.xml");
	boost::archive::xml_oarchive oa(ofs);
	CAuditorium * ca = CAuditorium::getInstance();
	oa<<BOOST_SERIALIZATION_NVP(ca);
	ofs.close(); 
}

void CAuditorium::loadStaticEntities()
{
	// TUTAJ JEST NOWA SALA - widok studentow
	
	/*new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/students/main.png");
	new CStaticEntity(30.0, 736.0, 60.0, "../res/graphics/sprites/auditorium/students/bottom.png");	
	new CStaticEntity(45.0, 696.0, 50.0, "../res/graphics/sprites/auditorium/students/row1.png");
	new CStaticEntity(62.0, 661.0, 40.0, "../res/graphics/sprites/auditorium/students/row2.png");
	new CStaticEntity(77.0, 626.0, 30.0, "../res/graphics/sprites/auditorium/students/row3.png");
	new CStaticEntity(92.0, 595.0, 20.0, "../res/graphics/sprites/auditorium/students/row4.png");*/
	

	new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/teacher/main.png");

	new CStaticEntity(9.0, 585.0, 60.0, "../res/graphics/sprites/auditorium/teacher/bottom.png");	
	new CStaticEntity(28.0, 471.0, 50.0, "../res/graphics/sprites/auditorium/teacher/row1.png");
	new CStaticEntity(46.0, 366.0, 40.0, "../res/graphics/sprites/auditorium/teacher/row2.png");
	new CStaticEntity(63.0, 269.0, 30.0, "../res/graphics/sprites/auditorium/teacher/row3.png");
	new CStaticEntity(79.0, 179.0, 20.0, "../res/graphics/sprites/auditorium/teacher/row4.png");
	new CStaticEntity(95.0, 96.0, 10.0, "../res/graphics/sprites/auditorium/teacher/row5.png");
							
}
//
bool CAuditorium::seatNewStudent(int row, int col,string filename, string type)
{

//	boost::shared_ptr<CField> cf(fields_[at.first][at.second]);
//	boost::shared_ptr<CField> cf(fields_[row][col]);
	CField *  cf = (fields_[row][col]);
	if(cf->isFree_)
	{	
		if(type == "CDynamicEntity")	 
		{
			cf->entPtr_ = EntityPtr(		
				( new CDynamicEntity(cf->x_, cf->y_, cf->z_+0.1f, filename))->selfPtr_);
			cf->isFree_ = false;
			cf->isBusy_ = true;
			return true;
		}
		if(type == "CStaticEntity")	 
		{
			cf->entPtr_ = EntityPtr(		
							( new CStaticEntity(cf->x_, cf->y_, cf->z_+0.1f, filename))->selfPtr_); 
			cf->isFree_ = false;
			cf->isBusy_ = true;
			return true;
		}
	}
	return false;
}

//
bool CAuditorium::seatNewStudent(int row, int col, int type)
{
	switch(type)
	{
		case 0: 
		case 1:
		case 2:
			seatNewStudent(row,col,"../res/graphics/animsequences/idle_sequence.dat", "CDynamicEntity");
			return true;
		
		case 3:
		case 4:
		case 5:
			seatNewStudent(row,col,"../res/graphics/sprites/students/boy2.png","CStaticEntity");
			return true;
		case 6:
		case 7:
		case 8:
			seatNewStudent(row,col,"../res/graphics/sprites/students/boy3.png","CStaticEntity");
			return true;
		default:
			return false;
	
	}
}

