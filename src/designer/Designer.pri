# Designer main UI

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT +=sql

SOURCES +=\
    Designer.cpp \
    views/assemblyview/AssemblyItemPlasmid.cpp \
    views/assemblyview/AssemblyItemCompartment.cpp \
    views/assemblyview/AssemblyScene.cpp \
    views/assemblyview/AssemblyCreateAndDrag.cpp \
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
    views/assemblyview/AssemblyPropertyWidget.cpp \
    views/assemblyview/AssemblySearchWidget.cpp \
    DesignerDebug.cpp \
    views/welcomeview/WelcomeView.cpp \
    views/assemblyview/AssemblyView.cpp \
    views/sbmleditorview/SBMLEditorView.cpp \
    views/sbmleditorview/SBMLEditorViewHighlighter.cpp \    
    views/behaviorview/BehaviorView.cpp \
    documents/MoDeL/MoDeLDocParser.cpp \
    documents/MoDeL/MoDeLDoc.cpp \
    common/widgets/MainWndTabWidget.cpp \
    views/filedescriptionview/FileDescriptionView.cpp \
    views/networkview/NetworkViewGraphicsSceneContainer.cpp \
    common/panels/propertypanel/DesignerPropertiesPanelWidget.cpp \
    views/networkview/NetworkViewGraphicsItem.cpp \
    models/common/ModelSymbol.cpp \
    src/designer/views/plot3dview/Plot3DView.cpp \
    src/designer/views/partview/PartView.cpp \
    src/designer/views/odeview/ODEView.cpp \
    src/designer/views/aboutview/AboutView.cpp \
    src/designer/views/clothodbview/ClothoDBView.cpp \
    src/designer/interfaces/DesignerViewItf.cpp \
    src/designer/interfaces/DesignerModelItf.cpp \
    src/designer/interfaces/DesignerExtensionItf.cpp \
    src/designer/interfaces/DesignerDocItf.cpp \
    src/designer/views/webpageview/WebPageView.cpp \
    src/designer/models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.cpp \
    src/designer/documents/RSBPML/RSBPMLDoc.cpp \
    src/designer/documents/RSBPML/RSBPMLParser.cpp \
    src/designer/documents/common/designerxmldocparser/DesignerXMLDocParser.cpp \
    src/designer/documents/SBOL/SBOLDoc.cpp \
    src/designer/documents/SBOL/SBOLParser.cpp \
    src/designer/documents/SBML/SBMLParser.cpp \
    src/designer/documents/FASTA/FASTADocParser.cpp \
    src/designer/documents/FASTA/FASTADoc.cpp \
    src/designer/documents/EMBL/EMBLDocParser.cpp \
    src/designer/documents/EMBL/EMBLDoc.cpp \
    src/designer/documents/GENBANK/GENBANKDoc.cpp \
    src/designer/documents/GENBANK/GENBANKDocParser.cpp \
    src/designer/documents/common/designerpartdocparser/DesignerPartDocParser.cpp \
    src/designer/documents/MoDeL_1/MoDeL1Parser.cpp \
    src/designer/documents/MoDeL_1/MoDeL1Doc.cpp \
    src/designer/documents/USML/USMLDoc.cpp \
    src/designer/documents/USML/USMLParser.cpp \
    src/designer/common/app/DesignerApp.cpp \
    src/designer/common/mainwnd/DesignerMainWnd.cpp \
    src/designer/views/assemblyview/AssemblyItemMolecule.cpp \
    src/designer/models/igamemodel/IGame.cpp \
    src/designer/views/assemblyview/AssemblyPropertyEditor.cpp \
    src/designer/views/assemblyview/AssemblyDBEditor.cpp \
    src/designer/views/behaviorview/BehaviorViewInterp.cpp \
    src/designer/common/drawwnd/DesignerDrawWnd.cpp \
    src/designer/common/drawwnd/DesignerDrawWidget.cpp \
    src/designer/views/networkview/Layouter/main.cpp \
    src/designer/views/networkview/Layouter/lagraphlayouterthread.cpp \
    src/designer/views/networkview/Layouter/lagraphlayouter.cpp \
    src/designer/views/networkview/NetworkView.cpp \
    src/designer/views/networkview/NetworkViewButton.cpp


HEADERS  += \
    views/assemblyview/AssemblyItemPlasmid.h \
    views/assemblyview/AssemblyItemCompartment.h \
    views/assemblyview/AssemblyScene.h \
    views/assemblyview/AssemblyLib.h \
    views/assemblyview/AssemblyCreateAndDrag.h \
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
    views/assemblyview/AssemblyPropertyWidget.h \
    views/assemblyview/AssemblySearchWidget.h \
    DesignerDebug.h \
    views/welcomeview/WelcomeView.h \
    views/assemblyview/AssemblyView.h \
    views/sbmleditorview/SBMLEditorView.h \
    views/sbmleditorview/SBMLEditorViewHighlighter.h \    
    views/behaviorview/BehaviorView.h \
    documents/MoDeL/MoDeLDocParser.h \
    documents/MoDeL/MoDeLDoc.h \
    common/widgets/MainWndTabWidget.h \
    views/filedescriptionview/FileDescriptionView.h \
    views/networkview/NetworkViewGraphicsSceneContainer.h \
    common/panels/propertypanel/DesignerPropertiesPanelWidget.h \
    views/networkview/NetworkViewGraphicsItem.h \
    src/designer/views/plot3dview/Plot3DView.h \
    src/designer/views/partview/PartView.h \
    src/designer/views/odeview/ODEView.h \
    src/designer/views/aboutview/AboutView.h \
    src/designer/views/clothodbview/ClothoDBView.h \
    src/designer/models/common/ModelFunction.h \
    src/designer/interfaces/DesignerViewItf.h \
    src/designer/interfaces/DesignerModelItf.h \
    src/designer/interfaces/DesignerExtensionItf.h \
    src/designer/interfaces/DesignerDocItf.h \
    src/designer/common/utils/itemregistry/ItemRegistry.h \
    src/designer/interfaces/DesignerInterface.h \
    src/designer/views/webpageview/WebPageView.h \
    src/designer/models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h \
    src/designer/documents/RSBPML/RSBPMLDoc.h \
    src/designer/documents/RSBPML/RSBPMLParser.h \
    src/designer/documents/common/designerxmldocparser/DesignerXMLDocParser.h \
    src/designer/documents/SBOL/SBOLDoc.h \
    src/designer/documents/SBOL/SBOLParser.h \
    src/designer/documents/SBML/SBMLParser.h \
    src/designer/documents/FASTA/FASTADocParser.h \
    src/designer/documents/FASTA/FASTADoc.h \
    src/designer/documents/EMBL/EMBLDocParser.h \
    src/designer/documents/EMBL/EMBLDoc.h \
    src/designer/documents/GENBANK/GENBANKDoc.h \
    src/designer/documents/GENBANK/GENBANKDocParser.h \
    src/designer/documents/common/designerpartdocparser/DesignerPartDocParser.h \
    src/designer/documents/MoDeL_1/MoDeL1Parser.h \
    src/designer/documents/MoDeL_1/MoDeL1Doc.h \
    src/designer/documents/USML/USMLParser.h \
    src/designer/documents/USML/USMLDoc.h \
    src/designer/common/app/DesignerApp.h \
    src/designer/common/mainwnd/DesignerMainWnd.h \
    src/designer/views/assemblyview/AssemblyItemMolecule.h \
    src/designer/models/igamemodel/IGame.h \
    src/designer/views/assemblyview/AssemblyPropertyEditor.h \
    src/designer/views/assemblyview/AssemblyDBEditor.h \
    src/designer/views/behaviorview/BehaviorViewInterp.h \
    src/designer/common/drawwnd/DesignerDrawWnd.h \
    src/designer/common/drawwnd/DesignerDrawWidget.h \
    src/designer/views/networkview/Layouter/lagraphlayouterthread.h \
    src/designer/views/networkview/Layouter/lagraphlayouter.h \
    src/designer/views/networkview/NetworkView.h \
    src/designer/views/networkview/NetworkViewButton.h

FORMS    += \
    views/welcomeview/WelcomeView.ui \
    views/behaviorview/BehaviorView.ui \
    views/filedescriptionview/FileDescriptionView.ui \
    src/designer/views/partview/PartView.ui \
    src/designer/views/aboutview/AboutView.ui \
    src/designer/views/clothodbview/ClothoDBView.ui \
    src/designer/common/mainwnd/DesignerMainWnd.ui \
    src/designer/views/assemblyview/AssemblyDBEditor.ui \
    src/designer/views/networkview/NetworkView.ui

RESOURCES += \
    resources/DesignerResources.qrc

OTHER_FILES += \
    models/reactionnetworkmodel/ReactionNetworkDataTypes.prototype \
    src/designer/documents/SBML/SBML.parserules \
    src/designer/documents/SBOL/SBOL.parserules \
    src/designer/documents/RSBPML/RSBPML.parserules \
    src/designer/documents/MoDeL_1/MoDeL1.parserules \
    src/designer/documents/USML/USML.parserules
