package com.example;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.Function;

import java.util.ArrayList; 
import java.util.Collections; 
import java.util.List; 

public class App {
    public static void main(String[] args) {
        // Konfiguracja Sparka
        SparkConf conf = new SparkConf().setAppName("JavaSparkHadoopMergesort");
        JavaSparkContext sc = new JavaSparkContext(conf);

        String inputFile = "hdfs://input.txt";
        String outputFile = "hdfs://output.txt";

        // Wczytanie danych z pliku
        JavaRDD<String> data = sc.textFile(inputFile);

        JavaRDD<String> sortedData = data.mapPartitions(iter -> {
            List<String> dataList = new ArrayList<>();
            while (iter.hasNext()) {
                dataList.add(iter.next());
            }
            Collections.sort(dataList);
            return dataList.iterator();
        });

        // Zapis posortowanych danych do pliku
        sortedData.saveAsTextFile(outputFile);

        sc.stop();
    }
}
