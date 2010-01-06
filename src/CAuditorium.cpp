/**
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft
* 
* @brief klasa CAuditorium 
*/

#include "CAuditorium.hpp"

const float CAuditorium::MARGIN = 0.0146f;
const float CAuditorium::TAB =  0.0136f;
const float CAuditorium::CUT_OFF = 99.0f/109.0f;

CAuditorium::CAuditorium() 
				: fields_(boost::extents[ROWS][COLUMNS]), teacher_(false)
{
	cout<<"-------------------------------->CAuditorium::CAuditorium() tworzenie"<<endl;
}

CAuditorium::~CAuditorium() 
{
	
	cout<<"-------------------------------->CAuditorium::~CAuditorium() nieszczenie"<<endl;
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
	 
		//	tylko do debugowania
	//		cout<<"CAuditorium::init powstaje CField>"<<">"<<currentX<<"<>"<<currentY<<"<>"<<j<<"<>"<<i<<"<>"<<h<<"<>"<<w<<"<"<<endl;
	/*	
			float pX = ptr->getX();
			float pY = ptr->getY();
			float pW = ptr->getWidth();
			float pH = ptr->getHeight();
			new CStaticEntity(pX,pY, 100.0, "..\\res\\graphics\\sprites\\auditorium\\kwadrat.png");
			new CStaticEntity(pX+pW-10.0, pY+pH-10.0, 101.1, "..\\res\\graphics\\sprites\\auditorium\\kwadrat1.png");
	*/	

		}
	}
	
/*	
	for(int j = 0; j<ROWS; j++)
	{
		for (int i = 0; i<COLUMNS;i++)
		{
		cout<<"fields_: "<<fields_[j][i]->getX()<<endl;
		}
	}
*/		
}

bool CAuditorium::seatNewStudent(int row, int col)
{

//	boost::shared_ptr<CField> cf(fields_[at.first][at.second]);
	boost::shared_ptr<CField> cf(fields_[row][col]);
	if(cf->isFree_)	 
	{
		if(CTimer::getInstance()->getTime() % 5 < 3)
			new CDynamicEntity(cf->x_,
						cf->y_,
						cf->z_+0.1f,
						"..\\res\\graphics\\sprites\\students\\animset_sit.dat");
		else if(CTimer::getInstance()->getTime() % 5 <2)
			new CStaticEntity(cf->x_-10,
						cf->y_,
						cf->z_+0.1f, 
						"..\\res\\graphics\\sprites\\students\\boy2.png");
		else
			new CStaticEntity(cf->x_-5,
						cf->y_,
						cf->z_+0.1f, 
						"..\\res\\graphics\\sprites\\students\\boy3.png");

		cf->isFree_ = false;
		cf->isBusy_ = true;
		return true;
	}

	return false;

}

