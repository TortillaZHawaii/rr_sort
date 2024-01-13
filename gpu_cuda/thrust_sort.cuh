#pragma once

#include <string>
#include <vector>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <thrust/sort.h>
#include <thrust/copy.h>

namespace rr::gpu_cuda {
    // since it's a template function, it needs to be defined in the header
template <typename T>
void thrust_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
    // find strings that are of length at most 4 and store them in a device vector as ints
    thrust::host_vector<std::string> h_vec(begin, end);
    thrust::host_vector<std::string> shortStrings(h_vec.size());
    thrust::host_vector<std::string> longStrings(h_vec.size());

    auto shortEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), shortStrings.begin(),
        [](std::string s) { return s.length() <= static_cast<int>(sizeof(T)); });
    auto longEnd = thrust::copy_if(h_vec.begin(), h_vec.end(), longStrings.begin(), 
        [](std::string s) { return s.length() > static_cast<int>(sizeof(T)); });

    shortStrings.resize(std::distance(shortStrings.begin(), shortEnd));
    longStrings.resize(std::distance(longStrings.begin(), longEnd));

    thrust::host_vector<T> shortStringsInt(shortStrings.size());
    thrust::device_vector<T> d_vec(shortStrings.size());
    thrust::transform(shortStrings.begin(), shortStrings.end(), shortStringsInt.begin(), 
        [](std::string s) { 
            T result = 0;
            for (char i = 0; i < s.length(); ++i) {
                result |= (s[i] << (8 * (3 - i)));
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
        [](T tstring) {
            std::string result;
            for (char i = 0; i < static_cast<char>(sizeof(T)); ++i) {
                char c = (tstring >> (8 * (static_cast<char>(sizeof(T)) - i - 1))) & 0xFF;
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
}
