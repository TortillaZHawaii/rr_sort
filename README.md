# TODO
* w defaultowym koneterze nie jest podłączony spark

## Notes
* hadoop składa się z yarn, dfs, map-reduce
* trzeba zastąpić map-reduce przez sparka
* zrobić `jar` i wrzucić do 

## References
* (GO TO solution, also with Python) https://hub.docker.com/r/oneoffcoder/spark-jupyter 
* (basic solution, just hadoop) https://hub.docker.com/r/apache/hadoop

## Misc
```
$SPARK_HOME/bin/spark-submit --class org.apache.spark.examples.SparkPi \
    --master yarn \
    $SPARK_HOME/examples/jars/spark-examples*.jar \
    100
```