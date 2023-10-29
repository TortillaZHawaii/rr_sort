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

5. (In progress...) Tu pojawi się info jak uruchomić nasze zadania (tworzenie jar'ów i zarządzanie zadaniami)

### Kroki do zrobienia

- Skonteneryzować:  maven'a (wraz z .m [.m powinien być w katalogu HOME]), vim, update ubuntu.
- Zaimplementować inne algorytmy sortowania

