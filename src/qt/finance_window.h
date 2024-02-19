#ifndef FINANCE_WINDOW_H
#define FINANCE_WINDOW_H

#include <QComboBox>
#include <QDialog>
#include <QMessageBox>
#include <QRadioButton>

extern "C" {
#include "../modules/smart_calc.h"
}

namespace Ui {
class Finance_window;
}

class Finance_window : public QDialog {
  Q_OBJECT

 public:
  explicit Finance_window(QWidget *parent = nullptr);
  ~Finance_window();

 private:
  Ui::Finance_window *ui;

  QWidget *creditWidgetGroup;
  QWidget *debitWidgetGroup;

  int cap = 0;
  int term_per = 12;
  int freq_payment = 12;

  void updateInvestFreq(int index);
  void updateInvestTerm(int index);
  QComboBox *comboBox_invest_freq;
  QComboBox *comboBox_invest_term;

 private slots:
  void on_creditButton_clicked();
  void on_debitButton_clicked();
  void onButton1Clicked();
  void onButton2Clicked();

  void on_calculate_credit_clicked();
  void on_calculate_clear_clicked();
  void on_calculate_invest_clicked();
  void on_calculate_clear_invest_clicked();
};

#endif  // FINANCE_WINDOW_H
