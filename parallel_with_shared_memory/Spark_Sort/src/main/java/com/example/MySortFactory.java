package com.example;

import java.util.Objects;

public class MySortFactory {

    public MySort createMySort(String nameOfSortAlgorithm) {
        if (Objects.equals(nameOfSortAlgorithm, "defaultsort")) {
            return new MergeSortInMapReduceStyle();
        } else if (Objects.equals(nameOfSortAlgorithm, "timsort")) {
            return new TimSortInMapReduceStyle();
        } else if (Objects.equals(nameOfSortAlgorithm, "mergesort")) {
            return new MergeSortInMapReduceStyle();
        } else if (Objects.equals(nameOfSortAlgorithm, "java")) {
            return new SparkStyleSort();
        }
        return new SparkStyleSort();
    }
}