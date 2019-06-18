#include "groupobjects.h"

GroupObjects::GroupObjects()
{
    m_Scale = 1.0f;
}

void GroupObjects::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    for(auto o: m_Objects) o->draw(program, functions);
}

void GroupObjects::rotate(const QQuaternion &r)
{
    m_Rotate = r * m_Rotate;

    QMatrix4x4 localmatrix;
    localmatrix.setToIdentity();
    localmatrix.translate(m_Translate);
    localmatrix.rotate(m_Rotate);
    localmatrix.scale(m_Scale);
    localmatrix = m_GlobalTransform * localmatrix;

    for(auto o: m_Objects) o->setGlobalTransform(localmatrix);
}

void GroupObjects::translate(const QVector3D &t)
{
    m_Translate += t;

    QMatrix4x4 localmatrix;
    localmatrix.setToIdentity();
    localmatrix.translate(m_Translate);
    localmatrix.rotate(m_Rotate);
    localmatrix.scale(m_Scale);
    localmatrix = m_GlobalTransform * localmatrix;

    for(auto o: m_Objects) o->setGlobalTransform(localmatrix);
}

void GroupObjects::scale(const float &s)
{
    m_Scale *= s;

    QMatrix4x4 localmatrix;
    localmatrix.setToIdentity();
    localmatrix.translate(m_Translate);
    localmatrix.rotate(m_Rotate);
    localmatrix.scale(m_Scale);
    localmatrix = m_GlobalTransform * localmatrix;

    for(auto o: m_Objects) o->setGlobalTransform(localmatrix);
}

void GroupObjects::setGlobalTransform(const QMatrix4x4 &gt)
{
    m_GlobalTransform = gt;

    QMatrix4x4 localmatrix;
    localmatrix.setToIdentity();
    localmatrix.translate(m_Translate);
    localmatrix.rotate(m_Rotate);
    localmatrix.scale(m_Scale);
    localmatrix = m_GlobalTransform * localmatrix;

    for(auto o: m_Objects) o->setGlobalTransform(localmatrix);
}

void GroupObjects::add(Transformational *obj)
{
    m_Objects.append(obj);

    QMatrix4x4 localmatrix;
    localmatrix.setToIdentity();
    localmatrix.translate(m_Translate);
    localmatrix.rotate(m_Rotate);
    localmatrix.scale(m_Scale);
    localmatrix = m_GlobalTransform * localmatrix;

    obj->setGlobalTransform(localmatrix);
}

bool GroupObjects::del(Transformational *obj)
{
    return m_Objects.removeAll(obj) > 0 ? true : false;
}

void GroupObjects::del(const int &ind)
{
    m_Objects.remove(ind);
}
