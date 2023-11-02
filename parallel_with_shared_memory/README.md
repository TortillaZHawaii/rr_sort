# Wersja równoległa na maszyny z pamięcią wspólną

### Jak to odpalić? (Wstępna wersja - łopatologiczna)

1. Pobierz obraz dokerowy [oneoffcoder/spark-jupyter](https://hub.docker.com/r/oneoffcoder/spark-jupyter)
```sh
docker pull oneoffcoder/spark-jupyter
```
2. Postaw kontener za pomocą komendy: 
```sh
docker run -it -p 9870:9870 -p 8088:8088 -p 8080:8080 -p 18080:18080 -p 9000:9000 -p 8888:8888 -p 9864:9864 -v $HOME/git/docker-containers/spark-jupyter/ubuntu/root/ipynb:/root/ipynb -v /root/Projects/rr_sort/parallel_with_shared_memory/Spark_Sort/:/root/Spark_Sort oneoffcoder/spark-jupyter
```
(można też przy użyciu docker compose [klik](./docker-compose.yml) )

gdzie,
```sh
/root/Projects/rr_sort/parallel_with_shared_memory/Spark_Sort/
```
jest ścieżka pod którą sklonowałeś repo.

3. Aby dostać się do wnętrzna kontenera (Polecam uruchomienie wielu terminali):
```sh
docker exec -it <id> /bin/bash
```
gdzie <id> to id kontenera, który postawiłeś w pkt. 2 (id możesz podpatrzyć komendą: ```docker ps```)

4. Uruchomienie przykładowego zadania, gdy jesteśmy już w kontenerze
```sh
yarn jar $HADOOP_HOME/share/hadoop/mapreduce/hadoop-mapreduce-examples-3.2.1.jar pi 1 50
```

Wynik wypisze się na konsoli a sam status pracy dostępny pod [adresem](http://localhost:8088/cluster). Więcej info na [githubie](https://github.com/oneoffcoder/docker-containers/tree/master/spark-jupyter).

5. Uruchamianie naszych zadań
   - Jak skompliować projekt?
   
   Uruchom polecenie ```mvn clean install``` w katalogu Spark_Sort (W nim znajduje się plik pom.xml czytany przez Maven'a). Skompliowany jar będzie znajdował się w katalogu target.

   - Jak uruchomić projekt?
   
   Skompilowany jar przyjmuje 3 argumenty: ```Spark_Sort-1.0-SNAPSHOT.jar <ścieżka do pliku, który chcemy posortować> <ścieżka do pliku wynikowego> <wybór wersji sekwernycjna/równoległa - java/spark>```
     
   - Wersja sekwencyjna
   
   Przykład komendy gdy znajdujemy się w katalogu target:
   ```sh
   java -jar Spark_Sort-1.0-SNAPSHOT.jar ../input.txt output.txt java
   ```
     
   - Wersja równoległa

   Przykład komendy gdy znajdujemy się w katalogu głównym projektu:
   ```sh
   $SPARK_HOME/bin/spark-submit --class com.example.App --master yarn target/Spark_Sort-1.0-SNAPSHOT.jar hdfs:///input.txt hdfs:///output.txt spark
   ```
   , gdzie
   ```hdfs:///input.txt``` oznacza ścieżkę ```/input.txt``` na hdfs'ie.

   Aktualnie input.txt nie znajduje się na hdfs a jedynie w naszym projekcie lokalnym. Aby wrzucić go na hdfs możemy użyć komendy:
   ```sh
   hadoop fs -put input.txt /
   ```
   TIP: Do hdfs'a można odwoływać się jak do zwykłego systemu plików w linuxie przykłady: ```hadoop fs -ls /``` (Wyświetli ls w katalogu / na hdfs'ie).

   INFO: Po uruchomieniu projektu w wersji równoległej wyniki czyli input.txt na hdfs będzie katalogiem w skład którego będą wchodziły "bloki". Chodzi o to, że HDFS u swojego powstania zakłada podział na bloki po max. 128 MB każdy. Czyli prawdopodobnie posorotwany tesks znajduje się na hdfs'ie pod ścieżką: ```/output.txt/part-00000```. Jeśli chcesz wypisać go na konsoli możesz wykorzystać polecenie: ```hadoop fs -cat /output.txt/part-00000```.
