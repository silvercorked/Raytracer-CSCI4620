
#include "Type.hpp"
#include "helpers.hpp"

namespace Tokenizer {
	bool TypeRegistry::TypesLess::operator()(const Type& t1, const Type& t2) const {
		const size_t idx1 = t1.index();
		const size_t idx2 = t2.index();
		if (idx1 != idx2) {
			return idx1 < idx2;
		}
		switch (idx1) {
		case 0:
			return std::get<0>(t1) < std::get<0>(t2);
		case 1:
			return std::get<1>(t1).innerTypeId < std::get<1>(t2).innerTypeId;
		case 2: {
			const functionType& ft1 = std::get<2>(t1);
			const functionType& ft2 = std::get<2>(t2);
			if (ft1.returnTypeId != ft2.returnTypeId) {
				return ft1.returnTypeId < ft2.returnTypeId;
			}
			if (ft1.paramTypeId.size() != ft2.paramTypeId.size()) {
				return ft1.paramTypeId.size() < ft2.paramTypeId.size();
			}
			for (size_t i = 0; i < ft1.paramTypeId.size(); ++i) {
				if (ft1.paramTypeId[i].typeId != ft2.paramTypeId[i].typeId) {
					return ft1.paramTypeId[i].typeId < ft2.paramTypeId[i].typeId;
				}
				if (ft1.paramTypeId[i].byRef != ft2.paramTypeId[i].byRef) {
					return ft2.paramTypeId[i].byRef;
				}
			}
		}
		}
		return false;
	}
	TypeRegistry::TypeRegistry() {}

	TypeHandle TypeRegistry::getHandle(const Type& t) {
		return std::visit(overloaded{
			[](simpleType t) {
				switch (t) {
				case simpleType::nothing:
					return TypeRegistry::getVoidHandle();
				case simpleType::number:
					return TypeRegistry::getNumberHandle();
				case simpleType::string:
					return TypeRegistry::getStringHandle();
				}
			},
			[this](const auto& t) {
				return &(*(_types.insert(t).first));
			}
			}, t);
	}
	Type TypeRegistry::voidType = simpleType::nothing;
	Type TypeRegistry::numberType = simpleType::number;
	Type TypeRegistry::stringType = simpleType::string;
}

namespace std {
	using namespace Tokenizer;
	std::string toString(TypeHandle t) {
		return std::visit(overloaded{
			[](simpleType st) {
				switch (st) {
				case simpleType::nothing:
					return std::string("void");
				case simpleType::number:
					return std::string("number");
				case simpleType::string:
					return std::string("string");
				}
			},
			[](const arrayType& at) {
				std::string ret = toString(at.innerTypeId);
				ret += "[]";
				return ret;
			},
			[](const functionType& ft) {
				std::string ret = toString(ft.returnTypeId) + "(";
				const char* separator = "";
				for (const functionType::param& p : ft.paramTypeId) {
					ret += separator + toString(p.typeId) + (p.byRef ? "&" : "");
					separator = ",";
				}
				ret += ")";
				return ret;
}
		}, *t);
	}
}
