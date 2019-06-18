#include "object.h"

#include<QOpenGLTexture>
#include<QOpenGLShaderProgram>
#include<QOpenGLFunctions>

Object::Object()
    : m_VertexBuffer(QOpenGLBuffer::VertexBuffer), // это значение по-умолчанию
      m_IndexBuffer(QOpenGLBuffer::IndexBuffer),
      m_Texture(nullptr)
{
    m_Scale = 1.0f;
}

Object::Object(const QVector<VertexData> &vert, const QVector<GLuint> &ind, const QImage &img)
    : m_VertexBuffer(QOpenGLBuffer::VertexBuffer), // это значение по-умолчанию
      m_IndexBuffer(QOpenGLBuffer::IndexBuffer),
      m_Texture(nullptr)
{
    m_Scale = 1.0f;
    init(vert, ind, img);
}

Object::~Object()
{
    free();
}

void Object::free()
{
    if(m_VertexBuffer.isCreated()) m_VertexBuffer.destroy();
    if(m_IndexBuffer.isCreated()) m_IndexBuffer.destroy();
    if(m_Texture != nullptr && m_Texture->isCreated())
    { delete m_Texture; m_Texture = nullptr; }
}

void Object::init(const QVector<VertexData> &vert, const QVector<GLuint> &ind, const QImage &img)
{
    free();

    m_VertexBuffer.create();
    m_VertexBuffer.bind();
    m_VertexBuffer.allocate(vert.constData(), vert.size() * static_cast<int>(sizeof(VertexData)));
    m_VertexBuffer.release();// temp

    m_IndexBuffer.create();
    m_IndexBuffer.bind();
    m_IndexBuffer.allocate(ind.constData(), ind.size() * static_cast<int>(sizeof(GLuint)));
    m_IndexBuffer.release();// temp

    m_Texture = new QOpenGLTexture(img.mirrored());
    m_Texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_Texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Object::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    if(!m_VertexBuffer.isCreated() || !m_IndexBuffer.isCreated()) return;

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(m_Translate); // здесь важен порядок преобразований *
    modelMatrix.rotate(m_Rotate); // *
    modelMatrix.scale(m_Scale); // *
    modelMatrix = m_GlobalTransform * modelMatrix;

    m_Texture->bind(0);
    program->setUniformValue("u_texture", 0);
    program->setUniformValue("u_modelMatrix", modelMatrix);

    m_VertexBuffer.bind();

    int offset = 0;

    int vertloc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertloc);
    program->setAttributeBuffer(vertloc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texloc = program->attributeLocation("a_textcoord");
    program->enableAttributeArray(texloc);
    program->setAttributeBuffer(texloc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normloc = program->attributeLocation("a_normal");
    program->enableAttributeArray(normloc);
    program->setAttributeBuffer(normloc, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_IndexBuffer.bind();

    functions->glDrawElements(GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

    m_VertexBuffer.release();
    m_IndexBuffer.release();
    m_Texture->release();
}

void Object::rotate(const QQuaternion &r)
{
    m_Rotate = r * m_Rotate;
}

void Object::translate(const QVector3D &t)
{
    m_Translate += t;
}

void Object::scale(const float &s)
{
    m_Scale *= s;
}

void Object::setGlobalTransform(const QMatrix4x4 &gt)
{
    m_GlobalTransform = gt;
}
