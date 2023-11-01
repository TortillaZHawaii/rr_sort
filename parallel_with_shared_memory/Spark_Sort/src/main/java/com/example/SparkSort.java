package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;

import java.util.Arrays;

public class SparkSort implements MySort {

    @Override
    public void sort(String inputPath, String outputPath) {
        SparkConf conf = new SparkConf().setAppName("HadoopSparkSort");
        JavaSparkContext sc = new JavaSparkContext(conf);

        JavaRDD<String> lines = sc.textFile(inputPath);

        JavaRDD<String> sortedLines = lines.flatMap(line -> Arrays.asList(line.split(" ")).iterator())
                .sortBy(word -> word, true, 1);

        sortedLines.saveAsTextFile(outputPath);

        sc.stop();
        sc.close();
    }
}
