package com.example;

import java.util.Objects;

public class MySortFactory {

    MySort createMySort(String nameOfSortAlgorithm) {
        if (Objects.equals(nameOfSortAlgorithm, "spark")) {
            return new SparkSort();
        } else if (Objects.equals(nameOfSortAlgorithm, "java")) {
            return new SparkStyleSort();
        }
        return new SparkStyleSort();
    }
}
