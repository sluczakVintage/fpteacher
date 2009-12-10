#include "globals.hpp"

using namespace std;


int main( int argc, char* args[] )
{
	int i = 0;

	COGLWindow* window = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay(200,200,-1,false,"Test");
	COGLWindow* window2 = COGLWindow::getInstance();
	while(i <= 6000){
	COGLWindow::getInstance()->update();
	i++;
	}
	COGLWindow::getInstance()->closeDisplay();
	COGLWindow::destroyInstance();
		
	return 0;
}
