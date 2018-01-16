/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *general;
    QGroupBox *seriesDatabaseGroupBox;
    QRadioButton *tmdbRadioButton;
    QRadioButton *omdbRadioButton;
    QLabel *recommendLabel;
    QRadioButton *tvdbRadioButton;
    QGroupBox *saveOnExitGroupBox;
    QCheckBox *savePathCheckBox;
    QCheckBox *saveSeriesCheckBox;
    QGroupBox *interfaceGroupBox;
    QCheckBox *showSeriesInformationCheckBox;
    QComboBox *selectInterfaceLanguageComboBox;
    QLabel *languageLabel;
    QCheckBox *darkThemeCheckBox;
    QGroupBox *saveInDirectoryGroupBox;
    QCheckBox *savePosterCheckBox;
    QGroupBox *miscGroupBox;
    QCheckBox *autoSetDetectedSeasonCheckBox;
    QWidget *video;
    QListWidget *fileTypeListWidget;
    QGroupBox *videoGroupBox;
    QLineEdit *newFileTypeLineEdit;
    QPushButton *newFileTypeAddButton;
    QPushButton *fileTypeRemoveButton;
    QWidget *nameScheme;
    QGroupBox *newNameSchemeGroupBox;
    QLineEdit *newNameSchemeLineEdit;
    QPushButton *newNameSchemeAddButton;
    QPushButton *nameSchemeRemoveButton;
    QListWidget *nameSchemeListWidget;
    QPushButton *resetButton;
    QPushButton *doneButton;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(500, 320);
        SettingsWindow->setMinimumSize(QSize(500, 320));
        SettingsWindow->setMaximumSize(QSize(500, 320));
        tabWidget = new QTabWidget(SettingsWindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(5, 5, 490, 260));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideRight);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        general = new QWidget();
        general->setObjectName(QStringLiteral("general"));
        seriesDatabaseGroupBox = new QGroupBox(general);
        seriesDatabaseGroupBox->setObjectName(QStringLiteral("seriesDatabaseGroupBox"));
        seriesDatabaseGroupBox->setGeometry(QRect(10, 135, 250, 85));
        tmdbRadioButton = new QRadioButton(seriesDatabaseGroupBox);
        tmdbRadioButton->setObjectName(QStringLiteral("tmdbRadioButton"));
        tmdbRadioButton->setEnabled(true);
        tmdbRadioButton->setGeometry(QRect(10, 30, 60, 20));
        tmdbRadioButton->setChecked(true);
        omdbRadioButton = new QRadioButton(seriesDatabaseGroupBox);
        omdbRadioButton->setObjectName(QStringLiteral("omdbRadioButton"));
        omdbRadioButton->setEnabled(true);
        omdbRadioButton->setGeometry(QRect(170, 30, 60, 20));
        recommendLabel = new QLabel(seriesDatabaseGroupBox);
        recommendLabel->setObjectName(QStringLiteral("recommendLabel"));
        recommendLabel->setGeometry(QRect(70, 32, 101, 16));
        QFont font1;
        font1.setPointSize(8);
        recommendLabel->setFont(font1);
        tvdbRadioButton = new QRadioButton(seriesDatabaseGroupBox);
        tvdbRadioButton->setObjectName(QStringLiteral("tvdbRadioButton"));
        tvdbRadioButton->setGeometry(QRect(10, 55, 100, 20));
        saveOnExitGroupBox = new QGroupBox(general);
        saveOnExitGroupBox->setObjectName(QStringLiteral("saveOnExitGroupBox"));
        saveOnExitGroupBox->setGeometry(QRect(315, 0, 160, 80));
        savePathCheckBox = new QCheckBox(saveOnExitGroupBox);
        savePathCheckBox->setObjectName(QStringLiteral("savePathCheckBox"));
        savePathCheckBox->setGeometry(QRect(10, 25, 140, 20));
        saveSeriesCheckBox = new QCheckBox(saveOnExitGroupBox);
        saveSeriesCheckBox->setObjectName(QStringLiteral("saveSeriesCheckBox"));
        saveSeriesCheckBox->setGeometry(QRect(10, 50, 140, 20));
        interfaceGroupBox = new QGroupBox(general);
        interfaceGroupBox->setObjectName(QStringLiteral("interfaceGroupBox"));
        interfaceGroupBox->setGeometry(QRect(10, 0, 290, 135));
        showSeriesInformationCheckBox = new QCheckBox(interfaceGroupBox);
        showSeriesInformationCheckBox->setObjectName(QStringLiteral("showSeriesInformationCheckBox"));
        showSeriesInformationCheckBox->setEnabled(true);
        showSeriesInformationCheckBox->setGeometry(QRect(10, 95, 290, 20));
        selectInterfaceLanguageComboBox = new QComboBox(interfaceGroupBox);
        selectInterfaceLanguageComboBox->setObjectName(QStringLiteral("selectInterfaceLanguageComboBox"));
        selectInterfaceLanguageComboBox->setGeometry(QRect(10, 40, 170, 26));
        languageLabel = new QLabel(interfaceGroupBox);
        languageLabel->setObjectName(QStringLiteral("languageLabel"));
        languageLabel->setGeometry(QRect(15, 25, 150, 16));
        darkThemeCheckBox = new QCheckBox(interfaceGroupBox);
        darkThemeCheckBox->setObjectName(QStringLiteral("darkThemeCheckBox"));
        darkThemeCheckBox->setGeometry(QRect(10, 70, 290, 20));
        saveInDirectoryGroupBox = new QGroupBox(general);
        saveInDirectoryGroupBox->setObjectName(QStringLiteral("saveInDirectoryGroupBox"));
        saveInDirectoryGroupBox->setGeometry(QRect(315, 80, 160, 55));
        savePosterCheckBox = new QCheckBox(saveInDirectoryGroupBox);
        savePosterCheckBox->setObjectName(QStringLiteral("savePosterCheckBox"));
        savePosterCheckBox->setGeometry(QRect(10, 25, 140, 20));
        miscGroupBox = new QGroupBox(general);
        miscGroupBox->setObjectName(QStringLiteral("miscGroupBox"));
        miscGroupBox->setGeometry(QRect(275, 135, 200, 85));
        autoSetDetectedSeasonCheckBox = new QCheckBox(miscGroupBox);
        autoSetDetectedSeasonCheckBox->setObjectName(QStringLiteral("autoSetDetectedSeasonCheckBox"));
        autoSetDetectedSeasonCheckBox->setGeometry(QRect(10, 25, 185, 20));
        tabWidget->addTab(general, QString());
        video = new QWidget();
        video->setObjectName(QStringLiteral("video"));
        fileTypeListWidget = new QListWidget(video);
        fileTypeListWidget->setObjectName(QStringLiteral("fileTypeListWidget"));
        fileTypeListWidget->setGeometry(QRect(10, 10, 465, 150));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fileTypeListWidget->sizePolicy().hasHeightForWidth());
        fileTypeListWidget->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(12);
        fileTypeListWidget->setFont(font2);
        fileTypeListWidget->setDefaultDropAction(Qt::MoveAction);
        fileTypeListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        fileTypeListWidget->setMovement(QListView::Static);
        fileTypeListWidget->setFlow(QListView::TopToBottom);
        fileTypeListWidget->setProperty("isWrapping", QVariant(true));
        fileTypeListWidget->setResizeMode(QListView::Fixed);
        fileTypeListWidget->setLayoutMode(QListView::Batched);
        fileTypeListWidget->setSpacing(10);
        fileTypeListWidget->setGridSize(QSize(90, 18));
        fileTypeListWidget->setViewMode(QListView::IconMode);
        fileTypeListWidget->setModelColumn(0);
        fileTypeListWidget->setUniformItemSizes(false);
        fileTypeListWidget->setWordWrap(true);
        videoGroupBox = new QGroupBox(video);
        videoGroupBox->setObjectName(QStringLiteral("videoGroupBox"));
        videoGroupBox->setGeometry(QRect(10, 160, 465, 65));
        videoGroupBox->setFont(font);
        newFileTypeLineEdit = new QLineEdit(videoGroupBox);
        newFileTypeLineEdit->setObjectName(QStringLiteral("newFileTypeLineEdit"));
        newFileTypeLineEdit->setGeometry(QRect(10, 30, 200, 22));
        newFileTypeLineEdit->setFont(font);
        newFileTypeAddButton = new QPushButton(videoGroupBox);
        newFileTypeAddButton->setObjectName(QStringLiteral("newFileTypeAddButton"));
        newFileTypeAddButton->setEnabled(true);
        newFileTypeAddButton->setGeometry(QRect(220, 25, 120, 32));
        newFileTypeAddButton->setFont(font);
        fileTypeRemoveButton = new QPushButton(videoGroupBox);
        fileTypeRemoveButton->setObjectName(QStringLiteral("fileTypeRemoveButton"));
        fileTypeRemoveButton->setEnabled(true);
        fileTypeRemoveButton->setGeometry(QRect(340, 25, 120, 32));
        fileTypeRemoveButton->setFont(font);
        tabWidget->addTab(video, QString());
        nameScheme = new QWidget();
        nameScheme->setObjectName(QStringLiteral("nameScheme"));
        newNameSchemeGroupBox = new QGroupBox(nameScheme);
        newNameSchemeGroupBox->setObjectName(QStringLiteral("newNameSchemeGroupBox"));
        newNameSchemeGroupBox->setGeometry(QRect(10, 160, 465, 65));
        newNameSchemeLineEdit = new QLineEdit(newNameSchemeGroupBox);
        newNameSchemeLineEdit->setObjectName(QStringLiteral("newNameSchemeLineEdit"));
        newNameSchemeLineEdit->setGeometry(QRect(10, 30, 200, 22));
        newNameSchemeAddButton = new QPushButton(newNameSchemeGroupBox);
        newNameSchemeAddButton->setObjectName(QStringLiteral("newNameSchemeAddButton"));
        newNameSchemeAddButton->setEnabled(true);
        newNameSchemeAddButton->setGeometry(QRect(220, 25, 120, 32));
        nameSchemeRemoveButton = new QPushButton(newNameSchemeGroupBox);
        nameSchemeRemoveButton->setObjectName(QStringLiteral("nameSchemeRemoveButton"));
        nameSchemeRemoveButton->setEnabled(true);
        nameSchemeRemoveButton->setGeometry(QRect(340, 25, 120, 32));
        nameSchemeListWidget = new QListWidget(nameScheme);
        nameSchemeListWidget->setObjectName(QStringLiteral("nameSchemeListWidget"));
        nameSchemeListWidget->setGeometry(QRect(10, 10, 465, 150));
        nameSchemeListWidget->setMovement(QListView::Static);
        nameSchemeListWidget->setResizeMode(QListView::Fixed);
        nameSchemeListWidget->setLayoutMode(QListView::SinglePass);
        nameSchemeListWidget->setViewMode(QListView::ListMode);
        tabWidget->addTab(nameScheme, QString());
        resetButton = new QPushButton(SettingsWindow);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(10, 275, 141, 32));
        resetButton->setFont(font);
        doneButton = new QPushButton(SettingsWindow);
        doneButton->setObjectName(QStringLiteral("doneButton"));
        doneButton->setEnabled(true);
        doneButton->setGeometry(QRect(400, 275, 90, 32));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI"));
        font3.setBold(false);
        font3.setWeight(50);
        doneButton->setFont(font3);
        doneButton->setAutoDefault(true);
        doneButton->setFlat(false);

        retranslateUi(SettingsWindow);

        tabWidget->setCurrentIndex(0);
        nameSchemeListWidget->setCurrentRow(-1);
        doneButton->setDefault(true);


        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Settings", nullptr));
        seriesDatabaseGroupBox->setTitle(QApplication::translate("SettingsWindow", "Series database", nullptr));
        tmdbRadioButton->setText(QApplication::translate("SettingsWindow", "TMDb", nullptr));
#ifndef QT_NO_TOOLTIP
        omdbRadioButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        omdbRadioButton->setText(QApplication::translate("SettingsWindow", "OMDb", nullptr));
        recommendLabel->setText(QApplication::translate("SettingsWindow", "<html><head/><body><p><span style=\" color:#353535;\">(recommended)</span></p></body></html>", nullptr));
        tvdbRadioButton->setText(QApplication::translate("SettingsWindow", "TVDB", nullptr));
        saveOnExitGroupBox->setTitle(QApplication::translate("SettingsWindow", "Save on exit", nullptr));
        savePathCheckBox->setText(QApplication::translate("SettingsWindow", "Path", nullptr));
        saveSeriesCheckBox->setText(QApplication::translate("SettingsWindow", "Series", nullptr));
        interfaceGroupBox->setTitle(QApplication::translate("SettingsWindow", "Interface", nullptr));
        showSeriesInformationCheckBox->setText(QApplication::translate("SettingsWindow", "Show series information", nullptr));
        languageLabel->setText(QApplication::translate("SettingsWindow", "Language", nullptr));
        darkThemeCheckBox->setText(QApplication::translate("SettingsWindow", "Dark theme (requires restart)", nullptr));
#ifndef QT_NO_TOOLTIP
        saveInDirectoryGroupBox->setToolTip(QApplication::translate("SettingsWindow", "Saving following things in directory on renaming.", nullptr));
#endif // QT_NO_TOOLTIP
        saveInDirectoryGroupBox->setTitle(QApplication::translate("SettingsWindow", "Save in series directory", nullptr));
        savePosterCheckBox->setText(QApplication::translate("SettingsWindow", "Poster", nullptr));
        miscGroupBox->setTitle(QApplication::translate("SettingsWindow", "Misc", nullptr));
        autoSetDetectedSeasonCheckBox->setText(QApplication::translate("SettingsWindow", "Set detected season", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(general), QApplication::translate("SettingsWindow", "General", nullptr));
        videoGroupBox->setTitle(QApplication::translate("SettingsWindow", "New format", nullptr));
        newFileTypeAddButton->setText(QApplication::translate("SettingsWindow", "Add", nullptr));
        fileTypeRemoveButton->setText(QApplication::translate("SettingsWindow", "Remove", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(video), QApplication::translate("SettingsWindow", "Video", nullptr));
        newNameSchemeGroupBox->setTitle(QApplication::translate("SettingsWindow", "New name scheme", nullptr));
        newNameSchemeAddButton->setText(QApplication::translate("SettingsWindow", "Add", nullptr));
        nameSchemeRemoveButton->setText(QApplication::translate("SettingsWindow", "Remove", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(nameScheme), QApplication::translate("SettingsWindow", "Name scheme", nullptr));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QApplication::translate("SettingsWindow", "Resets all settings. Video formats and name schemes stay untouched.", nullptr));
#endif // QT_NO_TOOLTIP
        resetButton->setText(QApplication::translate("SettingsWindow", "Reset", nullptr));
        doneButton->setText(QApplication::translate("SettingsWindow", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
