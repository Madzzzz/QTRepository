#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QtGui>
#include <QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

class Vertex;
//! \brief Base class for displayable objects.

//! This class includes a couple of virtual functions and a pointer
//! for memory allocation.
//! The implementation and also memory allocation is done in derived classes.
//!
class DisplayObject : protected QOpenGLFunctions//public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    DisplayObject();

    //! \brief virtual destructor.

    //! The destructor make the OpenGL calls
    //! glDeleteBuffers(1, &m_vertexBuffer);
    //! glDeleteBuffers(1, &m_indexBuffer);
    //! before the object itself is deleted.
    virtual ~DisplayObject();
    virtual void initVertexBufferObjects() = 0;
    virtual void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute=-1) = 0 ;
    virtual void setTexture(GLuint texture);


protected:
    Vertex* m_vertices;         // minneallokering i avledede klasser
    GLuint m_antallVertices;
    GLuint m_vertexBuffer;      //GLuint m_normalBuffer; //GLuint m_textureBuffer;
    GLuint m_indexBuffer;
    GLuint m_texture;
};

#endif // DISPLAYOBJECT_H
