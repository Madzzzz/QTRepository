/**
 * @file glwidget.cpp
 * @author Dag Nylund
 * @date 16.04.2013
 *
 *
 */
#include <QStatusBar>
#include <QMainWindow>
#include <QtGui/QOpenGLFunctions>
#include <QTimer>
#include <ctime>
#include <QPushButton>
#include "glwidget.h"
#include "mainWindow.h"
#include "displayobject.h"
#include "shaderprogram.h"

int GLWidget::m_frame0 = 0;
int GLWidget::m_tid0 = 0;

/**
 * @brief GLWidget::GLWidget.
 * @param parent Peker til mainWindow
 *
 * Konstruktør som initierer @var m_parent og oppretter en timer
 */
GLWidget::GLWidget(MainWindow *parent) : QOpenGLWidget( parent),
    m_parent(parent),  m_frame(0), m_shaderProgramObjekt(0), QOpenGLFunctions()//, m_lightPosition(-5.0, -3.0, -3.0)
{
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_context = 0;
    m_tid = new QTime(QTime::currentTime());
    m_tid->start();
    m_sosipunkter = new SosiPunkter();
}

// Dette er protected i QWidget
void GLWidget::update()
{
    QWidget::update();

    //Viser tiden
    //m_parent->statusBar()->showMessage(m_tid->currentTime().toString());

    // Beregner fps på en enkel måte.
    // m_tid er en klokke som startes i konstruktøren og går
    // m_frame telles i paintGL()
    int millisekunder = m_tid->elapsed();
    if (millisekunder % 1000 < 10) {
        m_frame0 = m_frame - m_frame0;
        m_tid0 = millisekunder - m_tid0;
        float fps = 1000 * m_frame0/m_tid0;
        QStatusBar* sb = m_parent->statusBar();
        sb->showMessage(QString::number(fps));
    }
}
void GLWidget::repaint()
{
    //QWidget::repaint();
    qDebug() << "repaint";// << sender();
}

GLWidget::~GLWidget()
{
    delete m_shaderProgramObjekt;
    delete m_timer;
    delete m_context;
    delete m_tid;
    delete m_sosipunkter;
}

/// property i QWidget klassen
QSize GLWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GLWidget::init()
{
    m_shaderProgramObjekt = new ShaderProgramObjekt();
    m_shaderProgramObjekt->initShader(m_parent->hentVertexShaderKode(), m_parent->hentFragmentShaderKode());
    m_shaderProgramObjekt->useProgram();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_SAMPLER_2D);

    m_positionAttribute = m_shaderProgramObjekt->getAttribLocation("aVertexPosition");
    m_colorAttribute = m_shaderProgramObjekt->getAttribLocation("aVertexColor");
    m_uniformMVMatrix = m_shaderProgramObjekt->getUniformLocation("uMVMatrix");
    m_uniformPMatrix = m_shaderProgramObjekt->getUniformLocation("uPMatrix");

    qDebug() << "GLWidget init " << m_positionAttribute  << m_colorAttribute;

    m_sosipunkter->initVertexBufferObjects();

    glEnableVertexAttribArray(m_positionAttribute);
    glEnableVertexAttribArray(m_colorAttribute);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    qDebug() << "GLWidget::init() utført" ;

}

void GLWidget::initializeGL()
{
    //f = QOpenGLContext::currentContext()->functions();
    initializeOpenGLFunctions();

    init();
    qDebug() << "GLWidget::initializeGL() utført" ;
}


// Felles slot for alle pushbuttons i mainWindow
void GLWidget::klikket()
{
    //initializeOpenGLFunctions();
    QString navn = sender()->objectName();
    qDebug() << navn;
    if (navn == "start")
    {
        m_timer->start(17);
        sender()->setObjectName("stopp");
        QPushButton* qpb = dynamic_cast<QPushButton*>(sender());
        qpb->setText("stopp");
    }
    if (navn == "stopp")
    {
        m_timer->stop();
        sender()->setObjectName("start");
        QPushButton* qpb = dynamic_cast<QPushButton*>(sender());
        qpb->setText("start");
    }
    if (navn == "1")
    {
        m_uniformMVMatrix = m_shaderProgramObjekt->getUniformLocation("uMVMatrix");
        m_uniformPMatrix = m_shaderProgramObjekt->getUniformLocation("uPMatrix");
        qDebug() << "uniforms m_uniformMVMatrix " << m_uniformMVMatrix;
        qDebug() << "uniforms m_uniformPMatrix " << m_uniformPMatrix;
    }
}

void GLWidget::redigert()
{
    makeCurrent();
    bool timerActive=false;
    qDebug() << "redigert";

    if (m_timer->isActive())
    {
        m_timer->stop();
        timerActive = true;
    }
    m_shaderProgramObjekt->deleteProgram();
    delete m_shaderProgramObjekt;
    m_shaderProgramObjekt = new ShaderProgramObjekt();
    m_shaderProgramObjekt->initShader(m_parent->hentVertexShaderKode(), m_parent->hentFragmentShaderKode());
    if (timerActive)
        m_timer->start(17);
}

void GLWidget::paintGL()
{
    // MouseMove i MainWindow genererer events som får paintGL() til
    // å utføres. Hindrer dette ved å teste om timeren går.

    if (!m_timer->isActive())
    {
        //qDebug() << "paintGL() timer inaktiv";
        return;
    }
    m_shaderProgramObjekt->useProgram();

    glViewport(0, 0, width(), height());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_PMatrix.setToIdentity();
    m_PMatrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    m_shaderProgramObjekt->setUniformMatrix(m_uniformPMatrix, 1, GL_FALSE, m_PMatrix.constData());

    m_MVMatrix.setToIdentity();
    m_MVMatrix.scale(0, 0, 0);

    m_shaderProgramObjekt->setUniformMatrix(m_uniformMVMatrix, 1, GL_FALSE, m_MVMatrix.constData());
    m_sosipunkter->draw(m_positionAttribute, m_colorAttribute);


    glEnable(GL_TEXTURE_2D);
    ++m_frame; // brukes i update til å telle fps
}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);
}


