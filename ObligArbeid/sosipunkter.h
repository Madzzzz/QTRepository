#ifndef SOSIPUNKTER_H
#define SOSIPUNKTER_H

#include "displayobject.h"

class SosiPunkter : public DisplayObject
{

private:
    void lesfil(std::string filnavn);

public:
    SosiPunkter();
    ~SosiPunkter();

    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint normalAttribute, GLint
              textureAttribute=-1);
};
#endif // SOSIPUNKTER_H
