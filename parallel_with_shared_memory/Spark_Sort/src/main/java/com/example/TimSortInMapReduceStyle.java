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
         SparkConf conf = new SparkConf().setAppName("merge-k-sorted-lists-in-map-reduce-style");
         JavaSparkContext sc = new JavaSparkContext(conf);

         JavaRDD<String> lines = sc.textFile(inputPath);
         JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split(" ")).iterator());

         JavaRDD<String> sortedWords = words.mapPartitions(iterator -> {
             List<String> list = new java.util.ArrayList<>();
             while (iterator.hasNext()) {
                 list.add(iterator.next());
             }

             timSort(list);

             return list.iterator();
         });

         JavaRDD<String> coalescedSortedWords = sortedWords.coalesce(1);

//         List<String> finalSortedResults = mergeKSortedLists(coalescedSortedWords.collect());
         List<String> finalSortedResult = coalescedSortedWords.collect();

         mergeSort(finalSortedResult);

         sc.parallelize(finalSortedResult, 1).saveAsTextFile(outputPath);

         sc.stop();
         sc.close();
     }

     private List<String> mergeKSortedLists(List<String> lists) {
         PriorityQueue<String> minHeap = new PriorityQueue<>(lists);

         List<String> result = new java.util.ArrayList<>();
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
             List<String> sublist = new ArrayList<>(list.subList(i, end));

             insertionSort(sublist);

             for (int j = i; j < end; j++) {
                 list.set(j, sublist.get(j - i));
             }
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

     public void mergeSort(List<String> list) {
         if (list.size() <= 1) {
             return;
         }

         int middle = list.size() / 2;

         List<String> left = new ArrayList<>(list.subList(0, middle));
         List<String> right = new ArrayList<>(list.subList(middle, list.size()));

         mergeSort(left);
         mergeSort(right);

         merge(list, left, right);
     }

     private void merge(List<String> result, List<String> left, List<String> right) {
         int i = 0, j = 0, k = 0;

         while (i < left.size() && j < right.size()) {
             if (left.get(i).compareTo(right.get(j)) <= 0) {
                 result.set(k++, left.get(i++));
             } else {
                 result.set(k++, right.get(j++));
             }
         }

         while (i < left.size()) {
             result.set(k++, left.get(i++));
         }

         while (j < right.size()) {
             result.set(k++, right.get(j++));
         }
     }
 }