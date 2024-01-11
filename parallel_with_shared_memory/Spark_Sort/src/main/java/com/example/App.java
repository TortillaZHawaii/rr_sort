package com.example;

import java.util.Objects;

public class App {

    public static void main(String[] args) {
        validArgs(args);
        MySortFactory factory = new MySortFactory();
        MySort mySort = factory.createMySort(args[2]);
        mySort.sort(args[0], args[1]);
    }

    private static void validArgs(String[] args) {
        validNumberOfArgs(args);
        validSelectedAlgorithm(args);
    }

    private static void validNumberOfArgs(String[] args) {
        if (args.length != 3) {
            System.err.println("Usage: SortWords <inputPath> <outputPath> <algorithm>");
            System.exit(1);
        }
    }

    private static void validSelectedAlgorithm(String[] args) {
        if (!Objects.equals(args[2], "defaultsort") &&
                !args[2].equals("timsort") &&
                !args[2].equals("mergesort") &&
                !args[2].equals("insertionsort") &&
                !args[2].equals("java")) {
            System.err.println("There are five algorithms available: defaultsort, timsort, mergesortm, insertionsort and java.");
            System.exit(1);
        }
    }
}