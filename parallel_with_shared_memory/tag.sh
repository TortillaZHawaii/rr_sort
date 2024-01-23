#!/bin/bash

ORGANIZATION=lorca19
REPOSITORY=modified-spark-jupyter
IMAGEID=modified-spark-jupyter:v.01

docker tag ${IMAGEID} ${ORGANIZATION}/${REPOSITORY}:latest

docker tag ${IMAGEID} ${ORGANIZATION}/${REPOSITORY}:latest
