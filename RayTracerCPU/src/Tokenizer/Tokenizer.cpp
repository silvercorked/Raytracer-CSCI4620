
#include "Tokenizer.hpp"
#include <map>
#include <string>
#include <cctype>
#include <stack>
#include <cstdlib>
#include "PushBackStream.hpp"
#include "TokenizerError.hpp"

namespace Tokenizer {
	namespace {
		enum struct characterType {
			eof,
			space,
			alphanum,
			punct
		};
		characterType getCharacterType(int c) {
			if (c < 0) {
				return characterType::eof;
			}
			if (std::isspace(c)) {
				return characterType::space;
			}
			if (std::isalpha(c) || std::isdigit(c) || c == '_') {
				return characterType::alphanum;
			}
			return characterType::punct;
		}
		Token fetchWord(PushBackStream& stream) {
			size_t lineNumber = stream.lineNumber();
			size_t charIndex = stream.charIndex();

			std::string word;
			int c = stream();
			bool isNumber = isdigit(c);
			do {
				word.push_back(char(c));
				c = stream();
			} while (getCharacterType(c) == characterType::alphanum || (isNumber && c == '.'));
			stream.pushBack(c);
			if (std::optional<reservedToken> t = getKeyword(word)) {
				return Token(*t, lineNumber, charIndex);
			}
			else {
				if (std::isdigit(word.front())) {
					char* endptr;
					double num = strtol(word.c_str(), &endptr, 0);
					if (*endptr != 0) {
						num = strtod(word.c_str(), &endptr);
						if (*endptr != 0) {
							size_t remaining = word.size() - (endptr - word.c_str());
							throw unexpectedError(
								std::string(1, char(*endptr)),
								stream.lineNumber(),
								stream.charIndex() - remaining
							);
						}
					}
					return Token(num, lineNumber, charIndex);
				}
				else {
					return Token(identifier{ std::move(word) }, lineNumber, charIndex);
				}
			}
		}
		Token fetchOperator(PushBackStream& stream) {
			size_t lineNumber = stream.lineNumber();
			size_t charIndex = stream.charIndex();
			if (std::optional<reservedToken> t = getOperator(stream)) {
				return Token(*t, lineNumber, charIndex);
			}
			else {
				std::string unexpected;
				size_t errLineNumber = stream.lineNumber();
				size_t errCharIndex = stream.charIndex();
				for (int c = stream(); getCharacterType(c) == characterType::punct; c = stream()) {
					unexpected.push_back(char(c));
				}
				throw unexpectedError(unexpected, errLineNumber, errCharIndex);
			}
		}
		Token fetchString(PushBackStream& stream) {
			size_t lineNumber = stream.lineNumber();
			size_t charIndex = stream.charIndex();
			std::string str;
			bool escaped = false;
			int c = stream();
			for (; getCharacterType(c) != characterType::eof; c = stream()) {
				if (c == '#') {
					escaped = true;
				}
				else {
					if (escaped) {
						switch (c) {
							case 't':
								str.push_back('\t');
								break;
							case 'n':
								str.push_back('\n');
								break;
							case 'r':
								str.push_back('\r');
								break;
							case '0':
								str.push_back('\0');
								break;
							default:
								str.push_back(c);
								break;
						}
					}
					else {
						switch (c) {
							case '\t':
							case '\n':
							case '\r':
								stream.pushBack(c);
								throw parsingError("Expected closing '\"'", stream.lineNumber(), stream.charIndex());
							case '"':
								return Token(std::move(str), lineNumber, charIndex);
							default:
								str.push_back(c);
						}
					}
				}
			}
			stream.pushBack(c);
			throw parsingError("Expected closing '\"'", stream.lineNumber(), stream.charIndex());
		}
		void skipLineComment(PushBackStream& stream) {
			int c;
			do {
				c = stream();
			} while (c != '\n' && getCharacterType(c) != characterType::eof);
			if (c != '\n') {
				stream.pushBack(c);
			}
		}
		void skipBlockComment(PushBackStream& stream) {
			bool closing = false;
			int c;
			do {
				c = stream();
				if (closing && c == '/') {
					return;
				}
				closing = (c == '*');
			} while (getCharacterType(c) != characterType::eof);
			stream.pushBack(c);
			throw parsingError("Expected closing '*/'", stream.lineNumber(), stream.charIndex());
		}
	}
	Token tokenize(PushBackStream& stream) {
		while (true) {
			size_t lineNumber = stream.lineNumber();
			size_t charIndex = stream.charIndex();
			int c = stream();
			switch (getCharacterType(c)) {
				case characterType::eof:
					return { eof(), lineNumber, charIndex };
				case characterType::space:
					continue;
				case characterType::alphanum:
					stream.pushBack(c);
					return fetchWord(stream);
				case characterType::punct:
					switch (c) {
						case '"':
							return fetchString(stream);
						case '#':
							skipLineComment(stream);
							continue;
						case '/': {
							char c1 = stream();
							switch (c1) {
								case '/':
									skipLineComment(stream);
									continue;
								case '*':
									skipBlockComment(stream);
									continue;
								default:
									stream.pushBack(c1);
							}
						}
						default:
							stream.pushBack(c);
							return fetchOperator(stream);
					}
					break;
			}
		}
	}
	TokenIterator::TokenIterator(PushBackStream& stream) :
		_stream(stream),
		_current(eof(), 0, 0)
	{
		++(*this);
	}
	TokenIterator& TokenIterator::operator++() {
		_current = tokenize(_stream);
		return *this;
	}
	const Token& TokenIterator::operator*() const {
		return _current;
	}
	const Token* TokenIterator::operator->() const {
		return &_current;
	}
	TokenIterator::operator bool() const {
		return !_current.isEOF();
	}
}
