
#ifndef HELPERS_H
#define HELPERS_H

namespace Tokenizer {
	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}

#endif
