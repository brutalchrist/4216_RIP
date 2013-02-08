#include "imagendialogo.h"
#include "ui_imagendialogo.h"

ImagenDialogo::ImagenDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagenDialogo)
{
    ui->setupUi(this);
}

ImagenDialogo::~ImagenDialogo()
{
    delete ui;
}

void ImagenDialogo::on_botonCerrar_clicked()
{
    this->hide();
}

void ImagenDialogo::setImagen(QString urlImagen){
    ui->imagen->setPixmap(QPixmap(urlImagen));
}
