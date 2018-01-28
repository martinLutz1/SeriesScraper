TEMPLATE = subdirs
 
SUBDIRS = \
    SeriesScraperTest \
    SeriesScraperApp \
    SeriesScraperLib

SeriesScraperLib.subdir = SeriesScraperLib
SeriesScraperApp.subdir = SeriesScraperApp
SeriesScraperTest.subdir = SeriesScraperTest

SeriesScraperApp.depends = SeriesScraperLib
SeriesScraperTest.depends = SeriesScraperLib
