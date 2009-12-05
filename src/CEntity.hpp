/**
* @brief klasa CEntity jest abstrakcyjna blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*
*
*/

#include <iostream>
#include <string>
using namespace std;
 

class CEntity
{
public:
	void draw(void);
	virtual ~CEntity(void); 


private:
//	CSprite sprite_;

};