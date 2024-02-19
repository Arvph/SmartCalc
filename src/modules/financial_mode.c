#include "smart_calc.h"

void credit(double amount, int month, double percent, int c_type,
            char* res_monthly, char* res_last, char* res_overpay,
            char* res_total) {
  double m_percent = percent / (100 * 12);
  double total = 0;
  double overpay = 0;
  double month_payment = 0;

  // Аннуитетный платеж
  if (c_type == 1) {
    month_payment = amount * (m_percent / (1 - pow((1 + m_percent), -month)));
    total = month_payment * month;
    overpay = total - amount;

    snprintf(res_monthly, 50, "%.2f", month_payment);
    snprintf(res_overpay, 50, "%.2f", overpay);
    snprintf(res_total, 50, "%.2f", total);
  }
  // Дифференцированный платеж
  else if (c_type == 0) {
    double count = 0;
    double month_principal = amount / month;
    double first_month = 0;
    double last_month = 0;

    for (int i = 0; i < month; i++) {
      double interest = (amount - (month_principal * i)) * m_percent;
      count += interest;
      double monthly_payment = month_principal + interest;
      if (i == 0) {
        first_month = monthly_payment;
      } else if (i == month - 1) {
        last_month = monthly_payment;
      }
    }
    overpay = count;
    total = amount + overpay;

    snprintf(res_monthly, 50, "%.2f", first_month);
    snprintf(res_last, 50, "%.2f", last_month);
    snprintf(res_overpay, 50, "%.2f", overpay);
    snprintf(res_total, 50, "%.2f", total);
  }
}

int invest_term(int term, int term_per) { return term * term_per; }

double invest_rate(double rate) { return rate * 0.01; }

double invest_total(double amount, int term, int term_per, double int_rate,
                    int frq_pay, bool capitalization, double replenishments,
                    double withdraws) {
  double interest = invest_rate(int_rate);
  double amount_buff = amount;
  double total_earn = 0;
  int period = invest_term(term, term_per);

  if (period >= frq_pay) {
    for (int m = 1; m <= period; m++) {
      double buff_of_earn = 0;
      if (frq_pay == 1) {
        buff_of_earn = amount_buff * interest / 12;
      } else if (frq_pay == 12 && m % 12 == 0) {
        buff_of_earn = amount_buff * interest;
      }
      amount_buff = amount_buff + replenishments - withdraws;
      if (capitalization) {
        amount_buff += buff_of_earn;
      }
      total_earn += buff_of_earn;
    }
  }
  return total_earn;
}

double invest_tax_amount(double total_amount, double tax_rate) {
  double tax = invest_rate(tax_rate);
  return total_amount * tax;
}

double invest_total_deposit(double total_amount, double amount,
                            double tax_amount, int term, int term_per,
                            double replenishments, double withdraws) {
  int period = invest_term(term, term_per);
  double repl_and_wtdrw = (replenishments - withdraws) * period;
  return amount + total_amount - tax_amount + repl_and_wtdrw;
}

void deposit(double amount, int term, int term_per, double percent, double tax,
             int frequency_payment, int capitalization, double replenishment,
             double withdrawal, char* final_income, char* tax_sum,
             char* total) {
  double total_earn =
      invest_total(amount, term, term_per, percent, frequency_payment,
                   capitalization, replenishment, withdrawal);
  double tax_amount = invest_tax_amount(total_earn, tax);
  double total_deposit =
      invest_total_deposit(total_earn, amount, tax_amount, term, term_per,
                           replenishment, withdrawal);

  sprintf(final_income, "%.2f", total_earn);
  sprintf(tax_sum, "%.2f", tax_amount);
  sprintf(total, "%.2f", total_deposit);
}
