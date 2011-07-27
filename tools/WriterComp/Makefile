protocomp: 
	g++ writercomp.cpp -o writercomp.exe

install:
	make
	cp -f writercomp.exe ../../src/designer/documents/SBML/writercomp.exe
	cp -f writercomp.exe ../../src/designer/documents/SBOL/writercomp.exe
	mv -f writercomp.exe ../../src/designer/documents/RSBPML/writercomp.exe
	make update

update:
	../../src/designer/documents/SBML/writercomp.exe ../../src/designer/documents/SBML/SBML.writerules
	../../src/designer/documents/SBOL/writercomp.exe ../../src/designer/documents/SBOL/SBOL.writerules
	../../src/designer/documents/RSBPML/writercomp.exe ../../src/designer/documents/RSBPML/RSBPML.writerules
