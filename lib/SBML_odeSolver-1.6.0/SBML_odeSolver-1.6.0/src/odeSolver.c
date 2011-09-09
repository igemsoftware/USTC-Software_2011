/*
  Last changed Time-stamp: <2005-12-16 18:30:53 raim>
  $Id: odeSolver.c,v 1.36 2005/12/16 17:35:54 raimc Exp $
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
 *     Stefanie Widder
 *     Christoph Flamm
 *     Stefan M�ller
 *     Andrew Finney
 */
/*! \defgroup odeSolver High Level Interfaces
    \brief This module contains high level interfaces to SOSlib, which
    take an SBML model and integratorSettings as input and return results
    mapped back to SBML structures.

    Please see sbmlResults for interfaces to the returned result
    structures.

*/
/*@{*/

#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <string.h>
#include <time.h>

#include <sbml/SBMLTypes.h>

#include "sbmlsolver/odeSolver.h"

static int globalizeParameter(Model_t *, char *id, char *rid);
static int localizeParameter(Model_t *, char *id, char *rid);
static int SBMLResults_createSens(SBMLResults_t *, cvodeData_t *);

/** Solves the timeCourses for a SBML model, passed via a libSBML
    SBMLDocument structure and according to passed integration
    settings and returns the SBMLResults structure.
*/

SBML_ODESOLVER_API SBMLResults_t *
SBML_odeSolver(SBMLDocument_t *d, cvodeSettings_t *set) {

  SBMLDocument_t *d2 = NULL;
  Model_t *m = NULL;
  SBMLResults_t *results;
  
  /** Convert SBML Document level 1 to level 2, and
      get the contained model
  */
  if ( SBMLDocument_getLevel(d) != 2 ) {
    d2 = convertModel(d);
    m = SBMLDocument_getModel(d2);    
  }
  else {
    m = SBMLDocument_getModel(d);
  }  
  RETURN_ON_FATALS_WITH(NULL);

  /** Call Model_odeSolver */
  results = Model_odeSolver(m, set);
  
  /** free temporary level 2 version of the document */
  if ( d2 != NULL ) {
    SBMLDocument_free(d2);
  }
  
  return results;
  
}


/** Solves the timeCourses for a SBML model, passed via a libSBML
    SBMLDocument structure and according to passed 
    integration and parameter variation settings and returns
    the SBMLResultsMatrix containing SBMLResults for each
    varied parameter (columns) and each of its values (rows).
*/

SBML_ODESOLVER_API SBMLResultsMatrix_t *
SBML_odeSolverBatch(SBMLDocument_t *d, cvodeSettings_t *set,
		    varySettings_t *vs) 
{

  SBMLDocument_t *d2 = NULL;
  Model_t *m = NULL;
  SBMLResultsMatrix_t *resM;
  
  /** Convert SBML Document level 1 to level 2, and
      get the contained model
  */
  if ( SBMLDocument_getLevel(d) != 2 ) {
    d2 = convertModel(d);
    m = SBMLDocument_getModel(d2);    
  }
  else {
    m = SBMLDocument_getModel(d);
  }  
  RETURN_ON_FATALS_WITH(NULL);

  /** Call Model_odeSolverBatch */  
  resM = Model_odeSolverBatch(m, set, vs);
  /** free temporary level 2 version of the document */
  if ( d2 != NULL ) {
    SBMLDocument_free(d2);
  }
  
  return resM;
    
}


/** Solves the timeCourses for a SBML model, passed via a libSBML
    Model_t  (must be level 2 SBML!!) and according to passed
    integration settings and returns the SBMLResults structure.

*/

SBML_ODESOLVER_API SBMLResults_t *
Model_odeSolver(Model_t *m, cvodeSettings_t *set)
{
  odeModel_t *om;
  integratorInstance_t *ii; 
  SBMLResults_t *results;
  int errorCode = 0;
  
  /** At first, ODEModel_create, attempts to construct a simplified
     SBML model with reactions replaced by ODEs. SBML RateRules,
     AssignmentRules,AlgebraicRules and Events are copied to the
     simplified model. AlgebraicRules or missing mathematical
     expressions produce fatal errors and appropriate messages. All
     function definitions are replaced by their values or expressions
     respectively in all remaining formulas (ie. rules and events). If
     that conversion was successful, an internal model structure
     (odeModel) is created, that contains indexed versions of all
     formulae (AFM's AST_INDEX) where the index of a former AST_NAME
     corresponds to its position in a value array (double *), that is
     used to store current values and to evaluate AST formulae during
     integration.
  */

  om = ODEModel_create(m);      
  RETURN_ON_FATALS_WITH(NULL);
  /**
     Second, an integratorInstance is created from the odeModel
     and the passed cvodeSettings. If that worked out ...
  */
  
  ii = IntegratorInstance_create(om, set);
  RETURN_ON_FATALS_WITH(NULL);

  /** .... the integrator loop can be started,
      that invoking CVODE to move one time step and store.
      The function will also handle events and
      check for steady states.
  */
  while (!IntegratorInstance_timeCourseCompleted(ii) && !errorCode) {
    if (!IntegratorInstance_integrateOneStep(ii))
      errorCode = IntegratorInstance_handleError(ii);
  }  
  RETURN_ON_FATALS_WITH(NULL);

  /** finally, map cvode results back to SBML compartments, species
      and parameters  */
  results = SBMLResults_fromIntegrator(m, ii);

  /* free integration data */
  IntegratorInstance_free(ii);
  /* free odeModel */
  ODEModel_free(om);
  
  /* ... well done. */
  return(results);
}


/** Solves the timeCourses for a SBML model, passed via a libSBML
    Model_t (must be level 2 SBML!!) structure and according to passed 
    integration and parameter variation settings and returns
    the SBMLResultsMatrix containing SBMLResults for each
    varied parameter (columns) and each of its values (rows).

*/

SBML_ODESOLVER_API SBMLResultsMatrix_t *
Model_odeSolverBatch (Model_t *m, cvodeSettings_t *set,
		      varySettings_t *vs) {


  int i, j;
  double value, increment;
 
  odeModel_t *om;
  integratorInstance_t *ii;
  variableIndex_t *vi;
  SBMLResultsMatrix_t *resM;

  char *local_param;
  
  int errorCode = 0;


  resM = SBMLResultsMatrix_allocate(vs->nrparams, vs->nrdesignpoints);
 
  /** At first, globalize all local (kineticLaw) parameters to be varied */
  for ( i=0; i<vs->nrparams; i++ ) 
    if ( vs->rid[i] != NULL ) 
      globalizeParameter(m, vs->id[i], vs->rid[i]);     
    
 
  /** Then create internal odeModel: attempts to construct a simplified
     SBML model with reactions replaced by ODEs.
     See comments in Model_odeSolver for details.  */
  om = ODEModel_create(m);      
  RETURN_ON_FATALS_WITH(NULL);
 
  /** an integratorInstance is created from the odeModel and the passed
     cvodeSettings. If that worked out ...  */  
  ii = IntegratorInstance_create(om, set);
  RETURN_ON_FATALS_WITH(NULL);
      
  /** now, work through the passed parameters in varySettings */
  for ( i=0; i<vs->nrparams; i++ ) {

    /* get the index for parameter i */
    if ( vs->rid[i] != NULL ) {
      ASSIGN_NEW_MEMORY_BLOCK(local_param,
			      strlen(vs->id[i]) + strlen(vs->rid[i]) + 4,
			      char , 0);
      sprintf(local_param, "r_%s_%s", vs->rid[i], vs->id[i]);
      vi = ODEModel_getVariableIndex(om, local_param);
      free(local_param);
    }
    else
      vi = ODEModel_getVariableIndex(om, vs->id[i]);
    
    if ( vi == NULL )
      return NULL;
  
    /* then, work through all values for this parameter */
    for ( j=0; j<vs->nrdesignpoints; j++ ) {

      /* Set the value!*/
      IntegratorInstance_setVariableValue(ii, vi, vs->params[i][j]);

 
      /** .... the integrator loop can be started, that invokes
	  CVODE to move one time step and store results. These
	  functions will also handle events and check for steady states. */
      errorCode = 0;
      while (!IntegratorInstance_timeCourseCompleted(ii) && !errorCode)
	if (!IntegratorInstance_integrateOneStep(ii))
	  errorCode = IntegratorInstance_handleError(ii);
  
      RETURN_ON_FATALS_WITH(NULL);
        
      /** map cvode results back to SBML compartments, species and
	  parameters  */
      resM->results[i][j] = SBMLResults_fromIntegrator(m, ii);
      IntegratorInstance_reset(ii);
    }
  }
  /** localize parameters again, unfortunately the new globalized
     parameter cannot be freed currently  */
  for ( i=0; i<vs->nrparams; i++ ) 
    if ( vs->rid[i] != NULL ) 
      localizeParameter(m, vs->id[i], vs->rid[i]);     

  /* free variableIndex, used for setting values */
  VariableIndex_free(vi);
  /* free integration data */
  IntegratorInstance_free(ii);
  /* free odeModel */
  ODEModel_free(om);
  /* ... well done. */
  return(resM);

}

static int globalizeParameter(Model_t *m, char *id, char *rid) {

  int i, found;
  Reaction_t *r;
  KineticLaw_t *kl;
  Parameter_t *p, *p_global;
  ASTNode_t *math;
  char *newname;
 
  r = Model_getReactionById (m, (const char *) rid);
  
  if ( r == NULL )
    return 0;
  
  kl = Reaction_getKineticLaw(r);
  math = (ASTNode_t *)KineticLaw_getMath(kl);

  ASSIGN_NEW_MEMORY_BLOCK(newname, strlen(id) + strlen(rid) + 4, char , 0);
  sprintf(newname, "r_%s_%s", rid, id);
  AST_replaceNameByName(math, (const char *) id,  (const char *) newname);

  found = 0;
  
  for ( i=0; i<KineticLaw_getNumParameters(kl); i++ ) {
    p = KineticLaw_getParameter(kl, i);
    if ( strcmp(Parameter_getId(p), id) == 0 ) {
      p_global = Model_createParameter(m);
      Parameter_setConstant(p_global, 1);
      Parameter_setId(p_global, newname);
      if (Parameter_isSetValue(p)) 
	Parameter_setValue(p_global, Parameter_getValue(p));
      if(Parameter_isSetUnits(p)) 
	Parameter_setUnits(p_global, Parameter_getUnits(p));
      if (Parameter_isSetName(p)) 
	Parameter_setName(p_global, Parameter_getName(p));
      found = 1;
    }
  }
  free(newname);
  return found;
}

static int localizeParameter(Model_t *m, char *id, char *rid) {

  int i, found;
  Reaction_t *r;
  KineticLaw_t *kl;
  ListOf_t     *pl;
  Parameter_t *p;
  ASTNode_t *math;
  char *newname;
  
  r = Model_getReactionById (m, (const char *) rid);
  
  if ( r == NULL )
    return 0;
  
  kl = Reaction_getKineticLaw(r);
  math = (ASTNode_t *)KineticLaw_getMath(kl);  
  ASSIGN_NEW_MEMORY_BLOCK(newname, strlen(id) + strlen(rid) + 4, char , 0);
  sprintf(newname, "r_%s_%s", rid, id);
  AST_replaceNameByName(math, (const char *) newname, (const char *) id);

  /* just freeing the last parameter, one for each `rid',
     only if the globalized parameter is present */
  found = 0;
  if ( Model_getParameterById(m, newname) != NULL ) {
    found = 1;
    pl = Model_getListOfParameters(m);
    p = (Parameter_t *) ListOf_remove(pl, ListOf_getNumItems(pl) - 1);
    Parameter_free(p);
  }  

  free(newname);
  return found;

}

/** @} */


/*! \addtogroup sbmlResults */
/*@{*/

/** Maps the integration results from internal data structures
    back to SBML structures (compartments, species, parameters
    and reaction fluxes)
*/


SBML_ODESOLVER_API SBMLResults_t *SBMLResults_fromIntegrator(Model_t *m, integratorInstance_t *ii) {

  int i, j, k, flag;
  Reaction_t *r;
  KineticLaw_t *kl;
  ASTNode_t **kls;
  timeCourseArray_t *tcA;
  timeCourse_t *tc;
  SBMLResults_t *sbml_results;

  odeModel_t *om = ii->om;
  cvodeData_t *data = ii->data;
  cvodeResults_t *cv_results = ii->results;

  /* check if data is available */
  if ( data == NULL ) 
    return NULL;
  else if ( cv_results == NULL ) 
    return NULL;

  sbml_results = SBMLResults_create(m, cv_results->nout+1);

  /* Allocating temporary kinetic law ASTs, for evaluation of fluxes */

  ASSIGN_NEW_MEMORY_BLOCK(kls, Model_getNumReactions(m), ASTNode_t *, NULL);

  for ( i=0; i<Model_getNumReactions(m); i++ ) {
    r = Model_getReaction(m, i);
    kl = Reaction_getKineticLaw(r);
    kls[i] = copyAST(KineticLaw_getMath(kl));
    AST_replaceNameByParameters(kls[i], KineticLaw_getListOfParameters(kl));
    AST_replaceConstants(m, kls[i]);
  }
  
  
  /*  filling results for each calculated timepoint.  */
  for ( i=0; i<sbml_results->time->timepoints; i++ ) {
    
    /* writing time steps */
    sbml_results->time->values[i] = cv_results->time[i];
    
    /* updating time and values in cvodeData_t *for calculations */
    data->currenttime = cv_results->time[i]; 
    for ( j=0; j<data->nvalues; j++ ) 
      data->value[j] = cv_results->value[j][i]; 

    /* filling time courses for SBML species  */
    tcA = sbml_results->species;  
    for ( j=0; j<tcA->num_val; j++ ) {
      tc = tcA->tc[j];
      /* search in cvodeData_t for values */
      for ( k=0; k<data->nvalues; k++ )
	if ( (strcmp(tc->name, om->names[k]) == 0) )
	  tc->values[i] = cv_results->value[k][i];
    }
    
    /* filling variable compartment time courses */
    tcA = sbml_results->compartments;  
    for ( j=0; j<tcA->num_val; j++ ) {
      tc = tcA->tc[j];
      /* search in cvodeData_t for values */
      for ( k=0; k<data->nvalues; k++ )
	if ( (strcmp(tc->name, om->names[k]) == 0) )
	  tc->values[i] = cv_results->value[k][i];
    }         

    /* filling variable parameter time courses */
    tcA = sbml_results->parameters;  
    for ( j=0; j<tcA->num_val; j++ ) {
      tc = tcA->tc[j];
      /* search in cvodeData_t for values */
      for ( k=0; k<data->nvalues; k++ ) 
	if ( (strcmp(tc->name, om->names[k]) == 0) ) 
	  tc->values[i] = cv_results->value[k][i];
    }

    /* filling reaction flux time courses */
    tcA = sbml_results->fluxes;
    for ( j=0; j<tcA->num_val; j++ ) {
      tc = tcA->tc[j];
      tc->values[i] = evaluateAST(kls[j], data);
    }

  }

  /* freeing temporary kinetic law ASTs */
  for ( i=0; i<Model_getNumReactions(m); i++ ) 
    ASTNode_free(kls[i]);
  free(kls);

  /* filling sensitivities */
  flag = 0;
  if ( cv_results->nsens > 0 )
    flag = SBMLResults_createSens(sbml_results, data);
  if ( flag == 0)
    sbml_results->nsens = 0;
 
  
  return(sbml_results);
}

static int SBMLResults_createSens(SBMLResults_t *Sres,
				  cvodeData_t *data)
{
  int i, j, k;
  odeModel_t *om = data->model;
  cvodeResults_t *res = data->results;
  timeCourse_t *tc;

  Sres->nsens = res->nsens;
  
  ASSIGN_NEW_MEMORY_BLOCK(Sres->param, res->nsens, char *, 0);  
  for ( i=0; i<res->nsens; i++ ) {
    ASSIGN_NEW_MEMORY_BLOCK(Sres->param[i],
			    strlen(om->names[om->index_sens[i]]+1), char, 0);
    sprintf(Sres->param[i], om->names[om->index_sens[i]]);
  }
  for ( i=0; i<res->neq; i++ ) {
    tc = SBMLResults_getTimeCourse(Sres, om->names[i]);
    ASSIGN_NEW_MEMORY_BLOCK(tc->sensitivity, res->nsens, double *, 0);
    for ( j=0; j<res->nsens; j++ ) {
      ASSIGN_NEW_MEMORY_BLOCK(tc->sensitivity[j], res->nout, double, 0);
      for ( k=0; k<res->nout; k++ )
	tc->sensitivity[j][k] = res->sensitivity[i][j][k];
      /* printf("Hallo sens fuer %s / %s \n", om->names[i], */
/* 	     om->names[om->index_sens[j]]); */ 
    }    
  }
  return 1;
}

/** @} */

/*! \defgroup varySettings Parameter Variation Settings
    \ingroup odeSolver
    
    \brief Create the varySettings structure with a series of
    parameter values used for the batch functions
    
*/
/*@{*/


/** Allocate varySettings structure for settings for parameter
    variation batch runs: nrparams is the number of parameters to be
    varied, and nrdesignpoints is the number of values to be tested
    for each parameter.
*/

SBML_ODESOLVER_API 
varySettings_t *VarySettings_allocate(int nrparams, int nrdesignpoints)
{
  int i;
  varySettings_t *vs;
  ASSIGN_NEW_MEMORY(vs, struct varySettings, NULL);
  ASSIGN_NEW_MEMORY_BLOCK(vs->id, nrparams, char *, NULL);
  ASSIGN_NEW_MEMORY_BLOCK(vs->rid, nrparams, char *, NULL);
  ASSIGN_NEW_MEMORY_BLOCK(vs->params, nrparams, double *, NULL);
  for ( i=0; i<nrparams; i++ ) {
    ASSIGN_NEW_MEMORY_BLOCK(vs->params[i], nrdesignpoints, double, NULL);
  } 
  vs->nrdesignpoints = nrdesignpoints;
  vs->nrparams = nrparams;
  /* set conuter to 0, will be used as counter in addParameters */
  vs->cnt_params = 0;
  return vs;
}


/** Add a parameter to the varySettings.

    For local (reaction/kineticLaw)
    parameters, the reaction id must be passed as `rid'. For global
    parameters `rid' must be passed as NULL.

*/

SBML_ODESOLVER_API 
int VarySettings_addParameter(varySettings_t *vs, char *id, char *rid,
			      double start, double end)
{
  int j;
  double value;

  /* calculating default internal parameter array */
  for ( j=0; j<vs->nrdesignpoints; j++ ) {
    value = start + j*((end-start)/(vs->nrdesignpoints-1));
    VarySettings_setValue(vs, vs->cnt_params, j, value);
  }  
  VarySettings_setName(vs, vs->cnt_params, id, rid);
  /* count and return already filled parametervalues */
  return vs->cnt_params++;  
}


/** Get the name (SBML ID) of the ith parameter,

    where  \n
    0 <= i < nrparams   \n
    as used for varySettings_allocate
*/

SBML_ODESOLVER_API 
const char *VarySettings_getName(varySettings_t *vs, int i)
{   
  return (const char *) vs->id[i];
}



/** Get the name (SBML ID) of the reaction of the ith parameter,

    where  \n
    0 <= i < nrparams   \n
    as used for varySettings_allocate.
    Returns NULL, if the parameter is global.
*/

SBML_ODESOLVER_API 
const char *VarySettings_getReactionName(varySettings_t *vs, int i)
{   
  return (const char *) vs->rid[i];
}


/** Set the id (SBML ID) of the ith parameter,

    where \n
    0 <= i < nrparams  \n
    as used for varySettings_allocate.  \n
    `rid' is the SBML reaction id, if a local parameter shall
    be varied. For global parameters rid must be passed as NULL.
*/

SBML_ODESOLVER_API 
int VarySettings_setName(varySettings_t *vs, int i,
				  char *id, char *rid)
{

  /* free if parameter nr. i has already been set */
  if ( vs->id[i] != NULL )
    free(vs->id[i]);
  if  ( vs->rid[i] != NULL )
    free(vs->rid[i]);
  
  /* setting parameter reaction id: local parameters will be
     `globalized' in the input model */
  if ( rid != NULL ) {
    ASSIGN_NEW_MEMORY_BLOCK(vs->rid[i], strlen(rid)+1, char, 0);
    sprintf(vs->rid[i], "%s", rid);    
  }
  else 
    vs->rid[i] = NULL;

  ASSIGN_NEW_MEMORY_BLOCK(vs->id[i], strlen(id)+1, char, 0);
  sprintf(vs->id[i], "%s", id);
  

  return 1;
}

/** Get the jth value of the ith parameter,

    where \n
    0 <= i < nrparams  and \n
    0 <= j < nrdesignpoints \n
    as used for varySettings_allocate
*/

SBML_ODESOLVER_API
double VarySettings_getValue(varySettings_t *vs, int i, int j)
{
  return vs->params[i][j];
}


/** Set the jth value of the ith parameter,

    where \n
    0 <= i < nrparams  and \n
    0 <= j < nrdesignpoints \n
    as used for varySettings_allocate
*/

SBML_ODESOLVER_API
void VarySettings_setValue(varySettings_t *vs, int i, int j, double value)
{
  vs->params[i][j] = value;
}


/** Print all parameters and their values in varySettings
*/

SBML_ODESOLVER_API void VarySettings_dump(varySettings_t *vs)
{
  int i, j;
  printf("\n");
  printf("Design Series for %d Parameter(s) and %d values:",
	 vs->nrparams, vs->nrdesignpoints);fflush(stdout);
  for ( i=0; i<vs->nrparams; i++ ) {
    printf("\n%d. %s: ", i, vs->id[i]);
    for ( j=0; j<vs->nrdesignpoints; j++ ) {
      printf("%.3f ", vs->params[i][j]);
    }    
  }
  printf("\n\n");
}


/** Frees varySettings structure
*/

SBML_ODESOLVER_API void VarySettings_free(varySettings_t *vs)
{
  int i, j;
  
  for ( i=0; i<vs->nrparams; i++ ) {
    free(vs->id[i]);
    free(vs->rid[i]);
    free(vs->params[i]);
  }
  free(vs->id);
  free(vs->rid);
  free(vs->params);
  free(vs);    
}



/* adds arrays of parameters and predefined values not used at the moment */
int VarySettings_addParameterSet(varySettings_t *vs,
				 double **designpoints, char **id, char **rid)
{
  int i, j;
  for ( i=0; i<vs->nrparams; i++ ) {
    VarySettings_setName(vs, i, id[i], rid[i]);
    for ( j=0; j<vs->nrdesignpoints; j++ )
      VarySettings_setValue(vs, i, j, designpoints[i][j]);
  }
  return (i+1);
}



/*\@} */



/* End of file */
