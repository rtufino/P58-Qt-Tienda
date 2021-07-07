#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QObject>

class Producto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int codigo READ codigo WRITE setCodigo)
    Q_PROPERTY(QString nombre READ nombre WRITE setNombre)
    Q_PROPERTY(float precio READ precio WRITE setPrecio)
private:
    int m_codigo;
    QString m_nombre;
    float m_precio;

public:
    explicit Producto(QObject *parent = nullptr);
    Producto(int codigo, QString nombre, float precio);

    int codigo() const;
    void setCodigo(int codigo);

    QString nombre() const;
    void setNombre(const QString &nombre);

    float precio() const;
    void setPrecio(float precio);

signals:

};

#endif // PRODUCTO_H
