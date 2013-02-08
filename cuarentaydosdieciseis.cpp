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

    //Se deja con tamaño fijo
    this->setFixedSize(this->width(), this->height());

    ui->tablaTrabajos->setVisible(false);
    ui->tablaClientesEditar->setVisible(false);
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

/*Eventos menu*/
void cuarentaydosdieciseis::on_actionCerrar_2_triggered()
{
    qApp->quit();
}

void cuarentaydosdieciseis::on_actionNuevoCliente_triggered()
{
    infoMsg("Nuevo cliente");
}

void cuarentaydosdieciseis::on_actionEditarCliente_triggered()
{
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
    infoMsg("Eliminar cliente");
}

void cuarentaydosdieciseis::on_actionNuevaBicicleta_triggered()
{
    infoMsg("Nueva bicicleta");
}

void cuarentaydosdieciseis::on_actionEditarBicicleta_triggered()
{
    infoMsg("Editar bicicleta");
}

void cuarentaydosdieciseis::on_actionEliminarBicicleta_triggered()
{
    infoMsg("Eliminar bicicleta");
}

void cuarentaydosdieciseis::on_actionNuevoTrabajo_triggered()
{
    infoMsg("Nuevo Trabajo");
}

void cuarentaydosdieciseis::on_actionPendientesTrabajo_triggered()
{
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
    infoMsg("Entregar trabajo");
}

void cuarentaydosdieciseis::on_actionHistorialTrabajo_triggered()
{
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

