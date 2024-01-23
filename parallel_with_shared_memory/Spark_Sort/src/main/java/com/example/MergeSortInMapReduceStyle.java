 package com.example;

 import org.apache.spark.SparkConf;
 import org.apache.spark.api.java.JavaRDD;
 import org.apache.spark.api.java.JavaSparkContext;

 import java.io.Serializable;
 import java.util.ArrayList;
 import java.util.Arrays;
 import java.util.List;

 public class MergeSortInMapReduceStyle implements MySort, Serializable {

     private final int NUMBER_OF_CHUNKS = 10;

     @Override
     public void sort(String inputPath, String outputPath) {
         // SETUP SPARK
         SparkConf conf = new SparkConf().setAppName("merge-sort-in-map-reduce-style");
         JavaSparkContext sc = new JavaSparkContext(conf);

         // READ FROM HDFS
         JavaRDD<String> lines = sc.textFile(inputPath);

         // MAP
         JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split(" ")).iterator());
         JavaRDD<String> sortedWords = words.mapPartitions(iterator -> {
             List<String> list = new ArrayList<>();
             while (iterator.hasNext()) {
                 list.add(iterator.next());
             }

             mergeSort(list);

             return list.iterator();
         });

         // REDUCE
         JavaRDD<String> coalescedSortedWords = sortedWords.coalesce(1);
         List<String> finalSortedResults = new ArrayList<>(coalescedSortedWords.collect());
         mergeKSort(finalSortedResults);

         // WRITE TO HDFS
         sc.parallelize(finalSortedResults, 1).saveAsTextFile(outputPath);

         // TEARDOWN SPARK
         sc.stop();
         sc.close();
     }

     private List<String> mergeSort(List<String> list) {
         if (list.size() <= 1) {
             return list;
         }

         int middle = list.size() / 2;
         List<String> left = mergeSort(list.subList(0, middle));
         List<String> right = mergeSort(list.subList(middle, list.size()));

         return merge(left, right);
     }

     private List<String> merge(List<String> left, List<String> right) {
         List<String> result = new ArrayList<>();
         int i = 0;
         int j = 0;

         while (i < left.size() && j < right.size()) {
             if (left.get(i).compareTo(right.get(j)) <= 0) {
                 result.add(left.get(i));
                 i++;
             } else {
                 result.add(right.get(j));
                 j++;
             }
         }

         while (i < left.size()) {
             result.add(left.get(i));
             i++;
         }

         while (j < right.size()) {
             result.add(right.get(j));
             j++;
         }

         return result;
     }

     public void mergeKSort(List<String> list) {
         if (list.size() <= 1) {
             return;
         }

         int middle = list.size() / 2;

         List<String> left = new ArrayList<>(list.subList(0, middle));
         List<String> right = new ArrayList<>(list.subList(middle, list.size()));

         mergeSort(left);
         mergeSort(right);

         mergeK(list, left, right);
     }

     private void mergeK(List<String> result, List<String> left, List<String> right) {
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
