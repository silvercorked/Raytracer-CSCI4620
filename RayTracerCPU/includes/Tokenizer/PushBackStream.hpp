
#ifndef PUSHBACKSTREAM_H
#define PUSHBACKSTREAM_H

#include <stack>
#include <functional>

namespace Tokenizer {
	using getCharacter = std::function<int()>;
	
	class PushBackStream {
	private:
		const getCharacter& _input;
		std::stack<int> _stack;
		size_t _lineNumber;
		size_t _charIndex;
	public:
		PushBackStream(const getCharacter& input);

		int operator()();

		void pushBack(int c);

		size_t lineNumber() const;
		size_t charIndex() const;
	};
}

#endif
