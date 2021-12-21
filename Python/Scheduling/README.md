# Scheduling with dependencies

## Basic Scheduler

This object will have the following operations:

- add_task: we should be able to add a task, along with the task dependencies.
- reset: indicating that we are about to run the sequences of tasks again.
- available_tasks: this property should return the set of things that we can do in parallel.
- mark_completed: used to notify the scheduler that we have completed a task. This should return the set of new tasks that we can do due to this task being completed; we can do these tasks in parallel alongside with the others that we are already doing.
- all_done: returns True/False according to whether we have completed all tasks.
- redo: marks a task and all its successors to be redone -- that is, it unmarks them as done.
- cooking_redo: In code, when one file changes, you only need to redo the things that depend on that file. In cooking, it is different: even if nothing changed in the bacon, onions, and cooked pasta, once you add to it rotten eggs you have to redo the pasta, bacon, onions, etc, as well, as they have now been contaminated. Different from redo, cooking_redo makes successors AND predecessors to be redone. 

The scheduler class will be implemented in similar fashion to the graph class, with tasks corresponding to graph vertices, and dependencies represented as edges. The difference is that here, given a vertex (that is, a task)  `v` , it will be useful to be able to access both:

- the predecessors of  `v` , that is, the tasks  u  that are declared as prerequisites of  v , and
- the successors of  `v` , that is, the tasks  u  such that  v  was declared as a prerequisite for  u .

## Slightly More Complicated Scheduler
It is basically the same as the basic scheduler except with two key differences, these two new methods:
* `add_and_task(self, t, dependencies)` adds a task `t` with list of dependencies `dependencies`, so that `t` can be done when _all_ of the dependencies are done.  The task `t` is called an AND node in the dependency graph. 
* `add_or_task(self, t, dependencies)` adds a task `t` with list of dependencies `dependencies`, so that `t` can be done when _at least one_ of the dependencies is done.  The task `t` is called an OR node in the dependency graph. 

## Schedule Runner

This is a class that specifically runs a scheduler.

An object of class RunSchedule is initialized with the basic scheduler. It then has the following methods:

- reset: mark all tasks as not completed.
- step: perform one step in the schedule, completing a single task.
- run: performs all steps in the schedule, until completion.
- done: indicates that all tasks have been done.

While both classes could technically be combined into one, the idea in keeping the two classes separate is clarity of goals:

- The scheduler is concerned with what can be done next.
- The runner is concerned with any practical constraint to the execution, and with the choice of what, among the possible, is actually done.