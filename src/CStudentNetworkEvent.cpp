#include "CStudentNetworkEvent.hpp"
#include "CAuditorium.hpp"

//BOOST_CLASS_EXPORT(CStudentNetworkEvent);
CStudentNetworkEvent::CStudentNetworkEvent()
{

}

CStudentNetworkEvent::CStudentNetworkEvent(int row, int column, int type)
	: row_(row), column_(column), type_(type)
{

}

void CStudentNetworkEvent::execute()
{
	CAuditorium::getInstance()->seatNewStudent(row_,column_,type_);
}
