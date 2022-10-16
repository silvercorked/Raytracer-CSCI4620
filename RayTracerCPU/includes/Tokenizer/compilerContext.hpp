
#ifndef COMPILERCONTEXT_HPP
#define COMPILERCONTEXT_HPP

#include <unordered_map>
#include <memory>
#include <string>

#include "Type.hpp"

namespace Tokenizer {
	class IdentifierInfo {
	private:
		TypeHandle _typeId;
		size_t _index;
		bool _isGlobal;
		bool _isConstant;
	public:
		IdentifierInfo(TypeHandle typeId, size_t index, bool isGlobal, bool isConstant);
		TypeHandle typeId() const;
		size_t index() const;
		bool isGlobal() const;
		bool isConstant() const;
	};

	class IdentifierLookup {
	private:
		std::unordered_map<std::string, IdentifierInfo> _identifiers;
	protected:
		const IdentifierInfo* insertIdentifier(std::string name, TypeHandle typeId, size_t index, bool isGlobal, bool isConstant);
		size_t identifiersSize() const;
	public:
		virtual const IdentifierInfo* find(const std::string& name) const;
		virtual const IdentifierInfo* createIdentifier(std::string name, TypeHandle typeId, bool isConstant) = 0;
		virtual ~IdentifierLookup();
	};

	class GlobalIdentifierLookup : public IdentifierLookup {
	public:
		const IdentifierInfo* createIdentifier(std::string name, TypeHandle typeId, bool isConstant) override;
	};

	class LocalIdentifierLookup : public IdentifierLookup {
	private:
		std::unique_ptr<LocalIdentifierLookup> _parent;
		int _nextIdentifierIndex;
	public:
		LocalIdentifierLookup(std::unique_ptr<LocalIdentifierLookup> parentLookup);
		const IdentifierInfo* find(const std::string& name) const override;
		const IdentifierInfo* createIdentifier(std::string name, TypeHandle typeId, bool isConstant) override;
		std::unique_ptr<LocalIdentifierLookup> detachParent();
	};

	class FunctionIdentifierLookup : public LocalIdentifierLookup {
	private:
		int _nextParamIndex;
	public:
		FunctionIdentifierLookup();
		const IdentifierInfo* createParam(std::string name, TypeHandle typeId);
	};

	class CompilerContext {
	private:
		GlobalIdentifierLookup _globals;
		FunctionIdentifierLookup* _params;
		std::unique_ptr<LocalIdentifierLookup> _locals;
		TypeRegistry _types;
	public:
		CompilerContext();
		TypeHandle getHandle(const Type& t);
		const IdentifierInfo* find(const std::string& name) const;
		const IdentifierInfo* createIdentifier(std::string name, TypeHandle typeId, bool isConstant);
		const IdentifierInfo* createParam(std::string name, TypeHandle TypeId);
		void enterScope();
		void enterFunction();
		bool leaveScope();
	};
}

#endif
