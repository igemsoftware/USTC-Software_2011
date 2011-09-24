#ifndef SBMLODESOLVER_H
#define SBMLODESOLVER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <sbml/SBMLDocument.h>
#include <QThread>
#include <gsl/gsl_odeiv2.h>
#include "views/paramfittingview/ParamFittingDef.h"

extern "C"
{
int func(double t, const double y[], double f[], void *ode);
}

class SbmlOdeSolver : public QObject
{
    Q_OBJECT
public:
    explicit SbmlOdeSolver(SBMLDocument *sbml, QObject *parent = 0);

    void InitSimulation();
    void exec();
signals:
    void Finished(int n_species, int n_points, double **data);
public slots:


private:
    SBMLDocument *sbml_;
    QMap<std::string,unsigned> id_map_;
    PfOdeDescriptor *ode_;

    class Worker : public QThread
    {
    public:
        Worker(SbmlOdeSolver *solver, double end_time, double step, int interval) : solver_(solver), end_time_(end_time), step_(step), interval_(interval) {}
        virtual void run() { solver_->Run(end_time_, step_, interval_); }
    private:
        SbmlOdeSolver *solver_;
        double end_time_;
        double step_;
        int interval_;
    };

    void Run(double end_time, double step, int interval);
    void PostTraversalAST(const QMap<std::string,unsigned> &local_map, QVector<double> &parameters, ASTNode *tree, QVector<unsigned> &stack);
    void ParseReaction(QVector<double> &parameters, Reaction *reaction, QVector<unsigned> &stack);
};

#endif // SBMLODESOLVER_H
