#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc >= 3) {

        int range     = std::atoi(argv[2]);     //users input
        int workerNum = std::atoi(argv[1]);    //number of workers to be created

        int evenjob = range / workerNum;         //shares the job almost evenly

                                            // Range for worker
        int minrange = 1;
        int maxrange = evenjob;

                                         // Creation of workers
        for (int i = 0; i < workerNum; i++) {
            int status;
            int pid = fork();          // Fork creates the child (worker) process

            if (pid == 0) {
                                        // Convert integers to strings to pass to the worker
                std::string low = std::to_string(minrange);
                std::string high = std::to_string(maxrange);

                execl("./workerboss", "./workerboss", low.c_str(), high.c_str(), (char*)NULL);
                std::cerr << "Low = " << low << ", High = " << high << std::endl;
                exit(-1); // Exit child process if execl fails
            }
            else if (pid > 0) {
                // Parent process: wait for the child process
                waitpid(pid, &status, 0);
            }
            else {
                std::cerr << "Fork failed!" << std::endl;
                return 1;
            }

                                            // Range for the next worker
            minrange = maxrange + 1;        //goes to the end of the previous worker increments by 1
            maxrange = maxrange + evenjob; //forms the end of the current worker

            if (i == workerNum - 2) { 
               maxrange = range;         //last worker gets whatever is left
            }

            std::cout << std::endl;
        }
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <workers> <range>\n" << std::endl;
        return 1;
    }

    return 0;
}
