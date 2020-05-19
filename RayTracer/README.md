This program uses a multithreaded architecture that involves the following:

1) initializing 4 "worker" objects in four separate threads
2) running each worker such that is grabs an available "request" object to complete, or waits for a new one
3) creating new request objects for each pixel in BMP, and either assigning to a worker if available, or adding to a queue
4) waiting for all pixel values to be calculated
5) writing pixel contents to a BMP
