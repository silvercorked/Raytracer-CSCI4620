
#include "Token.hpp"
#include "Lookup.hpp"
#include <string_view>

namespace Tokenizer {
	namespace {
		const Lookup<std::string_view, reservedToken> operatorTokenMap {
			
		};
		const Lookup<std::string_view, reservedToken> keywordTokenMap {
			{"v", reservedToken::vertex},
			{"vt", reservedToken::vertexTexture},
			{"vn", reservedToken::vertexNormal},
			{"vp", reservedToken::vertexParameter},
			{"f", reservedToken::faces}
		};
		const Lookup<reservedToken, std::string_view> tokenStringMap = ([]() {
			std::vector<std::pair<reservedToken, std::string_view>> container;
			container.reserve(operatorTokenMap.size() + keywordTokenMap.size());
			for (const auto& p : operatorTokenMap) {
				container.emplace_back(p.second, p.first);
			}
			for (const auto& p : keywordTokenMap) {
				container.emplace_back(p.second, p.first);
			}
			return Lookup<reservedToken, std::string_view>(std::move(container));
		})();
	}
	std::ostream& operator<<(std::ostream& os, reservedToken t) {
		os << tokenStringMap.find(t)->second;
		return os;
	}
	std::optional<reservedToken> getKeyword(std::string_view word) {
		auto it = keywordTokenMap.find(word);
		return it == keywordTokenMap.end() ? std::nullopt : std::make_optional(it->second);
	}
	namespace {
		class MaximalMunchComparator {
		private:
			size_t _idx;
		public:
			MaximalMunchComparator(size_t idx) : _idx(idx) {}
			bool operator()(char i, char r) const {
				return i < r;
			}
			bool operator()(std::pair<std::string_view, reservedToken> l, char r) const {
				return l.first.size() <= _idx || l.first[_idx] < r;
			}
			bool operator()(char l, std::pair<std::string_view, reservedToken> r) const {
				return r.first.size() > _idx && l < r.first[_idx];
			}
			bool operator()(std::pair<std::string_view, reservedToken> l, std::pair<std::string_view, reservedToken> r) {
				return r.first.size() > _idx && (l.first.size() < _idx || l.first[_idx] < r.first[_idx]);
			}
		};
	}
	std::optional<reservedToken> getOperator(PushBackStream& stream) {
		auto candidates = std::make_pair(operatorTokenMap.begin(), operatorTokenMap.end());
		std::optional<reservedToken> ret;
		size_t matchSize = 0;
		std::stack<int> chars;
		for (size_t idx = 0; candidates.first != candidates.second; ++idx) {
			chars.push(stream());
			candidates = std::equal_range(candidates.first, candidates.second, char(chars.top()), MaximalMunchComparator(idx));
			if (candidates.first != candidates.second && candidates.first->first.size() == idx + 1) {
				matchSize = idx + 1;
				ret = candidates.first->second;
			}
		}
		while (chars.size() > matchSize) {
			stream.pushBack(chars.top());
			chars.pop();
		}
		return ret;
	}
	Token::Token(tokenValue value, size_t lineNumber, size_t charIndex) :
		_value(std::move(value)),
		_lineNumber(lineNumber),
		_charIndex(charIndex)
	{}

	bool Token::isReservedToken() const {
		return std::holds_alternative<reservedToken>(_value);
	}
	bool Token::isIdentifier() const {
		return std::holds_alternative<identifier>(_value);
	}
	bool Token::isNumber() const {
		return std::holds_alternative<double>(_value);
	}
	bool Token::isString() const {
		return std::holds_alternative<std::string>(_value);
	}
	bool Token::isEOF() const {
		return std::holds_alternative<eof>(_value);
	}
	reservedToken Token::getReservedToken() const {
		return std::get<reservedToken>(_value);
	}
	std::string_view Token::getIdentifier() const {
		return std::get<identifier>(_value).name;
	}
	double Token::getNumber() const {
		return std::get<double>(_value);
	}
	std::string_view Token::getString() const {
		return std::get<std::string>(_value);
	}
	size_t Token::getLineNumber() const {
		return _lineNumber;
	}
	size_t Token::getCharIndex() const {
		return _charIndex;
	}
}