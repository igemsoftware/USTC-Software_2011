/*
  Last changed Time-stamp: <2005-11-03 11:24:14 raim>
  $Id: options.h,v 1.2 2005/11/03 11:04:00 raimc Exp $
*/
#ifndef _OPTIONS_H_
#define _OPTIONS_H_

/* Command-line Options */
typedef struct _Options {
  char ExeName[256];    /* name of executable */
  char GvFormat[64];    /* output format for graph drawings */
  char ModelFile[256];  /* model file name */
  char ModelPath[256];  /* path to the model file */
  char Parameter[64];   /* Paramter for variation in batch process
			   or variable for sensitivity analysis*/
  char Schema11[64];    /* name of schema L1v1 file */
  char Schema12[64];    /* name of schema L1v2 file */
  char Schema21[64];    /* name of schema L1v3 file */
  char SchemaPath[256]; /* path to schema files */
  double Time;          /* Time to which model is integrated */
  double PrintStep;     /* Number of output steps from 0 to 'Time' */
  double Error;         /* absolute tolerance in Cvode integration */
  double RError;        /* relative tolerance in Cvode integration */
  double Mxstep;        /* maximum step number for CVode integration */
  int Determinant;      /* Calculate and print determinant of the
			   jacobian matrix */
  int DrawReactions;    /* Calculate a graph of the reaction network */
  int DrawJacobian;     /* Calculate a graph of species interaction
			   as determined by the jacobian matrix */
  int HaltOnEvent;      /* stop integration if event is detected */
  int InterActive;      /* Start program in interactive mode */
  int Jacobian;         /* Do not use jacobian matrix for integration */
  int Sensitivity;      /* Activate Sensitivity Analysis */
  int PrintAll;         /* Print all given results instead of only one */
  int PrintJacobian;    /* Print out time course of the jacobian matrix */
  int PrintReactions;   /* Print out time course of the reaction rates */
  int PrintModel;       /* Print out model, ODEs and jacobian expressions */
  int PrintODEsToSBML;  /* Construct ODE model and print out SBML */
  int PrintOnTheFly;    /* Print species concentration during integration */
  int Wheel;            /* Print progress wheel */
  int PrintRates;       /* Print time course of the ODE values */
  int PrintMessage;     /* Print messages of integration procedure */
  int SteadyState;      /* Check for steady states during integration */
  int Validate;         /* Validate SBML model before doing anything else */
  int Write;            /* Print results to file instead of stdout */
  int Xmgrace;          /* Print results to XMGrace instead of stdout */
} Options;

Options Opt;

void
decodeCML(int argc, char *argv[]);
void
initializeOptions(void);
void
usage (int status);

#endif

/* End of file */
