#include <iostream>
#include <map>
#include <memory>
#include <iterator>


template<typename T>
struct logging_allocator {
    using value_type = T;

    using pointer = T*;
	
	void* PoolStart;
	size_t mSize = 200;
	int mUsed = 0;
	pointer pCurElement = nullptr;
	pointer pFirstElement = nullptr;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };

    logging_allocator() = default;
    ~logging_allocator() = default;

    template<typename U>
     logging_allocator(const logging_allocator<U>&)  {
    }

    T *allocate(std::size_t n) {
		pointer p;
		if(mUsed == 11)
			throw std::bad_alloc();
		std::cout << "allocating: ";
		if (mUsed == 0) {
			PoolStart = std::malloc(mSize * sizeof(T));
			std::cout << " NEW [" << PoolStart << "]" << std::endl;
			p = (pointer)PoolStart;
			pFirstElement = p;
		}
		else {
			std::cout << " using: [" << mUsed << " in "<< PoolStart <<"]" << std::endl;
			p = pCurElement + sizeof(T);
		}
		++mUsed;
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
		std::cout << "deallocating [n  = " << p << "] ";
		if (mUsed > 0 && p == pFirstElement){
			std::free(PoolStart);
			std::cout << "OK! [" << PoolStart << "] " << std::endl;
			mUsed = 0;
		}
		else
			std::cout << " skipped! ["<< PoolStart  <<"] " << std::endl;
		p = nullptr;
    }

	template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
			std::cout << "construct " << p << std::endl;
			new(p) U(std::forward<Args>(args)...);
			pCurElement = (T*)p;
    };

	void destroy(T *p) {
		std::cout << "destroing " << p;
		p->~T();
		std::cout << "  Ok!" << std::endl;
    }
};

long double fact(int N)
{
	if (N < 0) return 0;
	else if (N == 0)
		return 1;
	else
		return N * fact(N - 1);
}



template<typename T>
class ptr_iterator
	: public std::iterator<std::forward_iterator_tag, T>
{
	typedef ptr_iterator<T>  iterator;
	pointer pos_;
public:
	ptr_iterator() : pos_(nullptr) {}
	ptr_iterator(T* v) : pos_(v) {}
	~ptr_iterator() {}

	iterator operator++(int) { pos_ = pos_->next; return this; }
	iterator& operator++() { pos_ = pos_->next; return this; }
	void next() { pos_ = pos_->next; };
	bool end() { return pos_ == nullptr; };

	reference operator* () const { return *pos_; }
	pointer   operator->() const { return pos_; }
	bool operator!=(const iterator& rhs) const { return pos_ != rhs.pos_; }
};



struct MyStruct {
	MyStruct(int n) : i(n) { next = nullptr;  };
	int i;
	MyStruct* next;
};

template<typename T>
struct MyContainer {
	
	MyContainer* p;
	size_t cnt = 0;
	MyStruct* firstElem = nullptr;
	MyStruct* currElem = nullptr;
	T* allocator;

	MyContainer() {
		allocator = new T();
	}
	~MyContainer() {
		allocator->deallocate(firstElem, 1);
	}
	MyStruct* Add(int i) 
	{
		MyStruct* tmpElem = allocator->allocate(1);
		allocator->construct(tmpElem, i);
		if (firstElem == nullptr) {
			firstElem = currElem = tmpElem;
		}
		else {
			currElem->next = tmpElem;
			currElem = tmpElem;
		}
		++cnt;
		return currElem;
	}

	ptr_iterator<MyStruct>* begin() { return new ptr_iterator<MyStruct>(firstElem); };
	ptr_iterator<MyStruct>* end() { return nullptr; };
};



int main(int, char *[]) {

	auto m1 = std::map<int, int>{};
	for (int i = 0; i < 10; ++i) {
		m1[i] = (int)fact(i);
	}

	auto m2 = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>> >{};
     for (int i = 0; i < 10; ++i) {
         m2[i] = (int)fact(i);
     }

	 for (auto mm : m2) {
		 std::cout << mm.first <<" "<< mm.second << std::endl;
	 }
	 
	 auto v3 = std::make_unique < MyContainer<logging_allocator<MyStruct>>>();
	 for (int i = 0; i < 10; ++i) {
		 v3->Add(i);
	 }
	 
	 for (ptr_iterator<MyStruct>* it = v3->begin(); !it->end(); it->next() ) {
		 std::cout << (*it)->i << std::endl;
	 }

    return 0;
}
