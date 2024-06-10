#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    en2zh = new QHash<QString, QString>();
    QString totalJson = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "total.json";


    QFile file(totalJson);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->output->setText("cann't open file: " + totalJson);
    }

    QByteArray fileContent = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent);
    if (!jsonDoc.isObject()) {
        ui->output->setText("invalid json file: " + totalJson);
    }
    QJsonObject jsonObj = jsonDoc.object();
    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        en2zh->insert(it.key(), it.value().toString());
    }
    //qInfo() << en2zh->size() << en2zh->value("hello");
    ui->output->setText(QString::number(en2zh->size()) + " words were loaded");
}

Widget::~Widget()
{
    delete ui;
    delete en2zh;
}




void Widget::on_input_textChanged(const QString &arg1)
{
    //qInfo() << arg1 << "textchanged";
    if(!arg1.isEmpty()){
        QChar cr = arg1.at(0);
        if(cr.isLetter()){
            //qInfo() << QString(arg1.at(0)) + " is latter";
            QString value = en2zh->value(arg1);
            if(!value.isEmpty()){
                ui->output->setText(value);
            }
        }else {
            ui->output->setText("");
        }
    }else {
        ui->output->setText("");
    }
}

