#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Qt Action 示例"));
    resize(620, 420);
    setMinimumSize(480, 340);

    createActions();
    createMenusAndToolBar();
    createContent();
    updateView();
}

void MainWindow::createActions()
{
    m_incrementAction = new QAction(tr("增加 (&I)"), this);
    m_incrementAction->setShortcut(QKeySequence::ZoomIn);
    m_incrementAction->setStatusTip(tr("计数器加一"));
    connect(m_incrementAction, &QAction::triggered, this, [this] {
        m_counter.increment();
        updateView();
    });

    m_decrementAction = new QAction(tr("减少 (&D)"), this);
    m_decrementAction->setShortcut(QKeySequence::ZoomOut);
    m_decrementAction->setStatusTip(tr("计数器减一"));
    connect(m_decrementAction, &QAction::triggered, this, [this] {
        m_counter.decrement();
        updateView();
    });

    m_resetAction = new QAction(tr("重置 (&R)"), this);
    m_resetAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+0")));
    m_resetAction->setStatusTip(tr("将计数器恢复为零"));
    connect(m_resetAction, &QAction::triggered, this, [this] {
        m_counter.reset();
        updateView();
    });
}

void MainWindow::createMenusAndToolBar()
{
    auto *fileMenu = menuBar()->addMenu(tr("文件 (&F)"));
    auto *quitAction = fileMenu->addAction(tr("退出 (&Q)"));
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    auto *counterMenu = menuBar()->addMenu(tr("计数器 (&C)"));
    counterMenu->addAction(m_incrementAction);
    counterMenu->addAction(m_decrementAction);
    counterMenu->addSeparator();
    counterMenu->addAction(m_resetAction);

    auto *helpMenu = menuBar()->addMenu(tr("帮助 (&H)"));
    auto *aboutAction = helpMenu->addAction(tr("关于"));
    connect(aboutAction, &QAction::triggered, this, [this] {
        QMessageBox::about(
            this,
            tr("关于 Qt Action 示例"),
            tr("一个展示 QAction、Qt Widgets、CMake 和多平台 CI 的小型示例。"));
    });

    auto *toolBar = addToolBar(tr("计数器"));
    toolBar->setObjectName(QStringLiteral("counterToolBar"));
    toolBar->setMovable(false);
    toolBar->addAction(m_decrementAction);
    toolBar->addAction(m_incrementAction);
    toolBar->addSeparator();
    toolBar->addAction(m_resetAction);

    statusBar()->showMessage(tr("就绪"));
}

void MainWindow::createContent()
{
    auto *central = new QWidget(this);
    central->setObjectName(QStringLiteral("centralPanel"));
    auto *layout = new QVBoxLayout(central);
    layout->setContentsMargins(52, 42, 52, 42);
    layout->setSpacing(18);

    auto *title = new QLabel(tr("一个动作，多处使用"), central);
    title->setObjectName(QStringLiteral("titleLabel"));
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 8);
    titleFont.setBold(true);
    title->setFont(titleFont);

    auto *description = new QLabel(
        tr("菜单、工具栏与按钮共享同一组 QAction。尝试使用 Ctrl++、Ctrl+- 和 Ctrl+0。"),
        central);
    description->setWordWrap(true);
    description->setObjectName(QStringLiteral("descriptionLabel"));

    m_valueLabel = new QLabel(central);
    m_valueLabel->setAlignment(Qt::AlignCenter);
    m_valueLabel->setObjectName(QStringLiteral("valueLabel"));
    m_valueLabel->setMinimumHeight(110);

    auto *buttonRow = new QHBoxLayout;
    buttonRow->setSpacing(12);
    buttonRow->addStretch();
    for (QAction *action : {m_decrementAction, m_resetAction, m_incrementAction}) {
        auto *button = new QToolButton(central);
        button->setDefaultAction(action);
        button->setToolButtonStyle(Qt::ToolButtonTextOnly);
        button->setMinimumSize(108, 40);
        buttonRow->addWidget(button);
    }
    buttonRow->addStretch();

    layout->addWidget(title);
    layout->addWidget(description);
    layout->addStretch();
    layout->addWidget(m_valueLabel);
    layout->addStretch();
    layout->addLayout(buttonRow);

    setCentralWidget(central);
    central->setStyleSheet(QStringLiteral(
        "#centralPanel { background: #f5f7fb; }"
        "#titleLabel { color: #172033; }"
        "#descriptionLabel { color: #596579; }"
        "#valueLabel { background: white; color: #2563eb; border: 1px solid #dbe3ef; "
        "border-radius: 14px; font-size: 48px; font-weight: 700; }"
        "QToolButton { background: #ffffff; color: #25324a; border: 1px solid #cad5e3; "
        "border-radius: 8px; padding: 8px 16px; }"
        "QToolButton:hover { background: #eef4ff; border-color: #7aa2ee; }"
        "QToolButton:pressed { background: #dfeaff; }"
        "QToolButton:disabled { color: #9ba7b7; background: #eef1f5; }"));
}

void MainWindow::updateView()
{
    const int value = m_counter.value();
    m_valueLabel->setText(QString::number(value));
    m_incrementAction->setEnabled(m_counter.canIncrement());
    m_decrementAction->setEnabled(m_counter.canDecrement());
    m_resetAction->setEnabled(value != 0);
    statusBar()->showMessage(tr("当前值：%1").arg(value), 2000);
}
