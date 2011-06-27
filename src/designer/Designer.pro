#-------------------------------------------------
#
# Project created by QtCreator 2011-06-23T16:49:44
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = Designer
TEMPLATE = app

# Designer main UI

SOURCES +=\
    DesignerMainWnd.cpp \
    Designer.cpp \
    DesignerWelcomeDialog.cpp \
    DesignerViewItf.cpp \
    DesignerDocItf.cpp \

HEADERS  += DesignerMainWnd.h \
    DesignerWelcomeDialog.h \
    DesignerViewItf.h \
    DesignerDocItf.h \

FORMS    += DesignerMainWnd.ui \
    DesignerWelcomeDialog.ui

# views

## assembly view

SOURCES += \
    views\\assemblyview\\DesignerAssemblyView.cpp

HEADERS  += \
    views\\assemblyview\\DesignerAssemblyView.h

FORMS    += \
    views\\assemblyview\\DesignerAssemblyView.ui

## network view

SOURCES += \
    views\\networkview\\DesignerNetworkView.cpp \
    views\\networkview\\DesignerNetworkView_SBMLHighlighter.cpp

HEADERS  += \
    views\\networkview\\DesignerNetworkView_SBMLHighlighter.h \
    views\\networkview\\DesignerNetworkView.h

FORMS    += \
    views\\networkview\\DesignerNetworkView.ui

## behavior view

SOURCES += \
    views\\behaviorview\\DesignerBehaviorView.cpp

HEADERS  += \
    views\\behaviorview\\DesignerBehaviorView.h

FORMS    += \
    views\\behaviorview\\DesignerBehaviorView.ui
