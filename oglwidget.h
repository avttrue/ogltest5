#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>

class Object;
class Transformational;
class GroupObjects;
class Eye;
class SkyBox;

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent* event);

    void initShaders();
    void initCube(float width, const QImage &img);

private:
    QMatrix4x4 m_PojectionMatrix;
    QOpenGLShaderProgram m_Program;
    QOpenGLShaderProgram m_ProgramSkyBox;
    QVector2D m_MousePosition;
    QQuaternion m_Rotation;
    QVector<Object*> m_Objects;
    QVector<GroupObjects*> m_Groups;
    QVector<Transformational*> m_TransformObjects;

    Eye* m_Eye;
    SkyBox* m_SkyBox;

    QBasicTimer m_Timer;

    double m_AngleObject;
    double m_AngleGrop1;
    double m_AngleGrop2;
    double m_AngleGrop3;
    double m_AngleGropMain;
};

#endif // OGLWIDGET_H
