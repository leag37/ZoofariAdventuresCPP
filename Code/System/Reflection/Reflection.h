// Filename: Reflection.h

// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include "CReflectionDefinition.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(reflection)

#define ZOOFARI_DECLARE_REFLECTION(TReflectableClass) \
	public:	\
		class CReflectableData; \
		static system::reflection::CReflectionDefinition<TReflectableClass> const & GetReflectionDefinition();

#define ZOOFARI_BEGIN_REFLECTION_DESCRIPTION(TReflectableClass) \
	class TReflectableClass::CReflectableData \
	{ \
	public: \
		CReflectableData () \
			: m_ClassName( #TReflectableClass ) \
		{ \
		} \
		std::string const & GetClassName() const \
		{ \
			return m_ClassName; \
		}

#define ZOOFARI_END_REFLECTION_DESCRIPTION() \
	private: \
		std::string m_ClassName; \
	};
//vector<CAttribute> m_Attributes; \
	//};																		

////#define ZOOFARI_ADD_ATTRIBUTE(TAttribute)	\
////	m_Attributes.emplace_back(CAttribute(##TAttribute));
//
#define ZOOFARI_DEFINE_REFLECTION(TReflectableClass) \
	system::reflection::CReflectionDefinition<TReflectableClass> const & TReflectableClass::GetReflectionDefinition() \
	{ \
		static system::reflection::CReflectionDefinition<TReflectableClass> sReflectionDefinition = \
			system::reflection::CReflectionDefinition<TReflectableClass>(TReflectableClass::CReflectableData()); \
		return sReflectionDefinition; \
	}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()