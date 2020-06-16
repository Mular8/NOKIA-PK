#pragma once

#include <QLabel>

#include "UeGui/ITextMode.hpp"
#include "QtSubmitTextEdit.hpp"
#include "QtUeModeWidget.hpp"


namespace ue
{

class QtAlertMode : public QtUeModeWidget, public IUeGui::ITextMode
{
    Q_OBJECT
public:
    QtAlertMode(QtPhoneNumberEdit& phoneNumberEdit,
                QtStackedWidget& stackedWidget);

    void setText(const std::string& text) override;

private:
    void constructGUI();
    void connectSignals();

    QLabel alertText;

signals:
    void setTextSignal(QString);

private slots:
    void activateSlot() override;
    void setTextSlot(QString);
};

}

