// THIS FILE IS AUTO-GENERATED BY PROTOCOMP.
// PLEASE DON'T EDIT THIS FILE MANUALLY.
// Generate Time: Tue Jul 05 22:47:14 2011

#ifndef REACTIONNETWORKDATATYPES_H
#define REACTIONNETWORKDATATYPES_H

#include <QMetaType>
#include <QScriptValue>
#include <QVariant>

#include "models/common/ModelSymbol.h"

namespace ReactionNetworkDataTypes
{


	using lachesis::symbol_t;
	using lachesis::symbollist_t;
	using lachesis::valuelist_t;
	using lachesis::mathexpr_t;
	using lachesis::mathsegexpr_t;
	using lachesis::predicate_t;



	struct Reaction
	{
		symbol_t name;
		predicate_t reversible;
		symbollist_t reactants;
		symbollist_t modifiers;
		symbollist_t products;
		mathexpr_t kineticLaw;

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Reaction &s)
		{
			QScriptValue obj = engine->newObject();
			obj.setProperty("name", convertModelTypeToScriptValue(engine, s.name));
			obj.setProperty("reversible", convertModelTypeToScriptValue(engine, s.reversible));
			obj.setProperty("reactants", convertModelTypeToScriptValue(engine, s.reactants));
			obj.setProperty("modifiers", convertModelTypeToScriptValue(engine, s.modifiers));
			obj.setProperty("products", convertModelTypeToScriptValue(engine, s.products));
			obj.setProperty("kineticLaw", convertModelTypeToScriptValue(engine, s.kineticLaw));
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Reaction &s)
		{
			s.name = qscriptvalue_cast<symbol_t>(obj.property("name"));
			s.reversible = qscriptvalue_cast<predicate_t>(obj.property("reversible"));
			s.reactants = qscriptvalue_cast<symbollist_t>(obj.property("reactants"));
			s.modifiers = qscriptvalue_cast<symbollist_t>(obj.property("modifiers"));
			s.products = qscriptvalue_cast<symbollist_t>(obj.property("products"));
			s.kineticLaw = qscriptvalue_cast<mathexpr_t>(obj.property("kineticLaw"));
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "reversible" , QVariant::predicate ) );
			propertyList.push_back( PropertyDescriptor( "reactants" , QVariant::symbollist ) );
			propertyList.push_back( PropertyDescriptor( "modifiers" , QVariant::symbollist ) );
			propertyList.push_back( PropertyDescriptor( "products" , QVariant::symbollist ) );
			propertyList.push_back( PropertyDescriptor( "kineticLaw" , QVariant::mathexpr ) );
			return propertyList;
		}
		*/
	};





	struct Compartment
	{
		// symbol_t name; ;; instance-value
		// precisevalue_t size; ;; instance-value
		// valuelist_t contains; ;; instance-value

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Compartment &s)
		{
			QScriptValue obj = engine->newObject();
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Compartment &s)
		{
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "size" , QVariant::precisevalue ) );
			propertyList.push_back( PropertyDescriptor( "contains" , QVariant::valuelist ) );
			return propertyList;
		}
		*/
	};





	struct Species
	{
		symbol_t name;
		// symbol_t compartment; ;; instance-value
		// valuelist_t structure; ;; instance-value

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Species &s)
		{
			QScriptValue obj = engine->newObject();
			obj.setProperty("name", convertModelTypeToScriptValue(engine, s.name));
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Species &s)
		{
			s.name = qscriptvalue_cast<symbol_t>(obj.property("name"));
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "compartment" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "structure" , QVariant::valuelist ) );
			return propertyList;
		}
		*/
	};





	struct Chain
	{
		// symbol_t name; ;; instance-value
		// symbol_t type; ;; instance-value
		// valuelist_t structure; ;; instance-value

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Chain &s)
		{
			QScriptValue obj = engine->newObject();
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Chain &s)
		{
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "type" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "structure" , QVariant::valuelist ) );
			return propertyList;
		}
		*/
	};





	struct Part
	{
		symbol_t name;
		symbol_t type;
		valuelist_t structure;

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Part &s)
		{
			QScriptValue obj = engine->newObject();
			obj.setProperty("name", convertModelTypeToScriptValue(engine, s.name));
			obj.setProperty("type", convertModelTypeToScriptValue(engine, s.type));
			obj.setProperty("structure", convertModelTypeToScriptValue(engine, s.structure));
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Part &s)
		{
			s.name = qscriptvalue_cast<symbol_t>(obj.property("name"));
			s.type = qscriptvalue_cast<symbol_t>(obj.property("type"));
			s.structure = qscriptvalue_cast<valuelist_t>(obj.property("structure"));
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "type" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "structure" , QVariant::valuelist ) );
			return propertyList;
		}
		*/
	};





	struct Parameter
	{
		symbol_t id;
		symbol_t unit;
		mathsegexpr_t rule;

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Parameter &s)
		{
			QScriptValue obj = engine->newObject();
			obj.setProperty("id", convertModelTypeToScriptValue(engine, s.id));
			obj.setProperty("unit", convertModelTypeToScriptValue(engine, s.unit));
			obj.setProperty("rule", convertModelTypeToScriptValue(engine, s.rule));
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Parameter &s)
		{
			s.id = qscriptvalue_cast<symbol_t>(obj.property("id"));
			s.unit = qscriptvalue_cast<symbol_t>(obj.property("unit"));
			s.rule = qscriptvalue_cast<mathsegexpr_t>(obj.property("rule"));
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "id" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "unit" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "rule" , QVariant::mathsegexpr ) );
			return propertyList;
		}
		*/
	};





	struct Unit
	{
		symbol_t name;
		valuelist_t ratio;

		static QScriptValue toScriptValue(QScriptEngine *engine,   const Unit &s)
		{
			QScriptValue obj = engine->newObject();
			obj.setProperty("name", convertModelTypeToScriptValue(engine, s.name));
			obj.setProperty("ratio", convertModelTypeToScriptValue(engine, s.ratio));
			return obj;
		}

		static void fromScriptValue(const QScriptValue &obj, Unit &s)
		{
			s.name = qscriptvalue_cast<symbol_t>(obj.property("name"));
			s.ratio = qscriptvalue_cast<valuelist_t>(obj.property("ratio"));
		}
		/*
		inline static const QList<PropertyDescriptor> listProperty()
		{
			QList<PropertyDescriptor> propertyList;
			propertyList.push_back( PropertyDescriptor( "name" , QVariant::symbol ) );
			propertyList.push_back( PropertyDescriptor( "ratio" , QVariant::valuelist ) );
			return propertyList;
		}
		*/
	};















}
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Reaction);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Compartment);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Species);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Chain);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Part);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Parameter);
	Q_DECLARE_METATYPE(ReactionNetworkDataTypes::Unit);

#endif // REACTIONNETWORKDATATYPES_H
