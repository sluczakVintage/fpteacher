/**@file CAuditorium.cpp
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft
* 
* @brief klasa CAuditorium przedstawia sale
* 
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
	if(!(CNetwork::getInstance()->getIsClient()))
	{
		std::ifstream ifs("../res/XML/teacher/CAuditorium.xml");
		boost::archive::xml_iarchive ia(ifs);
		CAuditorium * ca = CAuditorium::getInstance();
		ia>>BOOST_SERIALIZATION_NVP(ca);
		ifs.close();	 
	}
	else
	{
		std::ifstream ifs("../res/XML/student/CAuditorium.xml");
		boost::archive::xml_iarchive ia(ifs);
		CAuditorium * ca = CAuditorium::getInstance();
		ia>>BOOST_SERIALIZATION_NVP(ca);
		ifs.close();	
	}

}

void CAuditorium::init(bool teacher)
{
		// TUTAJ JEST NOWA SALA
	if((CNetwork::getInstance()->getIsClient()))
	{
		new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/students/main.png");
		new CStaticEntity(30.0, 736.0, 60.0, "../res/graphics/sprites/auditorium/students/bottom.png");	
		new CStaticEntity(150.0, 220.0, 5.0, "../res/graphics/sprites/teacher/teacher.png");
		CStaticEntity * rows[] = {new CStaticEntity(45.0, 696.0, 50.0, "../res/graphics/sprites/auditorium/students/row1.png"),
									new CStaticEntity(62.0, 661.0, 40.0, "../res/graphics/sprites/auditorium/students/row2.png"),
									new CStaticEntity(77.0, 626.0, 30.0, "../res/graphics/sprites/auditorium/students/row3.png"),
									new CStaticEntity(92.0, 595.0, 20.0, "../res/graphics/sprites/auditorium/students/row4.png"),
									new CStaticEntity(107.0, 565.0, 10.0, "../res/graphics/sprites/auditorium/students/row5.png"),

						};
		teacher_ = false;

		float currentX;  
		float currentY; 
		float currentZ;
		float h;
		float w; 
		int j,k;
		for(j = ROWS - 1 ,k = 0; j>=0; j--, k++)
		{
			//h = rows[k]->getHeight() * CUT_OFF ;
			h = 35.0f;
			w = (rows[k]->getWidth() - ((COLUMNS - 1) * TAB + 2 * MARGIN) * rows[k]-> getWidth())/COLUMNS;
			
			currentX = rows[k]->getX() + rows[k]->getWidth()  -  TAB * rows[k]->getWidth() - w;
				//rows[k]->getX() + TAB * rows[k]->getWidth();
			currentY = rows[k]->getY() -3;// + rows[k]->getHeight() - 90.0f;
			//currentY = rows[j]->getY();
			currentZ = rows[k]->getZ();

			int i,l;
			for (i = COLUMNS -1, l = 0; i>=0;i--, l++)
			{
				//boost::shared_ptr<CField> ptr(new CField(currentX, currentY, currentZ, w, h, j,	i));
				CField * ptr = (new CField(currentX, currentY, currentZ, w, h, j,	l));
				fields_[j][l] = ptr;
				
				//new CStaticEntity(currentX, currentY, currentZ, "../res/graphics/sprites/auditorium/kwadrat.png");
				//new CStaticEntity(currentX + w - 10.0f, currentY + h - 10.0f, 120.0f, "../res/graphics/sprites/auditorium/kwadrat1.png");
				currentX -= w +  TAB * rows[k]->getWidth();
			}

		}
	}
	else
	{
		new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/teacher/main.png");
		new CStaticEntity(9.0, 585.0, 60.0, "../res/graphics/sprites/auditorium/teacher/bottom.png");	

		CStaticEntity * rows[] ={new CStaticEntity(28.0, 471.0, 50.0, "../res/graphics/sprites/auditorium/teacher/row1.png"),
								new CStaticEntity(46.0, 366.0, 40.0, "../res/graphics/sprites/auditorium/teacher/row2.png"),
								new CStaticEntity(63.0, 269.0, 30.0, "../res/graphics/sprites/auditorium/teacher/row3.png"),
								new CStaticEntity(79.0, 179.0, 20.0, "../res/graphics/sprites/auditorium/teacher/row4.png"),
								new CStaticEntity(95.0, 96.0, 10.0, "../res/graphics/sprites/auditorium/teacher/row5.png")
								};
		
		teacher_ = true;
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
				
				//new CStaticEntity(currentX, currentY, currentZ, "../res/graphics/sprites/auditorium/kwadrat.png");
				//new CStaticEntity(currentX + w - 10.0f, currentY + h - 10.0f, 120.0f, "../res/graphics/sprites/auditorium/kwadrat1.png");
				currentX += w +  TAB * rows[j]->getWidth();
			}
		}
	}
}
void CAuditorium::saveToXml()
{ 
	if(!(CNetwork::getInstance()->getIsClient()))
	{
		std::ofstream ofs("../res/XML/teacher/CAuditorium.xml");
		boost::archive::xml_oarchive oa(ofs);
		CAuditorium * ca = CAuditorium::getInstance();
		oa<<BOOST_SERIALIZATION_NVP(ca);
		ofs.close(); 
	}else
	{
		std::ofstream ofs("../res/XML/student/CAuditorium.xml");
		boost::archive::xml_oarchive oa(ofs);
		CAuditorium * ca = CAuditorium::getInstance();
		oa<<BOOST_SERIALIZATION_NVP(ca);
		ofs.close(); 
	}
}

void CAuditorium::loadStaticEntities()
{
	
	
	if(!(CNetwork::getInstance()->getIsClient()))
	{
		new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/teacher/main.png");
		new CStaticEntity(9.0, 585.0, 60.0, "../res/graphics/sprites/auditorium/teacher/bottom.png");	
		new CStaticEntity(28.0, 471.0, 50.0, "../res/graphics/sprites/auditorium/teacher/row1.png");
		new CStaticEntity(46.0, 366.0, 40.0, "../res/graphics/sprites/auditorium/teacher/row2.png");
		new CStaticEntity(63.0, 269.0, 30.0, "../res/graphics/sprites/auditorium/teacher/row3.png");
		new CStaticEntity(79.0, 179.0, 20.0, "../res/graphics/sprites/auditorium/teacher/row4.png");
		new CStaticEntity(95.0, 96.0, 10.0, "../res/graphics/sprites/auditorium/teacher/row5.png");


	}

	// TUTAJ JEST NOWA SALA - widok studentow	
	else { 
		new CStaticEntity(1.0, 1.0, 0.0, "../res/graphics/sprites/auditorium/students/main.png");
		new CStaticEntity(30.0, 736.0, 60.0, "../res/graphics/sprites/auditorium/students/bottom.png");	
		new CStaticEntity(45.0, 696.0, 50.0, "../res/graphics/sprites/auditorium/students/row1.png");
		new CStaticEntity(62.0, 661.0, 40.0, "../res/graphics/sprites/auditorium/students/row2.png");
		new CStaticEntity(77.0, 626.0, 30.0, "../res/graphics/sprites/auditorium/students/row3.png");
		new CStaticEntity(92.0, 595.0, 20.0, "../res/graphics/sprites/auditorium/students/row4.png");
		new CStaticEntity(107.0, 565.0, 10.0, "../res/graphics/sprites/auditorium/students/row5.png");
		new CStaticEntity(150.0, 250.0, 5.0, "../res/graphics/sprites/teacher/teacher.png");

	}
/*
*/							
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
	cout<<"CAuditorium::seatNewStudent row col type"<<row<<"  "<< col<<"  "<< type<<endl;

	if(!(CNetwork::getInstance()->getIsClient()))
	{
		switch(type)
		{
			case 0: 
			case 1:
			case 2:
				seatNewStudent(row,col,"../res/graphics/animsequences/1idle_sequence.dat", "CDynamicEntity");
				return true;
			
			case 3:
			case 4:
			case 5:
				seatNewStudent(row,col,"../res/graphics/animsequences/2idle_sequence.dat", "CDynamicEntity");
				return true;
			case 6:
			case 7:
			case 8:
				seatNewStudent(row,col,"../res/graphics/animsequences/3idle_sequence.dat", "CDynamicEntity");
				return true;
			default:
				return false;
		}
	} 
	else 
	{
		switch(type)
		{
			case 0: 
			case 1:
			case 2:
				seatNewStudent(row,col,"../res/graphics/sprites/students/rear/boy1.png","CStaticEntity");
				return true;
			
			case 3:
			case 4:
			case 5:
				seatNewStudent(row,col,"../res/graphics/sprites/students/rear/boy2.png","CStaticEntity");
				return true;
			case 6:
			case 7:
			case 8:
				seatNewStudent(row,col,"../res/graphics/sprites/students/rear/boy3.png","CStaticEntity");
				return true;
			default:
				return false;

		}
	}
}

