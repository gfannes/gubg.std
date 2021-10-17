#ifndef HEADER_gubg_ix_Range_hpp_ALREADY_INCLUDED
#define HEADER_gubg_ix_Range_hpp_ALREADY_INCLUDED

#include <cstdint>

namespace gubg { namespace ix { 

	class Range
	{
	public:
		std::size_t begin() const {return begin_;}
		std::size_t end()   const {return end_;}
		std::size_t size()  const {return end_ - begin_;}
		bool empty()        const {return end_ == begin_;}

		template <typename Index>
		void consume(std::size_t size, Index &index)
		{
			begin_ = index;
			end_ = begin_+size;
			index += size;
		}

		template <typename Ftor, typename... Data>
		void each(Ftor &&ftor, Data&&... data)
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(data[ix]...);
		}
		template <typename Ftor>
		void each_index(Ftor &&ftor)
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(ix);
		}
		template <typename Ftor, typename... Data>
		void each_with_index(Ftor &&ftor, Data&&... data)
		{
			for (auto ix = begin_; ix != end_; ++ix) ftor(data[ix]..., ix);
		}

	private:
		std::size_t begin_ = 0u;
		std::size_t end_ = 0u;
	};

} } 

#endif