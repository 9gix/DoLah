#include "DoLahUI.h"

namespace DoLah {
    DoLahUI::DoLahUI(QWidget *parent)
        : QMainWindow(parent)
    {
        this->setupUI();
        QFile stylesheet("stylesheet.qss");
        if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        setStyleSheet(stylesheet.readAll());
        stylesheet.close();
        }
    }

    DoLahUI::~DoLahUI()
    {

    }

    // MAIN WINDOW

    void DoLahUI::setupUI() {
        if (this->objectName().isEmpty()) {
            this->setObjectName(QStringLiteral("DoLahUIWindow"));
        }

        this->resize(350, 570);
        this->setFixedSize(this->size());
        this->setWindowFlags(Qt::CustomizeWindowHint);
        this->setWindowFlags(Qt::FramelessWindowHint);
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        initMenu();
        initDisplayArea();
        initInputArea();

        this->setCentralWidget(centralWidget);

        QMetaObject::connectSlotsByName(this);
    }

    // HANDLE DRAGGING OF WINDOW

    void DoLahUI::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void DoLahUI::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

    // MENU

    void DoLahUI::initMenu() {
        menu = new QWidget(centralWidget);
        menu->setGeometry(QRect(0, 0, 350, 70));

        menuLayout = new QHBoxLayout(menu);
        menuLayout->setAlignment(Qt::AlignRight);
        menuLayout->setContentsMargins(5, 5, 5, 5);

        exitButton = new MenuLabel;
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setMinimumHeight(65);
        QPixmap exitIcon("exit.png");
        exitButton->setPixmap(exitIcon);
        menuLayout->addWidget(exitButton);

        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(menuExit()));
    }

    // DISPLAY AREA

    void DoLahUI::initDisplayArea() {
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setGeometry(QRect(5, 70, 340, 450));
        scrollArea->setFrameStyle(QFrame::NoFrame);

        scrollArea->setWidgetResizable(true);

        taskBox = new QTextBrowser();
        taskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox->setFixedHeight(40);
        taskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        taskBox->setText("<font size=4><b>1. polish GUI</b></font><br><font size=3><font color=#2fb6a7>today</font></font>");

        tasksContainer = new QWidget(scrollArea);
        tasksContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        tasksLayout = new QVBoxLayout(tasksContainer);
        tasksLayout->setAlignment(Qt::AlignTop);
        //tasksLayout->addWidget(taskBox);
        tasksLayout->setSpacing(3);
        tasksLayout->setContentsMargins(0, 0, 0, 0);
        loadTasks();

        scrollArea->setWidget(tasksContainer);
    }

    void DoLahUI::loadTasks() {
        std::vector<AbstractTask*> taskList = (appClient.getCalendar()).getTaskList();
        for (int i = 0; i < taskList.size(); ++i) {
            createTaskBox(i, taskList[i]);
        }
    }

    void DoLahUI::refreshTasks() {
        QLayoutItem* child;
        while ((child = tasksLayout->takeAt(0)) != 0)
        {
            QWidget* widget = child->widget();
            if (widget)
            {
                delete child->widget();
                delete child;
            }
        }
        loadTasks();
    }

    void DoLahUI::createTaskBox(int index, AbstractTask *task) {
        std::string name = task->getName();

        // dynamic casting??
        QString tasktitle = "<font size=4><b>" + QString::number(index) + ". " + QString::fromStdString(name);
        QTextBrowser *tempTaskBox = new UITaskBox();
        tempTaskBox->setObjectName(QStringLiteral("Task"));
        tempTaskBox->setText(tasktitle);
        tasksLayout->addWidget(tempTaskBox);
    }

    // INPUT AREA

    void DoLahUI::initInputArea() {
        message = new QLabel(centralWidget);
        message->setText("Enter a command:");
        message->setGeometry(QRect(7, 520, 338, 20));

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 540, 340, 25));
        lineEdit->setFocus();

        // handles events when enter key is pressed
        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    // SLOTS

    void DoLahUI::handleUserInput() {
        QString input = lineEdit->text();
        std::string inputline = input.toStdString();
        try {
            this->appClient.parseAndProcessCommand(inputline);
            refreshTasks();
            message->setText("Done. Enter next command:");
        }
        catch(std::exception e) {
            QString text = QString(e.what());
            message->setText(text);
            
        }
    }

    void DoLahUI::menuExit() {
        exit(0);
    }

}