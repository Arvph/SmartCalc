#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // added by me
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_open_br, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_close_br, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_extent, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// added by me
void MainWindow::digits_numbers(){

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button) {
        QString button_text = button->text();
        QString current_text = ui->result_line->text();
        int textLength = current_text.length();

        if (br_check(button_text)){
            if (textLength==1 && current_text=="0"){
                current_text.chop(1);
            } else if (textLength==2 && current_text=="-0"){
                current_text.chop(1);
            }
            ui->result_line->setText(current_text + button_text + '(');
        } else if (is_digit(button_text[0])) {
            // операции с цифрами
            if (textLength==1 && current_text=="0" && button_text!="."){
               current_text.chop(1);
            }
            ui->result_line->setText(current_text + button_text);
        } else if (oprt_check(button_text[0])) {
            if (!current_text.isEmpty() && oprt_check(current_text.at(textLength-1))) {
                current_text.chop(1);
            } else if (!current_text.isEmpty() && current_text.at(textLength-1) == '(') {
                return;
            }
            ui->result_line->setText(current_text + button_text);

        } else if (button_text=="mod"){
            if (oprt_check(current_text.at(textLength-1))){
                current_text.chop(1);
            } else if (current_text.at(textLength-1)!='('){
                ui->result_line->setText(current_text + '%');
            }
        }else if (button_text[0]=='('){
            if (oprt_check(current_text.at(textLength-1))){
                ui->result_line->setText(current_text + button_text);
            }
            return;
        } else if (button_text[0]==')'){
            if (count_closed_br(current_text)){
                ui->result_line->setText(current_text + button_text);
            }
            return;
        } else {
            ui->result_line->setText(current_text + button_text);
        }
    }
}

bool MainWindow::oprt_check(QChar ch) {
    return QString("+-*/^%").contains(ch);
}

bool MainWindow::is_digit(QChar ch){
    return (ch>='0' && ch <= '9') || ch <= '.';
}

bool MainWindow::br_check(QString ch){
    bool flag = false;
    if (ch=="sin" || ch=="cos" || ch=="tan"){
        flag = true;
    } else  if (ch=="asin" || ch=="acos" || ch=="atan"){
        flag = true;
    } else  if (ch=="ln" || ch=="log" || ch=="sqrt"){
        flag = true;
    }
    return flag;
}


bool MainWindow::count_closed_br(const QString& str) {
    int close = 0;
    int open = 0;

    for (int i = 0; i < str.length(); ++i) {
        if (str.at(i) == ')') {
            close++;
        } else if (str.at(i) == '(') {
            open++;
        }
    }
    return open > close;
}

void MainWindow::on_pushButton_point_clicked() {
    QString currentText = ui->result_line->text();
    if (isPointAllowed(currentText)) {
        ui->result_line->setText(currentText + ".");
    }
}

bool MainWindow::isPointAllowed(const QString& text) {
    int length = text.length();
    if (length == 0)
        return true;

    QChar lastChar = text[length - 1];
    if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/')
        return true;

    // Проверяем, есть ли уже точка в текущем числе
    int i = length - 1;
    while (i >= 0) {
        if (text[i] == '.')
            return false; // Точка уже присутствует в текущем числе
        if (!text[i].isDigit())
            break; // Достигнут нецифровой символ, текущее число закончилось
        i--;
    }

    return true; // Разрешаем точку, если нет точки в текущем числе
}

void MainWindow::on_pushButton_equal_clicked()
{
    std::string str = ui->result_line->text().toStdString();
    const char* cstr = str.c_str();
    double x = 1;
    char postfix[256];
    char result[256];

    to_postfix(cstr, postfix);
    calculation(postfix, x, result);

    ui->result_line->setText(QString(result));

}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->result_line->setText("0");
}


void MainWindow::on_pushButton_C_clicked()
{
    QString current_text = ui->result_line->text();
    if (!current_text.isEmpty()){
        if (is_digit(current_text.at(current_text.length()-1))){
            current_text = current_text.chopped(1);
        } else {
            while(!current_text.isEmpty() && !is_digit(current_text.at(current_text.length()-1))){
                current_text = current_text.chopped(1);
            }
        }
        ui->result_line->setText(current_text);
    }
    if (current_text.isEmpty()){
        ui->result_line->setText("0");
    }
}


void MainWindow::on_pushButton_unar_clicked() {
    QString currentText = ui->result_line->text();

    if (currentText.isEmpty()) {
        return;
    }

    // Находим индекс последнего оператора или скобки
    int lastOpIndex = -1;
    for (int i = currentText.length() - 1; i >= 0; --i) {
        if (oprt_check(currentText[i]) || currentText[i] == '(' || currentText[i] == ')') {
            lastOpIndex = i;
            break;
        }
    }

    // Обрабатываем унарный минус
    if (lastOpIndex != -1 && currentText[lastOpIndex] != '-') {
        // Добавляем минус после последнего оператора/скобки
        currentText.insert(lastOpIndex + 1, '-');
    } else if (lastOpIndex == -1) {
        // Добавляем минус в начало строки, если нет операторов
        currentText.prepend('-');
    } else {
        // Удаляем уже существующий унарный минус
        currentText.remove(lastOpIndex, 1);
    }

    ui->result_line->setText(currentText);
}




void MainWindow::on_pushButton_FIN_clicked()
{
    Finance_window fin;
    fin.setModal(true);
    fin.exec();
}

