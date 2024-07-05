#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <format>


class Job {
    public:
        int getJobId() const { return jobId; }
        int getNextJobId() const { return nextJobId; }
        int getJobRuntime() const { return jobRuntime; }

        friend std::istream& operator>>(std::istream& is, Job& job) {
            char comma1, comma2;
            is >> job.jobId >> comma1
               >> job.jobRuntime >> comma2
               >> job.nextJobId;

            if(!job.isValid())
                is.setstate(std::ios::failbit);
            return is;
        }

    private:
        inline bool isValid() const {
            return jobId > -1 && jobRuntime > -1 && nextJobId > -1;
        }

    private:
        int jobId;
        int jobRuntime;
        int nextJobId;   
};


class JobChain {
    public:
        JobChain(int startJobId_, int endJobId_, int numJobs_, int totalChainRuntime_)
        : startJobId { startJobId_ }
        , endJobId { endJobId_ }
        , numJobs { numJobs_ }
        , totalChainRuntime { totalChainRuntime_ }
        {}

    private:
        int startJobId;
        int endJobId;
        int numJobs;
        int totalChainRuntime;
};


class JobProcessor {

    public:
        bool processJobs() {
            if(!readInJobs())
                return false;

            // add each job to set to process them later
            int duplicateJobId {0};
            std::for_each(begin(jobs), end(jobs), [&nonProcessedJobs = nonProcessedJobs, &duplicateJobId](const Job& job) {
                int currentJobId = job.getJobId();
                // two jobs same id is error
                if(nonProcessedJobs.contains(currentJobId)) {
                    duplicateJobId = 1;
                    return;
                }
                nonProcessedJobs.insert(currentJobId);
            });

            if(duplicateJobId)
                return false;
            
            // we can't have input s.t. jobId = nextJobId (i.e. 3,100,3) doesn't make sense inf loop
            int sameJobIdAsNextJob = 0;
            // chain the jobs together in map to allow us to iterate over them
            std::for_each(begin(jobs), end(jobs), [&previousJobs = previousJobs, &sameJobIdAsNextJob](const Job& job ) {
                int nextJobId = job.getNextJobId();
                int currentJobId = job.getJobId();

                if(currentJobId == nextJobId) {
                    sameJobIdAsNextJob = 1;
                    return;
                }
                if(nextJobId != 0)
                    previousJobs[nextJobId] = job;
            });

            if(sameJobIdAsNextJob)
                return false;

            bool validJobChain = generateJobChains();
            return validJobChain;
        }

    private:
        bool readInJobs() {
            std::string csvHeader;
            std::cin >> csvHeader;

            std::copy (
                std::istream_iterator<Job> {std::cin},
                std::istream_iterator<Job> {},
                std::back_inserter(jobs)
            );

            if(std::cin.fail() && !std::cin.eof())
                return false;

            return true;
        }

        bool generateJobChains() {
            int jobChainCycle {0};
            for(const auto& job : jobs) {
                int jobId = job.getJobId();
                int nextJobId = job.getNextJobId();
                jobIdsInChain.clear();

                if(nextJobId != 0) {
                    int startJobId { jobId };
                    int endJobId { jobId };
                    int jobChainRuntime { job.getJobRuntime() };
                    int jobsInChain { 1 };

                    // remove this job from our list
                    nonProcessedJobs.erase(jobId);
                    // store current job Ids in the chain, we need this to prevent cyclic graph situation
                    // (i.e) jobs are 1,100,4 and 4,100,1 would cause inf loop
                    jobIdsInChain.insert(jobId);

                    auto previousJobIt = previousJobs.find(jobId);
                    while(previousJobIt != end(previousJobs)) {
                        const Job& previousJob = (*previousJobIt).second;
                        int prevJobId = previousJob.getJobId();
                        int jobRuntime = previousJob.getJobRuntime();

                        // we have seen this jobId before in this chain this means there is a loop
                        // treating loops as malformed input
                        if(jobIdsInChain.contains(prevJobId)) {
                            std::cout << std::format("Cycle with job id {}\n", prevJobId);
                            return false;
                        }

                        // update chain info
                        startJobId = prevJobId;
                        jobChainRuntime += jobRuntime;
                        ++jobsInChain;

                        jobIdsInChain.insert(prevJobId);
                        // remove from jobs we havent processed
                        nonProcessedJobs.erase(prevJobId);
                        // get the previous job in this chain or end if no previous job
                        previousJobIt = previousJobs.find(prevJobId);                         
                    }
                    jobChains.emplace_back(startJobId, endJobId, jobChainRuntime, jobsInChain);
                }
            };

            if(!nonProcessedJobs.empty()) 
                return false;
            return true;
        }
    
    private:
        std::vector<Job> jobs;
        std::vector<JobChain> jobChains;
        std::unordered_map<int, Job> previousJobs;
        std::unordered_set<int> nonProcessedJobs;
        std::unordered_set<int> jobIdsInChain;
};

int main() {
    JobProcessor processor;
    if(!processor.processJobs()) {
        std::cout << "Malformed Input\n";
        return -1;
    }
    return 0;
}

/*

edge cases:
    incorrect input format
    duplicate job id
    jobId and nextJobId are same
    overflow?
    single jobs?
    jobs form cycle?
*/