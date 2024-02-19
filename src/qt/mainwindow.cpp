#include "mainwindow.h"

#include "finance_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle("Calculator");
  setFixedSize(width(), height());

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

  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_extent, SIGNAL(clicked()), this, SLOT(operators()));

  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
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

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (button) {
    QString button_text = button->text();
    QString current_text = ui->result_line->text();
    int textLength = current_text.length();

    if (br_check(button_text)) {
      if (textLength == 1 && current_text == "0") {
        current_text.chop(1);
      } else if (textLength == 2 && current_text == "-0") {
        current_text.chop(1);
      } else if (current_text.at(textLength - 1) == '.' ||
                 current_text.back().isDigit() || current_text.back() == ')' ||
                 current_text.back() == 'x') {
        return;
      }
      ui->result_line->setText(current_text + button_text + '(');
    } else if (is_digit(button_text[0])) {
      // операции с цифрами
      if (textLength == 1 && current_text == "0" && button_text != ".") {
        current_text.chop(1);
      } else if (textLength == 2 && current_text == "-0") {
        current_text.chop(1);
      } else if (current_text.back() == 'x' || current_text.back() == ')') {
        return;
      }
      ui->result_line->setText(current_text + button_text);
    } else if (button_text == "mod") {
      if (oprt_check(current_text.at(textLength - 1))) {
        current_text.chop(1);
        ui->result_line->setText(current_text + '%');
      } else if (current_text.at(textLength - 1) == '(') {
        return;
      } else if (current_text.at(textLength - 1) == '.') {
        return;
      }
      ui->result_line->setText(current_text + '%');
    } else {
      ui->result_line->setText(current_text + button_text);
    }
  }
}

void MainWindow::operators() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  QString button_text = button->text();
  QString current_text = ui->result_line->text();
  int textLength = current_text.length();

  if (!current_text.isEmpty() && oprt_check(current_text.at(textLength - 1))) {
    current_text.chop(1);
  } else if (!current_text.isEmpty() &&
             current_text.at(textLength - 1) == '(') {
    return;
  } else if (current_text.at(textLength - 1) == '.') {
    return;
  }

  ui->result_line->setText(current_text + button_text);
}

bool MainWindow::oprt_check(QChar ch) { return QString("+-*/^%").contains(ch); }

bool MainWindow::is_digit(QChar ch) {
  return (ch >= '0' && ch <= '9') || ch <= '.';
}

bool MainWindow::br_check(QString ch) {
  bool flag = false;
  if (ch == "sin" || ch == "cos" || ch == "tan") {
    flag = true;
  } else if (ch == "asin" || ch == "acos" || ch == "atan") {
    flag = true;
  } else if (ch == "ln" || ch == "log" || ch == "sqrt") {
    flag = true;
  }
  return flag;
}

void MainWindow::on_pushButton_open_br_clicked() {
  QString current_text = ui->result_line->text();
  int textLength = current_text.length();

  if (textLength == 0 || oprt_check(current_text.at(textLength - 1)) ||
      current_text.at(textLength - 1) == '(') {
    ui->result_line->setText(current_text + '(');
  } else if ((textLength == 1 && current_text == "0") ||
             (textLength == 2 && current_text == "-0")) {
    current_text.chop(1);
    ui->result_line->setText(current_text + '(');
  }
}

void MainWindow::on_pushButton_close_br_clicked() {
  QString current_text = ui->result_line->text();

  if (!current_text.isEmpty() && count_closed_br(current_text)) {
    ui->result_line->setText(current_text + ')');
  }
}

bool MainWindow::count_closed_br(const QString& str) {
  int open = 0;

  for (int i = 0; i < str.length(); ++i) {
    if (str.at(i) == '(') {
      open++;
    } else if (str.at(i) == ')') {
      if (open == 0) {
        return false;
      }
      open--;
    }
  }
  return open > 0;
}

void MainWindow::on_pushButton_point_clicked() {
  QString currentText = ui->result_line->text();
  if (isPointAllowed(currentText) && currentText.back() != ')' &&
      currentText.back() != 'x') {
    ui->result_line->setText(currentText + ".");
  }
}

bool MainWindow::isPointAllowed(const QString& text) {
  int length = text.length();
  if (length == 0) return true;

  QChar lastChar = text[length - 1];
  if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/')
    return true;

  // Проверяем, есть ли уже точка в текущем числе
  int i = length - 1;
  while (i >= 0) {
    if (text[i] == '.') return false;  // Точка уже присутствует в текущем числе
    if (!text[i].isDigit())
      break;  // Достигнут нецифровой символ, текущее число закончилось
    i--;
  }
  return true;  // Разрешаем точку, если нет точки в текущем числе
}

void MainWindow::on_pushButton_equal_clicked() {
  std::string str = ui->result_line->text().toStdString();
  const char* cstr = str.c_str();
  char postfix[256];
  char result[256];
  bool xOk = false;
  double x =
      ui->line_X->text().isEmpty() ? 0 : ui->line_X->text().toDouble(&xOk);

  if (!xOk) {
    QString errorMessage =
        "Please enter valid numeric values for the following fields:\n";
    if (!xOk) errorMessage += "- X\n";
    QMessageBox::warning(this, "Error", errorMessage);
    return;
  }
  if (graphWindow == nullptr) {
    to_postfix(cstr, postfix);
    calculation(postfix, x, result);
    ui->result_line->setText(QString(result));
  } else {
    emit newTextAvailable(ui->result_line->text());
  }
}

void MainWindow::on_pushButton_AC_clicked() { ui->result_line->setText("0"); }

void MainWindow::on_pushButton_C_clicked() {
  QString current_text = ui->result_line->text();
  if (!current_text.isEmpty()) {
    if (is_digit(current_text.at(current_text.length() - 1))) {
      current_text = current_text.chopped(1);
    } else {
      while (!current_text.isEmpty() &&
             !is_digit(current_text.at(current_text.length() - 1))) {
        current_text = current_text.chopped(1);
      }
    }
    ui->result_line->setText(current_text);
  }
  if (current_text.isEmpty()) {
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
    if (oprt_check(currentText[i]) || currentText[i] == '(' ||
        currentText[i] == ')') {
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

void MainWindow::on_pushButton_FIN_clicked() {
  Finance_window fin;
  fin.setModal(true);
  fin.exec();
}

void MainWindow::on_pushButton_GRAPH_clicked() {
  if (graphWindow) {
    graphWindow->close();
    delete graphWindow;  // Удаляем объект, чтобы избежать утечек памяти
    graphWindow = nullptr;  // Сбрасываем указатель
    return;
  }

  graphWindow = new graph(this);
  if (!graphWindow) {
    return;
  }
  graphWindow->setAttribute(Qt::WA_DeleteOnClose);

  connect(this, &MainWindow::newTextAvailable, graphWindow,
          &graph::on_newTextAvailable);
  emit newTextAvailable(ui->result_line->text());

  QPoint currentPos = this->pos();
  QSize currentSize = this->size();
  graphWindow->move(currentPos + QPoint(currentSize.width(), 0));
  graphWindow->show();

  // connect(graphWindow, &QObject::destroyed, [this]() {
  connect(graphWindow, &QObject::destroyed, this,
          [this]() { this->graphWindow = nullptr; });
}

void MainWindow::on_pushButton_X_clicked() {
  QString current_text = ui->result_line->text();
  QChar last_char = current_text.isEmpty() ? QChar() : current_text.back();
  int textLength = current_text.length();

  if (textLength == 1 && current_text == "0") {
    ui->result_line->setText("x");
  } else if (textLength == 2 && current_text == "-0") {
    current_text.chop(1);
    ui->result_line->setText(current_text + "x");
  } else if (!current_text.isEmpty() && last_char != 'x') {
    if (oprt_check(last_char) || last_char == '(') {
      ui->result_line->setText(current_text + "x");
    }
  }
}
