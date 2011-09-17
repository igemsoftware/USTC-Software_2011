/*
  Last changed Time-stamp: <2005-12-12 16:18:51 raim>
  $Id: integrate.c,v 1.12 2005/12/12 14:40:53 raimc Exp $
*/
/* 
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * authors have no obligations to provide maintenance, support,
 * updates, enhancements or modifications.  In no event shall the
 * authors be liable to any party for direct, indirect, special,
 * incidental or consequential damages, including lost profits, arising
 * out of the use of this software and its documentation, even if the
 * authors have been advised of the possibility of such damage.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Rainer Machne
 *
 * Contributor(s):
 */

#include <stdio.h>
#include <stdlib.h>

#include <sbmlsolver/odeSolver.h>


int
main (int argc, char *argv[]){
  int i, j;
  char *model;
  double time;
  double printstep;
  /* libSBML types */
  SBMLDocument_t *d;
  SBMLReader_t *sr;
  Model_t *m;
  Reaction_t *r;
  KineticLaw_t *kl;
  ASTNode_t *nary;
  ASTNode_t *diff;
  /* SOSlib types */
  SBMLResults_t *results;
  timeCourse_t *tc;
  cvodeSettings_t *set;

  /* parsing command-line arguments */
  if (argc < 4 ) {
    fprintf(stderr,
	    "usage %s sbml-model-file simulation-time time-steps\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }
  model = argv[1];
  time = atof(argv[2]);
  printstep = atoi(argv[3]); 

  /* parsing the SBML model with libSBML */
  sr = SBMLReader_create();
  d = SBMLReader_readSBML(sr, model);
  SBMLReader_free(sr);

  m = SBMLDocument_getModel(d);

  r = Model_getReaction(m,0);
  kl = Reaction_getKineticLaw(r);
  nary = KineticLaw_getMath(kl);
  printf("N-ary formula: %s\n", SBML_formulaToString(nary));
  diff = differentiateAST(nary, "Product");
  printf("N-ary diff: %s\n", SBML_formulaToString(diff));
  ASTNode_free(diff);

  return (EXIT_SUCCESS);  
}



/* End of file */
