#pragma once
#include "pch.h"

namespace ViSolEngine {
	class RTTI {
	public:
		RTTI(const char* typeName, const RTTI* parent = nullptr);

		bool isTypeOf(const RTTI& other) const;
		bool isDerivedFrom(const RTTI& other) const;

		const char* getTypeName() const;
		const RTTI* getParentClass() const;
	private:
		const char* mTypeName;
		const RTTI* mParentClass;
	};
}

#define DECLARE_RTTI \
	static const ViSolEngine::RTTI runTimeType; \
	virtual const ViSolEngine::RTTI& getRunTimeTypeInfo() const;

#define DEFINE_RTTI(typeName, parent) \
	const ViSolEngine::RTTI typeName::runTimeType(#typeName, &parent); \
	const ViSolEngine::RTTI& typeName::getRunTimeTypeInfo() const { return runTimeType; }

#define DEFINE_RTTI_NO_PARENT(typeName) \
	const ViSolEngine::RTTI typeName::runTimeType(#typeName); \
	const ViSolEngine::RTTI& typeName::getRunTimeTypeInfo() const { return runTimeType; }
    