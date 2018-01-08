#include <QMessageBox>
#include <cstdio>
#include <string>

#include "MainWindow.h"
#include "3rdparty/ClientSocket.h"
#include "3rdparty/SocketException.h"

MainWindow::MainWindow(QDialog* parent)
    : QDialog(parent), ui{std::make_unique<Ui::MainWindow>()}
{
    ui->setupUi(this);
}

void MainWindow::wake()
{
    QString mac = ui->mac_field->text();
    mac = mac.toUpper();
    ui->mac_field->setText(mac);
    
    QString broad = ui->broad_field->text();
    
    // Parse/validate MAC
    if (mac.length() != 17) {
        QMessageBox::warning(this, tr("Warning"), tr("Invalid MAC Address"));
        return;
    }else{
        for (int i=2; i<=14; i+=3){
            if (mac[i] != ":") {
                QMessageBox::warning(this, tr("Warning"), tr("Invalid MAC Address"));
                return;
            }
        }
    }
    
    // QString to hex
    unsigned char macaddress[6];
    sscanf(mac.toStdString().c_str(), 
           "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &macaddress[0],
           &macaddress[1],
           &macaddress[2],
           &macaddress[3],
           &macaddress[4],
           &macaddress[5]);
    
    // Build the packet
    std::string packet;
    packet.reserve(102);
    for (int i=0;i<6;++i) {
        packet.push_back(0xff);
    }
    for (int i=0; i<16; ++i) {
        for (unsigned int j=0; j<6; ++j) {
            packet.push_back(macaddress[j]);
        }
    }

    // Create socket and send
    try {
        ClientSocket client_socket ( broad.toStdString().c_str(), 7 ); // Port 7, but could be 9
        client_socket << packet;
    }catch (SocketException& e) {
        QMessageBox::warning(this, tr("Warning"), tr(e.description().c_str()));
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {  
        this->wake();
    }
}