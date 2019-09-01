#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T> class singleton_wrapper
{
 public:
   static void create(std::unique_ptr<T> data)
   {
      if(_inst)
      {
         throw std::runtime_error("pnh");
      }
      _inst.reset(new singleton_wrapper(std::move(data)));
   }

   static const std::unique_ptr<T>& inst()
   {
      if(_inst)
      {
         return _inst->_data;
      }
   }

   ~singleton_wrapper()
   {
      std::cout << "dtor" << std::endl;
      // delete _inst;
   }

 private:
   singleton_wrapper(std::unique_ptr<T> data) : _data(std::move(data)) {}

   std::unique_ptr<T> _data;

   static std::unique_ptr<singleton_wrapper<T>> _inst;
};

template <typename T> std::unique_ptr<singleton_wrapper<T>> singleton_wrapper<T>::_inst = nullptr;

int main()
{

   auto str = std::make_unique<std::string>("hello");
   singleton_wrapper<std::string>::create(std::move(str));

   singleton_wrapper<int>::create(std::make_unique<int>(10));

   singleton_wrapper<std::string>::inst()->append(", world");

   std::cout << *singleton_wrapper<std::string>::inst() << std::endl;
   std::cout << *singleton_wrapper<int>::inst() << std::endl;

   return 0;
}