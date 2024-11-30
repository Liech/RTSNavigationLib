#pragma once

#include <functional>
#include <vector>
#include <map>

//https://stackoverflow.com/questions/76444431/faster-alternatives-to-the-hungarian-algorithm
//https://developers.google.com/optimization/flow/assignment_min_cost_flow

namespace RTSNavigationLib {
  class AssignmentProblemSolverPlain {
  public:
    static std::vector<size_t> getTickets(size_t workerAmount,const std::map<std::pair<size_t, size_t>,double>& allCosts);
  };

  template<typename Worker, typename Task>
  class AssignmentProblemMinCostFlow {
  public:
    AssignmentProblemMinCostFlow(const std::vector<Worker>& workers_, const std::vector<Task>& tasks_,std::function<double(const Worker&, const Task&)> costFunction)
      : workers(workers_),
      tasks(tasks_)
    {
      assert(workers.size() == tasks.size());
      getCost = costFunction;
    }

    //the ticket vector has the same order as workers. for each worker the best task index is returned
    std::vector<size_t> getTickets() const {
      auto costs = getAllCosts();
      return AssignmentProblemSolverPlain::getTickets(workers.size(),costs);
    }

  private:
    std::map<std::pair<size_t, size_t>, double> getAllCosts() const {
      std::map<std::pair<size_t, size_t>, double> result;
      for (size_t dude = 0;dude < workers.size();dude++)
        for (size_t job = 0;job<tasks.size();job++)
          result[std::make_pair(dude, job)] = getCost(workers[dude], tasks[job]);
      return result;
    }

    std::function<double(const Worker&, const Task&)> getCost;

    const std::vector<Worker>& workers;
    const std::vector<Task>  & tasks;
  };
}