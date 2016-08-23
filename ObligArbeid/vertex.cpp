#include <QDebug>
#include "vertex.h"

Vertex::Vertex()
{

}

/*
Vertex::Vertex(GLfloat* xyz, GLfloat* rgba, GLfloat* normal, GLfloat* st)
{
    set_xyz(xyz);
    set_rgba(rgba);
    set_normal(normal);
    set_st(st);
}*/

Vertex::~Vertex()
{
    //qDebug() << "Vertex::~Vertex()";
}

void Vertex::set_xyz(GLfloat* xyz)
{
    for (int i=0; i<3; i++) m_xyz[i] = xyz[i];
}

void Vertex::set_xyz(GLfloat x, GLfloat y, GLfloat z)
{
    m_xyz[0] = x; m_xyz[1] = y; m_xyz[2] = z;
}

void Vertex::set_rgb(GLfloat* rgb)
{
    for (int i=0; i<3; i++) m_normal[i] = rgb[i];
}

void Vertex::set_rgb(GLfloat r, GLfloat g, GLfloat b)
{
    m_normal[0] = r; m_normal[1] = g; m_normal[2] = b;
}

void Vertex::set_normal(GLfloat* normal)
{
    for (int i=0; i<3; i++) m_normal[i] = normal[i];
}

void Vertex::set_normal(GLfloat x, GLfloat y, GLfloat z)
{
    m_normal[0] = x; m_normal[1] = y; m_normal[2] = z;
}

void Vertex::set_st(GLfloat* st)
{
    for (int i=0; i<2; i++) m_st[i] = st[i];
}

void Vertex::set_st(GLfloat s, GLfloat t)
{
    m_st[0] = s; m_st[1] = t;
}

std::ostream& operator<< (std::ostream& os, const Vertex& v)
{
   os << "(" << v.m_xyz[0] << ", " << v.m_xyz[1] << ", " << v.m_xyz[2] << ") ";
   os << "(" << v.m_normal[0] << ", " << v.m_normal[1] << ", " << v.m_normal[2] << ") ";
   os << "(" << v.m_st[0] << ", " << v.m_st[1] << ") ";
   return os;
}
std::istream& operator>> (std::istream& is, Vertex& v)
{
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
   char dum, dum2, dum3, dum4;
   is >> dum >> v.m_xyz[0] >> dum2 >> v.m_xyz[1] >> dum3 >> v.m_xyz[2] >> dum4;
   is >> dum >> v.m_normal[0] >> dum2 >> v.m_normal[1] >> dum3 >> v.m_normal[2] >> dum4;
   is >> dum >> v.m_st[0] >> dum2 >> v.m_st[1] >> dum3;

   return is;
}

void Vertex::data(float v[]) const
{
    //return static_cast<float*>(*this);

    for (int i=0; i<3; i++) v[i] = m_xyz[i];
    for (int i=3; i<6; i++) v[i] = m_normal[i-3];
    for (int i=6; i<8; i++) v[i] = m_st[i-6];
}
