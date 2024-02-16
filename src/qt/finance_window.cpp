#include "finance_window.h"
#include "ui_finance_window.h"

Finance_window::Finance_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Finance_window)
{
    ui->setupUi(this);

    // Показываем виджет по умолчанию
    ui->creditWidget->setVisible(true);
    ui->debitWidget->setVisible(false);

    // Подключение сигналов и слотов
    connect(ui->creditButton, &QPushButton::clicked, this, &Finance_window::on_creditButton_clicked);
    connect(ui->debitButton, &QPushButton::clicked, this, &Finance_window::on_debitButton_clicked);

    connect(ui->creditButton, &QPushButton::clicked, this, &Finance_window::onButton1Clicked);
    connect(ui->debitButton, &QPushButton::clicked, this, &Finance_window::onButton2Clicked);

    // Установка настроек кнопок
    ui->creditButton->setAutoDefault(false);
    ui->debitButton->setAutoDefault(false);

    // Подключение comboBox и stackedWidget
    connect(ui->comboBox_payment, SIGNAL(currentIndexChanged(int)), ui->stackedWidget_result, SLOT(setCurrentIndex(int)));
}

Finance_window::~Finance_window()
{
    delete ui;
}


void Finance_window::onButton1Clicked() {
    ui->creditButton->setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #FF7832, stop: 1 #FF9739); color: white; border: 1px solid gray;");
    ui->debitButton->setStyleSheet("background-color: rgb(215, 151, 57); color: white; border: 1px solid gray;");
}

void Finance_window::onButton2Clicked() {
    ui->creditButton->setStyleSheet("background-color: rgb(215, 151, 57); color: white; border: 1px solid gray;");
    ui->debitButton->setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #FF7832, stop: 1 #FF9739); color: white; border: 1px solid gray;");
}



void Finance_window::on_creditButton_clicked() {
    ui->creditWidget->setVisible(true); // Показать виджеты для кредита
    ui->debitWidget->setVisible(false); // Скрыть виджеты для дебета
}

void Finance_window::on_debitButton_clicked() {
    ui->creditWidget->setVisible(false); // Скрыть виджеты для кредита
    ui->debitWidget->setVisible(true);  // Показать виджеты для дебета
}



// void Finance_window::on_creditButton_clicked() {
//     creditWidgetGroup->setVisible(true); // Показать виджеты для кредита
//     debitWidgetGroup->setVisible(false); // Скрыть виджеты для дебета
// }

// void Finance_window::on_debitButton_clicked() {
//     creditWidgetGroup->setVisible(false); // Скрыть виджеты для кредита
//     debitWidgetGroup->setVisible(true);  // Показать виджеты для дебета
// }


void Finance_window::on_calculate_credit_clicked()
{
    bool amountOk, periodOk, percentOk;
    double amount = ui->credit_amount->text().toDouble(&amountOk);
    double period = ui->credit_period->text().toDouble(&periodOk);
    double percent = ui->credit_rate->text().toDouble(&percentOk);

    if (!amountOk || !periodOk || !percentOk) {
        QMessageBox::warning(this, "Error", "Please enter valid numeric values.");
        return;
    }

    int c_type = (ui->comboBox_payment->currentText() == "Annuity") ? 1 : 0;

    const int bufferSize = 50;
    char monthly[bufferSize];
    char last[bufferSize];
    char overpay[bufferSize];
    char total[bufferSize];

    credit(amount, period, percent, 1, monthly, last, overpay, total);
    ui->credit_payment_an->setText(QString(monthly));
    ui->credir_overpay_an->setText(QString(overpay));
    ui->credi_total_an->setText(QString(total));

    credit(amount, period, percent, 0, monthly, last, overpay, total);
    ui->credit_first_d->setText(QString(monthly));
    ui->credit_last_d->setText(QString(last));
    ui->credir_overpay_d->setText(QString(overpay));
    ui->credi_total_d->setText(QString(total));
}

void Finance_window::on_calculate_clear_clicked()
{
    ui->credit_amount->clear();
    ui->credit_period->clear();
    ui->credit_rate->clear();

    ui->credit_payment_an->setText("");
    ui->credir_overpay_an->setText("");
    ui->credi_total_an->setText("");

    ui->credit_first_d->setText("");
    ui->credit_last_d->setText("");
    ui->credir_overpay_d->setText("");
    ui->credi_total_d->setText("");
}

