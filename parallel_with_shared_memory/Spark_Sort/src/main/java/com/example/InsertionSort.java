package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.List;

public class InsertionSort implements MySort, Serializable {

    private final int NUMBER_OF_CHUNKS = 10;

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("insertion-sort");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath);

        JavaRDD<String> sortedLines = lines.mapPartitions(iterator -> {
            List<String> list = new java.util.ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            insertionSort(list);

            return list.iterator();
        });

        sortedLines.saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }

    private static void insertionSort(List<String> list) {
        int n = list.size();
        for (int i = 1; i < n; ++i) {
            String key = list.get(i);
            int j = i - 1;

            while (j >= 0 && list.get(j).compareTo(key) > 0) {
                list.set(j + 1, list.get(j));
                j = j - 1;
            }
            list.set(j + 1, key);
        }
    }
}