#include "application.h"

#include "mainwindow.h"
#include "aboutdialog.h"
#include "settingswindow.h"
#include "controller.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv)
{
    view = nullptr;
    about = nullptr;
    settings = nullptr;
    controller = nullptr;

    app.setApplicationName("SeriesScraper");
    app.setApplicationVersion("0.7.1");
}

Application::~Application()
{
    if (view != nullptr)
        delete view;
    if (about != nullptr)
        delete about;
    if (settings != nullptr)
        delete settings;
    if (controller != nullptr)
        delete controller;
}

void Application::init()
{
    if (view == nullptr)
        view = new MainWindow();
    if (about == nullptr)
        about = new AboutDialog();
    if (settings == nullptr)
        settings = new SettingsWindow();
    if (controller == nullptr)
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
