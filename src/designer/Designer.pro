#-------------------------------------------------
#
# Project created by QtCreator 2011-06-23T16:49:44
#
#-------------------------------------------------

QT       += core gui script scripttools xml

TARGET = Designer
TEMPLATE = app

# Designer main UI

SOURCES +=\
    DesignerMainWnd.cpp \
    Designer.cpp \
    DesignerWelcomeDialog.cpp \
    DesignerViewItf.cpp \
    DesignerDocItf.cpp \
    views/assemblyview/AssemblyItemPlasmid.cpp \
    views/assemblyview/AssemblyItemCompartment.cpp \
    views/assemblyview/AssemblyScene.cpp \
    views/assemblyview/AssemblyCreateAndDrag.cpp \
    DesignerModelItf.cpp \
    models/reactionnetworkmodel/ReactionNetwork.cpp \
    views/networkview/NetworkViewGraphicsScene.cpp \
    views/networkview/NetworkViewGraphicsSceneEdge.cpp \
    views/networkview/NetworkViewGraphicsSceneNode.cpp \
    views/networkview/NetworkViewGraphicsSceneNodeSubstance.cpp \
    views/networkview/NetworkViewGraphicsSceneNodeReaction.cpp \
    views/networkview/NetworkViewGraphicsSceneLabel.cpp \
    views/assemblyview/AssemblyItemBase.cpp \
    views/assemblyview/AssemblyItemPart.cpp \
    views/behaviorview/BehaviorViewPlotWidget.cpp \
    documents/SBML/SBMLDoc.cpp \
    documents/SBML/SBMLDocParser.cpp \
    DesignerChooseViewDialog.cpp \
    views/assemblyview/AssemblyPropertyWidget.cpp \
    views/assemblyview/AssemblySearchWidget.cpp \
    DesignerDebug.cpp

HEADERS  += DesignerMainWnd.h \
    DesignerWelcomeDialog.h \
    DesignerViewItf.h \
    DesignerDocItf.h \
    views/assemblyview/AssemblyItemPlasmid.h \
    views/assemblyview/AssemblyItemCompartment.h \
    views/assemblyview/AssemblyScene.h \
    views/assemblyview/AssemblyLib.h \
    views/assemblyview/AssemblyCreateAndDrag.h \
    DesignerModelItf.h \
    models/common/ModelSymbol.h \
    views/networkview/NetworkViewGraphicsScene.h \
    views/networkview/NetworkViewGraphicsSceneEdge.h \
    views/networkview/NetworkViewGraphicsSceneNode.h \
    views/networkview/NetworkViewGraphicsSceneNodeSubstance.h \
    views/networkview/NetworkViewGraphicsSceneNodeReaction.h \
    views/networkview/NetworkViewGraphicsSceneLabel.h \
    views/assemblyview/AssemblyItemBase.h\
    models/reactionnetworkmodel/ReactionNetworkDataTypes.h \
    models/reactionnetworkmodel/ReactionNetwork.h \
    views/assemblyview/AssemblyItemPart.h \
    views/behaviorview/BehaviorViewPlotWidget.h \
    documents/SBML/SBMLDoc.h \
    documents/SBML/SBMLDocParser.h \
    models/reactionnetworkmodel/ReactionNetworkSBMLImportProxy.h \
    DesignerChooseViewDialog.h \
    views/assemblyview/AssemblyPropertyWidget.h \
    views/assemblyview/AssemblySearchWidget.h \
    DesignerDebug.h

FORMS    += DesignerMainWnd.ui \
    DesignerWelcomeDialog.ui \
    DesignerChooseViewDialog.ui

# views

## assembly view

SOURCES += \
    views/assemblyview/DesignerAssemblyView.cpp

HEADERS  += \
    views/assemblyview/DesignerAssemblyView.h

FORMS    += \
    views/assemblyview/DesignerAssemblyView.ui

## network view

SOURCES += \
    views/networkview/DesignerNetworkView.cpp \
    views/networkview/DesignerNetworkView_SBMLHighlighter.cpp

HEADERS  += \
    views/networkview/DesignerNetworkView_SBMLHighlighter.h \
    views/networkview/DesignerNetworkView.h

FORMS    += \
    views/networkview/DesignerNetworkView.ui

## behavior view

SOURCES += \
    views/behaviorview/DesignerBehaviorView.cpp

HEADERS  += \
    views/behaviorview/DesignerBehaviorView.h

FORMS    += \
    views/behaviorview/DesignerBehaviorView.ui

RESOURCES += \
    resources/DesignerResources.qrc

INCLUDEPATH += views/behaviorview

OTHER_FILES += \
    models/reactionnetworkmodel/ReactionNetworkDataTypes.prototype
