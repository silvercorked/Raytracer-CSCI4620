
#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <variant>
#include <set>
#include <ostream>

namespace Tokenizer {
	enum struct simpleType {
		nothing,
		number,
		string
	};
	struct arrayType;
	struct functionType;

	using Type = std::variant<simpleType, arrayType, functionType>;
	using TypeHandle = const Type*;
	
	struct arrayType {
		TypeHandle innerTypeId;
	};
	struct functionType {
		struct param {
			TypeHandle typeId;
			bool byRef;
		};
		TypeHandle returnTypeId;
		std::vector<param> paramTypeId;
	};

	class TypeRegistry {
	private:
		struct TypesLess {
			bool operator()(const Type& t1, const Type& t2) const;
		};
		std::set<Type, TypesLess> _types;

		static Type voidType;
		static Type numberType;
		static Type stringType;
	public:
		TypeRegistry();
		TypeHandle getHandle(const Type& t);
		static TypeHandle getVoidHandle() {
			return &voidType;
		}
		static TypeHandle getNumberHandle() {
			return &numberType;
		}
		static TypeHandle getStringHandle() {
			return &stringType;
		}
	};
}

namespace std {
	std::string toString(Tokenizer::TypeHandle t);
}

#endif
