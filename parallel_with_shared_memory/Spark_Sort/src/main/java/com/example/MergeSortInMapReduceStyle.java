package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class MergeSortInMapReduceStyle implements MySort, Serializable {

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("merge-sort-in-map-reduce-style");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath);

        JavaRDD<String> sortedLines = lines.mapPartitions(iterator -> {
            List<String> list = new ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            list = mergeSort(list);

            return list.iterator();
        });

        sortedLines.saveAsTextFile(outputPath);

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
}
