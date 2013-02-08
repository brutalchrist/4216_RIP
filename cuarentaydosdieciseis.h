#ifndef CUARENTAYDOSDIECISEIS_H
#define CUARENTAYDOSDIECISEIS_H

#include "imagendialogo.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlError>

namespace Ui {
class cuarentaydosdieciseis;
}

class cuarentaydosdieciseis : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit cuarentaydosdieciseis(QWidget *parent = 0);
    ~cuarentaydosdieciseis();
    QSqlDatabase db;
    ImagenDialogo dialogo;
    
private slots:
    bool conectarMysql();
    void desconectarMysql();
    void on_actionCerrar_2_triggered();
    void advertenciaMsg(QString msg);
    void errorMsg(QString msg);
    void infoMsg(QString msg);
    void ventanaImagen(QString url);

    void on_actionPendientesTrabajo_triggered();
    void on_tabla_doubleClicked(const QModelIndex &index);

private:
    Ui::cuarentaydosdieciseis *ui;
};

#endif // CUARENTAYDOSDIECISEIS_H
