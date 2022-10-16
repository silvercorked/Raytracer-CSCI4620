
#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <optional>
#include <string_view>
#include <ostream>
#include <variant>

#include "PushBackStream.hpp"

namespace Tokenizer {
	enum struct reservedToken {
		vertex,				// geometric vetices		(x, y, z [, w])		0-1.0
		vertexTexture,		// texture coordinates		(u [, v, w])		0-1.0
		vertexNormal,		// vertex normals			(x, y, z)
		vertexParameter,	// parameter space vertices	(u [, v] [, w])
		faces,				// polygonal face elements
	};

	std::ostream& operator<<(std::ostream& os, reservedToken t);
	std::optional<reservedToken> getKeyword(std::string_view word);
	std::optional<reservedToken> getOperator(PushBackStream& stream);

	struct identifier {
		std::string name;
	};
	struct eof {};

	class Token {
	private:
		using tokenValue = std::variant<reservedToken, identifier, double, std::string, eof>;

		tokenValue _value;
		size_t _lineNumber;
		size_t _charIndex;
	public:
		Token(tokenValue value, size_t lineNumber, size_t charIndex);
		bool isReservedToken() const;
		bool isIdentifier() const;
		bool isNumber() const;
		bool isString() const;
		bool isEOF() const;

		reservedToken getReservedToken() const;
		std::string_view getIdentifier() const;
		double getNumber() const;
		std::string_view getString() const;

		size_t getLineNumber() const;
		size_t getCharIndex() const;
	};
}

#endif
