#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pricer.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Monte Carlo Options Pricer");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calculateButton_clicked() {
    double S0 = ui->stockPriceLineEdit->text().toDouble();
    double K = ui->strikePriceLineEdit->text().toDouble();
    double r = ui->interestRateLineEdit->text().toDouble();
    double sigma = ui->volatilityLineEdit->text().toDouble();
    double T = ui->timeToMaturityLineEdit->text().toDouble();
    int numSimulations = ui->numSimulationsLineEdit->text().toInt();

    // Validate the number of simulations
    if (numSimulations > 1000000) {
        QMessageBox::warning(this, "Input Error", "Number of simulations is too high. Please enter a value less than or equal to 1,000,000.");
        return;
    }

    double callPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, true);
    double putPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, false);

    QString resultText = QString("Call Option Price: %1\nPut Option Price: %2").arg(callPrice).arg(putPrice);
    ui->statusbar->showMessage(resultText);
}
