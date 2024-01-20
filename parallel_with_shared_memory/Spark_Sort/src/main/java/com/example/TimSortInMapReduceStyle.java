package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;

public class TimSortInMapReduceStyle implements MySort, Serializable {

    private final int NUMBER_OF_CHUNKS = 10;

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("tim-sort-in-map-reduce-style");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath).repartition(40);
        JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split(" ")).iterator());

        JavaRDD<String> sortedWords = words.mapPartitions(iterator -> {
            List<String> list = new java.util.ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            timSort(list);

            return list.iterator();
        });

        sortedWords.coalesce(1).saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }

    private void timSort(List<String> list) {
        int n = list.size();
        int chunkSize = Math.max(1, n / NUMBER_OF_CHUNKS);

        for (int i = 0; i < n; i += chunkSize) {
            int end = Math.min(i + chunkSize, n);
            List<String> sublist = list.subList(i, end);

            insertionSort(sublist);
        }

        insertionSort(list);
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