# Last changed Time-stamp: <2005-05-23 17:42:02 xtof>
# $Id: Makefile.PL.in,v 1.1.1.1 2005/05/30 19:49:13 raimc Exp $
use ExtUtils::MakeMaker;

my @Xtralib = map{chomp; $_} <DATA>;
WriteMakefile(MAKEFILE => 'Makefile-perl',
              NAME     => 'LibODES',
              LIBS     => [join(' ', @Xtralib)],
	      dynamic_lib =>
	      {LDDLFLAGS=> '-Wl,-rpath,/mingw/lib -L/mingw/lib -lsbml'},
              INC      => '-I../swig -I../../src -I/usr/local/include -I/mingw/include -I/mingw/include/sbml',
              MYEXTLIB => '../../src/libODES.a',
              OBJECT   => 'LibODES_wrap.o',
              AUTHOR   => 'Christoph Flamm <xtof@tbi.univie.ac.at>',
              VERSION  => '1.6.0',
);

sub MY::postamble {
	return <<'MAKE_FRAG';
LibODES_wrap.c:
	swig -Wall -perl5 -proxy -I../../src/ -I/mingw/include -I/mingw/include/sbml LibODES.i
MAKE_FRAG
}

__DATA__
-L/mingw/lib -lsundials_kinsol -lsundials_cvodes -lsundials_cvode -lsundials_nvecserial -lsundials_shared
 
 
-L/mingw/lib -lsundials_kinsol -lsundials_cvodes -lsundials_cvode -lsundials_nvecserial -lsundials_shared
-L/mingw/lib -lsbml
-lxerces-c
-lm
