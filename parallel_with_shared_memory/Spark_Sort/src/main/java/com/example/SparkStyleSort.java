package com.example;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Comparator;

public class SparkStyleSort implements MySort {
    private static final int MIN_RUN = 32;

    @Override
    public void sort(String inputPath, String outputPath) {
        try {
            String text = new String(Files.readAllBytes(Paths.get(inputPath)), StandardCharsets.UTF_8);
            String[] words = text.split("\\s+");
            sort(words, String.CASE_INSENSITIVE_ORDER);
            Files.write(Paths.get(outputPath), String.join("\n", words).getBytes());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public <T> void sort(T[] arr, Comparator<T> comparator) {
        int n = arr.length;
        for (int i = 0; i < n; i += MIN_RUN) {
            int end = Math.min(i + MIN_RUN, n);
            Arrays.sort(arr, i, end, comparator);
        }
        timsortMerge(arr, n, comparator);
    }

    private <T> void timsortMerge(T[] arr, int n, Comparator<T> comparator) {
        for (int size = MIN_RUN; size < n; size *= 2) {
            mergePass(arr, size, comparator);
        }
    }

    private <T> void mergePass(T[] arr, int size, Comparator<T> comparator) {
        int n = arr.length;
        for (int start = 0; start < n; start += 2 * size) {
            int mid = Math.min(start + size, n);
            int end = Math.min(start + 2 * size, n);
            if (mid < end) {
                merge(arr, start, mid, end, comparator);
            }
        }
    }

    private <T> void merge(T[] arr, int left, int mid, int right, Comparator<T> comparator) {
        int leftSize = mid - left;
        int rightSize = right - mid;
        T[] leftArr = Arrays.copyOfRange(arr, left, mid);
        T[] rightArr = Arrays.copyOfRange(arr, mid, right);
        int i = 0, j = 0, k = left;

        while (i < leftSize && j < rightSize) {
            if (comparator.compare(leftArr[i], rightArr[j]) <= 0) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }

        while (i < leftSize) {
            arr[k++] = leftArr[i++];
        }

        while (j < rightSize) {
            arr[k++] = rightArr[j++];
        }
    }
}
