def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic) -> List[Directions]:
    myPriorityQueue = util.PriorityQueue()
    visitedCoords = {}
    start=problem.getStartState()
    myPriorityQueue.push((start, [], 0),heuristic(start,problem))
    while not myPriorityQueue.isEmpty():
        current_coord, current_path, current_path_cost = myPriorityQueue.pop()
        if problem.isGoalState(current_coord):
            print(current_path)
            return current_path
        if current_coord not in visitedCoords or current_path_cost < visitedCoords[current_coord]:
            visitedCoords[current_coord] = current_path_cost
            for suc_coord, suc_direction, suc_step_cost in problem.getSuccessors(current_coord):
                new_path_cost = current_path_cost + suc_step_cost
                if suc_coord not in visitedCoords or new_path_cost < visitedCoords[suc_coord]:
                    greedy_cost = heuristic(suc_coord, problem)
                    new_cost = new_path_cost + greedy_cost
                    new_path = current_path + [suc_direction]
                    myPriorityQueue.push((suc_coord,new_path, new_path_cost), new_cost)
    
    # incase goal wasn't reached
    return []