#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <format>

enum class ErrorFlags {
    InvalidFormat = 1 << 0,
    DuplicateJobId = 1 << 1,
    InvalidChain = 1 << 2,
    NoError = 0
};

std::string convertSecondsToTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int hours = minutes / 60;
    int seconds = totalSeconds % 60;
    return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
}

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
            return jobId > 0 && jobRuntime > -1 && nextJobId > -1;
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

        friend std::ostream& operator<<(std::ostream& os, const JobChain& jobChain) {
            os << std::format("Start Job Id: {}\n", jobChain.startJobId)
               << std::format("End Job Id: {}\n", jobChain.endJobId)
               << std::format("Total Jobs in Chain: {}\n", jobChain.numJobs)
               << std::format("Total Chain Runtime: {}\n", convertSecondsToTime(jobChain.totalChainRuntime));
            return os;
        }

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

            std::for_each(begin(jobs), end(jobs), [&nonProcessedJobs = nonProcessedJobs, &errorFlags = errorFlags](const Job& job) {
                int currentJobId = job.getJobId();
                // two jobs same id is error
                if(nonProcessedJobs.contains(currentJobId))
                    errorFlags = ErrorFlags::DuplicateJobId;
                    
                nonProcessedJobs.insert(currentJobId);
            });
            
            // chain the jobs together in map to allow us to iterate over them
            std::for_each(begin(jobs), end(jobs), [&previousJobs = previousJobs](const Job& job ) {
                int nextJobId = job.getNextJobId();
                int currentJobId = job.getJobId();

                if(nextJobId != 0)
                    previousJobs[nextJobId] = job;
            });

            bool validJobChain = generateJobChains();
            if(validJobChain)
                printJobChains();

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

                if(nextJobId == 0) {
                    int startJobId { jobId };
                    int endJobId { jobId };
                    int jobChainRuntime { job.getJobRuntime() };
                    int jobsInChain { 1 };

                    auto previousJobIt = previousJobs.find(jobId);
                    while(previousJobIt != end(previousJobs)) {
                        const Job& previousJob = (*previousJobIt).second;
                        int prevJobId = previousJob.getJobId();
                        int jobRuntime = previousJob.getJobRuntime();

                        // update chain info
                        startJobId = prevJobId;
                        jobChainRuntime += jobRuntime;
                        ++jobsInChain;
                        // remove from jobs we havent processed
                        nonProcessedJobs.erase(prevJobId);
                        // get the previous job in this chain or end if no previous job
                        previousJobIt = previousJobs.find(prevJobId);                         
                    }
                    jobChains.emplace_back(startJobId, endJobId, jobsInChain, jobChainRuntime);
                }
            };

            if(!nonProcessedJobs.empty())
                return false;

            return true;
        }

        void printJobChains() {
            std::cout << "------\n";
            std::copy (
                begin(jobChains),
                end(jobChains),
                std::ostream_iterator<JobChain> {std::cout, "------\n"}
            );
        }
    
    private:
        std::vector<Job> jobs;
        std::vector<JobChain> jobChains;
        std::unordered_map<int, Job> previousJobs;
        std::unordered_set<int> nonProcessedJobs;
        ErrorFlags errorFlags;
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