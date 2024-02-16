#include "smart_calc.h"

void credit(double amount, int month, double percent, int c_type, char* res_monthly, char* res_last, char* res_overpay, char* res_total) {
    double m_percent = percent / (100 * 12);
    double total = 0;
    double overpay = 0;
    double month_payment = 0;

    // Аннуитетный платеж
    if (c_type == 1) {
        month_payment = amount * (m_percent / (1 - pow((1 + m_percent), -month)));
        total = month_payment * month;
        overpay = total - amount;

        snprintf(res_monthly, 50, "%.2f", month_payment); // предполагаем, что размер буфера достаточный, например 256
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
            } else if (i == month - 1){
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
