#ifndef IMAGENDIALOGO_H
#define IMAGENDIALOGO_H

#include <QDialog>

namespace Ui {
class ImagenDialogo;
}

class ImagenDialogo : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImagenDialogo(QWidget *parent = 0);
    ~ImagenDialogo();

public slots:
    void setImagen(QString urlImagen);

private slots:
    void on_botonCerrar_clicked();

private:
    Ui::ImagenDialogo *ui;
};

#endif // IMAGENDIALOGO_H
