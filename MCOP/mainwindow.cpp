#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pricer.h"
#include <QMessageBox>
#include <future>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Monte Carlo Options Pricer");

    // Initialize QLabel objects from the UI
    // These are directly accessible through the ui pointer
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::removeCommas(QString input) {
    return input.remove(',');
}

void MainWindow::on_calculateButton_clicked() {
    double S0 = removeCommas(ui->stockPriceLineEdit->text()).toDouble();
    double K = removeCommas(ui->strikePriceLineEdit->text()).toDouble();
    double r = removeCommas(ui->interestRateLineEdit->text()).toDouble();
    double sigma = removeCommas(ui->volatilityLineEdit->text()).toDouble();
    double T = removeCommas(ui->timeToMaturityLineEdit->text()).toDouble();
    int numSimulations = removeCommas(ui->numSimulationsLineEdit->text()).toInt();

    // Change this if you want to increase the number of simulation possible.
    if (numSimulations > 99000000) {
        QMessageBox::warning(this, "Input Error", "Number of simulations is too high. Please enter a value less than or equal to 99,000,000.");
        return;
    }

    // Run MC in a separate thread (Basically multithreading)
    std::future<double> callPriceFuture = std::async(std::launch::async, [=] {
        Pricer pricer(S0, K, r, sigma, T, numSimulations);
        return pricer.calculateOptionPrice(true);
    });

    std::future<double> putPriceFuture = std::async(std::launch::async, [=] {
        Pricer pricer(S0, K, r, sigma, T, numSimulations);
        return pricer.calculateOptionPrice(false);
    });

    std::future<Contract> callGreeksFuture = std::async(std::launch::async, [=] {
        Pricer pricer(S0, K, r, sigma, T, numSimulations);
        return pricer.calculateGreeks(true);
    });

    std::future<Contract> putGreeksFuture = std::async(std::launch::async, [=] {
        Pricer pricer(S0, K, r, sigma, T, numSimulations);
        return pricer.calculateGreeks(false);
    });


    double callPrice = callPriceFuture.get();
    double putPrice = putPriceFuture.get();

    Contract callGreeks = callGreeksFuture.get();
    Contract putGreeks = putGreeksFuture.get();

    QString callPriceText = QString("Call Option Price: %1").arg(callPrice);
    QString putPriceText = QString("Put Option Price: %1").arg(putPrice);
    QString callGreeksText = QString("Call Option Greeks:\nDelta: %1\nGamma: %2\nTheta: %3\nVega: %4\nRho: %5")
                                 .arg(callGreeks.delta)
                                 .arg(callGreeks.gamma)
                                 .arg(callGreeks.theta)
                                 .arg(callGreeks.vega)
                                 .arg(callGreeks.rho);
    QString putGreeksText = QString("Put Option Greeks:\nDelta: %1\nGamma: %2\nTheta: %3\nVega: %4\nRho: %5")
                                .arg(putGreeks.delta)
                                .arg(putGreeks.gamma)
                                .arg(putGreeks.theta)
                                .arg(putGreeks.vega)
                                .arg(putGreeks.rho);

    ui->callPriceLabel->setText(callPriceText);
    ui->putPriceLabel->setText(putPriceText);
    ui->callGreeksLabel->setText(callGreeksText);
    ui->putGreeksLabel->setText(putGreeksText);
}
