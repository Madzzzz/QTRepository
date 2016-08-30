#ifndef SOSIKURVER_H
#define SOSIKURVER_H

#include "displayobject.h"

class SosiKurver : public DisplayObject
{

private:
    void lesfil(std::string filnavn);

public:
    SosiKurver();
    ~SosiKurver();

    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint normalAttribute, GLint
              textureAttribute=-1);
};
#endif // SOSIKURVER_H
