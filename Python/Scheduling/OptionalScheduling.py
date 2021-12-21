from collections import defaultdict
import networkx as nx # Library for displaying graphs.
import matplotlib.pyplot as plt

class AND_OR_Scheduler(object):

    def __init__(self):
        # It is up to you to implement the initialization.
        # YOUR CODE HERE

        self.tasks = set()
        # The successors of a task are the tasks that depend on it, and can
        # only be done once the task is completed.
        self.successors = defaultdict(set)
        # The predecessors of a task have to be done before the task.
        self.predecessors = defaultdict(set)
        self.optionalPredecessors = defaultdict(set)
        self.completed_tasks = set() # completed tasks

    def add_and_task(self, t, dependencies):
        """Adds an AND task t with given dependencies."""
        # Makes sure we know about all tasks mentioned.
        assert t not in self.tasks or len(self.predecessors[t]) == 0, "The task was already present."
        self.tasks.add(t)
        self.tasks.update(dependencies)
        # The predecessors are the tasks that need to be done before.
        self.predecessors[t] = set(dependencies)
        # The new task is a successor of its dependencies.
        for u in dependencies:
            self.successors[u].add(t)

    def add_or_task(self, t, dependencies):
        """Adds an OR task t with given dependencies."""
        # Makes sure we know about all tasks mentioned.
        assert t not in self.tasks or len(self.optionalPredecessors[t]) == 0, "The task was already present."
        self.tasks.add(t)
        self.tasks.update(dependencies)
        # The predecessors are the tasks that need to be done before.
        self.optionalPredecessors[t] = set(dependencies)
        # The new task is a successor of its dependencies.
        for u in dependencies:
            self.successors[u].add(t)

    @property
    def done(self):
        # YOUR CODE HERE
        return self.completed_tasks == self.tasks

    @property
    def uncompleted(self):
        """Returns the tasks that have not been completed.
        This is a property, so you can say scheduler.uncompleted rather than
        scheduler.uncompleted()"""
        return self.tasks - self.completed_tasks

    @property
    def available_tasks(self):
        """Returns the set of tasks that can be done in parallel.
        A task can be done if:
        - It is an AND task, and all its predecessors have been completed, or
        - It is an OR task, and at least one of its predecessors has been completed.
        And of course, we don't return any task that has already been
        completed."""
        availableTasks = set()
        for u in self.uncompleted:
            if (u in self.predecessors):
                available = True
                for x in self.predecessors[u]:
                    if (x not in self.completed_tasks):
                        available = False
                if (available):
                    availableTasks.add(u)       
            elif (u in self.optionalPredecessors):
                available = False 
                for x in self.optionalPredecessors[u]:
                    if (x in self.completed_tasks):
                        available = True
                if (available):
                    availableTasks.add(u)
            else:
                availableTasks.add(u)
            
        return availableTasks

    def mark_completed(self, t):
        """Marks the task t as completed, and returns the additional
        set of tasks that can be done (and that could not be
        previously done) once t is completed."""
        newTasks = set()
        previousAvailableTasks = self.available_tasks
        self.completed_tasks.add(t)
        newAvailableTasks  = self.available_tasks
        for task in newAvailableTasks:
            if task not in previousAvailableTasks:
                newTasks.add(task)
        return newTasks

    def show(self):
        return NotImplementedError()