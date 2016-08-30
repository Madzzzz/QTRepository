#include <QDebug>
#include <QImage>
#include <cstdio>
#include <iostream>
#include "sosipunkter.h"
#include "vertex.h"
#include "fil.h"

using namespace std;

SosiPunkter::SosiPunkter() : DisplayObject()
{
    lesfil("C:/Users/mads/Desktop/Visim/Kartdata_403_Hamar_UTM33_N50_SOSI/SosiTestPunkter.txt");

}

SosiPunkter::~SosiPunkter()
{
    delete [] m_vertices;
}

void SosiPunkter::lesfil(std::string filnavn)
{
    cout << "SOSI::lesfil()" << endl;
    Fil::les(filnavn, m_vertices, m_antallVertices);
    cout << "SOSI antall " << m_antallVertices << endl;
}

void SosiPunkter::initVertexBufferObjects()
{
    initializeOpenGLFunctions();
    // Skal nå sende all vertex og color data til ett buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_antallVertices*sizeof(Vertex), m_vertices, GL_STATIC_DRAW);
}

void SosiPunkter::draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute)
{

    // Har en array av strukturer (noen Vertex objekter) som skal splittes på to
    // attributter i vertex shader. stride blir her størrelsen av hver struktur
    // Må bruke offset for start
    initializeOpenGLFunctions();
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
    offset = 3*sizeof(GLfloat);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
    // Tekstur
    if (textureAttribute != -1)
    {
        //glUniform1i(colorAttribute, 0);
        offset = 6*sizeof(GLfloat);
        //glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    glDrawArrays(GL_LINE_LOOP, 0, m_antallVertices);
}
