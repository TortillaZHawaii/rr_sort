package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.List;
import java.util.Collections;

public class QuickSort implements MySort, Serializable {

    private final int NUMBER_OF_CHUNKS = 10;

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("quick-sort");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath);

        JavaRDD<String> sortedLines = lines.mapPartitions(iterator -> {
            List<String> list = new java.util.ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            quickSort(list);

            return list.iterator();
        });

        sortedLines.saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }

    private static void quickSort(List<String> list) {
        // Java stdlib implementation of QuickSort
        Collections.sort(list);
        // return list;
    }
}
