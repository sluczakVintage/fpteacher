#include "CVideoSystem.hpp"

using namespace std;

CVideoSystem::CVideoSystem()
{
	cout << "Powstaje CVideoSystem" << endl;
}


CVideoSystem::~CVideoSystem()
{
	cout << "CVideoSystem niszczony" << endl;
}

void CVideoSystem::bindTexture(const CSprite& sprite) const
{
		glBindTexture(GL_TEXTURE_2D, sprite.getTexID()); //log, ?
}

void CVideoSystem::drawCSprite(float x, float y, const CSprite& sprite  ) const
{
	utils::TexDims tex_dims = sprite.getTexDimensions();


	glColor4ub(255,255,255, sprite.getSpriteAlpha()); 
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    bindTexture(sprite);
    glBegin(GL_TRIANGLE_STRIP); 
		glTexCoord2f(tex_dims.texMinX,tex_dims.texMinY);    glVertex2f(x,y);
		glTexCoord2f(tex_dims.texMaxX,tex_dims.texMinY);    glVertex2f(x+sprite.getSpriteWidth(),y);
        glTexCoord2f(tex_dims.texMinX,tex_dims.texMaxY);    glVertex2f(x,y+sprite.getSpriteHeight());
        glTexCoord2f(tex_dims.texMaxX,tex_dims.texMaxY);    glVertex2f(x+sprite.getSpriteWidth(),y+sprite.getSpriteHeight());
    glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);
}