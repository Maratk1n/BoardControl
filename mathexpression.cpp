#include "mathexpression.h"
#include "ui_mathexpression.h"
#include <QScriptEngine>
#include <QtScript/QScriptEngine>
#include <QMessageBox>

MathExpression::MathExpression(MathButton *button, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MathExpression),
    _button(button)
{
    ui->setupUi(this);
    ui->typeNameBox->addItem("Коэффициент");
    ui->typeNameBox->addItem("Формула");

    if (_button) {
        _coeff = _button->_coeff;
        _formula = _button->_formula;
    }
    init();
}

MathExpression::~MathExpression()
{
    delete ui;
}

void MathExpression::setCoefficient(float coeff)
{
    _formula.clear();
    _coeff = coeff;
    init();
}

void MathExpression::setFormula(const QString &formula)
{
    _formula = formula;
    init();
}

void MathExpression::init()
{
    if (!_formula.isEmpty()) {
        ui->typeNameBox->setCurrentIndex(kFormula);
        ui->data->setText(_formula);
    }
    else {
        ui->typeNameBox->setCurrentIndex(kCoefficient);
        ui->data->setText(QString::number(_coeff));
    }
}

void MathExpression::on_apply_clicked()
{
    auto data = ui->data->text();
    if (ui->typeNameBox->currentIndex() == kCoefficient) {
        bool ok;
        float coeff = data.toFloat(&ok);
        if (ok && _button) _button->setCoefficient(coeff);
        else {
            QMessageBox::warning(this, "Внимание","Неверное число");
            return;
        }
    }
    else {
        QScriptEngine expression;
        float dummy = 1.5;
        QString text = QString(data).arg(dummy);
        if (expression.checkSyntax(text).state() !=
                QScriptSyntaxCheckResult::Valid) {
            QMessageBox::warning(this, "Внимание","Неверное выражение");
            return;
        }
        else if (_button) _button->setFormula(data);
    }
    accept();
}

void MathExpression::on_reset_clicked()
{
    if (_button != nullptr) {
        _button->resetExpr();
    }
    accept();
}
