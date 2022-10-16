
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <functional>
#include <string_view>
#include <iostream>
#include <variant>

#include "Token.hpp"
#include "PushBackStream.hpp"

namespace Tokenizer {
	class TokenIterator {
	private:
		PushBackStream& _stream;
		Token _current;
	public:
		TokenIterator(PushBackStream& stream);
		const Token& operator*() const;
		const Token* operator->() const;
		TokenIterator& operator++();
		explicit operator bool() const;
	};
}

#endif
