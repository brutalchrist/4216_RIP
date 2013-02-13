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
    ui->grupoNuevoCliente->hide();
    ui->grupoEditarCliente->hide();
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

    ocultarTablas();
    ui->grupoNuevoCliente->show();
}

void cuarentaydosdieciseis::on_botonEnviarCliente_clicked()
{
    QString sql = "insert into usuario value (";
    QSqlQuery query;

    if(!ui->rutCliente->text().isEmpty() && !ui->nombreCliente->text().isEmpty() && !ui->apellidoPCliente->text().isEmpty() &&
            !ui->apellidoMCliente->text().isEmpty() && !ui->loginCliente->text().isEmpty() && !ui->passwordCliente->text().isEmpty()){
        if(!ui->movilCliente->text().isEmpty() || !ui->telefonoCliente->text().isEmpty()){

            sql += "'" + ui->rutCliente->text() + "', "+"'" + ui->nombreCliente->text() + "', "+"'" + ui->apellidoPCliente->text() + "', "+
                    "'" + ui->apellidoMCliente->text() + "', "+"'" + ui->loginCliente->text() + "', "+"'" +
                    QCryptographicHash::hash(ui->passwordCliente->text().toLatin1(), QCryptographicHash::Md5).toHex() + "', "+
                    "'" + ui->telefonoCliente->text() + "', "+"'" + ui->movilCliente->text() + "', "+"'" + ui->mailCliente->text() + "', '2')";

            if(conectarMysql()){
                if(query.exec(sql)){
                    infoMsg("El usuario a sido ingresado correctamente");
                    ocultarTablas();
                }
                else
                    errorMsg("El usuario no pudo ser ingresado");
            }
            else{
                errorMsg("No se pudo conectar a la base de datos");
            }
        }
        else{
            advertenciaMsg("Se debe ingresar al menos un contacto telefónico ");
        }
    }
    else{
        advertenciaMsg("Los campos RUT, Nombres, Apellido Paterno, Apellido Materno, Login y Password no deben estar vacíos ");
    }
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
    QMessageBox::about(this, "Acerca de", "Este es el acerca de");
}

/*Eventos tablas*/
void cuarentaydosdieciseis::on_tablaTrabajos_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 2)
        ventanaImagen(index.data().toString());
}

void cuarentaydosdieciseis::on_tablaClientesEditar_doubleClicked(const QModelIndex &index)
{
    this->setWindowTitle(QString("Editando " + index.data(1).toString() + " - Cuarentaydos Dieciséis"));

    if(conectarMysql()){
        QSqlQuery query;

        QString sql = "select * from usuario where rut = '" + index.sibling(index.row(), 0).data().toString() + "'";

        query.exec(sql);

        while(query.next()){
            ui->rutClienteEditar->setText(query.value(0).toString());
            ui->nombreClienteEditar->setText(query.value(1).toString());
            ui->apellidoPClienteEditar->setText(query.value(2).toString());
            ui->apellidoMClienteEditar->setText(query.value(3).toString());
            ui->loginClienteEditar->setText(query.value(4).toString());
            ui->telefonoClienteEditar->setText(query.value(6).toString());
            ui->movilClienteEditar->setText(query.value(7).toString());
            ui->mailClienteEditar->setText(query.value(8).toString());;
        }

        ocultarTablas();
        ui->grupoEditarCliente->show();

    }
    else{
        errorMsg("No se pudo conectar a la base de datos");
    }
}

void cuarentaydosdieciseis::on_botonEditarCliente_clicked()
{
    QString sql = "update usuario set nombres = '"+ui->nombreClienteEditar->text()+"', apellidoPaterno ='"+ui->apellidoPClienteEditar->text()
            +"', apellidoMaterno = '"+ui->apellidoMClienteEditar->text()+"', login = '"+ui->loginClienteEditar->text()+"', telefonoFijo = '"+
            ui->telefonoClienteEditar->text()+"', telefonoMovil = '"+ui->movilClienteEditar->text()+"', email = '"+ui->mailClienteEditar->text()+"'";

    if(ui->passwordClienteEditar->text().isEmpty()){
        sql += " where rut = '"+ui->rutClienteEditar->text()+"'";
    }
    else{
        sql += ", password = '"+QCryptographicHash::hash(ui->passwordClienteEditar->text().toLatin1(), QCryptographicHash::Md5).toHex()+"' where rut = '"+ui->rutClienteEditar->text()+"'";
    }

    if(siNoMsg("Editar", "¿Son correctos los datos ingresados?")){
        QSqlQuery query;

        if(query.exec(sql)){
            infoMsg("El usuario a sido editado correctamente");
            on_actionEditarCliente_triggered();
        }
        else{
            errorMsg("El usuario no a sido editado");
        }
    }
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
                on_actionEliminarCliente_triggered();
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

