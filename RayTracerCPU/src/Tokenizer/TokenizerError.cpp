
#include "TokenizerError.hpp"

namespace Tokenizer {
	TokenizerError::TokenizerError(std::string message, size_t lineNumber, size_t charIndex) noexcept :
		_message(std::move(message)),
		_lineNumber(lineNumber),
		_charIndex(charIndex)
	{
	}

	const char* TokenizerError::what() const noexcept {
		return _message.c_str();
	}

	size_t TokenizerError::lineNumber() const noexcept {
		return _lineNumber;
	}

	size_t TokenizerError::charIndex() const noexcept {
		return _charIndex;
	}

	TokenizerError parsingError(const char* message, size_t lineNumber, size_t charIndex) {
		std::string errorMessage("Parsing error: ");
		errorMessage += message;
		return TokenizerError(std::move(errorMessage), lineNumber, charIndex);
	}

	TokenizerError unexpectedError(std::string_view unexpected, size_t lineNumber, size_t charIndex) {
		std::string message("Unexpected '");
		message += unexpected;
		message += "'";
		return parsingError(message.c_str(), lineNumber, charIndex);
	}

	void format_error(const TokenizerError& err, getCharacter source, std::ostream& output) {
		output << "(" << (err.lineNumber() + 1) << ") " << err.what() << std::endl;

		size_t charIndex = 0;

		for (size_t lineNumber = 0; lineNumber < err.lineNumber(); ++charIndex) {
			int c = source();
			if (c < 0) {
				return;
			}
			else if (c == '\n') {
				++lineNumber;
			}
		}

		size_t indexInLine = err.charIndex() - charIndex;

		std::string line;
		for (size_t idx = 0;; ++idx) {
			int c = source();
			if (c < 0 || c == '\n' || c == '\r') {
				break;
			}
			line += char(c);
		}

		output << line << std::endl;

		for (size_t idx = 0; idx < indexInLine; ++idx) {
			output << " ";
		}

		output << "^" << std::endl;
	}
};
