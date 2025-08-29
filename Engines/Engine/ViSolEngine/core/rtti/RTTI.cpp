#include"RTTI.h"


namespace ViSolEngine {
	RTTI::RTTI(const char* typeName, const RTTI* parent) : mTypeName(typeName), mParentClass(parent) {

	}

	bool RTTI::isTypeOf(const RTTI& other) const {
		return !strcmp(mTypeName, other.mTypeName);
	}

	bool RTTI::isDerivedFrom(const RTTI& other) const {
		const RTTI* parent = this;

		while (parent) {
			if (!strcmp(parent->mTypeName, other.mTypeName)) {
				return true;
			}

			parent = parent->mParentClass;
		}

		return false;
	}

	const char* RTTI::getTypeName() const { 
		return mTypeName; 
	}

	const RTTI* RTTI::getParentClass() const { 
		return mParentClass; 
	}
}