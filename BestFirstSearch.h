#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <queue>
using std::priority_queue;

class LessThanByHeuristic {
public:    
    bool operator()(unique_ptr<Searchable> & a, unique_ptr<Searchable> & b) const {
        return a->heuristicValue() > b->heuristicValue(); // smaller first, reverse
    }
};

class BestFirstSearch {

protected:
    
    priority_queue<unique_ptr<Searchable>, std::vector<unique_ptr<Searchable>>, LessThanByHeuristic> searchSpace;
    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        searchSpace.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
		/*
	    while (!searchSpace.empty()) {
			std::cout << searchSpace.top()->heuristicValue() << " , ";
			searchSpace.pop();
		}
		cout << endl;
		cout << "debug" << endl;
		*/

        while (!searchSpace.empty()) {
            // If the solution on the front of the queue is a solution
            if (searchSpace.top()->isSolution()) {
                return searchSpace.top().get(); // return the pointer
            }
            
            ++nodes; // we've now looked at one more node, increment our counter
            
            // Steal the pointer to the board at the front of the queue, by moving it into a unique_ptr here
            // After this, the pointer on the front of the queue is `nullptr`...
			//cout << "heuristicValue is : " << searchSpace.top()->heuristicValue() << endl; // debug
            unique_ptr<Searchable> current(std::move(const_cast<unique_ptr<Searchable> &>(searchSpace.top())));
            
            // ...which can then be popped off the front of the queue
            searchSpace.pop();
            
            // Get the successors...
            vector<unique_ptr<Searchable>> successors = current->successors();
            
            for (auto & successor : successors) {
                // and push each one onto the back of queue.
                searchSpace.push(std::move(successor));
            }
        }
        return nullptr;
    }
};

// Do not edit below this line

#endif
