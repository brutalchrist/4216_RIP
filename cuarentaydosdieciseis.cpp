#include "cuarentaydosdieciseis.h"
#include "ui_cuarentaydosdieciseis.h"

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

    ui->tabla->setVisible(false);
}

cuarentaydosdieciseis::~cuarentaydosdieciseis()
{
    desconectarMysql();
    delete ui;
}

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

void cuarentaydosdieciseis::ventanaImagen(QString url){
    dialogo.move(((this->width()/2 +this->x()) - dialogo.width()/2), ((this->height()/2 + this->y()) - this->height()/2));
    dialogo.setImagen(url);
    dialogo.show();
}

void cuarentaydosdieciseis::on_actionCerrar_2_triggered()
{
    qApp->quit();
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

void cuarentaydosdieciseis::on_actionPendientesTrabajo_triggered()
{
    if(conectarMysql()){
        QSqlQueryModel *modelo = new QSqlQueryModel;

        modelo->setQuery("select * from bicicleta where estado = 1");

        ui->tabla->setModel(modelo);
        ui->tabla->show();

    }
    else{
        errorMsg("No se pudo conectar a la base de datos");
    }
}

void cuarentaydosdieciseis::on_tabla_doubleClicked(const QModelIndex &index)
{
    if(ui->tabla->currentIndex().column() == 2)
        ventanaImagen(ui->tabla->currentIndex().data().toString());
}
