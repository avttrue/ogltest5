#ifndef GROUPOBJECTS_H
#define GROUPOBJECTS_H

#include "transformational.h"

#include <QVector>
#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>

class GroupObjects : public Transformational
{
public:
    GroupObjects();
    void draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &gt);
    void add(Transformational* obj);
    bool del(Transformational* obj);
    void del(const int &ind);

private:
    QQuaternion m_Rotate;
    QVector3D m_Translate;
    float m_Scale;
    QMatrix4x4 m_GlobalTransform;
    QVector<Transformational*> m_Objects;
};

#endif // GROUPOBJECTS_H
