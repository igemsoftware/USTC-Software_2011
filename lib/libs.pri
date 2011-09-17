
include($$PWD/qtmmlwidget-2.4_1-opensource/src/qtmmlwidget.pri)

include($$PWD/qtpropertybrowser-2.5_1-opensource/src/qtpropertybrowser.pri)

include($$PWD/qtsingleapplication-2.6_1-opensource/src/qtsingleapplication.pri)

include($$PWD/qwtplot3d-0.2.7/qwtplot3d.pri)

include($$PWD/qwt-6.0.0/src/qwt.pri)

#gsl
LIBS += -L$$PWD/gsl/lib -lgsl -lgslcblas
INCLUDEPATH += $$PWD/gsl/include
