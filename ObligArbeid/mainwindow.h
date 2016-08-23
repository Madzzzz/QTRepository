#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "syntakshighlighter.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;

class QAbstractButton;
class QTextEdit;

class QPushButton;
class QPlainTextEdit;

class QHBoxLayout;
class QOpenGLWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    QString hentFragmentShaderFilnavn() const;
    QString hentVertexShaderFilnavn() const;
    QString hentFragmentShaderKode() const;
    QString hentVertexShaderKode() const;

public slots:
    void openFragmentShader();
    void openVertexShader();
    void saveFragmentShader();
    void saveVertexShader();
    void redigert();
    void close();

signals:

protected:

private:
    void createMenu();
    QLayout* buttonLayout();
    void kobleSignalsAndSlots();

    QHBoxLayout* m_hBoxLayout;
    bool loadFile(const QString& filnavn, QString& tekst);
    bool saveFile(const QString& filnavn, QString& tekst);

    enum { NumGridRows = 3, NumButtons = 13 };

    QMenuBar *menuBar;

    QPlainTextEdit *fragmentShaderEditor;
    QPlainTextEdit *vertexShaderEditor;

    SyntaksHighlighter *fragmetHighlighter;
    SyntaksHighlighter *vertexHighlighter;

    QGroupBox *verticalGroupBox;
    QAbstractButton *buttons[NumButtons];   // Endret fra QPushButton for fleksibilitet i GUI
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction* openFragmentAction;
    QAction* openVertexAction;
    QAction* saveFragmentAction;
    QAction* saveVertexAction;
    QAction *exitAction;

    QString* fragmentShaderFilnavn;
    QString* vertexShaderFilnavn;

    QOpenGLWidget* glWidget;
};

#endif
