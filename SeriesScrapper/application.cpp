#include "application.h"

#include "mainwindow.h"
#include "jsonparser.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv)
{
    view = NULL;
    jsonParser = NULL;
}

Application::~Application()
{
    if (view != NULL)
        delete view;
    if (jsonParser != NULL)
        delete jsonParser;
}

void Application::init()
{
    if (view == NULL)
        view = new MainWindow(0, this);
    if (jsonParser == NULL)
        jsonParser = new JsonParser();

    view->show();
}

int Application::exec()
{
    if (jsonParser->getIDfromURL("http://www.omdbapi.com/?t=lost&type=series&season=1", "Title")) {
        episodes = jsonParser->getIDValue();
        for (int i = 0; i < episodes.size(); i++)
            view->setRow(i, episodes.at(i), "Lost - Staffel 1 Episode " + QString::number(i+1) + " - " + episodes.at(i));
    }
    return app.exec();
}

void Application::setEpisode(int index, QString episode)
{
    while (episodes.length() <= index) // Make the list long enough for the requested index
        episodes.push_back("");

    if (episodes.at(index) != episode) {// Write only on change
        episodes[index] = episode;
        view->setRow(index, episodes.at(index), "Lost - Staffel 1 Episode " + QString::number(index+1) + " - " + episodes.at(index));
    }
}

