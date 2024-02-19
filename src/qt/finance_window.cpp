#include "finance_window.h"

#include "ui_finance_window.h"

Finance_window::Finance_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::Finance_window) {
  ui->setupUi(this);

  setWindowTitle("Financial");
  setFixedSize(width(), height());

  // Показываем виджет по умолчанию
  ui->creditWidget->setVisible(true);
  ui->debitWidget->setVisible(false);

  // Подключение сигналов и слотов
  connect(ui->creditButton, &QPushButton::clicked, this,
          &Finance_window::on_creditButton_clicked);
  connect(ui->debitButton, &QPushButton::clicked, this,
          &Finance_window::on_debitButton_clicked);

  connect(ui->creditButton, &QPushButton::clicked, this,
          &Finance_window::onButton1Clicked);
  connect(ui->debitButton, &QPushButton::clicked, this,
          &Finance_window::onButton2Clicked);

  connect(ui->comboBox_invest_freq,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Finance_window::updateInvestFreq);
  connect(ui->comboBox_invest_term,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Finance_window::updateInvestTerm);

  updateInvestFreq(ui->comboBox_invest_freq->currentIndex());
  updateInvestTerm(ui->comboBox_invest_term->currentIndex());

  // Установка настроек кнопок
  ui->creditButton->setAutoDefault(false);
  ui->debitButton->setAutoDefault(false);

  // Подключение comboBox и stackedWidget
  connect(ui->comboBox_payment, SIGNAL(currentIndexChanged(int)),
          ui->stackedWidget_result, SLOT(setCurrentIndex(int)));
}

Finance_window::~Finance_window() { delete ui; }

void Finance_window::onButton1Clicked() {
  ui->creditButton->setStyleSheet(
      "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 "
      "#FF7832, stop: 1 #FF9739); color: white; border: 1px solid gray;");
  ui->debitButton->setStyleSheet(
      "background-color: rgb(215, 151, 57); color: white; border: 1px solid "
      "gray;");
}

void Finance_window::onButton2Clicked() {
  ui->creditButton->setStyleSheet(
      "background-color: rgb(215, 151, 57); color: white; border: 1px solid "
      "gray;");
  ui->debitButton->setStyleSheet(
      "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 "
      "#FF7832, stop: 1 #FF9739); color: white; border: 1px solid gray;");
}

void Finance_window::on_creditButton_clicked() {
  ui->creditWidget->setVisible(true);  // Показать виджеты для кредита
  ui->debitWidget->setVisible(false);  // Скрыть виджеты для дебета
}

void Finance_window::on_debitButton_clicked() {
  ui->creditWidget->setVisible(false);  // Скрыть виджеты для кредита
  ui->debitWidget->setVisible(true);  // Показать виджеты для дебета
}

void Finance_window::on_calculate_credit_clicked() {
  bool amountOk, periodOk, percentOk;
  double amount = ui->credit_amount->text().toDouble(&amountOk);
  double period = ui->credit_period->text().toDouble(&periodOk);
  double percent = ui->credit_rate->text().toDouble(&percentOk);

  if (!amountOk || !periodOk || !percentOk) {
    // QMessageBox::warning(this, "Error", "Please enter valid numeric
    // values.");
    QString errorMessage =
        "Please enter valid numeric values for the following fields:\n";
    if (!amountOk) errorMessage += "- Credit amount\n";
    if (!periodOk) errorMessage += "- Credit term\n";
    if (!percentOk) errorMessage += "- Credit rate\n";
    QMessageBox::warning(this, "Error", errorMessage);
    return;
  }

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

void Finance_window::on_calculate_clear_clicked() {
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

void Finance_window::on_calculate_invest_clicked() {
  bool amountOk, periodOk, rateOk, tax_rateOk = true, replenishmentOk = true,
                                   withdrawalOk = true;
  double amount = ui->invest_amount->text().toDouble(&amountOk);
  int period = ui->invest_period->text().toInt(&periodOk);
  double rate = ui->invest_rate->text().toDouble(&rateOk);
  double tax_rate = ui->tax_rate->text().isEmpty()
                        ? 0
                        : ui->tax_rate->text().toDouble(&tax_rateOk);

  double replenishment =
      ui->invest_replenishment->text().isEmpty()
          ? 0
          : ui->invest_replenishment->text().toDouble(&replenishmentOk);
  double withdrawal =
      ui->invest_withdrawal->text().isEmpty()
          ? 0
          : ui->invest_withdrawal->text().toDouble(&withdrawalOk);

  if (!amountOk || !periodOk || !rateOk ||
      (ui->tax_rate->text().isEmpty() && !tax_rateOk) ||
      (ui->invest_replenishment->text().isEmpty() && !replenishmentOk) ||
      (ui->invest_withdrawal->text().isEmpty() && !withdrawalOk)) {
    QString errorMessage =
        "Please enter valid numeric values for the following fields:\n";
    if (!amountOk) errorMessage += "- Investment amount\n";
    if (!periodOk) errorMessage += "- Investment period\n";
    if (!rateOk) errorMessage += "- Investment rate\n";
    if (ui->tax_rate->text().isEmpty() && !tax_rateOk)
      errorMessage += "- Tax rate\n";
    if (ui->invest_replenishment->text().isEmpty() && !replenishmentOk)
      errorMessage += "- Replenishment\n";
    if (ui->invest_withdrawal->text().isEmpty() && !withdrawalOk)
      errorMessage += "- Withdrawal\n";

    QMessageBox::warning(this, "Error", errorMessage);
    return;
  }

  const int bufferSize = 50;
  char final_income[bufferSize];
  char tax_sum[bufferSize];
  char total[bufferSize];

  deposit(amount, period, term_per, rate, tax_rate, freq_payment, cap,
          replenishment, withdrawal, final_income, tax_sum, total);

  ui->invest_income->setText(QString(final_income));
  ui->invest_tax_sum->setText(QString(tax_sum));
  ui->invest_total->setText(QString(total));
}

void Finance_window::updateInvestFreq(int index) {
  if (index == 0) {
    cap = 0;
    freq_payment = 12;
  } else if (index == 1) {
    cap = 1;
    freq_payment = 12;
  } else if (index == 2) {
    cap = 1;
    freq_payment = 1;
  }
}

void Finance_window::updateInvestTerm(int index) {
  if (index == 0) {
    term_per = 1;
  } else if (index == 1) {
    term_per = 12;
  }
}
void Finance_window::on_calculate_clear_invest_clicked() {
  ui->invest_amount->clear();
  ui->invest_period->clear();
  ui->invest_rate->clear();
  ui->tax_rate->clear();

  ui->invest_replenishment->clear();
  ui->invest_withdrawal->clear();

  ui->invest_income->setText("");
  ui->invest_tax_sum->setText("");
  ui->invest_total->setText("");
}
