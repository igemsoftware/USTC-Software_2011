protocomp: 
	g++ parsercomp.cpp -o parsercomp.exe

install:
	make
	cp -f parsercomp.exe ../../src/designer/documents/SBML/parsercomp.exe
	cp -f parsercomp.exe ../../src/designer/documents/SBOL/parsercomp.exe
	cp -f parsercomp.exe ../../src/designer/documents/RSBPML/parsercomp.exe
	cp -f parsercomp.exe ../../src/designer/documents/MoDeL_1/parsercomp.exe
	mv -f parsercomp.exe ../../src/designer/documents/USML/parsercomp.exe
	make update

update:
	../../src/designer/documents/SBML/parsercomp.exe ../../src/designer/documents/SBML/SBML.parserules
	../../src/designer/documents/SBOL/parsercomp.exe ../../src/designer/documents/SBOL/SBOL.parserules
	../../src/designer/documents/RSBPML/parsercomp.exe ../../src/designer/documents/RSBPML/RSBPML.parserules
	../../src/designer/documents/MoDeL_1/parsercomp.exe ../../src/designer/documents/MoDeL_1/MoDeL1.parserules
	../../src/designer/documents/USML/parsercomp.exe ../../src/designer/documents/USML/USML.parserules
