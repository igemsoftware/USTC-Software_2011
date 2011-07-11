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
    DesignerDebug.cpp \
    DesignerExtensionItf.cpp \
    views/welcomeview/WelcomeView.cpp \
    views/assemblyview/AssemblyView.cpp \
    views/sbmleditorview/SBMLEditorView.cpp \
    views/sbmleditorview/SBMLEditorViewHighlighter.cpp \
    views/networkview/NetworkView.cpp \
    views/common/MainWndTabWidget.cpp \
    views/behaviorview/BehaviorView.cpp \
    models/common/MoDeLDoc.cpp \
    models/common/MoDeLDocParser.cpp \
    documents/MoDeL/MoDeLDocParser.cpp \
    documents/MoDeL/MoDeLDoc.cpp \
    views/behaviorview/BehaviorView.cpp \
    common/widgets/MainWndTabWidget.cpp \
    views/filedescriptionview/FileDescriptionView.cpp \
    views/networkview/NetworkViewGraphicsSceneContainer.cpp

HEADERS  += DesignerMainWnd.h \
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
    DesignerDebug.h \
    DesignerExtensionItf.h \
    views/welcomeview/WelcomeView.h \
    views/assemblyview/AssemblyView.h \
    views/sbmleditorview/SBMLEditorView.h \
    views/sbmleditorview/SBMLEditorViewHighlighter.h \
    views/networkview/NetworkView.h \
    views/common/MainWndTabWidget.h \
    views/behaviorview/BehaviorView.h \
    models/common/MoDeLDocParser.h \
    documents/MoDeL/MoDeLDocParser.h \
    documents/MoDeL/MoDeLDoc.h \
    common/widgets/MainWndTabWidget.h \
    views/filedescriptionview/FileDescriptionView.h \
    views/networkview/NetworkViewGraphicsSceneContainer.h

FORMS    += DesignerMainWnd.ui \
    DesignerChooseViewDialog.ui \
    views/welcomeview/WelcomeView.ui \
    views/behaviorview/BehaviorView.ui \
    views/filedescriptionview/FileDescriptionView.ui

# views

## assembly view

SOURCES +=

HEADERS  +=

FORMS    +=

## network view

SOURCES +=

HEADERS  +=

FORMS    +=

## behavior view

SOURCES +=

HEADERS  +=

FORMS    +=

RESOURCES += \
    resources/DesignerResources.qrc

OTHER_FILES += \
    models/reactionnetworkmodel/ReactionNetworkDataTypes.prototype
