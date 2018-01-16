TEMPLATE = subdirs
 
SUBDIRS = \
    SeriesScraperApp \
    SeriesScraperTest \
    SeriesScraperLib
 
SeriesScraperApp.subdir = SeriesScraperApp
SeriesScraperTest.subdir = SeriesScraperTest
SeriesScraperLib.subdir = SeriesScraperLib

SeriesScraperApp.depends = SeriesScraperLib
SeriesScraperTest.depends = SeriesScraperLib