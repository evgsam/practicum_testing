#include <cassert>
#include <stdexcept>

using namespace std::string_literals;

template<typename T>
class ScopedPtr {
public:
	ScopedPtr() = default;
	explicit ScopedPtr(T *raw_ptr) noexcept :
			ptr_(raw_ptr) {
	}
	ScopedPtr(const ScopedPtr&) = delete;
	~ScopedPtr() {
		delete ptr_;
	}

	T* GetRawPtr() const noexcept {
		return ptr_;
	}
	T* Release() noexcept {
		T *ptr2_ = ptr_;
		ptr_ = nullptr;
		return ptr2_;
	}
		
    // Оператор приведения к типу bool позволяет узнать, ссылается ли умный указатель
    // на какой-либо объект
    explicit operator bool() const noexcept {
        if (ptr_==nullptr){
        	return false;
        }
        else {
        	return true;
		}
    }

    // Оператор разыменования возвращает ссылку на объект
    // Выбрасывает исключение std::logic_error, если указатель нулевой
    T& operator*() const {
    	if (ptr_==nullptr){
    		throw std::logic_error("ptr == nullptr");
    	}
    	else {
			return &ptr_;
		}

        // Реализуйте самостоятельно
    }

    // Оператор -> должен возвращать указатель на объект
    // Выбрасывает исключение std::logic_error, если указатель нулевой
    T* operator->() const {
    	if (ptr_==nullptr){
    		throw std::logic_error("ptr == nullptr");
    	}
    	else {
			return *ptr_;
		}
    	// Реализуйте самостоятельно
    }


private:
	T *ptr_ = nullptr;
};

int main() {
	struct DeletionSpy {
		explicit DeletionSpy(bool &is_deleted) :
				is_deleted_(is_deleted) {
		}
		~DeletionSpy() {
			is_deleted_ = true;
		}
		bool &is_deleted_;
	};
	{
		bool is_deleted = false;
		{
			DeletionSpy *raw_ptr = new DeletionSpy(is_deleted);
			ScopedPtr<DeletionSpy> p(raw_ptr);
			assert(p.GetRawPtr() == raw_ptr);
			assert(!is_deleted);
		}
		assert(is_deleted);
	}
	{
		bool is_deleted = false;
		DeletionSpy *raw_ptr = new DeletionSpy(is_deleted);
		{
			ScopedPtr<DeletionSpy> scoped_ptr(raw_ptr);
			assert(scoped_ptr.Release() == raw_ptr);
			assert(scoped_ptr.GetRawPtr() == nullptr);
		}
		assert(!is_deleted);
		delete raw_ptr;
		assert(is_deleted);
	}
}
