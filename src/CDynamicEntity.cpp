/** @file CEntity.cpp
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
 
* @brief klasa CDynamicEntity jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/


#include "CDynamicEntity.hpp"

using namespace std;


//konstruktor 
//@param trzy liczby float
CDynamicEntity::CDynamicEntity(float x, float y, float z, const string& filename)
	: CEntity(x,y,z,filename)
{
	type_ = "CDynamicEntity";
	//if(&filename != NULL)
	//list<pair<string,int>> lista_animacji; /// @todo TO JEST BARDZO TYMCZASOWE
	//lista_animacji.push_back(make_pair(filename, 10)); ///////
	//lista_animacji.push_back(make_pair("../res/graphics/sprites/students/yawn_animset.dat", 2));//////
	animator_.openFile(filename);
	//animator_.refillCAnimator(lista_animacji, utils::ANIM_RANDOM);
	animator_.playAnimation();

	cout << "ANIMACJA STWORZONA!!" << endl;
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	cout<<"CDynamicEntity::CDynamicEntity: tworzenie zakoñczone sukcesem"<<endl;
}

CDynamicEntity::~CDynamicEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CDynamicEntity::~CDynamicEntity: niszczenie"<<endl;
}

//woluje metode rysowania
void CDynamicEntity::draw()
{
	animator_.animate(x_,y_);
}



//~~CDynamicEntity.cpp
