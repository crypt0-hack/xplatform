#include "./cache.hpp"

template<typename T> void LRU(List<T> &cache, T data, int page);
template<typename T> T& get(int page);
template<typename T> void work(List<T> &cache, int page);


int main() {
    #if 1
        srand(time(NULL));
        List<int> cache;

        for (int i = 0; i < MAX - 1; i++) {
            cache.push_front( i + 1, i + 1 );
        }
        cache.print();

        #if 1
            work<int>(cache, rand() % 10 + 1);
            cache.print();
        #endif
    #endif

    return 0;
}


template<typename T> void LRU(List<T> &cache, T data, int page) {
    struct SS<T> search;
    cache.find(page, search);

    if (!cache.is_full()) {
        cache.push_front(data, page);
    }  else if (search.page == page) {
        int index = cache.get_index(page);
        if (index != -1) {
            cache.remove(index);
            cache.push_front(data, page);
        }
    } else {
        cache.pop_back();
        cache.push_front(data, page);
    }
}
template<typename T> T& get(int page) {
    std::ifstream pt("page_table.txt"); // page table

    std::string tmp;
    getline(pt, tmp);

    for (int i = 0; i < 20; i++) {
        if (i == page) {
            return ( dynamic_cast<T&>(tmp) );
        }
        getline(pt, tmp);
    }

    return ( dynamic_cast<T&>(tmp) );
}
template<typename T> void work(List<T> &cache, int page) {
    int to_work = cache.get_index(page);

    if (to_work == -1) {
        std::cout << "Data not found" << std::endl;
        T data = get<T>(page);
        LRU<T>(cache, data, page);
    } else {
        T data = cache[to_work];
        std::cout << "Work with " << data<< std::endl;
        LRU<T>(cache, data, page);
    }
}
