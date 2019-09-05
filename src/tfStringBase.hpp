#pragma once

#include <string>
#include <sstream>
#include "tfVector.hpp"
#include <type_traits>
#include <cctype>

namespace tf
{
	template<typename TChar, typename TChild>
	class StringBase : public std::basic_string<TChar>
	{
	public:
		StringBase()
		{
		}

		StringBase(const TChar content)
		{
			this->push_back(content);
		}

		StringBase(const TChar* content) :
			std::basic_string<TChar>(content)
		{
		}

		StringBase(const TChar* content, const size_t size) :
			std::basic_string<TChar>(content, size)
		{
		}

		StringBase(const std::basic_string<TChar>& content) :
			std::basic_string<TChar>(content)
		{
		}

		StringBase(const TChild& format, const tf::Vector<TChild>& args) :
			std::basic_string<TChar>(this->format(format, args))
		{
		}

		template<typename TTarget>
		TTarget to() const
		{
			std::basic_istringstream<TChar> stream(*this);
			TTarget                         value;

			stream >> value;
			return value;
		}

		static TChild format(const TChild& format, const tf::Vector<TChild>& args)
		{
			static const std::basic_string<TChar> placeholder = {TChar('{'), TChar('}')};
			size_t                                count       = 0;
			size_t                                lastOffset  = 0;

			size_t                                nextOffset;
			TChild                                output;

			while ((nextOffset = format.find(placeholder, lastOffset)) != std::basic_string<TChar>::npos)
			{
				output += format.substr(lastOffset, nextOffset - lastOffset);
				output += (count < args.size()) ? args[count++] : placeholder;
				lastOffset = nextOffset + placeholder.size();
			}

			output += format.substr(lastOffset);

			return output;
		}

		bool contains(const TChild& token) const
		{
			return this->find(token) != std::basic_string<TChar>::npos;
		}

		size_t count(const TChild& token) const
		{
			size_t count  = 0;
			size_t offset = 0;

			while ((offset = this->find(token, offset)) != std::basic_string<TChar>::npos)
			{
				++count;
				offset += token.size();
			}

			return count;
		}

		tf::Vector<TChild> split(const TChild& token) const
		{
			size_t             lastOffset = 0;
			
			size_t             nextOffset;
			tf::Vector<TChild> components;

			while ((nextOffset = this->find(token, lastOffset)) != this->npos)
			{
				components.push_back(this->substr(lastOffset, nextOffset - lastOffset));
				lastOffset = nextOffset + token.size();
			}

			if (lastOffset <= this->size())
			{
				components.push_back(this->substr(lastOffset));
			}

			return components;
		}

		TChild left(const size_t length) const
		{
			return this->substr(0, length);
		}

		TChild right(const size_t length) const
		{
			return length <= this->size() ? this->substr(this->size() - length) : TChild(*this);
		}

		TChild middle(const size_t leftOffset, const size_t rightOffset) const
		{
			const size_t length = this->size() - rightOffset - leftOffset;

			return length <= this->size() ? TChild(this->substr(leftOffset, length)) : *this;
		}

		bool startsWith(const TChild& token) const
		{
			return left(token.size()) == token;
		}

		bool endsWith(const TChild& token) const
		{
			return right(token.size()) == token;
		}

		void replace(const TChild& oldToken, const TChild& newToken)
		{
			size_t lastOffset = 0;
			size_t nextOffset;

			while ((nextOffset = this->find(oldToken, lastOffset)) != std::basic_string<TChar>::npos)
			{
				std::basic_string<TChar>::replace(nextOffset, oldToken.size(), newToken);
				lastOffset = nextOffset;
			}
		}

		void stripLeft()
		{
			size_t whitespaceChars = 0;

			for (auto it = this->cbegin(); it != this->cend() && isWhitespace(*it); ++it)
			{
				++whitespaceChars;
			}

			*this = right(this->size() - whitespaceChars);
		}

		void stripRight()
		{
			size_t whitespaceChars = 0;

			for (auto it = this->crbegin(); it != this->crend() && isWhitespace(*it); ++it)
			{
				++whitespaceChars;
			}

			*this = left(this->size() - whitespaceChars);
		}

		void strip()
		{
			stripLeft();
			stripRight();
		}

	private:
		static bool isWhitespace(const TChar character)
		{
			return (character == TChar(' ') || character == TChar('\t') || character == TChar('\n') || character == TChar('\r') || character == TChar('\v') || character == TChar('\f'));
		}

	};
}