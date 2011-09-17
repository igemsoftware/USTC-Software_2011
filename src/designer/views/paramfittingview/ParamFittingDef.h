#ifndef PARAMFITTINGDEF_H
#define PARAMFITTINGDEF_H


const unsigned PF_OPERATOR      = 0;
const unsigned PF_SPECIES       = 1;
const unsigned PF_PARAM         = 2;
const unsigned PF_COMPARTMENT   = 3;

inline const unsigned PF_GET_TYPE(const unsigned a) { return (a)>>30; }

inline const unsigned PF_MAKE_OPERATOR(const unsigned type) { return ((PF_OPERATOR<<30)|type); }
inline const unsigned PF_MAKE_SPECIES(const unsigned index) { return ((PF_SPECIES<<30)|(index)); }
inline const unsigned PF_MAKE_PARAM(const unsigned index) { return ((PF_PARAM<<30)|(index)); }
inline const unsigned PF_MAKE_COMPARTMENT(const unsigned index) { return ((PF_COMPARTMENT<<30)|(index)); }

inline const unsigned PF_GET_OPERATOR_TYPE(const unsigned a) { return (a&((1<<30)-1)); }
inline const unsigned PF_GET_INDEX(const unsigned a) { return (a&((1<<30)-1)); }


extern "C"
{


struct PfOdeDescriptor
{
    int dimension;
    int **stack;
    int *stack_len;
    double *params;
    double *compartments_concentration;
    double *init_y;
    double *buff;
};




}


#endif // PARAMFITTINGDEF_H
