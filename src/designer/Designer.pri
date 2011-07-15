# Designer main UI

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


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
    views/assemblyview/AssemblyPropertyWidget.cpp \
    views/assemblyview/AssemblySearchWidget.cpp \
    DesignerDebug.cpp \
    DesignerExtensionItf.cpp \
    views/welcomeview/WelcomeView.cpp \
    views/assemblyview/AssemblyView.cpp \
    views/sbmleditorview/SBMLEditorView.cpp \
    views/sbmleditorview/SBMLEditorViewHighlighter.cpp \
    views/networkview/NetworkView.cpp \
    views/behaviorview/BehaviorView.cpp \
    common/widgets/MainWndTabWidget.cpp \
    views/filedescriptionview/FileDescriptionView.cpp \
    views/networkview/NetworkViewGraphicsSceneContainer.cpp \
    common/panels/propertypanel/DesignerPropertiesPanelWidget.cpp \
    views/networkview/NetworkViewGraphicsItem.cpp \
    src/designer/views/plot3dview/Plot3DView.cpp \
    src/designer/views/partview/PartView.cpp \
    src/designer/views/odeview/ODEView.cpp \
    src/designer/views/aboutview/AboutView.cpp

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
    views/assemblyview/AssemblyPropertyWidget.h \
    views/assemblyview/AssemblySearchWidget.h \
    DesignerDebug.h \
    DesignerExtensionItf.h \
    views/welcomeview/WelcomeView.h \
    views/assemblyview/AssemblyView.h \
    views/sbmleditorview/SBMLEditorView.h \
    views/sbmleditorview/SBMLEditorViewHighlighter.h \
    views/networkview/NetworkView.h \
    views/behaviorview/BehaviorView.h \
    common/widgets/MainWndTabWidget.h \
    views/filedescriptionview/FileDescriptionView.h \
    views/networkview/NetworkViewGraphicsSceneContainer.h \
    common/panels/propertypanel/DesignerPropertiesPanelWidget.h \
    views/networkview/NetworkViewGraphicsItem.h \
    src/designer/views/plot3dview/Plot3DView.h \
    src/designer/views/partview/PartView.h \
    src/designer/views/odeview/ODEView.h \
    src/designer/views/aboutview/AboutView.h

FORMS    += DesignerMainWnd.ui \
    views/welcomeview/WelcomeView.ui \
    views/behaviorview/BehaviorView.ui \
    views/filedescriptionview/FileDescriptionView.ui \
    src/designer/views/partview/PartView.ui \
    src/designer/views/aboutview/AboutView.ui

RESOURCES += \
    resources/DesignerResources.qrc

OTHER_FILES += \
    models/reactionnetworkmodel/ReactionNetworkDataTypes.prototype
