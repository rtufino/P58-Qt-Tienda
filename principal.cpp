#include "principal.h"
#include "ui_principal.h"

#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Lista de productos
    m_productos.append(new Producto(1,"Leche",0.85));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.00));
    // Mostrar la lista en la ventana
    for (int i = 0; i < m_productos.size(); ++i) {
       ui->inProducto->addItem(m_productos.at(i)->nombre());
    }
    // Colocar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Inicializar subtotal global
    m_subtotal = 0;
}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_cmdAgregar_released()
{
    // Validar que no se agregen productos con 0 cantidad
    int cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        return;
    }
    // Obtener datos de la GUI
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);


    // Calcular el subtotal del producto
    float subtotal = cantidad * p->precio();

    // Agregar datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(subtotal,'f',2)));

    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Invocar a calcular
    calcular(subtotal);

}

void Principal::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
}

void Principal::calcular(float stProducto)
{
    m_subtotal += stProducto;
    float iva = m_subtotal * IVA / 100;
    float total = m_subtotal + iva;

    ui->outSubtotal->setText(QString::number(m_subtotal,'f',2));
    ui->outIva->setText(QString::number(iva,'f',2));
    ui->outTotal->setText(QString::number(total,'f',2));


}
