#include "thrust_sort.cuh"

#include <thread>

#include <sys/types.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <thrust/sort.h>
#include <thrust/copy.h>

void rr::gpu_cuda::thrust_sort4(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
    // find strings that are of length at most 4 and store them in a device vector as ints
    thrust::host_vector<std::string> h_vec(begin, end);
    thrust::host_vector<std::string> shortStrings(h_vec.size());
    thrust::host_vector<std::string> longStrings(h_vec.size());

    auto shortEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), shortStrings.begin(),
        [](std::string s) { return s.length() <= 4;});
    auto longEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), longStrings.begin(), 
        [](std::string s) { return s.length() > 4; });

    shortStrings.resize(std::distance(shortStrings.begin(), shortEnd));
    longStrings.resize(std::distance(longStrings.begin(), longEnd));

    thrust::host_vector<int> shortStringsInt(shortStrings.size());
    thrust::device_vector<int> d_vec(shortStrings.size());
    thrust::transform(shortStrings.begin(), shortStrings.end(), shortStringsInt.begin(), 
        [](std::string s) { 
            int result = 0;
            for (char i = 0; i < s.length(); ++i) {
                result |= (s[i] << (8 * (4 - i - 1)));
            }
            return result;
        });
    thrust::copy(shortStringsInt.begin(), shortStringsInt.end(), d_vec.begin());

    // sort both vectors
    thrust::sort(d_vec.begin(), d_vec.end());
    thrust::sort(longStrings.begin(), longStrings.end());

    // copy back to host
    thrust::copy(d_vec.begin(), d_vec.end(), shortStringsInt.begin());

    // convert back to strings
    thrust::transform(shortStringsInt.begin(), shortStringsInt.end(), shortStrings.begin(), 
        [](int tstring) {
            std::string result;
            for (char i = 0; i < 4; ++i) {
                char c = (tstring >> (8 * (4 - i - 1))) & 0xFF;
                if (c != 0) {
                    result += c;
                } else {
                    break;
                }
            }
            return result;
        });

    // merge the two vectors
    thrust::merge(shortStrings.begin(), shortStrings.end(), longStrings.begin(), longStrings.end(), h_vec.begin());

    // copy back to original vector
    std::copy(h_vec.begin(), h_vec.end(), begin);
} 


void rr::gpu_cuda::thrust_sort8(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
    // find strings that are of length at most 4 and store them in a device vector as ints
    thrust::host_vector<std::string> h_vec(begin, end);
    thrust::host_vector<std::string> shortStrings(h_vec.size());
    thrust::host_vector<std::string> longStrings(h_vec.size());
    using ull = uint64_t;

    auto shortEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), shortStrings.begin(),
        [](std::string s) { return s.length() <= 8;});
    auto longEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), longStrings.begin(), 
        [](std::string s) { return s.length() > 8; });

    shortStrings.resize(std::distance(shortStrings.begin(), shortEnd));
    longStrings.resize(std::distance(longStrings.begin(), longEnd));

    thrust::host_vector<ull> shortStringsLL(shortStrings.size());
    thrust::device_vector<ull> d_vec(shortStrings.size());
    thrust::transform(shortStrings.begin(), shortStrings.end(), shortStringsLL.begin(), 
        [](std::string s) { 
            ull result = 0;
            for (int i = 0; i < s.length(); ++i) {
                result |= ((ull)s[i] << (8 * (8 - i - 1)));
            }
            return result;
        });
    
    thrust::copy(shortStringsLL.begin(), shortStringsLL.end(), d_vec.begin());

    // sort both vectors
    thrust::sort(d_vec.begin(), d_vec.end());
    thrust::sort(longStrings.begin(), longStrings.end());

    // copy back to host
    thrust::copy(d_vec.begin(), d_vec.end(), shortStringsLL.begin());
    
    // convert back to strings
    thrust::transform(shortStringsLL.begin(), shortStringsLL.end(), shortStrings.begin(), 
        [](ull tstring) {
            std::string result;
            for (char i = 0; i < 8; ++i) {
                char c = (char)(tstring >> (8 * (8 - i - 1)));
                if (c != 0) {
                    result += c;
                }
            }
            return result;
        });

    // merge the two vectors
    thrust::merge(shortStrings.begin(), shortStrings.end(), longStrings.begin(), longStrings.end(), h_vec.begin());

    // copy back to original vector
    std::copy(h_vec.begin(), h_vec.end(), begin);
} 

void rr::gpu_cuda::thrust_sort8split(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
    // find strings that are of length at most 4 and store them in a device vector as ints
    thrust::host_vector<std::string> h_vec(begin, end);
    thrust::host_vector<std::string> shortStrings(h_vec.size());
    thrust::host_vector<std::string> longStrings(h_vec.size());
    using ull = uint64_t;

    std::thread longWordsThread([&h_vec, &longStrings] {
        auto longEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), longStrings.begin(), 
            [](std::string s) { return s.length() > 8; });
        longStrings.resize(std::distance(longStrings.begin(), longEnd));

        // sort long words
        thrust::sort(longStrings.begin(), longStrings.end());
    });

    // short words thread
    auto shortEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), shortStrings.begin(),
        [](std::string s) { return s.length() <= 8;});
    shortStrings.resize(std::distance(shortStrings.begin(), shortEnd));

    thrust::host_vector<ull> shortStringsLL(shortStrings.size());
    thrust::device_vector<ull> d_vec(shortStrings.size());
    thrust::transform(shortStrings.begin(), shortStrings.end(), shortStringsLL.begin(), 
        [](std::string s) { 
            ull result = 0;
            for (int i = 0; i < s.length(); ++i) {
                result |= ((ull)s[i] << (8 * (8 - i - 1)));
            }
            return result;
        });
    
    thrust::copy(shortStringsLL.begin(), shortStringsLL.end(), d_vec.begin());

    // sort on device
    thrust::sort(d_vec.begin(), d_vec.end());

    // copy back to host
    thrust::copy(d_vec.begin(), d_vec.end(), shortStringsLL.begin());
    
    // convert back to strings
    thrust::transform(shortStringsLL.begin(), shortStringsLL.end(), shortStrings.begin(), 
        [](ull tstring) {
            std::string result;
            for (char i = 0; i < 8; ++i) {
                char c = (char)(tstring >> (8 * (8 - i - 1)));
                if (c != 0) {
                    result += c;
                }
            }
            return result;
        });

    // wait for long words to finish
    longWordsThread.join();

    // merge the two vectors
    thrust::merge(shortStrings.begin(), shortStrings.end(), longStrings.begin(), longStrings.end(), h_vec.begin());

    // copy back to original vector
    std::copy(h_vec.begin(), h_vec.end(), begin);
} 