// Vec3.h - Dag Nylund 15/04/15
// Liten klasse uten cpp-fil
#ifndef VEC3_H
#define VEC3_H

#include <qgl.h>    // definerer GLfloat
#include <cmath>

struct Vec3
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Vec3(GLfloat a=0.0, GLfloat b=0.0, GLfloat c=0.0) : x(a), y(b), z(c) { }
    const Vec3& operator = (const Vec3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    Vec3 operator + (const Vec3& v) const
    {
        Vec3 u;
        u.x = x + v.x;
        u.y = y + v.y;
        u.z = z + v.z;
        return u;
    }
    Vec3 operator - (const Vec3& v) const
    {
        Vec3 u;
        u.x = x - v.x;
        u.y = y - v.y;
        u.z = z - v.z;
        return u;
    }
    Vec3 operator ^ (const Vec3& v) const
    {
        Vec3 w;
        w.x =  y*v.z - z*v.y;
        w.y =  z*v.x - x*v.z;
        w.z =  x*v.y - y*v.x;
        return w;
    }
    void normalize()
    {
        GLfloat d = x*x+y*y+z*z;
        d = sqrt(d);
        if (d>0.0)
        {
            x=x/d;
            y=y/d;
            z=z/d;
        }
    }
    float operator * (const Vec3& v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
    // 151127
    Vec3 operator * (float c) const
    {
        return Vec3(x*c, y*c, z*c);
    }
};
#endif // VEC3_H
