#include "CAuditorium.hpp"

void CAuditorium::init()
{
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(55.0, 583.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");
	new CStaticEntity(65.0, 486.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\row1.png");
	new CStaticEntity(75.0, 390.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\row2.png");
	new CStaticEntity(84.0, 296.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\row3.png");
	new CStaticEntity(94.0, 203.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\row4.png");
	new CStaticEntity(102.0, 108.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\row5.png");

}