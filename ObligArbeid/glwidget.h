#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QMatrix4x4>
#include <QtGui/QScreen>
#include <QOpenGLFunctions>
#include <QTime>
#include "vec3.h"
#include "sosipunkter.h"
#include "sosikurver.h"

class MainWindow;
class DisplayObject;
class ShaderProgramObjekt;
//class Texture;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(MainWindow *parent = 0);
    ~GLWidget();

signals:

public slots:

    void klikket();
    void redigert();
    //ikke lag eget slot her - det er protected i QWidget
    void update();
    void repaint();
    //void initializeShader();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    QSize sizeHint() const;

    //! This function is responsible for most of the initialization
    //! that normally is done in initializeGL()
    //! To allow interactive shader editing most of the initialization
    //! must also been done when a shader is changed
    void init();
    ShaderProgramObjekt* m_shaderProgramObjekt; // Erstatter QOpenGLShaderProgram* m_program;


    QMatrix4x4 m_MVMatrix;
    QMatrix4x4 m_PMatrix;

    GLuint m_positionAttribute;
    GLuint m_colorAttribute;
    GLuint m_uniformPMatrix;
    GLuint m_uniformMVMatrix;

    int m_frame;
    QTimer* m_timer;
    static int m_frame0;    // 160105
    static int m_tid0;      //

    MainWindow* m_parent;

    QOpenGLContext* m_context;
    QTime* m_tid;

    DisplayObject *m_sosipunkter;
    DisplayObject *m_sosikurver;
};

#endif // GLWIDGET_H
