#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLFunctions>
#include <QString>

class ShaderProgramObjekt : protected QOpenGLFunctions
{
private:
    GLuint m_shaderProgramObjekt;
    GLuint shader(GLenum shaderType, const QString& kildeKode);

public:
    ShaderProgramObjekt();
    ~ShaderProgramObjekt();
    void initShader(const QString& vertexKode, const QString& fragmentKode);
    GLint getAttribLocation(const GLchar* name);
    GLint getUniformLocation(const GLchar* name);
    void setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void setUniformVec3(GLint location, float x, float y, float z);
    void useProgram();
    void deleteProgram();
    GLuint getShaderId() { return m_shaderProgramObjekt; }

};

#endif // SHADERPROGRAM_H
