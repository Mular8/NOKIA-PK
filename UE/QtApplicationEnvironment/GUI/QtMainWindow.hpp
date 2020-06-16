#pragma once

#include "IUeGui.hpp"
#include <QMainWindow>
#include <QKeyEvent>
#include "Logger/ILogger.hpp"

namespace ue
{

class QtMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QtMainWindow();
    void setCloseGuard(const IUeGui::CloseGuard &value);
    void closeEvent(QCloseEvent* event) override;

private:
    IUeGui::CloseGuard closeGuard;
    bool closeAccepted();
};

}

