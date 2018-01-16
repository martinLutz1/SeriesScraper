/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *episodeNameTable;
    QScrollArea *additionalInfoScrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *additionalScrollAreaHorizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *posterInfoLabel;
    QLabel *seriesNameInfoLabelData;
    QGroupBox *infoGroupBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *seriesInfohorizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *airDateInfoLabel;
    QLabel *seasonInfoLabel;
    QLabel *totalEpisodesInfoLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *airDateInfoLabelData;
    QHBoxLayout *horizontalLayout_2;
    QLabel *seasonInfoLabelData;
    QLabel *ofInfoLabel;
    QLabel *totalSeasonInfoLabelData;
    QSpacerItem *horizontalSpacer;
    QLabel *totalEpisodesInfoLabelData;
    QGroupBox *plotGroupBox;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *plotTextVerticalLayout;
    QPlainTextEdit *plotPlainTextEdit;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_9;
    QWidget *centralControlElementWidget;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *controlElementshorizontalLayout;
    QGroupBox *pathGroupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *directorySelectionHorizontalLayout;
    QVBoxLayout *selectionButtonVerticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *selectionButton;
    QVBoxLayout *verticalLayout_6;
    QLabel *pathLabel;
    QHBoxLayout *directoryWidgetHorizontalLayout;
    QLineEdit *directPathInputLineEdit;
    QComboBox *pathStructure4ComboBox;
    QComboBox *pathStructure3ComboBox;
    QComboBox *pathStructure2ComboBox;
    QComboBox *pathStructure1ComboBox;
    QPushButton *pathStructureContentButton;
    QPushButton *directoryUpdateButton;
    QLabel *correctPathLabel;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *seriesGroupBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *seriesSelectionHorizontalLayout;
    QVBoxLayout *seriesVerticalLayout;
    QLabel *seriesLabel;
    QHBoxLayout *seriesLineEditHorizontalLayout;
    QLineEdit *seriesLineEdit;
    QLabel *correctSeriesLabel;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *seasonVerticalLayout;
    QLabel *seasonLabel;
    QComboBox *seasonComboBox;
    QVBoxLayout *languageVerticalLayout;
    QLabel *seriesLanguageLabel;
    QComboBox *seriesLanguageComboBox;
    QVBoxLayout *nameSchemeVerticalLayout;
    QLabel *nameSchemeLabel;
    QComboBox *nameSchemeComboBox;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *renameButton;
    QScrollArea *renameProgressScrollArea;
    QWidget *renameProgressWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *renamingProgressVerticalLayout;
    QHBoxLayout *renamingProgressLabelHorizontalLayout;
    QLabel *renamingLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *renamingProgressCurrentObjectLabel;
    QLabel *renamingProgressOfLabel;
    QLabel *renamingProgressTotalObjectsLabel;
    QSpacerItem *horizontalSpacer_5;
    QProgressBar *renamingProgressBar;
    QHBoxLayout *renamingProgressFileOutputHorizontalLayout;
    QLabel *renamingProgressFileOutputLabel;
    QSpacerItem *horizontalSpacer_6;
    QLabel *renamingProgressCurrentFileLabel;
    QSpacerItem *horizontalSpacer_7;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1500, 700);
        MainWindow->setMinimumSize(QSize(1050, 620));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/app_logo/seriesScraper_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(800, 500));
        centralWidget->setStyleSheet(QLatin1String("#renameButton {\n"
"	color: rgb(255, 255, 255);\n"
"	background-image: url(:/images/button_blue.png);\n"
"	border: none;\n"
"	outline: none;\n"
"}\n"
"\n"
"#renameButton:pressed {\n"
"	background-image: url(:/images/button_blue_pressed.png);\n"
"}\n"
"\n"
"#renameButton:!enabled {\n"
"	color: rgb(200, 200, 200);\n"
"	background-image: url(:/images/button_grey.png);\n"
"}\n"
"\n"
"#posterInfoLabel {\n"
"	border-radius: 5px;\n"
"    border: 2px solid #8c8c8c;\n"
"}"));
        episodeNameTable = new QTableWidget(centralWidget);
        episodeNameTable->setObjectName(QStringLiteral("episodeNameTable"));
        episodeNameTable->setGeometry(QRect(10, 10, 631, 420));
        episodeNameTable->setFocusPolicy(Qt::ClickFocus);
        episodeNameTable->setAutoFillBackground(false);
        episodeNameTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        additionalInfoScrollArea = new QScrollArea(centralWidget);
        additionalInfoScrollArea->setObjectName(QStringLiteral("additionalInfoScrollArea"));
        additionalInfoScrollArea->setGeometry(QRect(1000, 10, 201, 421));
        additionalInfoScrollArea->setFocusPolicy(Qt::NoFocus);
        additionalInfoScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        additionalInfoScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        additionalInfoScrollArea->setWidgetResizable(true);
        additionalInfoScrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 8, 199, 403));
        horizontalLayoutWidget_4 = new QWidget(scrollAreaWidgetContents);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 0, 191, 401));
        additionalScrollAreaHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        additionalScrollAreaHorizontalLayout->setSpacing(6);
        additionalScrollAreaHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        additionalScrollAreaHorizontalLayout->setObjectName(QStringLiteral("additionalScrollAreaHorizontalLayout"));
        additionalScrollAreaHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        additionalScrollAreaHorizontalLayout->addItem(horizontalSpacer_8);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        posterInfoLabel = new QLabel(horizontalLayoutWidget_4);
        posterInfoLabel->setObjectName(QStringLiteral("posterInfoLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(posterInfoLabel->sizePolicy().hasHeightForWidth());
        posterInfoLabel->setSizePolicy(sizePolicy);
        posterInfoLabel->setMinimumSize(QSize(80, 120));
        posterInfoLabel->setBaseSize(QSize(0, 9));
        posterInfoLabel->setLayoutDirection(Qt::LeftToRight);
        posterInfoLabel->setStyleSheet(QStringLiteral(""));
        posterInfoLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(posterInfoLabel);


        verticalLayout_3->addLayout(horizontalLayout);

        seriesNameInfoLabelData = new QLabel(horizontalLayoutWidget_4);
        seriesNameInfoLabelData->setObjectName(QStringLiteral("seriesNameInfoLabelData"));
        seriesNameInfoLabelData->setMinimumSize(QSize(0, 16));
        seriesNameInfoLabelData->setMaximumSize(QSize(16777215, 16));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        seriesNameInfoLabelData->setFont(font);
        seriesNameInfoLabelData->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(seriesNameInfoLabelData);

        infoGroupBox = new QGroupBox(horizontalLayoutWidget_4);
        infoGroupBox->setObjectName(QStringLiteral("infoGroupBox"));
        infoGroupBox->setMinimumSize(QSize(0, 82));
        infoGroupBox->setMaximumSize(QSize(16777215, 82));
        infoGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayoutWidget_2 = new QWidget(infoGroupBox);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 10, 181, 76));
        seriesInfohorizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        seriesInfohorizontalLayout->setSpacing(6);
        seriesInfohorizontalLayout->setContentsMargins(11, 11, 11, 11);
        seriesInfohorizontalLayout->setObjectName(QStringLiteral("seriesInfohorizontalLayout"));
        seriesInfohorizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        seriesInfohorizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 5, -1);
        airDateInfoLabel = new QLabel(horizontalLayoutWidget_2);
        airDateInfoLabel->setObjectName(QStringLiteral("airDateInfoLabel"));
        airDateInfoLabel->setFont(font);

        verticalLayout->addWidget(airDateInfoLabel);

        seasonInfoLabel = new QLabel(horizontalLayoutWidget_2);
        seasonInfoLabel->setObjectName(QStringLiteral("seasonInfoLabel"));
        seasonInfoLabel->setFont(font);

        verticalLayout->addWidget(seasonInfoLabel);

        totalEpisodesInfoLabel = new QLabel(horizontalLayoutWidget_2);
        totalEpisodesInfoLabel->setObjectName(QStringLiteral("totalEpisodesInfoLabel"));
        totalEpisodesInfoLabel->setFont(font);

        verticalLayout->addWidget(totalEpisodesInfoLabel);


        seriesInfohorizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        airDateInfoLabelData = new QLabel(horizontalLayoutWidget_2);
        airDateInfoLabelData->setObjectName(QStringLiteral("airDateInfoLabelData"));
        airDateInfoLabelData->setFont(font);

        verticalLayout_2->addWidget(airDateInfoLabelData);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        seasonInfoLabelData = new QLabel(horizontalLayoutWidget_2);
        seasonInfoLabelData->setObjectName(QStringLiteral("seasonInfoLabelData"));

        horizontalLayout_2->addWidget(seasonInfoLabelData);

        ofInfoLabel = new QLabel(horizontalLayoutWidget_2);
        ofInfoLabel->setObjectName(QStringLiteral("ofInfoLabel"));

        horizontalLayout_2->addWidget(ofInfoLabel);

        totalSeasonInfoLabelData = new QLabel(horizontalLayoutWidget_2);
        totalSeasonInfoLabelData->setObjectName(QStringLiteral("totalSeasonInfoLabelData"));

        horizontalLayout_2->addWidget(totalSeasonInfoLabelData);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        totalEpisodesInfoLabelData = new QLabel(horizontalLayoutWidget_2);
        totalEpisodesInfoLabelData->setObjectName(QStringLiteral("totalEpisodesInfoLabelData"));
        totalEpisodesInfoLabelData->setFont(font);

        verticalLayout_2->addWidget(totalEpisodesInfoLabelData);


        seriesInfohorizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(infoGroupBox);

        plotGroupBox = new QGroupBox(horizontalLayoutWidget_4);
        plotGroupBox->setObjectName(QStringLiteral("plotGroupBox"));
        verticalLayoutWidget_3 = new QWidget(plotGroupBox);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(30, 30, 81, 102));
        plotTextVerticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        plotTextVerticalLayout->setSpacing(6);
        plotTextVerticalLayout->setContentsMargins(11, 11, 11, 11);
        plotTextVerticalLayout->setObjectName(QStringLiteral("plotTextVerticalLayout"));
        plotTextVerticalLayout->setContentsMargins(0, 0, 0, 0);
        plotPlainTextEdit = new QPlainTextEdit(verticalLayoutWidget_3);
        plotPlainTextEdit->setObjectName(QStringLiteral("plotPlainTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plotPlainTextEdit->sizePolicy().hasHeightForWidth());
        plotPlainTextEdit->setSizePolicy(sizePolicy1);
        plotPlainTextEdit->setMinimumSize(QSize(0, 60));
        plotPlainTextEdit->setMaximumSize(QSize(16777215, 300));
        plotPlainTextEdit->setFocusPolicy(Qt::ClickFocus);
        plotPlainTextEdit->setFrameShape(QFrame::StyledPanel);
        plotPlainTextEdit->setFrameShadow(QFrame::Sunken);
        plotPlainTextEdit->setUndoRedoEnabled(false);
        plotPlainTextEdit->setReadOnly(true);
        plotPlainTextEdit->setCursorWidth(0);
        plotPlainTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        plotPlainTextEdit->setBackgroundVisible(false);

        plotTextVerticalLayout->addWidget(plotPlainTextEdit);


        verticalLayout_3->addWidget(plotGroupBox);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);


        additionalScrollAreaHorizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        additionalScrollAreaHorizontalLayout->addItem(horizontalSpacer_9);

        additionalInfoScrollArea->setWidget(scrollAreaWidgetContents);
        centralControlElementWidget = new QWidget(centralWidget);
        centralControlElementWidget->setObjectName(QStringLiteral("centralControlElementWidget"));
        centralControlElementWidget->setGeometry(QRect(10, 440, 1171, 200));
        centralControlElementWidget->setMinimumSize(QSize(0, 200));
        centralControlElementWidget->setMaximumSize(QSize(16777215, 200));
        horizontalLayoutWidget_5 = new QWidget(centralControlElementWidget);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(0, 0, 1161, 171));
        controlElementshorizontalLayout = new QHBoxLayout(horizontalLayoutWidget_5);
        controlElementshorizontalLayout->setSpacing(6);
        controlElementshorizontalLayout->setContentsMargins(11, 11, 11, 11);
        controlElementshorizontalLayout->setObjectName(QStringLiteral("controlElementshorizontalLayout"));
        controlElementshorizontalLayout->setContentsMargins(0, 0, 0, 0);
        pathGroupBox = new QGroupBox(horizontalLayoutWidget_5);
        pathGroupBox->setObjectName(QStringLiteral("pathGroupBox"));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        font1.setPointSize(11);
        pathGroupBox->setFont(font1);
        pathGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayoutWidget = new QWidget(pathGroupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 20, 907, 129));
        directorySelectionHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        directorySelectionHorizontalLayout->setSpacing(6);
        directorySelectionHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        directorySelectionHorizontalLayout->setObjectName(QStringLiteral("directorySelectionHorizontalLayout"));
        directorySelectionHorizontalLayout->setContentsMargins(5, 0, 5, 10);
        selectionButtonVerticalLayout = new QVBoxLayout();
        selectionButtonVerticalLayout->setSpacing(6);
        selectionButtonVerticalLayout->setObjectName(QStringLiteral("selectionButtonVerticalLayout"));
        verticalSpacer = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        selectionButtonVerticalLayout->addItem(verticalSpacer);

        selectionButton = new QPushButton(horizontalLayoutWidget);
        selectionButton->setObjectName(QStringLiteral("selectionButton"));
        selectionButton->setMinimumSize(QSize(90, 32));
        selectionButton->setMaximumSize(QSize(120, 32));
        selectionButton->setFont(font);

        selectionButtonVerticalLayout->addWidget(selectionButton);


        directorySelectionHorizontalLayout->addLayout(selectionButtonVerticalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        pathLabel = new QLabel(horizontalLayoutWidget);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy2);
        pathLabel->setMaximumSize(QSize(16777215, 13));
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(10);
        pathLabel->setFont(font2);
        pathLabel->setTextFormat(Qt::AutoText);
        pathLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        pathLabel->setMargin(0);
        pathLabel->setIndent(3);

        verticalLayout_6->addWidget(pathLabel);

        directoryWidgetHorizontalLayout = new QHBoxLayout();
        directoryWidgetHorizontalLayout->setSpacing(6);
        directoryWidgetHorizontalLayout->setObjectName(QStringLiteral("directoryWidgetHorizontalLayout"));
        directPathInputLineEdit = new QLineEdit(horizontalLayoutWidget);
        directPathInputLineEdit->setObjectName(QStringLiteral("directPathInputLineEdit"));
        directPathInputLineEdit->setMinimumSize(QSize(200, 20));
        directPathInputLineEdit->setMaximumSize(QSize(16777215, 20));

        directoryWidgetHorizontalLayout->addWidget(directPathInputLineEdit);

        pathStructure4ComboBox = new QComboBox(horizontalLayoutWidget);
        pathStructure4ComboBox->setObjectName(QStringLiteral("pathStructure4ComboBox"));
        pathStructure4ComboBox->setMinimumSize(QSize(100, 26));
        pathStructure4ComboBox->setMaximumSize(QSize(220, 26));
        pathStructure4ComboBox->setInsertPolicy(QComboBox::InsertAtBottom);

        directoryWidgetHorizontalLayout->addWidget(pathStructure4ComboBox);

        pathStructure3ComboBox = new QComboBox(horizontalLayoutWidget);
        pathStructure3ComboBox->setObjectName(QStringLiteral("pathStructure3ComboBox"));
        pathStructure3ComboBox->setMinimumSize(QSize(100, 26));
        pathStructure3ComboBox->setMaximumSize(QSize(220, 26));

        directoryWidgetHorizontalLayout->addWidget(pathStructure3ComboBox);

        pathStructure2ComboBox = new QComboBox(horizontalLayoutWidget);
        pathStructure2ComboBox->setObjectName(QStringLiteral("pathStructure2ComboBox"));
        pathStructure2ComboBox->setMinimumSize(QSize(100, 26));
        pathStructure2ComboBox->setMaximumSize(QSize(220, 26));

        directoryWidgetHorizontalLayout->addWidget(pathStructure2ComboBox);

        pathStructure1ComboBox = new QComboBox(horizontalLayoutWidget);
        pathStructure1ComboBox->setObjectName(QStringLiteral("pathStructure1ComboBox"));
        pathStructure1ComboBox->setMinimumSize(QSize(100, 26));
        pathStructure1ComboBox->setMaximumSize(QSize(300, 26));

        directoryWidgetHorizontalLayout->addWidget(pathStructure1ComboBox);

        pathStructureContentButton = new QPushButton(horizontalLayoutWidget);
        pathStructureContentButton->setObjectName(QStringLiteral("pathStructureContentButton"));
        pathStructureContentButton->setMinimumSize(QSize(50, 32));
        pathStructureContentButton->setMaximumSize(QSize(50, 16777215));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ui_icons/arrow_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        pathStructureContentButton->setIcon(icon1);

        directoryWidgetHorizontalLayout->addWidget(pathStructureContentButton);

        directoryUpdateButton = new QPushButton(horizontalLayoutWidget);
        directoryUpdateButton->setObjectName(QStringLiteral("directoryUpdateButton"));
        directoryUpdateButton->setEnabled(false);
        directoryUpdateButton->setMinimumSize(QSize(50, 32));
        directoryUpdateButton->setMaximumSize(QSize(50, 32));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ui_icons/update.png"), QSize(), QIcon::Normal, QIcon::On);
        directoryUpdateButton->setIcon(icon2);

        directoryWidgetHorizontalLayout->addWidget(directoryUpdateButton);

        correctPathLabel = new QLabel(horizontalLayoutWidget);
        correctPathLabel->setObjectName(QStringLiteral("correctPathLabel"));

        directoryWidgetHorizontalLayout->addWidget(correctPathLabel);


        verticalLayout_6->addLayout(directoryWidgetHorizontalLayout);


        directorySelectionHorizontalLayout->addLayout(verticalLayout_6);


        controlElementshorizontalLayout->addWidget(pathGroupBox);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        controlElementshorizontalLayout->addItem(horizontalSpacer_2);

        seriesGroupBox = new QGroupBox(horizontalLayoutWidget_5);
        seriesGroupBox->setObjectName(QStringLiteral("seriesGroupBox"));
        seriesGroupBox->setFont(font1);
        seriesGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayoutWidget_3 = new QWidget(seriesGroupBox);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 20, 575, 101));
        seriesSelectionHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        seriesSelectionHorizontalLayout->setSpacing(6);
        seriesSelectionHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        seriesSelectionHorizontalLayout->setObjectName(QStringLiteral("seriesSelectionHorizontalLayout"));
        seriesSelectionHorizontalLayout->setContentsMargins(10, 0, 10, 10);
        seriesVerticalLayout = new QVBoxLayout();
        seriesVerticalLayout->setSpacing(6);
        seriesVerticalLayout->setObjectName(QStringLiteral("seriesVerticalLayout"));
        seriesLabel = new QLabel(horizontalLayoutWidget_3);
        seriesLabel->setObjectName(QStringLiteral("seriesLabel"));
        seriesLabel->setMaximumSize(QSize(16777215, 18));
        seriesLabel->setFont(font2);
        seriesLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        seriesVerticalLayout->addWidget(seriesLabel);

        seriesLineEditHorizontalLayout = new QHBoxLayout();
        seriesLineEditHorizontalLayout->setSpacing(6);
        seriesLineEditHorizontalLayout->setObjectName(QStringLiteral("seriesLineEditHorizontalLayout"));
        seriesLineEdit = new QLineEdit(horizontalLayoutWidget_3);
        seriesLineEdit->setObjectName(QStringLiteral("seriesLineEdit"));
        seriesLineEdit->setMinimumSize(QSize(120, 20));
        seriesLineEdit->setMaximumSize(QSize(200, 20));
        seriesLineEdit->setFont(font);
        seriesLineEdit->setAutoFillBackground(false);

        seriesLineEditHorizontalLayout->addWidget(seriesLineEdit);

        correctSeriesLabel = new QLabel(horizontalLayoutWidget_3);
        correctSeriesLabel->setObjectName(QStringLiteral("correctSeriesLabel"));
        correctSeriesLabel->setMinimumSize(QSize(20, 20));
        correctSeriesLabel->setMaximumSize(QSize(20, 20));

        seriesLineEditHorizontalLayout->addWidget(correctSeriesLabel);


        seriesVerticalLayout->addLayout(seriesLineEditHorizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        seriesVerticalLayout->addItem(verticalSpacer_3);


        seriesSelectionHorizontalLayout->addLayout(seriesVerticalLayout);

        seasonVerticalLayout = new QVBoxLayout();
        seasonVerticalLayout->setSpacing(6);
        seasonVerticalLayout->setObjectName(QStringLiteral("seasonVerticalLayout"));
        seasonLabel = new QLabel(horizontalLayoutWidget_3);
        seasonLabel->setObjectName(QStringLiteral("seasonLabel"));
        seasonLabel->setMaximumSize(QSize(16777215, 18));
        seasonLabel->setFont(font2);
        seasonLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        seasonVerticalLayout->addWidget(seasonLabel);

        seasonComboBox = new QComboBox(horizontalLayoutWidget_3);
        seasonComboBox->setObjectName(QStringLiteral("seasonComboBox"));
        seasonComboBox->setMinimumSize(QSize(50, 26));
        seasonComboBox->setMaximumSize(QSize(50, 26));
        seasonComboBox->setFont(font);

        seasonVerticalLayout->addWidget(seasonComboBox);


        seriesSelectionHorizontalLayout->addLayout(seasonVerticalLayout);

        languageVerticalLayout = new QVBoxLayout();
        languageVerticalLayout->setSpacing(6);
        languageVerticalLayout->setObjectName(QStringLiteral("languageVerticalLayout"));
        seriesLanguageLabel = new QLabel(horizontalLayoutWidget_3);
        seriesLanguageLabel->setObjectName(QStringLiteral("seriesLanguageLabel"));
        seriesLanguageLabel->setMaximumSize(QSize(16777215, 18));
        seriesLanguageLabel->setFont(font2);
        seriesLanguageLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        languageVerticalLayout->addWidget(seriesLanguageLabel);

        seriesLanguageComboBox = new QComboBox(horizontalLayoutWidget_3);
        seriesLanguageComboBox->setObjectName(QStringLiteral("seriesLanguageComboBox"));
        seriesLanguageComboBox->setMinimumSize(QSize(85, 26));
        seriesLanguageComboBox->setMaximumSize(QSize(130, 26));
        seriesLanguageComboBox->setFont(font);

        languageVerticalLayout->addWidget(seriesLanguageComboBox);


        seriesSelectionHorizontalLayout->addLayout(languageVerticalLayout);

        nameSchemeVerticalLayout = new QVBoxLayout();
        nameSchemeVerticalLayout->setSpacing(6);
        nameSchemeVerticalLayout->setObjectName(QStringLiteral("nameSchemeVerticalLayout"));
        nameSchemeLabel = new QLabel(horizontalLayoutWidget_3);
        nameSchemeLabel->setObjectName(QStringLiteral("nameSchemeLabel"));
        nameSchemeLabel->setEnabled(true);
        nameSchemeLabel->setMaximumSize(QSize(16777215, 18));
        nameSchemeLabel->setFont(font2);
        nameSchemeLabel->setScaledContents(false);
        nameSchemeLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        nameSchemeVerticalLayout->addWidget(nameSchemeLabel);

        nameSchemeComboBox = new QComboBox(horizontalLayoutWidget_3);
        nameSchemeComboBox->setObjectName(QStringLiteral("nameSchemeComboBox"));
        nameSchemeComboBox->setMinimumSize(QSize(95, 26));
        nameSchemeComboBox->setMaximumSize(QSize(160, 26));
        nameSchemeComboBox->setFont(font);

        nameSchemeVerticalLayout->addWidget(nameSchemeComboBox);


        seriesSelectionHorizontalLayout->addLayout(nameSchemeVerticalLayout);


        controlElementshorizontalLayout->addWidget(seriesGroupBox);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        controlElementshorizontalLayout->addItem(horizontalSpacer_3);

        renameButton = new QPushButton(horizontalLayoutWidget_5);
        renameButton->setObjectName(QStringLiteral("renameButton"));
        renameButton->setMinimumSize(QSize(120, 60));
        renameButton->setMaximumSize(QSize(120, 60));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI"));
        font3.setBold(false);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setKerning(true);
        font3.setStyleStrategy(QFont::PreferDefault);
        renameButton->setFont(font3);
        renameButton->setCursor(QCursor(Qt::PointingHandCursor));
        renameButton->setAutoFillBackground(false);
        renameButton->setStyleSheet(QLatin1String("#renameButton {\n"
"	color: rgb(255, 255, 255);\n"
"	background-image: url(:/ui_icons/button_blue.png);\n"
"	border: none;\n"
"	outline: none;\n"
"}\n"
"\n"
"#renameButton:pressed {\n"
"	background-image: url(:/ui_icons/button_blue_pressed.png);\n"
"}\n"
"\n"
"#renameButton:!enabled {\n"
"	color: rgb(200, 200, 200);\n"
"	background-image: url(:/ui_icons/button_grey.png);\n"
"}\n"
"\n"
"#posterInfoLabel {\n"
"	border-radius: 5px;\n"
"    border: 2px solid #8c8c8c;\n"
"}"));
        renameButton->setCheckable(false);
        renameButton->setAutoRepeat(false);
        renameButton->setAutoRepeatDelay(300);
        renameButton->setAutoDefault(false);
        renameButton->setFlat(false);

        controlElementshorizontalLayout->addWidget(renameButton);

        renameProgressScrollArea = new QScrollArea(centralWidget);
        renameProgressScrollArea->setObjectName(QStringLiteral("renameProgressScrollArea"));
        renameProgressScrollArea->setGeometry(QRect(60, 20, 500, 100));
        renameProgressScrollArea->setFocusPolicy(Qt::NoFocus);
        renameProgressScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        renameProgressScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        renameProgressScrollArea->setWidgetResizable(true);
        renameProgressWidget = new QWidget();
        renameProgressWidget->setObjectName(QStringLiteral("renameProgressWidget"));
        renameProgressWidget->setGeometry(QRect(0, 0, 498, 98));
        verticalLayoutWidget = new QWidget(renameProgressWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 501, 101));
        renamingProgressVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
        renamingProgressVerticalLayout->setSpacing(6);
        renamingProgressVerticalLayout->setContentsMargins(11, 11, 11, 11);
        renamingProgressVerticalLayout->setObjectName(QStringLiteral("renamingProgressVerticalLayout"));
        renamingProgressVerticalLayout->setContentsMargins(10, 10, 10, 10);
        renamingProgressLabelHorizontalLayout = new QHBoxLayout();
        renamingProgressLabelHorizontalLayout->setSpacing(6);
        renamingProgressLabelHorizontalLayout->setObjectName(QStringLiteral("renamingProgressLabelHorizontalLayout"));
        renamingLabel = new QLabel(verticalLayoutWidget);
        renamingLabel->setObjectName(QStringLiteral("renamingLabel"));

        renamingProgressLabelHorizontalLayout->addWidget(renamingLabel);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        renamingProgressLabelHorizontalLayout->addItem(horizontalSpacer_4);

        renamingProgressCurrentObjectLabel = new QLabel(verticalLayoutWidget);
        renamingProgressCurrentObjectLabel->setObjectName(QStringLiteral("renamingProgressCurrentObjectLabel"));

        renamingProgressLabelHorizontalLayout->addWidget(renamingProgressCurrentObjectLabel);

        renamingProgressOfLabel = new QLabel(verticalLayoutWidget);
        renamingProgressOfLabel->setObjectName(QStringLiteral("renamingProgressOfLabel"));

        renamingProgressLabelHorizontalLayout->addWidget(renamingProgressOfLabel);

        renamingProgressTotalObjectsLabel = new QLabel(verticalLayoutWidget);
        renamingProgressTotalObjectsLabel->setObjectName(QStringLiteral("renamingProgressTotalObjectsLabel"));

        renamingProgressLabelHorizontalLayout->addWidget(renamingProgressTotalObjectsLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        renamingProgressLabelHorizontalLayout->addItem(horizontalSpacer_5);


        renamingProgressVerticalLayout->addLayout(renamingProgressLabelHorizontalLayout);

        renamingProgressBar = new QProgressBar(verticalLayoutWidget);
        renamingProgressBar->setObjectName(QStringLiteral("renamingProgressBar"));
        renamingProgressBar->setValue(24);

        renamingProgressVerticalLayout->addWidget(renamingProgressBar);

        renamingProgressFileOutputHorizontalLayout = new QHBoxLayout();
        renamingProgressFileOutputHorizontalLayout->setSpacing(6);
        renamingProgressFileOutputHorizontalLayout->setObjectName(QStringLiteral("renamingProgressFileOutputHorizontalLayout"));
        renamingProgressFileOutputLabel = new QLabel(verticalLayoutWidget);
        renamingProgressFileOutputLabel->setObjectName(QStringLiteral("renamingProgressFileOutputLabel"));

        renamingProgressFileOutputHorizontalLayout->addWidget(renamingProgressFileOutputLabel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        renamingProgressFileOutputHorizontalLayout->addItem(horizontalSpacer_6);

        renamingProgressCurrentFileLabel = new QLabel(verticalLayoutWidget);
        renamingProgressCurrentFileLabel->setObjectName(QStringLiteral("renamingProgressCurrentFileLabel"));

        renamingProgressFileOutputHorizontalLayout->addWidget(renamingProgressCurrentFileLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        renamingProgressFileOutputHorizontalLayout->addItem(horizontalSpacer_7);


        renamingProgressVerticalLayout->addLayout(renamingProgressFileOutputHorizontalLayout);

        renameProgressScrollArea->setWidget(renameProgressWidget);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1500, 22));
        menuBar->setNativeMenuBar(true);
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(seriesLineEdit, seasonComboBox);
        QWidget::setTabOrder(seasonComboBox, seriesLanguageComboBox);
        QWidget::setTabOrder(seriesLanguageComboBox, nameSchemeComboBox);
        QWidget::setTabOrder(nameSchemeComboBox, renameButton);
        QWidget::setTabOrder(renameButton, selectionButton);
        QWidget::setTabOrder(selectionButton, directPathInputLineEdit);
        QWidget::setTabOrder(directPathInputLineEdit, pathStructure4ComboBox);
        QWidget::setTabOrder(pathStructure4ComboBox, pathStructure3ComboBox);
        QWidget::setTabOrder(pathStructure3ComboBox, pathStructure2ComboBox);
        QWidget::setTabOrder(pathStructure2ComboBox, pathStructure1ComboBox);
        QWidget::setTabOrder(pathStructure1ComboBox, pathStructureContentButton);
        QWidget::setTabOrder(pathStructureContentButton, directoryUpdateButton);
        QWidget::setTabOrder(directoryUpdateButton, renameProgressScrollArea);
        QWidget::setTabOrder(renameProgressScrollArea, plotPlainTextEdit);
        QWidget::setTabOrder(plotPlainTextEdit, additionalInfoScrollArea);
        QWidget::setTabOrder(additionalInfoScrollArea, episodeNameTable);

        retranslateUi(MainWindow);

        renameButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SeriesScraper", nullptr));
        posterInfoLabel->setText(QString());
        seriesNameInfoLabelData->setText(QApplication::translate("MainWindow", "seriesName", nullptr));
        infoGroupBox->setTitle(QApplication::translate("MainWindow", "Series information", nullptr));
        airDateInfoLabel->setText(QApplication::translate("MainWindow", "Air date:", nullptr));
        seasonInfoLabel->setText(QApplication::translate("MainWindow", "Season:", nullptr));
        totalEpisodesInfoLabel->setText(QApplication::translate("MainWindow", "Episode number: ", nullptr));
        airDateInfoLabelData->setText(QApplication::translate("MainWindow", "aD", nullptr));
        seasonInfoLabelData->setText(QApplication::translate("MainWindow", "s", nullptr));
        ofInfoLabel->setText(QApplication::translate("MainWindow", "/", nullptr));
        totalSeasonInfoLabelData->setText(QApplication::translate("MainWindow", "ts", nullptr));
        totalEpisodesInfoLabelData->setText(QApplication::translate("MainWindow", "te", nullptr));
        plotGroupBox->setTitle(QApplication::translate("MainWindow", "Plot", nullptr));
        pathGroupBox->setTitle(QApplication::translate("MainWindow", "Directory selection", nullptr));
        selectionButton->setText(QApplication::translate("MainWindow", "Selection", nullptr));
        pathLabel->setText(QApplication::translate("MainWindow", "Path", nullptr));
        pathStructureContentButton->setText(QString());
        directoryUpdateButton->setText(QString());
        correctPathLabel->setText(QString());
        seriesGroupBox->setTitle(QApplication::translate("MainWindow", "Series selection", nullptr));
        seriesLabel->setText(QApplication::translate("MainWindow", "Series", nullptr));
        correctSeriesLabel->setText(QString());
        seasonLabel->setText(QApplication::translate("MainWindow", "Season", nullptr));
        seriesLanguageLabel->setText(QApplication::translate("MainWindow", "Language", nullptr));
        nameSchemeLabel->setText(QApplication::translate("MainWindow", "Name scheme", nullptr));
        renameButton->setText(QApplication::translate("MainWindow", "Rename", nullptr));
        renamingLabel->setText(QApplication::translate("MainWindow", "Renaming:", nullptr));
        renamingProgressCurrentObjectLabel->setText(QApplication::translate("MainWindow", "1", nullptr));
        renamingProgressOfLabel->setText(QApplication::translate("MainWindow", "/", nullptr));
        renamingProgressTotalObjectsLabel->setText(QApplication::translate("MainWindow", "7", nullptr));
        renamingProgressFileOutputLabel->setText(QApplication::translate("MainWindow", "File:", nullptr));
        renamingProgressCurrentFileLabel->setText(QApplication::translate("MainWindow", "fileS01.avi", nullptr));
#ifndef QT_NO_TOOLTIP
        statusBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        statusBar->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
