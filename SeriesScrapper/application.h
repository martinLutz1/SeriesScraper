#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
class MainWindow;
class JsonParser;
class LanguageControl;

class Application
{

public:
    Application(int &argc, char *argv[]);
    ~Application();

    void init(); // Initialize the application
    int exec(); // Execute the application

    bool setSeries(QString series, int season); // Set series if existing and set table
    bool changeEpisodeName(int index, QString episode); // Change an existing episode name
    void updateView();

    // Getter
    QString getSeries();
    int getSeasons();

private:
    QApplication app; // Dont derive from QApplication
    MainWindow* view; // Create view after QApplication
    JsonParser* jsonParser;
    LanguageControl* languageControl;

    QString seriesText;
    QString seasonText;
    QString episodeText;
    QStringList episodesList;
    int amountSeasons;
    int selectedSeason;

    QString getFilenameText(int episodeIndex);

public slots:

};

#endif // APPLICATION_H
