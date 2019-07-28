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
			std::basic_string<TChar>(Format(format, args))
		{
		}

		template<typename TTarget>
		TTarget To() const
		{
			std::basic_istringstream<TChar> stream(*this);
			TTarget                         value;

			stream >> value;
			return value;
		}

		static TChild Format(const TChild& format, const tf::Vector<TChild>& args)
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

		bool Contains(const TChild& token) const
		{
			return this->find(token) != std::basic_string<TChar>::npos;
		}

		size_t Count(const TChild& token) const
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

		tf::Vector<TChild> Split(const TChild& token) const
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

		TChild Left(const size_t length) const
		{
			return this->substr(0, length);
		}

		TChild Right(const size_t length) const
		{
			return length <= this->size() ? this->substr(this->size() - length) : TChild(*this);
		}

		TChild Middle(const size_t leftOffset, const size_t rightOffset) const
		{
			const size_t length = this->size() - rightOffset - leftOffset;

			return length <= this->size() ? TChild(this->substr(leftOffset, length)) : *this;
		}

		bool StartsWith(const TChild& token) const
		{
			return Left(token.size()) == token;
		}

		bool EndsWith(const TChild& token) const
		{
			return Right(token.size()) == token;
		}

		void Replace(const TChild& oldToken, const TChild& newToken)
		{
			size_t lastOffset = 0;
			size_t nextOffset;

			while ((nextOffset = this->find(oldToken, lastOffset)) != std::basic_string<TChar>::npos)
			{
				this->replace(nextOffset, oldToken.size(), newToken);
				lastOffset = nextOffset;
			}
		}

		void StripLeft()
		{
			size_t whitespaceChars = 0;

			for (auto it = this->cbegin(); it != this->cend() && IsWhitespace(*it); ++it)
			{
				++whitespaceChars;
			}

			*this = Right(this->size() - whitespaceChars);
		}

		void StripRight()
		{
			size_t whitespaceChars = 0;

			for (auto it = this->crbegin(); it != this->crend() && IsWhitespace(*it); ++it)
			{
				++whitespaceChars;
			}

			*this = Left(this->size() - whitespaceChars);
		}

		void Strip()
		{
			StripLeft();
			StripRight();
		}

	private:
		static bool IsWhitespace(const TChar character)
		{
			return (character == TChar(' ') || character == TChar('\t') || character == TChar('\n') || character == TChar('\r') || character == TChar('\v') || character == TChar('\f'));
		}

	};
}