#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "http_server.h"
#include "http_connection.h"
#include "http_response.h"
#include "worker.h"

/*
test
  cpu: i7-4790
  memory: 32G
  OS: win10 1803
  QT: 5.11.2 MSVC 2017 64bit

qoo@DESKTOP-TJ713T0:~$ ab -t 15 -c 20 http://127.0.0.1:12345/
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 5000 requests
Completed 10000 requests
Completed 15000 requests
Completed 20000 requests
Finished 21513 requests


Server Software:
Server Hostname:        127.0.0.1
Server Port:            12345

Document Path:          /
Document Length:        5 bytes

Concurrency Level:      20
Time taken for tests:   15.000 seconds
Complete requests:      21513
Failed requests:        0
Total transferred:      1462884 bytes
HTML transferred:       107565 bytes
Requests per second:    1434.15 [#/sec] (mean)
Time per request:       13.946 [ms] (mean)
Time per request:       0.697 [ms] (mean, across all concurrent requests)
Transfer rate:          95.24 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    4   2.9      3      29
Processing:     2   10   3.3      9      32
Waiting:        1    6   2.6      5      27
Total:          5   14   3.4     13      39

Percentage of the requests served within a certain time (ms)
  50%     13
  66%     14
  75%     15
  80%     15
  90%     17
  95%     21
  98%     24
  99%     26
 100%     39 (longest request)
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker(10);

    HttpServer s;
    QObject::connect(&s, &HttpServer::OnCreatedConnection, &worker, &Worker::MoveToThread);
    QObject::connect(&s, &HttpServer::OnCreatedConnection, [](HttpConnection *http_connection){
        QObject::connect(http_connection, &HttpConnection::OnRequest, [=](const HttpRequest &){
            HttpResponse http_response;
            http_response.EasyText("hello");
            http_connection->Write(http_response.Data());
        });
    });

    s.Listen(12345);

    return a.exec();
}
