#ifndef PROTEININTERACTIONNETWORKMODELREACTION_H
#define PROTEININTERACTIONNETWORKMODELREACTION_H

#include <QMetaType>
#include <QScriptValue>

#include "models/common/ModelSymbol.h"

namespace ProteinInteractionNetwork
{
    using lachesis::symbollist_t;
    using lachesis::mathexpr_t;
    using lachesis::precisevalue_t;

    struct Reaction
    {
        bool reversible;
        symbollist_t reactants;
        symbollist_t modifiers;
        symbollist_t products;
        mathexpr_t kineticLaw;

        static QScriptValue toScriptValue(QScriptEngine *engine, const Reaction &s)
        {
          QScriptValue obj = engine->newObject();
          obj.setProperty("reversible", s.reversible);
          obj.setProperty("reactants", s.reactants);
          obj.setProperty("modifiers", s.modifiers);
          obj.setProperty("products", s.products);
          obj.setProperty("kineticLaw", s.kineticLaw);
          return obj;
        }

        static void fromScriptValue(const QScriptValue &obj, Reaction &s)
        {
          s.reversible = qscriptvalue_cast<symbollist_t>(obj.property("reversible"));
          s.reactants = qscriptvalue_cast<symbollist_t>(obj.property("reactants"));
          s.modifiers = qscriptvalue_cast<symbollist_t>(obj.property("modifiers"));
          s.products  = qscriptvalue_cast<symbollist_t>(obj.property("products") );
          s.kineticLaw = qscriptvalue_cast<mathexpr_t>(obj.property("products")  );
        }

    };
    Q_DECLARE_METATYPE(Reaction);


    struct Compartment
    {
//        precisevalue_t size;  ;;instance-property
//        contains              ;;instance-property

        static QScriptValue toScriptValue(QScriptEngine *engine, const Compartment &s)
        {
          QScriptValue obj = engine->newObject();
//          obj.setProperty("size", s.size); ;;instance-property
          return obj;
        }

        static void fromScriptValue(const QScriptValue &obj, Compartment &s)
        {
//          s.size = qscriptvalue_cast<precisevalue_t>(obj.property("size")); ;;instance-property
        }


    };
    Q_DECLARE_METATYPE(Compartment);


    struct Species
    {
        //instance-property: compartment(position)
        //instance-property: initial-amount
        symbollist_t sites;

        //instance-property: structure
        //  NOTE: valueis: [itself] (atom)
        //             or: [[species1, bind1_index, bind2_index], [species2, bind1_index, bind2_index], ...]
        static QScriptValue toScriptValue(QScriptEngine *engine, const Species &s)
        {
          QScriptValue obj = engine->newObject();
          obj.setProperty("sites", s.sites);
          return obj;
        }

        static void fromScriptValue(const QScriptValue &obj, Species &s)
        {
          s.sites = qscriptvalue_cast<symbollist_t>(obj.property("sites"));
        }
    };
    Q_DECLARE_METATYPE(Species);

    struct Parameter
    {
        symbol_t name;
        //mathexpr_segbytime_t behaviorrule; //instance-property

        static QScriptValue toScriptValue(QScriptEngine *engine, const Parameter &s)
        {
          QScriptValue obj = engine->newObject();
          obj.setProperty("name", s.name);
          //obj.setProperty("behaviorrule", s.behaviorrule);
          return obj;
        }

        static void fromScriptValue(const QScriptValue &obj, Parameter &s)
        {
          s.name = qscriptvalue_cast<symbollist_t>(obj.property("name"));
          //s.behaviorrule = qscriptvalue_cast<mathexpr_segbytime_t>(obj.property("behaviorrule"));
        }
    };
    Q_DECLARE_METATYPE(Parameter);

    struct Unit
    {
        symbol_t name;
        valuelist_t ratio;  //this unit is defined by [scale(10^)/multiplier(*), value, anotherUnit]
    };
    Q_DECLARE_METATYPE(Unit)

/*    struct Event
    {
        symbol_t name;
    }; */    //Want to give up this, should be express in Parameter.


}

#endif // PROTEININTERACTIONNETWORKMODELREACTION_H

//qScriptRegisterMetaType(engine, toScriptValue, fromScriptValue);
