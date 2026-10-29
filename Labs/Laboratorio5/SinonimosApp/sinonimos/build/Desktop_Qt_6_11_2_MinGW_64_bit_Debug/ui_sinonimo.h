/********************************************************************************
** Form generated from reading UI file 'sinonimo.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINONIMO_H
#define UI_SINONIMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sinonimo
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkbox;
    QLabel *sinonimosLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *editButton;
    QPushButton *removeButton;

    void setupUi(QWidget *Sinonimo)
    {
        if (Sinonimo->objectName().isEmpty())
            Sinonimo->setObjectName("Sinonimo");
        Sinonimo->resize(420, 40);
        horizontalLayout = new QHBoxLayout(Sinonimo);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(4, 2, 4, 2);
        checkbox = new QCheckBox(Sinonimo);
        checkbox->setObjectName("checkbox");
        checkbox->setChecked(false);

        horizontalLayout->addWidget(checkbox);

        sinonimosLabel = new QLabel(Sinonimo);
        sinonimosLabel->setObjectName("sinonimosLabel");

        horizontalLayout->addWidget(sinonimosLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        editButton = new QPushButton(Sinonimo);
        editButton->setObjectName("editButton");

        horizontalLayout->addWidget(editButton);

        removeButton = new QPushButton(Sinonimo);
        removeButton->setObjectName("removeButton");

        horizontalLayout->addWidget(removeButton);


        retranslateUi(Sinonimo);

        QMetaObject::connectSlotsByName(Sinonimo);
    } // setupUi

    void retranslateUi(QWidget *Sinonimo)
    {
        Sinonimo->setWindowTitle(QCoreApplication::translate("Sinonimo", "Sin\303\263nimo", nullptr));
        checkbox->setText(QString());
#if QT_CONFIG(tooltip)
        checkbox->setToolTip(QCoreApplication::translate("Sinonimo", "Marcar como revisado", nullptr));
#endif // QT_CONFIG(tooltip)
        sinonimosLabel->setText(QCoreApplication::translate("Sinonimo", "Subir - Ascender", nullptr));
        editButton->setText(QCoreApplication::translate("Sinonimo", "Editar", nullptr));
        removeButton->setText(QCoreApplication::translate("Sinonimo", "Quitar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sinonimo: public Ui_Sinonimo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINONIMO_H
