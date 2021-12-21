from collections import defaultdict
import networkx as nx # Library for displaying graphs.
import matplotlib.pyplot as plt

class DependencyScheduler(object):

    def __init__(self):
        self.tasks = set()
        # The successors of a task are the tasks that depend on it, and can
        # only be done once the task is completed.
        self.successors = defaultdict(set)
        # The predecessors of a task have to be done before the task.
        self.predecessors = defaultdict(set)
        self.completed_tasks = set() # completed tasks

    def add_task(self, t, dependencies):
        """Adds a task t with given dependencies."""
        # Makes sure we know about all tasks mentioned.
        assert t not in self.tasks or len(self.predecessors[t]) == 0, "The task was already present."
        self.tasks.add(t)
        self.tasks.update(dependencies)
        # The predecessors are the tasks that need to be done before.
        self.predecessors[t] = set(dependencies)
        # The new task is a successor of its dependencies.
        for u in dependencies:
            self.successors[u].add(t)

    def reset(self):
        self.completed_tasks = set()

    @property
    def done(self):
        return self.completed_tasks == self.tasks


    def show(self):
        """We use the nx graph to display the graph."""
        g = nx.DiGraph()
        g.add_nodes_from(self.tasks)
        g.add_edges_from([(u, v) for u in self.tasks for v in self.successors[u]])
        node_colors = ''.join([('g' if v in self.completed_tasks else 'r')
                           for v in self.tasks])
        nx.draw(g, with_labels=True)
        plt.show()

    @property
    def uncompleted(self):
        """Returns the tasks that have not been completed.
        This is a property, so you can say scheduler.uncompleted rather than
        scheduler.uncompleted()"""
        return self.tasks - self.completed_tasks

    def _check(self):
        """We check that if t is a successor of u, then u is a predecessor
        of t."""
        for u in self.tasks:
            for t in self.successors[u]:
                assert u in self.predecessors[t]

    @property
    def available_tasks(self):
        """Returns the set of tasks that can be done in parallel.
        A task can be done if all its predecessors have been completed.
        And of course, we don't return any task that has already been
        completed."""
        availableTasks = set()
        for u in self.uncompleted:
            available = True
            for x in self.predecessors[u]:
                if (x not in self.completed_tasks):
                    available = False
            if (available):
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

    def redo(self, t):
        """Mark the task t, and all its successors, as undone.
        Returns the set of successor tasks of t, with t included."""
        redoTasks = set()
        redoTasks.add(t)
        if t in self.completed_tasks:
            self.completed_tasks.remove(t)
        for u in self.successors[t]:
            if u in self.completed_tasks:
                self.completed_tasks.remove(u)
            redoTasks.add(u)
                        
        return redoTasks

    def cooking_redo(self, v):
        """Indicates that the task v needs to be redone, as something went bad.
        This is the "cooking" version of the redo, in which the redo propagates
        to both successors (as for code) and predecessors."""
        redoTasks = set()
        redoTasks.add(v)
        if v in self.completed_tasks:
            self.completed_tasks.remove(v)
        for u in self.successors[v]:
            if u in self.completed_tasks:
                self.completed_tasks.remove(u)
            redoTasks.add(u)
                    
        for x in self.predecessors[v]:
            if x in self.completed_tasks:
                self.completed_tasks.remove(x)
            redoTasks.add(x)            
        
        return redoTasks
