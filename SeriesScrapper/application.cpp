#include "application.h"

#include "mainwindow.h"
#include "jsonparser.h"

#include <QDebug>

Application::Application(int &argc, char *argv[]) : app(argc, argv), amountSeasons(1), selectedSeason(0)
{
    view = NULL;
    jsonParser = NULL;
    seasonText = " - Staffel ";
    episodeText = " Episode ";
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

bool Application::setSeries(QString series, int season)
{
    qDebug() << "Lädt";

    if (jsonParser->getSeriesSeason("http://www.omdbapi.com/?", series, season, "Title")) {
        qDebug() << "Laden erfolgreich";

        this->seriesText = series;
        this->selectedSeason = season;
        this->episodesList = jsonParser->getIDValue();
        this->amountSeasons = jsonParser->getAmountSeasons();
        updateView();

        return true;
    }
    qDebug() << "Laden fehlgeschlagen";
    return false;
}

bool Application::changeEpisodeName(int index, QString episode)
{
    if (index >= episodesList.length()) // Only write on existing items
        return false;
    else {
        if (episodesList.at(index) != episode) { // Write only on change
            episodesList[index] = episode;
            QString fileName = getFilenameText(index);
            view->setRow(index, episodesList.at(index), fileName);
        }
        return true;
    }
}

void Application::updateView()
{
    QString episodeName;
    QString fileName;
    view->clearTable();
    view->setAmountSeasons(amountSeasons);

    for (int i = 0; i < episodesList.length(); i++) { // Create table items
        episodeName = episodesList.at(i);
        fileName = getFilenameText(i);
        view->setRow(i, episodeName, fileName);
    }
}

QString Application::getSeries()
{
    return seriesText;
}

int Application::getSeasons()
{
    return amountSeasons;
}

QString Application::getFilenameText(int episodeIndex)
{
    QString episodeName = episodesList.at(episodeIndex);
    QString fileName = seriesText + seasonText + QString::number(selectedSeason)
            + episodeText + QString::number(episodeIndex + 1) + " - " + episodeName;
    return fileName;
}
