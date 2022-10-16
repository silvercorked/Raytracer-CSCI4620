
#include "compilerContext.hpp"

namespace Tokenizer {
	IdentifierInfo::IdentifierInfo(TypeHandle typeId, size_t index, bool isGlobal, bool isConstant) :
		_typeId(typeId),
		_index(index),
		_isGlobal(isGlobal),
		_isConstant(isConstant) {
	}
	TypeHandle IdentifierInfo::typeId() const {
		return _typeId;
	}
	size_t IdentifierInfo::index() const {
		return _index;
	}
	bool IdentifierInfo::isGlobal() const {
		return _isGlobal;
	}
	bool IdentifierInfo::isConstant() const {
		return _isConstant;
	}
	const IdentifierInfo* IdentifierLookup::insertIdentifier(std::string name, TypeHandle typeId, size_t index, bool isGlobal, bool isConstant) {
		return &_identifiers.emplace(std::move(name), IdentifierInfo(typeId, index, isGlobal, isConstant)).first->second;
	}
	size_t IdentifierLookup::identifiersSize() const {
		return _identifiers.size();
	}
	const IdentifierInfo* IdentifierLookup::find(const std::string& name) const {
		if (auto it = _identifiers.find(name); it != _identifiers.end()) {
			return &it->second;
		}
		else {
			return nullptr;
		}
	}
	IdentifierLookup::~IdentifierLookup() {}
	const IdentifierInfo* GlobalIdentifierLookup::createIdentifier(std::string name, TypeHandle typeId, bool isConstant) {
		return insertIdentifier(std::move(name), typeId, identifiersSize(), true, isConstant);
	}
	LocalIdentifierLookup::LocalIdentifierLookup(std::unique_ptr<LocalIdentifierLookup> parentLookup) :
		_parent(std::move(parentLookup)),
		_nextIdentifierIndex(_parent ? _parent->_nextIdentifierIndex : 1) {
	}
	const IdentifierInfo* LocalIdentifierLookup::find(const std::string& name) const {
		if (const IdentifierInfo* ret = IdentifierLookup::find(name)) {
			return ret;
		}
		else {
			return _parent ? _parent->find(name) : nullptr;
		}
	}
	const IdentifierInfo* LocalIdentifierLookup::createIdentifier(std::string name, TypeHandle typeId, bool isConstant) {
		return insertIdentifier(std::move(name), typeId, _nextIdentifierIndex++, false, isConstant);
	}
	std::unique_ptr<LocalIdentifierLookup> LocalIdentifierLookup::detachParent() {
		return std::move(_parent);
	}
	FunctionIdentifierLookup::FunctionIdentifierLookup() :
		LocalIdentifierLookup(nullptr),
		_nextParamIndex(-1) {
	}
	const IdentifierInfo* FunctionIdentifierLookup::createParam(std::string name, TypeHandle typeId) {
		return insertIdentifier(std::move(name), typeId, _nextParamIndex--, false, false);
	}
	CompilerContext::CompilerContext() : _params(nullptr) {}
	const Type* CompilerContext::getHandle(const Type& t) {
		return _types.getHandle(t);
	}
	const IdentifierInfo* CompilerContext::find(const std::string& name) const {
		if (_locals) {
			if (const IdentifierInfo* ret = _locals->find(name)) {
				return ret;
			}
		}
		return _globals.find(name);
	}
	const IdentifierInfo* CompilerContext::createIdentifier(std::string name, TypeHandle typeId, bool isConstant) {
		if (_locals) {
			return _locals->createIdentifier(std::move(name), typeId, isConstant);
		}
		else {
			return _globals.createIdentifier(std::move(name), typeId, isConstant);
		}
	}
	const IdentifierInfo* CompilerContext::createParam(std::string name, TypeHandle typeId) {
		return _params->createParam(name, typeId);
	}
	void CompilerContext::enterScope() {
		_locals = std::make_unique<LocalIdentifierLookup>(std::move(_locals));
	}
	void CompilerContext::enterFunction() {
		std::unique_ptr<FunctionIdentifierLookup> params = std::make_unique<FunctionIdentifierLookup>();
		_params = params.get();
		_locals = std::move(params);
	}
	bool CompilerContext::leaveScope() {
		if (!_locals) {
			return false;
		}
		if (_params == _locals.get()) {
			_params = nullptr;
		}
		_locals = _locals->detachParent();
		return true;
	}
}