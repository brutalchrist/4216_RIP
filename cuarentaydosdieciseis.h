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
    /*Metodos propios*/
    bool conectarMysql();
    void desconectarMysql();
    void ocultarTablas();

    /*Pop-up*/
    void advertenciaMsg(QString msg);
    void errorMsg(QString msg);
    void infoMsg(QString msg);
    void ventanaImagen(QString url);
    bool siNoMsg(QString titulo, QString msg);

    /*Eventos menu*/
    void on_actionPendientesTrabajo_triggered();
    void on_actionEditarCliente_triggered();
    void on_actionCerrar_2_triggered();
    void on_actionNuevoCliente_triggered();
    void on_actionEliminarCliente_triggered();
    void on_actionNuevaBicicleta_triggered();
    void on_actionEditarBicicleta_triggered();
    void on_actionEliminarBicicleta_triggered();
    void on_actionNuevoTrabajo_triggered();
    void on_actionEntregarTrabajo_triggered();
    void on_actionHistorialTrabajo_triggered();
    void on_actionAcerca_de_triggered();

    /*Eventos tablas*/
    void on_tablaTrabajos_doubleClicked(const QModelIndex &index);
    void on_tablaClientesEditar_doubleClicked(const QModelIndex &index);
    void on_tablaClientesEliminar_doubleClicked(const QModelIndex &index);




private:
    Ui::cuarentaydosdieciseis *ui;
};

#endif // CUARENTAYDOSDIECISEIS_H
