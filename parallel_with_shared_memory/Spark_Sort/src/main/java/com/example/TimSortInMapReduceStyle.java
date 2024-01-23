 package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;


public class TimSortInMapReduceStyle implements MySort, Serializable {

    private final int NUMBER_OF_CHUNKS = 10;

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("tim-sort-in-map-reduce-style");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath).repartition(2);
        JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split(" ")).iterator());

        JavaRDD<String> sortedWords = words.mapPartitions(iterator -> {
            List<String> list = new java.util.ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            timSort(list);

            return list.iterator();
        });

        JavaRDD<String> mergedList =sortedWords.coalesce(1);
        JavaRDD<String> sortedMergedWords = mergedList.mapPartitions(iterator -> {
            List<String> list = new java.util.ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            List<String> mergedKSotedList = mergeKSortedLists(list, 40);

            return mergedKSotedList.iterator();
        });

        sortedMergedWords.saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }

    public List<String> mergeKSortedLists(List<String> input, int k) {
        if (input == null || input.isEmpty()) {
            // return new ArrayList<>();
            throw new RuntimeException("Input list is empty");
        }

        PriorityQueue<String> minHeap = new PriorityQueue<>();
        List<String> result = new ArrayList<>();

        int groups = 0;
        for (String element : input) {
            minHeap.offer(element);
            groups++;

            if (groups == k) {
                while (!minHeap.isEmpty()) {
                    result.add(minHeap.poll());
                }
                groups = 0;
            }
        }

        while (!minHeap.isEmpty()) {
            result.add(minHeap.poll());
        }

        return result;
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