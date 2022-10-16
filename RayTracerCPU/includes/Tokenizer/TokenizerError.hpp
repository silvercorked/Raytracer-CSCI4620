
#ifndef errors_hpp
#define errors_hpp

#include <exception>
#include <string>
#include <string_view>
#include <ostream>
#include <functional>

namespace Tokenizer {
	class TokenizerError : public std::exception {
	private:
		std::string _message;
		size_t _lineNumber;
		size_t _charIndex;
	public:
		TokenizerError(std::string message, size_t lineNumber, size_t charIndex) noexcept;

		const char* what() const noexcept override;
		size_t lineNumber() const noexcept;
		size_t charIndex() const noexcept;
	};

	TokenizerError parsingError(const char* message, size_t lineNumber, size_t charIndex);
	TokenizerError unexpectedError(std::string_view unexpected, size_t lineNumber, size_t charIndex);

	using getCharacter = std::function<int()>;
	void formatError(const TokenizerError& err, getCharacter source, std::ostream& output);
};

#endif
