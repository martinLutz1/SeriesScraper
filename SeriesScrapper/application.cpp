#include "application.h"

#include "mainwindow.h"
#include "jsonparser.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv), amountSeasons(1)
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

bool Application::setSeries(QString series, int season)
{
    qDebug() << "Lädt";

    if (jsonParser->getSeriesSeason("http://www.omdbapi.com/?", series, season, "Title")) {
        qDebug() << "Laden erfolgreich";
        view->clearTable();
        this->series = series;
        episodes = jsonParser->getIDValue();

        amountSeasons = jsonParser->getAmountSeasons();
        view->setAmountSeasons(amountSeasons);

        for (int i = 0; i < episodes.size(); i++)
            view->setRow(i, episodes.at(i), series + " - Staffel " + QString::number(season) + " Episode " + QString::number(i+1) + " - " + episodes.at(i));
        return true;
    }
    qDebug() << "Laden fehlgeschlagen";
    return false;
}

QString Application::getSeries()
{
    return series;
}

int Application::getSeasons()
{
    return amountSeasons;
}

