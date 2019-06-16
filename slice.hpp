#ifndef _SLICE_HPP_
#define _SLICE_HPP_
#include <cstdint>
#include <iostream>

template<typename T>
class slice{
public:
	template<bool is_mut>
	class iterator_generic{
	public:
		iterator_generic(T base) : position(base){}
		iterator_generic(const iterator_generic &rhs) : position(rhs.position){}
		bool operator==(const iterator_generic &rhs) const{
			return position==rhs.position;
		}
		bool operator!=(const iterator_generic &rhs) const{
			return position!=rhs.position;
		}
		template<typename U = T>
		std::enable_if_t<is_mut, decltype(*std::declval<U>())&> operator*(){
			return *position;
		}
		template<typename U = T>
		const std::enable_if_t<!is_mut, decltype(*std::declval<U>())&> operator*(){
			const U &result = *position;
			return result;
		}
		T& operator->(){
			return position;
		}
		iterator_generic& operator+=(int offset){
			return position+=offset, *this;
		}
		iterator_generic& operator++(){ // ++a
			return ++position, *this;
		}
		iterator_generic operator++(int){ // a++
			return iterator_generic(position++);
		}
		iterator_generic operator+(int offset) const{
			return iterator_generic(position+offset);
		}
		iterator_generic& operator-=(int offset){
			return position-=offset, *this;
		}
		iterator_generic& operator--(){
			return ++position, *this;
		}
		iterator_generic operator--(int){
			return iterator_generic(position++);
		}
		iterator_generic operator-(int offset) const{
			return iterator_generic(position-offset);
		}

	protected:
		T position;
	};

	typedef decltype(*std::declval<T>()) valueType;
	typedef iterator_generic<true> iterator;
	typedef iterator_generic<false> const_iterator;

	slice(const T& begin, size_t n)
		: base(begin), length(n) {}
	iterator begin(){
		return iterator(base);
	}
	const_iterator begin() const{
		return iterator(base);
	}
	iterator end(){
		return iterator(base+length);
	}
	const_iterator end() const{
		return iterator(base+length);
	}
	size_t size() const{
		return length;
	}
	auto& operator[](const int offset){
		return *(base+offset);
	}
	const auto& operator[](const int offset) const{
		return *(base+offset);
	}

private:
	const T base;
	const size_t length;
};

#endif // _SLICE_HPP_