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
             List<String> list = new ArrayList<>();
             while (iterator.hasNext()) {
                 list.add(iterator.next());
             }

             timSort(list);

             return list.iterator();
         });

         JavaRDD<String> mergedList = sortedWords.repartition(1);
         JavaRDD<String> sortedMergedWords = mergedList.mapPartitions(iterator -> {
             List<String> list = new ArrayList<>();
             while (iterator.hasNext()) {
                 list.add(iterator.next());
             }

             List<String> mergedSortedLists = mergeKSortedLists(list, 40);

             return mergedSortedLists.iterator();
         });

         sortedMergedWords.saveAsTextFile(outputPath);

         sc.stop();
         sc.close();
     }

     public List<String> mergeKSortedLists(List<String> input, int k) {
         if (input == null || input.isEmpty()) {
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

         mergeSortedChunks(list, chunkSize);
     }

     private void insertionSort(List<String> list) {
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

     private void mergeSortedChunks(List<String> list, int chunkSize) {
         int n = list.size();

         for (int size = chunkSize; size < n; size *= 2) {
             for (int left = 0; left < n; left += 2 * size) {
                 int mid = Math.min(left + size, n);
                 int right = Math.min(left + 2 * size, n);

                 List<String> leftList = list.subList(left, mid);
                 List<String> rightList = list.subList(mid, right);

                 List<String> merged = new ArrayList<>(leftList.size() + rightList.size());
                 int i = 0, j = 0;

                 while (i < leftList.size() && j < rightList.size()) {
                     if (leftList.get(i).compareTo(rightList.get(j)) <= 0) {
                         merged.add(leftList.get(i++));
                     } else {
                         merged.add(rightList.get(j++));
                     }
                 }

                 while (i < leftList.size()) {
                     merged.add(leftList.get(i++));
                 }

                 while (j < rightList.size()) {
                     merged.add(rightList.get(j++));
                 }

                 for (int k = 0; k < merged.size(); k++) {
                     list.set(left + k, merged.get(k));
                 }
             }
         }
     }
 }
