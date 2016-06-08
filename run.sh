#!/bin/bash
qmake && make 
./server/server &
sleep 2
./client/client &
