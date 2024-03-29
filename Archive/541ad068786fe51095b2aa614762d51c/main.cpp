#include <functional>
#include <future>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <thread>


// Encapsulates an object of type T, a queue and a thread. The outside world can
// obtain access to T via callbacks. Callbacks are pushed to the queue from the
// user's thread and popped by the Actor in it's encapsulated thread. The
// callbacks are invoked in this thread as well.
template<typename T>
class Actor
{
public:
    template<typename ...Args>
    Actor(Args && ...args) : obj(std::forward<Args>(args)...) {}
    
    template<typename Ret>
    std::future<Ret> execute(const std::function<Ret(const T &)> & f)
    {
        auto promisePtr = std::make_shared< std::promise<Ret> >();
        auto l = [=]() { promisePtr->set_value(f(obj)); };
        Task task(l);
        queue.push_back(task);
        auto fut = promisePtr->get_future();
        return fut;
    } 
    
private:
    T obj;
    
    // type-erasure required to allow any kind of task
    typedef std::function<void()> Task; 
    
    // lockless queue would be better
    std::mutex mutex;
    std::condition_variable cond;
    std::deque<Task> queue;
};


struct Car
{
    unsigned age() const { return 2; }
};


int main()
{
    // Usage
    Actor<Car> car;
    std::future<unsigned> age = car.execute<unsigned>([](const Car & car) -> unsigned { return car.age(); });    
    std::cout << "age: " << age.get() << std::endl;
}