#pragma once

#include "counter.h"

#include <QMainWindow>

class QAction;
class QLabel;

class MainWindow final : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createActions();
    void createMenusAndToolBar();
    void createContent();
    void updateView();

    Counter m_counter;
    QLabel *m_valueLabel = nullptr;
    QAction *m_incrementAction = nullptr;
    QAction *m_decrementAction = nullptr;
    QAction *m_resetAction = nullptr;
};
