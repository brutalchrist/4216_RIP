#include "cuarentaydosdieciseis.h"
#include "ui_cuarentaydosdieciseis.h"
#include <QStringListModel>

//NOTA: apt-get install libqt4-sql-mysql

cuarentaydosdieciseis::cuarentaydosdieciseis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cuarentaydosdieciseis)
{
    ui->setupUi(this);

    //Codec para tildes
    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);

    //Se deja la ventana con tamaño fijo
    this->setFixedSize(this->width(), this->height());

    ocultarTablas();
}

cuarentaydosdieciseis::~cuarentaydosdieciseis()
{
    desconectarMysql();
    delete ui;
}

/*Metodos propios*/
bool cuarentaydosdieciseis::conectarMysql(){
    if(!db.isOpen()){
        db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName("localhost");
        db.setDatabaseName("4216");
        db.setUserName("root");
        db.setPassword("1020");

        if(!db.open()){
            return false;
        }
    }
    return true;
}

void cuarentaydosdieciseis::desconectarMysql(){
    if(db.isOpen()){
        db.close();
    }
}

void cuarentaydosdieciseis::ocultarTablas(){
    ui->tablaClientesEditar->hide();
    ui->tablaClientesEliminar->hide();
    ui->tablaTrabajos->hide();
}

/*Pop-up*/
void cuarentaydosdieciseis::ventanaImagen(QString url){
    dialogo.move(((this->width()/2 +this->x()) - dialogo.width()/2), ((this->height()/2 + this->y()) - this->height()/2));
    dialogo.setImagen(url);
    dialogo.show();
}

void cuarentaydosdieciseis::infoMsg(QString msg){
    QMessageBox::information(this, tr("Advertencia"), msg);
}

void cuarentaydosdieciseis::advertenciaMsg(QString msg){
    QMessageBox::warning(this, tr("Advertencia"), msg);
}

void cuarentaydosdieciseis::errorMsg(QString msg){
    QMessageBox::critical(this, tr("Error"), msg);
}

bool cuarentaydosdieciseis::siNoMsg(QString titulo, QString msg){

    if(QMessageBox::question(this, titulo, msg, "Si", "No", 0, 1) == 0)
        return true;
    else
        return false;
}

/*Eventos menu*/
void cuarentaydosdieciseis::on_actionCerrar_2_triggered()
{
    qApp->quit();
}

void cuarentaydosdieciseis::on_actionNuevoCliente_triggered()
{
    this->setWindowTitle("Nuevo cliente - Cuarentaydos Dieciséis");

    infoMsg("Nuevo cliente");
}

void cuarentaydosdieciseis::on_actionEditarCliente_triggered()
{
    this->setWindowTitle("Editar cliente - Cuarentaydos Dieciséis");

    if(conectarMysql()){
        QSqlQueryModel *modelo = new QSqlQueryModel;

        modelo->setQuery("select rut, nombres, apellidoPaterno, apellidoMaterno from usuario where idTipo = 2");

        ui->tablaClientesEditar->setModel(modelo);
        ocultarTablas();
        ui->tablaClientesEditar->show();
    }
    else{
        errorMsg("No se pudo conectar a la base de datos");
    }
}

void cuarentaydosdieciseis::on_actionEliminarCliente_triggered()
{
    this->setWindowTitle("Eliminar cliente - Cuarentaydos Dieciséis");

    if(conectarMysql()){
        QSqlQueryModel *modelo = new QSqlQueryModel;

        modelo->setQuery("select rut, nombres, apellidoPaterno, apellidoMaterno from usuario where idTipo = 2");

        ui->tablaClientesEliminar->setModel(modelo);
        ocultarTablas();
        ui->tablaClientesEliminar->show();
    }
    else{
        errorMsg("No se pudo conectar a la base de datos");
    }
}

void cuarentaydosdieciseis::on_actionNuevaBicicleta_triggered()
{
    this->setWindowTitle("Nueva bicicleta - Cuarentaydos Dieciséis");

    infoMsg("Nueva bicicleta");
}

void cuarentaydosdieciseis::on_actionEditarBicicleta_triggered()
{
    this->setWindowTitle("Editar bicicleta - Cuarentaydos Dieciséis");

    infoMsg("Editar bicicleta");
}

void cuarentaydosdieciseis::on_actionEliminarBicicleta_triggered()
{
    this->setWindowTitle("Eliminar bicicleta - Cuarentaydos Dieciséis");

    infoMsg("Eliminar bicicleta");
}

void cuarentaydosdieciseis::on_actionNuevoTrabajo_triggered()
{
    this->setWindowTitle("Nuevo trabajo - Cuarentaydos Dieciséis");

    infoMsg("Nuevo Trabajo");
}

void cuarentaydosdieciseis::on_actionPendientesTrabajo_triggered()
{
    this->setWindowTitle("Trabajos pendientes - Cuarentaydos Dieciséis");

    if(conectarMysql()){
        QSqlQueryModel *modelo = new QSqlQueryModel;

        modelo->setQuery("select * from bicicleta where estado = 1");

        ui->tablaTrabajos->setModel(modelo);
        ocultarTablas();
        ui->tablaTrabajos->show();

    }
    else{
        errorMsg("No se pudo conectar a la base de datos");
    }
}

void cuarentaydosdieciseis::on_actionEntregarTrabajo_triggered()
{
    this->setWindowTitle("Entregar trabajo - Cuarentaydos Dieciséis");

    infoMsg("Entregar trabajo");
}

void cuarentaydosdieciseis::on_actionHistorialTrabajo_triggered()
{
    this->setWindowTitle("Historial de trabajos - Cuarentaydos Dieciséis");

    infoMsg("Historial trabajo");
}

void cuarentaydosdieciseis::on_actionAcerca_de_triggered()
{   
    infoMsg("Acerca de");
}

/*Eventos tablas*/
void cuarentaydosdieciseis::on_tablaTrabajos_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 2)
        ventanaImagen(index.data().toString());
}

void cuarentaydosdieciseis::on_tablaClientesEditar_doubleClicked(const QModelIndex &index)
{
    infoMsg("Editar cliente");
}

void cuarentaydosdieciseis::on_tablaClientesEliminar_doubleClicked(const QModelIndex &index)
{
    if(siNoMsg("Eliminar", "¿Esta seguro de eliminar este cliente?")){
        QString sql1 = "delete from bicicleta where rutUsuario = "+index.sibling(index.row(), 0).data().toString();
        QString sql2 = "delete from usuario where rut = "+index.sibling(index.row(), 0).data().toString();

        if(conectarMysql()){
            QSqlQuery query;

            if(query.exec(sql1) && query.exec(sql2)){
                infoMsg("El usuario a sido eliminado correctamente");
                /*TODO: resfrescar el treeviwe*/
            }
            else{
                errorMsg("El usuario no a sido eliminado");
            }
        }
        else{
            errorMsg("No se pudo conectar a la base de datos");
        }
    }
}

