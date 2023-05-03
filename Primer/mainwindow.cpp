#include "mainwindow.h"
#include "./ui_mainwindow.h"

//INICIO NEURONA
Neurona::Neurona() // Constructor de la clase Neurona, inicializamos los valores para cada objeto que se creará
{
    id = red = green = blue = -1;
    voltaje = 0.0;
    posicion_x = posicion_y = 0;
    siguiente = NULL;
}

Neurona::~Neurona() //Destructor de la clase Neurona
{

}

void Neurona::agregarDato(int newId, float newVoltaje, int newPosicion_x, int newPosicion_y, int newRed, int newGreen, int newBlue)
{
    id = newId;
    voltaje = newVoltaje;
    posicion_x = newPosicion_x;
    posicion_y = newPosicion_y;
    red = newRed;
    green = newGreen;
    blue = newBlue;
}

QString Neurona::getId()
{
    return QString::number(id);
}

QString Neurona::getVoltaje()
{
    return QString::number(voltaje);
}

QString Neurona::getPosX()
{
    return QString::number(posicion_x);
}

QString Neurona::getPosY()
{
    return QString::number(posicion_y);
}

QString Neurona::getRed()
{
    return QString::number(red);
}

QString Neurona::getGreen()
{
    return QString::number(green);
}

QString Neurona::getBlue()
{
    return QString::number(blue);
}



//INICIO LISTA NEURONA

listaNeurona::listaNeurona()
{
    inicio = NULL;
    cont = 0;
}

listaNeurona::~listaNeurona()
{

}

bool listaNeurona::vacia()
{
    if(inicio == NULL)
        return true;
    return false;
}

int listaNeurona::cantidadNeuronas()
{
    return cont;
}

void listaNeurona::agregar_inicio(int newId, float newVoltaje, int newPosicion_x, int newPosicion_y, int newRed, int newGreen, int newBlue)
{
    Neurona *temp = new Neurona();
    temp->agregarDato(newId, newVoltaje, newPosicion_x, newPosicion_y, newRed, newGreen, newBlue);
    if(vacia())
    {
      inicio = temp;
    }
    else
    {
        temp->siguiente = inicio;
        inicio = temp;
    }
    cont++;
}

void listaNeurona::agregar_final(int newId, float newVoltaje, int newPosicion_x, int newPosicion_y, int newRed, int newGreen, int newBlue)
{
    Neurona *temp = new Neurona();
    temp->agregarDato(newId, newVoltaje, newPosicion_x, newPosicion_y, newRed, newGreen, newBlue);
    if(vacia())
    {
      inicio = temp;
    }
    else if(inicio->siguiente == NULL)
    {
        inicio->siguiente = temp;
    }
    else
    {
        Neurona *iter;
        iter = inicio;
        while(iter->siguiente != NULL)
        {
            iter = iter->siguiente;
        }
        iter->siguiente = temp;
    }
    cont++;
}

QString listaNeurona::mostrar()
{
    QString cadena;
    if(vacia())
    {
        cadena = "NO HAY NEURONAS";
    }
    else if(inicio->siguiente == NULL)
    {
        cadena = QString::fromUtf8("#1 ID: ") + inicio->getId() + QString::fromUtf8(", VOLTAJE: ") + inicio->getVoltaje() + QString::fromUtf8(", POSICION X: ") + inicio->getPosX() + QString::fromUtf8(", POSICION Y: ") + inicio->getPosY() + QString::fromUtf8(", RED: ") + inicio->getRed() + QString::fromUtf8(", GREEN: ") + inicio->getGreen() + QString::fromUtf8(", BLUE: ") + inicio->getBlue();
    }
    else
    {
        int i = 1;
        cadena = QString::fromUtf8("NEURONA #") + QString::number(i) + QString::fromUtf8(" ID: ") + inicio->getId() + QString::fromUtf8(", VOLTAJE: ") + inicio->getVoltaje() + QString::fromUtf8(", POSICION X: ") + inicio->getPosX() + QString::fromUtf8(", POSICION Y: ") + inicio->getPosY() + QString::fromUtf8(", RED: ") + inicio->getRed() + QString::fromUtf8(", GREEN: ") + inicio->getGreen() + QString::fromUtf8(", BLUE: ") + inicio->getBlue() + QString::fromUtf8("\n");
        Neurona *iter;
        iter = inicio;
        while(iter->siguiente != NULL)
        {
            i++;
            iter = iter->siguiente;
            cadena = cadena + QString::fromUtf8("NEURONA #") + QString::number(i) + QString::fromUtf8(" ID: ") + iter->getId() + QString::fromUtf8(", VOLTAJE: ") + iter->getVoltaje() + QString::fromUtf8(", POSICION X: ") + iter->getPosX() + QString::fromUtf8(", POSICION Y: ") + iter->getPosY() + QString::fromUtf8(", RED: ") + iter->getRed() + QString::fromUtf8(", GREEN: ") + iter->getGreen() + QString::fromUtf8(", BLUE: ") + iter->getBlue() + QString::fromUtf8("\n");
        }
    }
    return cadena;
}

void listaNeurona::guardar(string ruta)
{
    string newRuta = ruta;
    if(!vacia())
    {
        ofstream archivo(newRuta);
            if(archivo.is_open())
            {
                Neurona *tempG;
                tempG = inicio;
                while(tempG != NULL)
                {
                    archivo << tempG->getId().toStdString() << std::endl;
                    archivo << tempG->getVoltaje().toStdString() << std::endl;
                    archivo << tempG->getPosX().toStdString() << std::endl;
                    archivo << tempG->getPosY().toStdString() << std::endl;
                    archivo << tempG->getRed().toStdString() << std::endl;
                    archivo << tempG->getGreen().toStdString() << std::endl;
                    archivo << tempG->getBlue().toStdString() << std::endl;
                    tempG = tempG->siguiente;
                }
                archivo.close();
            }
            else
            {
                //AQUI VA UN POP UP! DE QUE HUBO ERROR EN APERTURA DE ARCHIVO
            }
    }
}

void listaNeurona::recuperar(string ruta)
{
    string newRuta = ruta;
    ifstream archivo(ruta);
    if(archivo.is_open())
    {
        string id;
        string voltaje;
        string posX;
        string posY;
        string red;
        string green;
        string blue;
        getline(archivo,id);
        while(id !="")
        {
            getline(archivo,voltaje);
            getline(archivo,posX);
            getline(archivo,posY);
            getline(archivo,red);
            getline(archivo,green);
            getline(archivo,blue);
            Neurona *temp = new Neurona();
            int newInt = stoi(id);
            std::stringstream out;
            out << std::fixed << std::setprecision(2) << std::stof(voltaje);
            float newVoltaje = std::stof(out.str());
            int newPosX = stoi(posX);
            int newPosY = stoi(posY);
            int newRed = stoi(red);
            int newGreen = stoi(green);
            int newBlue = stoi(blue);
            temp->agregarDato(newInt, newVoltaje, newPosX, newPosY, newRed, newGreen, newBlue);
            cont++;
            if(vacia())
            {
                inicio = temp;
            }
            else if(inicio->siguiente == NULL)
            {
                inicio->siguiente = temp;
            }
            else
            {
                Neurona *iter;
                iter = inicio;
                while(iter->siguiente != NULL)
                {
                    iter = iter->siguiente;
                }
                iter->siguiente = temp;
            }
            getline(archivo,id);
        }
        archivo.close();
    }
    else
    {
        //AQUI VA UN POP UP! DE QUE HUBO ERROR EN APERTURA DE ARCHIVO
    }
}

QString listaNeurona::devolverNeurona(int i)
{
    Neurona *iter;
    iter = inicio;
    int limite = i;
    int contador = 1;
    if(limite == 0)
    {

    }
    else if(limite == 1)
    {
        iter = iter->siguiente;
    }
    else
    {
        while(contador < limite)
        {
            iter = iter->siguiente;
            contador++;
        }
        iter = iter->siguiente;
    }
    QString cadena = iter->getId() + "." + iter->getVoltaje() + "." + iter->getPosX() + "." + iter->getPosY() + "." + iter->getRed() + "." + iter->getGreen() + "." + iter->getBlue();
    return cadena;
}

void listaNeurona::bubblesortId()
{
    int n = cont;
    cout << n << endl;
    if(n>1)
    {
        Neurona *temp, *temp2;
        temp = inicio;
        temp2 = temp->siguiente;
        cout << temp->getId().toInt() << endl;
        cout << temp2->getId().toInt() << endl;
        for(int i = 0; i < n-1; i++)
        {
            for(int j = 0; j < n-i-1; j++)
            {
                if(temp->getId().toInt() > temp2->getId().toInt())
                {
                    Neurona *temp3 = new Neurona();
                    temp3->agregarDato(temp2->getId().toInt(),temp2->getVoltaje().toFloat(),temp2->getPosX().toInt(),temp2->getPosY().toInt(),temp2->getRed().toInt(),temp2->getGreen().toInt(),temp2->getBlue().toInt());
                    temp2->agregarDato(temp->getId().toInt(),temp->getVoltaje().toFloat(),temp->getPosX().toInt(),temp->getPosY().toInt(),temp->getRed().toInt(),temp->getGreen().toInt(),temp->getBlue().toInt());
                    temp->agregarDato(temp3->getId().toInt(),temp3->getVoltaje().toFloat(),temp3->getPosX().toInt(),temp3->getPosY().toInt(),temp3->getRed().toInt(),temp3->getGreen().toInt(),temp3->getBlue().toInt());
                    delete temp3;
                }
                temp=temp2;
                temp2=temp2->siguiente;
            }
            temp = inicio;
            temp2 = temp->siguiente;
        }
    }
}

void listaNeurona::bubblesortVoltaje()
{
    int n = cont;
    cout << n << endl;
    if(n>1)
    {
        Neurona *temp, *temp2;
        temp = inicio;
        temp2 = temp->siguiente;
        cout << temp->getId().toInt() << endl;
        cout << temp2->getId().toInt() << endl;
        for(int i = 0; i < n-1; i++)
        {
            for(int j = 0; j < n-i-1; j++)
            {
                if(temp->getVoltaje().toFloat() > temp2->getVoltaje().toFloat())
                {
                    Neurona *temp3 = new Neurona();
                    temp3->agregarDato(temp2->getId().toInt(),temp2->getVoltaje().toFloat(),temp2->getPosX().toInt(),temp2->getPosY().toInt(),temp2->getRed().toInt(),temp2->getGreen().toInt(),temp2->getBlue().toInt());
                    temp2->agregarDato(temp->getId().toInt(),temp->getVoltaje().toFloat(),temp->getPosX().toInt(),temp->getPosY().toInt(),temp->getRed().toInt(),temp->getGreen().toInt(),temp->getBlue().toInt());
                    temp->agregarDato(temp3->getId().toInt(),temp3->getVoltaje().toFloat(),temp3->getPosX().toInt(),temp3->getPosY().toInt(),temp3->getRed().toInt(),temp3->getGreen().toInt(),temp3->getBlue().toInt());
                    delete temp3;
                }
                temp=temp2;
                temp2=temp2->siguiente;
            }
            temp = inicio;
            temp2 = temp->siguiente;
        }
    }
}
//FINAL DE LISTA
listaNeurona LN;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertarInicio_clicked()
{
    QString id = ui->datoId->text();
    QString voltaje = ui->datoVoltaje->text();
    QString posicion_x = ui->datoPosicionX->text();
    QString posicion_y = ui->datoPosicionY->text();
    QString red = ui->datoRed->text();
    QString green = ui->datoGreen->text();
    QString blue = ui->datoBlue->text();
    LN.agregar_inicio(id.toInt(), voltaje.toFloat(), posicion_x.toInt(), posicion_y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    ui->datoId->clear();
    ui->datoVoltaje->clear();
    ui->datoPosicionX->clear();
    ui->datoPosicionY->clear();
    ui->datoRed->clear();
    ui->datoGreen->clear();
    ui->datoBlue->clear();
}

void MainWindow::on_insertarFinal_clicked()
{
    QString id = ui->datoId->text();
    QString voltaje = ui->datoVoltaje->text();
    QString posicion_x = ui->datoPosicionX->text();
    QString posicion_y = ui->datoPosicionY->text();
    QString red = ui->datoRed->text();
    QString green = ui->datoGreen->text();
    QString blue = ui->datoBlue->text();
    LN.agregar_final(id.toInt(), voltaje.toFloat(), posicion_x.toInt(), posicion_y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    ui->datoId->clear();
    ui->datoVoltaje->clear();
    ui->datoPosicionX->clear();
    ui->datoPosicionY->clear();
    ui->datoRed->clear();
    ui->datoGreen->clear();
    ui->datoBlue->clear();
}


void MainWindow::on_mostrarNeuronas_clicked()
{
    ui->mallaMostrar->clear();
    ui->mallaMostrar->insertPlainText(LN.mostrar());
}


void MainWindow::on_actionAbrir_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this,"Abrir archivo", ".","archivos (*.txt)");
    std::string file=Filename.toStdString();
    LN.recuperar(file);
}


void MainWindow::on_actionGuardar_triggered()
{
    QString Filename = QFileDialog::getSaveFileName(this,"Guardar archivo", ".","archivos (*.txt)");
    std::string file=Filename.toStdString();
    LN.guardar(file);
}


void MainWindow::on_BotonMostrardelatabla_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID", "VOLTAJE", "POSICIÓN X", "POSICIÓN Y", "RED", "GREEN", "BLUE"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(LN.cantidadNeuronas());
    for(int i=0;i<LN.cantidadNeuronas();i++) //Aqui crearemos el QTableWidget
    {
        QStringList list = LN.devolverNeurona(i).split(".");
        QTableWidgetItem *id = new QTableWidgetItem(list[0]);
        QTableWidgetItem *v = new QTableWidgetItem(list[1]);
        QTableWidgetItem *x = new QTableWidgetItem(list[2]);
        QTableWidgetItem *y = new QTableWidgetItem(list[3]);
        QTableWidgetItem *r = new QTableWidgetItem(list[4]);
        QTableWidgetItem *g = new QTableWidgetItem(list[5]);
        QTableWidgetItem *b = new QTableWidgetItem(list[6]);
        //Mostrar en la TableWidget
        ui->tableWidget->setItem(i,0,id);
        ui->tableWidget->setItem(i,1,v);
        ui->tableWidget->setItem(i,2,x);
        ui->tableWidget->setItem(i,3,y);
        ui->tableWidget->setItem(i,4,r);
        ui->tableWidget->setItem(i,5,g);
        ui->tableWidget->setItem(i,6,b);
    }
}


void MainWindow::on_BotonBuscardelatabla_clicked()
{
    int cantidadN;
    cantidadN = LN.cantidadNeuronas();
    ui->tableWidget->clearContents();
    QString idLineEdit = ui->idBusqueda->text(); //Valor añadido por el usuario
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID", "VOLTAJE", "POSICIÓN X", "POSICIÓN Y", "RED", "GREEN", "BLUE"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(cantidadN);
    int row;
    row = 0;
    for(int i=0;i<cantidadN;i++) //Aqui crearemos el QTableWidget
    {
        QStringList list = LN.devolverNeurona(i).split(".");
        QTableWidgetItem *id = new QTableWidgetItem(list[0]);
        QTableWidgetItem *v = new QTableWidgetItem(list[1]);
        QTableWidgetItem *x = new QTableWidgetItem(list[2]);
        QTableWidgetItem *y = new QTableWidgetItem(list[3]);
        QTableWidgetItem *r = new QTableWidgetItem(list[4]);
        QTableWidgetItem *g = new QTableWidgetItem(list[5]);
        QTableWidgetItem *b = new QTableWidgetItem(list[6]);
        //Mostrar en la TableWidget
        if(list[0] == idLineEdit)
        {
            ui->tableWidget->setItem(row,0,id);
            ui->tableWidget->setItem(row,1,v);
            ui->tableWidget->setItem(row,2,x);
            ui->tableWidget->setItem(row,3,y);
            ui->tableWidget->setItem(row,4,r);
            ui->tableWidget->setItem(row,5,g);
            ui->tableWidget->setItem(row,6,b);
            row++;
        }
    }
    ui->idBusqueda->clear();
}

void MainWindow::on_dibujar_clicked()
{
    QPen pen;
    pen.setWidth(2);
    int cantidadN = LN.cantidadNeuronas();
    for(int i=0;i<cantidadN;i++)
    {
        QStringList list = LN.devolverNeurona(i).split(".");
        QColor color(list[4].toInt() ,list[5].toInt() ,list[6].toInt()); //Creamos un color con los datos de la neurona
        pen.setColor(color);
        escena.addEllipse(list[2].toInt(), list[3].toInt(), list[1].toFloat(), list[1].toFloat(), pen);
        ui->graphicsView->setScene(&escena);
    }
}


void MainWindow::on_limpiar_clicked()
{
    escena.clear();
}


void MainWindow::on_sort_clicked()
{
    QString cadena = "ORDENADO POR ID\n";
    LN.bubblesortId();
    ui->mallaMostrar->clear();
    ui->mallaMostrar->insertPlainText(cadena);
    ui->mallaMostrar->insertPlainText(LN.mostrar());
}


void MainWindow::on_sortV_clicked()
{
    QString cadena = "ORDENADO POR VOLTAJE\n";
    LN.bubblesortVoltaje();
    ui->mallaMostrar->clear();
    ui->mallaMostrar->insertPlainText(cadena);
    ui->mallaMostrar->insertPlainText(LN.mostrar());
}


void MainWindow::on_BotonMostrarSortID_clicked()
{
    LN.bubblesortId();
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID", "VOLTAJE", "POSICIÓN X", "POSICIÓN Y", "RED", "GREEN", "BLUE"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(LN.cantidadNeuronas());
    for(int i=0;i<LN.cantidadNeuronas();i++) //Aqui crearemos el QTableWidget
    {
        QStringList list = LN.devolverNeurona(i).split(".");
        QTableWidgetItem *id = new QTableWidgetItem(list[0]);
        QTableWidgetItem *v = new QTableWidgetItem(list[1]);
        QTableWidgetItem *x = new QTableWidgetItem(list[2]);
        QTableWidgetItem *y = new QTableWidgetItem(list[3]);
        QTableWidgetItem *r = new QTableWidgetItem(list[4]);
        QTableWidgetItem *g = new QTableWidgetItem(list[5]);
        QTableWidgetItem *b = new QTableWidgetItem(list[6]);
        //Mostrar en la TableWidget
        ui->tableWidget->setItem(i,0,id);
        ui->tableWidget->setItem(i,1,v);
        ui->tableWidget->setItem(i,2,x);
        ui->tableWidget->setItem(i,3,y);
        ui->tableWidget->setItem(i,4,r);
        ui->tableWidget->setItem(i,5,g);
        ui->tableWidget->setItem(i,6,b);
    }
}


void MainWindow::on_BotonMostrarSortV_clicked()
{
    LN.bubblesortVoltaje();
    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID", "VOLTAJE", "POSICIÓN X", "POSICIÓN Y", "RED", "GREEN", "BLUE"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(LN.cantidadNeuronas());
    for(int i=0;i<LN.cantidadNeuronas();i++) //Aqui crearemos el QTableWidget
    {
        QStringList list = LN.devolverNeurona(i).split(".");
        QTableWidgetItem *id = new QTableWidgetItem(list[0]);
        QTableWidgetItem *v = new QTableWidgetItem(list[1]);
        QTableWidgetItem *x = new QTableWidgetItem(list[2]);
        QTableWidgetItem *y = new QTableWidgetItem(list[3]);
        QTableWidgetItem *r = new QTableWidgetItem(list[4]);
        QTableWidgetItem *g = new QTableWidgetItem(list[5]);
        QTableWidgetItem *b = new QTableWidgetItem(list[6]);
        //Mostrar en la TableWidget
        ui->tableWidget->setItem(i,0,id);
        ui->tableWidget->setItem(i,1,v);
        ui->tableWidget->setItem(i,2,x);
        ui->tableWidget->setItem(i,3,y);
        ui->tableWidget->setItem(i,4,r);
        ui->tableWidget->setItem(i,5,g);
        ui->tableWidget->setItem(i,6,b);
    }
}


void MainWindow::on_btnBusqID_clicked()
{
    ui->mallaGrafNeuronas->setEnabled(true);
    ui->mallaGrafNeuronas->clear();
    QString idNeurona = ui->busqID->text(); //Valor añadido por el usuario
    ui->busqID->clear();
    int contTemp = 1;
    if(idNeurona != "")
    {
        for(int i=0;i<LN.cantidadNeuronas(); i++)
        {
            contTemp++;
            QStringList list = LN.devolverNeurona(i).split(".");
            if(list[0] == idNeurona)
            {
                ui->mallaGrafNeuronas->clear();
                ui->mallaGrafNeuronas->insertPlainText("ID: " + list[0] + "\n" + "Voltaje: " + list[1] + "\n" + "Posición X: " + list[2] + "\n" + "Posición Y: " + list[3] + "\n" + "Red: " + list[4] + "\n" + "Green: " + list[5] + "\n" + "Blue: " + list[6]);
                QPen pen;
                pen.setWidth(2);
                escena.clear();
                QColor color(list[4].toInt() ,list[5].toInt() ,list[6].toInt()); //Creamos un color con los datos de la neurona
                pen.setColor(color);
                escena.addEllipse(list[2].toInt(), list[3].toInt(), list[1].toFloat(), list[1].toFloat(), pen);
                QString textito = "("+list[2] +"," + list[3]+")";
                QGraphicsTextItem *texto = new QGraphicsTextItem(textito); //Instancia para el texto
                QFont fuente("Arial",12); //Creamos el objeto fuente
                texto->setFont(fuente); //Ingresamos la fuente a el objeto texto
                texto->setDefaultTextColor(QColor(Qt::red));
                texto->setPos(list[2].toFloat()+20, list[3].toFloat()+20);// Establecer la posición del objeto de texto en la escena
                escena.addItem(texto);
                ui->graphicsView->setScene(&escena);
                break;
            }
        }
        if(contTemp>LN.cantidadNeuronas())
        {
            ui->mallaGrafNeuronas->insertPlainText("NO EXISTE UNA\nNEURONA CON\nESE ID");
        }
    }
    else
    {
        ui->mallaGrafNeuronas->insertPlainText("NO INGRESO ID, \nPOR FAVOR INGRESELO");
    }
    ui->mallaGrafNeuronas->setEnabled(false);
}


void MainWindow::on_mallaMostrar_blockCountChanged(int newBlockCount)
{

}


void MainWindow::on_bruteForceGraphic_clicked()
{
    if(LN.cantidadNeuronas() > 0)
    {
        escena.clear();
    }
}

