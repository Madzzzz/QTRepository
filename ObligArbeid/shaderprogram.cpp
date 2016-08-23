#include <string>
#include <QDebug>
#include "shaderprogram.h"

ShaderProgramObjekt::ShaderProgramObjekt() : m_shaderProgramObjekt(0), QOpenGLFunctions()
{
    qDebug() << "ShaderProgramObjekt()";
}

/// @param shaderType: GL_VERTEX_SHADER eller GL_FRAGMENT_SHADER
/// @param kildeKode: kildekode for aktuell shader.
/// Gjør om en QString til parametre for glShaderSource
/// Heter loadShader() i Programming Guide

ShaderProgramObjekt::~ShaderProgramObjekt()
{
    qDebug() << "~ShaderProgramObjekt()";
    int status;
    glGetProgramiv(m_shaderProgramObjekt, GL_DELETE_STATUS, &status);
    glDeleteProgram(m_shaderProgramObjekt);
}

GLuint ShaderProgramObjekt::shader(GLenum shaderType, const QString& kildeKode)
{

    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
    {
        qDebug() << "glCreateShader() feilet.";
        return 0;
    }
    std::string s = kildeKode.toStdString();
    const char* cKildeKode = s.c_str();
    glShaderSource(shader, 1, &cKildeKode, 0);

    glCompileShader(shader);

    GLint compiled;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, 0, infoLog);
            qDebug() << "compile shader error" << infoLog;
            delete [] infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    /// Test
    char src[2000]; // Økt fra 500
    int bufLen;
    glGetShaderSource(shader, 2000, &bufLen, src);
    qDebug() << src;
    return shader;
}

void ShaderProgramObjekt::initShader(const QString& vertexKode, const QString &fragmentKode)
{

    qDebug() << "initShader()";

    initializeOpenGLFunctions();

    m_shaderProgramObjekt = glCreateProgram();
    qDebug() << "m_shaderProgramObjekt" << m_shaderProgramObjekt;

    GLuint vertexShader = shader(GL_VERTEX_SHADER, vertexKode);
    glAttachShader(m_shaderProgramObjekt, vertexShader);

    GLuint fragmentShader = shader(GL_FRAGMENT_SHADER, fragmentKode);
    glAttachShader(m_shaderProgramObjekt, fragmentShader);

    glLinkProgram(m_shaderProgramObjekt);

    GLint linked=-1;
    glGetProgramiv(m_shaderProgramObjekt, GL_LINK_STATUS, &linked);

    if (!linked) // linked==GL_FALSE
    {
        GLint infoLen = 0;
        glGetProgramiv(m_shaderProgramObjekt, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(m_shaderProgramObjekt, infoLen, 0, infoLog);
            qDebug() << "compile shader error" << infoLog;
            delete [] infoLog;
        }
        glDeleteProgram(m_shaderProgramObjekt);
        m_shaderProgramObjekt = 0;
    }
}


GLint ShaderProgramObjekt::getAttribLocation(const GLchar* name)
{
    GLint i = glGetAttribLocation(m_shaderProgramObjekt, name);
    qDebug() << "shaderprogram "  << "attributt" << i << " for " << name;
    glGetProgramiv(m_shaderProgramObjekt, GL_ACTIVE_ATTRIBUTES, &i);
    qDebug() << "shaderprogram" << "antall attributter = " << i;
    return glGetAttribLocation(m_shaderProgramObjekt, name);
}

GLint ShaderProgramObjekt::getUniformLocation(const GLchar* name)
{
    GLint i = glGetUniformLocation(m_shaderProgramObjekt, name);
    qDebug() << "shaderprogram" << " uniform" << i << " for " << name;
    glGetProgramiv(m_shaderProgramObjekt, GL_ACTIVE_UNIFORMS, &i);
    qDebug() << "shaderprogram" << "antall uniforms = " << i;
    return glGetUniformLocation(m_shaderProgramObjekt, name);
}
void ShaderProgramObjekt::setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(location, count, transpose, value);
}
void ShaderProgramObjekt::setUniformVec3(GLint location, float x, float y, float z)
{
    glUniform3f(location, x, y, z);

}

void ShaderProgramObjekt::useProgram()
{
    glUseProgram(m_shaderProgramObjekt);
}
void ShaderProgramObjekt::deleteProgram()
{
    GLint i;
    glDeleteProgram(m_shaderProgramObjekt);
    glGetProgramiv(m_shaderProgramObjekt, GL_DELETE_STATUS, &i);
    if (i == GL_FALSE)
        qDebug() << "shaderprogram delete status = GL_FALSE";
    else
        qDebug() << "shaderprogram delete status = GL_TRUE";
}
