#include "SbmlOdeSolver.h"
#include <QMap>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

SbmlOdeSolver::SbmlOdeSolver(SBMLDocument *sbml, QObject *parent) :
    QObject(parent), sbml_(sbml), ode_(0)
{
}

void SbmlOdeSolver::Run(double end_time, double step, int interval)
{/*
    int N = end_time/step+1;
    double **result = new double*[N/interval];
    int n = 0;

    gsl_odeiv2_system sys = { func, 0, ode_->dimension, (void*)ode_ };

    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk4, 1e-3, 1e-8, 1e-8);
    double t = 0;
    for( int i = 0 ; i < N ; i++ )
    {
        int s = gsl_odeiv2_driver_apply_fixed_step(driver, &t, 1e-3, 1, ode_->y);
        Q_ASSERT(s == GSL_SUCCESS);
        if( i%interval == 0 )
        {
            result[n] = new double[ode_->dimension];
            memcpy( result[n], ode_->y, sizeof(double)*ode_->dimension);
            n++;
        }
    }

    emit Finished(ode_->dimension, n, result);*/
}


void SbmlOdeSolver::InitSimulation()
{
    ode_ = new PfOdeDescriptor;
    Model *model = sbml_->getModel();

    ListOfSpecies *species_list = model->getListOfSpecies();
    ode_->dimension = species_list->size();
    double *species_amount = new double[ode_->dimension];
    for( int i = 0 ; i < ode_->dimension ; i++ )
    {
        Species *species = species_list->get(i);
        id_map_.insert(species->getId(), PF_MAKE_SPECIES(i));
        species_amount[i] = species->getInitialConcentration();
    }
    ode_->y = species_amount;

    ListOfCompartments *compartment_list = model->getListOfCompartments();
    int n_compartment = compartment_list->size();
    ode_->compartments_concentration = new double[n_compartment];
    for( int i = 0 ; i < n_compartment ; i++ )
    {
        Compartment *compartment = compartment_list->get(i);
        id_map_.insert(compartment->getId(), PF_MAKE_COMPARTMENT(i));
        ode_->compartments_concentration[i] = 0;
    }

    ListOfParameters *parameter_list = model->getListOfParameters();
    int n_parameter = parameter_list->size();
    QVector<double> tmp_parameters;
    for( int i = 0 ; i < n_parameter ; i++ )
    {
        Parameter *parameter = parameter_list->get(i);
        id_map_.insert(parameter->getId(), PF_MAKE_PARAM(i));
        tmp_parameters.append( parameter->getValue() );
    }

    QVector<unsigned> *formulas = new QVector<unsigned>[ode_->dimension];
    ListOfReactions *reaction_list = model->getListOfReactions();
    int n_reaction = reaction_list->size();
    for( int i = 0 ; i < n_reaction ; i++ )
    {
        QVector<unsigned> kinect_law;
        Reaction *reaction = reaction_list->get(i);
        ParseReaction(tmp_parameters, reaction, kinect_law);

        ListOfSpeciesReferences *reactant_list = reaction->getListOfReactants();
        int n_reactant = reactant_list->size();
        for( int j = 0 ; j < n_reactant ; j++ )
        {
            SpeciesReference *reactant = reinterpret_cast<SpeciesReference*>(reactant_list->get(i));
            int index = PF_GET_INDEX(id_map_[reactant->getId()]);
            bool empty = formulas[index].isEmpty();
            QVector<unsigned> &formula = formulas[index];
            formula += kinect_law;
            formula.append(PF_MAKE_PARAM(tmp_parameters.size()));
            tmp_parameters.append(reactant->getStoichiometry());
            formula.append(PF_MAKE_OPERATOR(AST_TIMES));
            if( !empty ) formula.append(PF_MAKE_OPERATOR(AST_MINUS));
        }

        ListOfSpeciesReferences *product_list = reaction->getListOfProducts();
        int n_product = product_list->size();
        for( int j = 0 ; j < n_product ; j++ )
        {
            SpeciesReference *product = reinterpret_cast<SpeciesReference*>(product_list->get(i));
            int index = PF_GET_INDEX(id_map_[product->getId()]);
            bool empty = formulas[index].isEmpty();
            QVector<unsigned> &formula = formulas[index];
            formula += kinect_law;
            formula.append(PF_MAKE_PARAM(tmp_parameters.size()));
            tmp_parameters.append(product->getStoichiometry());
            formula.append(PF_MAKE_OPERATOR(AST_TIMES));
            if( !empty ) formula.append(PF_MAKE_OPERATOR(AST_PLUS));
        }
    }

    ode_->params = new double[tmp_parameters.size()];
    for( int i = 0 ; i < tmp_parameters.size() ; i++ ) ode_->params[i] = tmp_parameters[i];

    ode_->stack = new int*[ode_->dimension];
    ode_->stack_len = new int[ode_->dimension];
    int max_len = 0;
    for( int i = 0 ; i < ode_->dimension ; i++ )
    {
        int size = formulas[i].size();
        ode_->stack_len[i] = size;
        if( max_len < size ) max_len = size;
        ode_->stack[i] = new int[size];
        memcpy(ode_->stack[i], formulas[i].data(), sizeof(int)*size );
    }
    ode_->buff = new double[max_len];
}

void SbmlOdeSolver::ParseReaction(QVector<double> &parameters, Reaction *reaction, QVector<unsigned> &stack)
{
    QMap<std::string,unsigned> local_map;

    ListOfParameters *parameter_list = reaction->getKineticLaw()->getListOfLocalParameters();
    int n_parameter = parameter_list->size();
    for( int i = 0 ; i < n_parameter ; i++ )
    {
        Parameter *param = parameter_list->get(i);
        local_map.insert(param->getId(), PF_MAKE_PARAM(parameters.size()));
        parameters.append(param->getValue());
    }

    const ASTNode *tree = reaction->getKineticLaw()->getMath();
    ASTNode *copy = tree->deepCopy();
    PostTraversalAST(local_map, parameters, copy, stack);

    delete copy;
}

void SbmlOdeSolver::PostTraversalAST(const QMap<std::string, unsigned> &local_map, QVector<double> &parameters, ASTNode *tree, QVector<unsigned> &stack)
{
    tree->canonicalize();
    tree->reduceToBinary();

    int n_child;
    switch( tree->getType() )
    {
    case AST_NAME:
        if( local_map.find(tree->getName()) != local_map.end() )
        {
            stack.append(local_map[tree->getName()]);
        }else if( id_map_.find(tree->getName()) != id_map_.end() )
        {
            stack.append(id_map_[tree->getName()]);
        }else Q_ASSERT(false);
        break;
    case AST_INTEGER:
        stack.append(PF_MAKE_PARAM(parameters.size()));
        parameters.append(tree->getInteger());
        break;
    case AST_REAL:
    case AST_REAL_E:
    case AST_RATIONAL:
        stack.append(PF_MAKE_PARAM(parameters.size()));
        parameters.append(tree->getReal());
        break;
    case AST_PLUS:
    case AST_MINUS:
    case AST_TIMES:
    case AST_DIVIDE:
    case AST_POWER:
        n_child = tree->getNumChildren();
        for( int i = 0 ; i < n_child ; i++ )
        {
            PostTraversalAST(local_map, parameters, tree->getChild(i), stack);
        }
        stack.append(PF_MAKE_OPERATOR(tree->getType()));
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}

int func(double t, const double y[], double f[], void *void_ode)
{
    PfOdeDescriptor *ode = reinterpret_cast<PfOdeDescriptor*>(void_ode);
    double * buff = ode->buff;
    double * params = ode->params;
    double * compartments = ode->compartments_concentration;
    for( int i = 0 ; i < ode->dimension ; i++ )
    {
        int top = 0;
        int *stack = ode->stack[i];
        int stack_len = ode->stack_len[i];
        for( int j = 0 ; j < stack_len ; j++ )
        {
            switch( PF_GET_TYPE(stack[j]) )
            {
            case PF_SPECIES:
                buff[top++] = y[PF_GET_INDEX(stack[j])];
                break;
            case PF_PARAM:
                buff[top++] = params[PF_GET_INDEX(stack[j])];
                break;
            case PF_OPERATOR:
                switch(PF_GET_OPERATOR_TYPE(stack[j]))
                {
                case AST_PLUS:
                    buff[top-2] += buff[top-1];
                    top--;
                    break;
                case AST_MINUS:
                    buff[top-2] -= buff[top-1];
                    top--;
                    break;
                case AST_TIMES:
                    buff[top-2] *= buff[top-1];
                    top--;
                    break;
                case AST_DIVIDE:
                    buff[top-2] /= buff[top-1];
                    top--;
                    break;
                case AST_POWER:
                    buff[top-2] = pow(buff[top-2],buff[top-1]);
                    break;
                }
                break;
            case PF_COMPARTMENT:
                buff[top++] = compartments[PF_GET_INDEX(stack[j])];
                break;
            }
        }
        Q_ASSERT(top==1);
        f[i] = buff[0];
    }
    return GSL_SUCCESS;
}











