#include "application.h"

#include "mainwindow.h"
#include "languagecontrol.h"
#include "controller.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv)
{
    view = NULL;
    languageControl = NULL;
    controller = NULL;
}

Application::~Application()
{
    if (view != NULL)
        delete view;
    if (languageControl != NULL)
        delete languageControl;
    if (controller != NULL)
        delete controller;
}

void Application::init()
{
    if (view == NULL)
        view = new MainWindow();
    if (languageControl == NULL)
        languageControl = new LanguageControl();
    if (controller == NULL)
        controller = new Controller();

    QObject::connect(view, SIGNAL(sendMessage(Message&)), controller, SLOT(notify(Message&)));
    QObject::connect(controller, SIGNAL(sendMessage(Message&)), view, SLOT(notify(Message&)));

    view->show();
}

int Application::exec()
{
    return app.exec();
}
