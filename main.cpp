#include <iostream>
#include <iterator>
#include <vector>
#include <memory>

class Iterator : public std::iterator<std::forward_iterator_tag, int>
{
  public:
    Iterator(const std::vector<int> & nums) {
        it = nums.begin();
        end = nums.end();
    }
    virtual ~Iterator() {}

    int next() {
        int val = *it;
        ++it;
        return val;
    }

    bool hasNext() const {
        return it != end;
    }

  private:
    std::vector<int>::const_iterator it;
    std::vector<int>::const_iterator end;
};

class PeekingIterator : public Iterator {
  public:
    PeekingIterator(const std::vector<int> & nums) : Iterator(nums) {
        val = Iterator::next();
        visited = false;
    }

    int peek() {
        if (!visited)
            return val;
        else {
            val = Iterator::next();
            visited = false;
            return val;
        }
    }

    int next() {
        if (!visited) {
            visited = true;
            return val;
        }
        else {
            return Iterator::next();
        }
    }

    bool hasNext() const {
        if (visited)
            return Iterator::hasNext();
        else
            return true;
    }

  private:
    bool visited;
    int val;
};

int main()
{
    std::vector<int> nums{ 1,2,3,4,5 };
    PeekingIterator it{ nums };
    std::cout << it.next() << std::endl; // 1
    std::cout << it.peek() << std::endl; // 2
    std::cout << it.peek() << std::endl; // 2
    std::cout << it.next() << std::endl; // 2
    std::cout << it.peek() << std::endl; // 3
    std::cout << it.next() << std::endl; // 3
    std::cout << it.next() << std::endl; // 4
    std::cout << it.peek() << std::endl; // 5
    std::cout << std::boolalpha << it.hasNext() << std::endl; // true
 
    
    // std::vector<int> nums{ 1,2,3 };
    // PeekingIterator it{ nums };
    // using std::cout;
    // using std::endl;
    // cout << it.next() << endl;
    // cout << it.peek() << endl;
    // cout << it.next() << endl;
    // cout << it.next() << endl;
    // cout << std::boolalpha << it.hasNext() << endl;
}
