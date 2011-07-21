protocomp: 
	g++ parsercomp.cpp -o parsercomp.exe

install:
	make
	cp -f parsercomp.exe ../../src/designer/documents/SBML/parsercomp.exe
	cp -f parsercomp.exe ../../src/designer/documents/SBOL/parsercomp.exe
	mv -f parsercomp.exe ../../src/designer/documents/RSBPML/parsercomp.exe
	make update

update:
	../../src/designer/documents/SBML/parsercomp.exe ../../src/designer/documents/SBML/SBML.prototype
	../../src/designer/documents/SBOL/parsercomp.exe ../../src/designer/documents/SBOL/SBOL.prototype
	../../src/designer/documents/RSBPML/parsercomp.exe ../../src/designer/documents/RSBPML/RSBPML.prototype
