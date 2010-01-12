#include "CStudentNetworkEvent.hpp"
#include "CAuditorium.hpp"
//#include "Boost/Serialization/tracking.hpp"

BOOST_CLASS_TRACKING(CStudentNetworkEvent, boost::serialization::track_never);
//BOOST_CLASS_EXPORT(CStudentNetworkEvent);

//Konstruktor domyslny
CStudentNetworkEvent::CStudentNetworkEvent()
{

}

//konstruktor ze wszystkimi waznymi parametrami
CStudentNetworkEvent::CStudentNetworkEvent(int row, int column, int type)
	: row_(row), column_(column), type_(type)
{

}

//metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
void CStudentNetworkEvent::execute()
{
	CAuditorium::getInstance()->seatNewStudent(row_,column_,type_);
}
