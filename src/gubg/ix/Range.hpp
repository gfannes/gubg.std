#ifndef HEADER_gubg_ix_Range_hpp_ALREADY_INCLUDED
#define HEADER_gubg_ix_Range_hpp_ALREADY_INCLUDED

#include <cstddef>
#include <ostream>

namespace gubg { namespace ix { 

	class Range
	{
	public:
		Range() {}
		Range(std::size_t start_ix, std::size_t size): begin_(start_ix), end_(start_ix+size) {}

		bool operator==(const Range &rhs) const {return begin_ == rhs.begin_ && end_ == rhs.end_;}
		bool operator!=(const Range &rhs) const {return !operator==(rhs);}

		std::size_t begin() const {return begin_;}
		std::size_t end()   const {return end_;}
		std::size_t size()  const {return end_ - begin_;}
		bool empty()        const {return end_ == begin_;}

		void clear() {*this = Range();}

		std::size_t ix(std::size_t offset) const {return begin_+offset;}
		std::size_t operator[](std::size_t offset) const {return ix(offset);}

		void setup(std::size_t start_ix, std::size_t size)
		{
			begin_ = start_ix;
			end_ = begin_+size;
		}
		void push_back(std::size_t size)
		{
			end_ += size;
		}
		void resize(std::size_t size)
		{
			end_ = begin_+size;
		}

		template <typename Ftor, typename... Data>
		void each(Ftor &&ftor, Data&&... data) const
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(data[ix]...);
		}
		template <typename Ftor>
		void each_index(Ftor &&ftor) const
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(ix);
		}
		template <typename Ftor, typename... Data>
		void each_with_index(Ftor &&ftor, Data&&... data) const
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(data[ix]..., ix);
		}

	private:
		std::size_t begin_ = 0u;
		std::size_t end_ = 0u;
	};

	inline std::ostream &operator<<(std::ostream &os, const Range &range)
	{
		return os << "["  << range.begin() << "; " << range.size() << "]";
	}

} } 

#endif