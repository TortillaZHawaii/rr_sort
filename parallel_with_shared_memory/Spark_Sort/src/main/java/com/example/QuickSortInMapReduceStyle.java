package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class QuickSortInMapReduceStyle implements MySort, Serializable {

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("quick-sort-in-map-reduce-style");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath);

        JavaRDD<String> sortedLines = lines.mapPartitions(iterator -> {
            List<String> list = new ArrayList<>();
            while (iterator.hasNext()) {
                list.add(iterator.next());
            }

            list = quickSort(list);

            return list.iterator();
        });

        sortedLines.saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }

    private List<String> quickSort(List<String> list) {
        if (list.size() <= 1) {
            return list;
        }

        String pivot = list.get(list.size() / 2);

        List<String> less = new ArrayList<>();
        List<String> equal = new ArrayList<>();
        List<String> greater = new ArrayList<>();

        for (String element : list) {
            int cmp = element.compareTo(pivot);
            if (cmp < 0) {
                less.add(element);
            } else if (cmp > 0) {
                greater.add(element);
            } else {
                equal.add(element);
            }
        }

        List<String> result = new ArrayList<>();
        result.addAll(quickSort(less));
        result.addAll(equal);
        result.addAll(quickSort(greater));

        return result;
    }
}
