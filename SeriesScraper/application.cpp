#include "application.h"

#include "mainwindow.h"
#include "aboutdialog.h"
#include "settingswindow.h"
#include "controller.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv)
{
    view = NULL;
    about = NULL;
    settings = NULL;
    controller = NULL;
}

Application::~Application()
{
    if (view != NULL)
        delete view;
    if (about != NULL)
        delete about;
    if (settings != NULL)
        delete settings;
    if (controller != NULL)
        delete controller;
}

void Application::init()
{
    if (view == NULL)
        view = new MainWindow();
    if (about == NULL)
        about = new AboutDialog();
    if (settings == NULL)
        settings = new SettingsWindow();
    if (controller == NULL)
        controller = new Controller();

    QObject::connect(view, SIGNAL(sendMessage(Message&)), controller, SLOT(notify(Message&)));
    QObject::connect(controller, SIGNAL(sendMessage(Message&)), view, SLOT(notify(Message&)));
    QObject::connect(controller, SIGNAL(sendMessage(Message&)), about, SLOT(notify(Message&)));
    QObject::connect(settings, SIGNAL(sendMessage(Message&)), controller, SLOT(notify(Message&)));
    QObject::connect(controller, SIGNAL(sendMessage(Message&)), settings, SLOT(notify(Message&)));

    controller->initialize();
    view->show();
}

int Application::exec()
{
    return app.exec();
}
