#include "connectedcities.h"
#include <list>
#include <unordered_map>
#include <iostream>
#include<iterator>
#include <map>
#include<algorithm>


using namespace std;


/*
I the undersigned promise that the submitted assignment is my own work. While I was 
free to discuss ideas with others, the work contained is my own. I recognize that 
should this not be the case; I will be subject to penalties as outlined in the course 
syllabus. 

Name: MASON WILKINS
Red ID: 825647427
*/

/**
 * <p>
 * Part A 
 * ---------------------------------------------------------------------------------------
 * For each city in a city list, find the list of reachable cities starting from the city 
 * following the train routes, and sort the cities in the descending order based on the 
 * number of their reachable cities.  
 * 
 * Required specifications - 
 *
 * Given a list of cities, and a list of one-way train routes from one city to another:
 *
 * 1) Create a graph with each node in the graph as an instance of the CityNode class,
 *    the graph can use any STL collection by your choice.
 *
 * 2) Populate the direct routes information to each CityNode's directRoutedCities collection.
 *    This is like an adjacency list graph representation.
 *
 * 3) For each city node in the graph, use Depth First Search algorithm to find all reachable 
 *    cities starting from the city following the train routes and store those reachable cities to 
 *    the CityNode's reachableCities collection. 
 *
 *    IMPORTANT: The reachable cities must include the starting city itself.  
 *
 *    Note: The train route can go from the starting city and stop at several cities 
 *          before reaching the destination city, all cities including the starting city and 
 *          the destination city along the path would be counted as reachable cities from 
 *          the city where the train starts.
 *
 * 4) Sort the cities in the descending order based on the number of their reachable cities,
 *    so that after sorting, starting from the first city in the sorted order, the train can 
 *    reach the greatest number of destination cities following the given one-way routes. 
 *
 * 5) You must use a RECURSIVE algorithm to implement the Depth First Search part to find
 *    all reachable cities from a starting city given the train routes, using an iterative 
 *    approach would result in a 30% penalty to your assignment 4 grade.  
 *
 * 6) You may add necessary helper functions as needed. Follow the comments for hints.
 * 
 * Assumptions - 
 * 1) Each city is represented by a unique two-letter code like "SD", "LA", 
 *    "SF", "SJ", "NY", etc.
 * 2) Each one-way train route is represented by a pair of city codes; for example, 
 *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to 
 *    Los Angeles (LA). 
 *
 * <p>
 * Part B
 * ---------------------------------------------------------------------------------------
 * Show the upper bound of the time complexity of this function would be O(c^2 + c * r) 
 * where:
 * c is the number of cities
 * r is the number of direct routes between cities
 * 
 * ---------------------------------------------------------------------------------------
 * @param  cities  a list of cities with each city identified by a two letter code
 * @param  routes  pairs of one-way train routes with each one-way train route represented 
 *                 by a pair of city codes; for example, route {"SD", "LA"} means train 
 *                 can go one-way from San Diego (SD) to Los Angeles (LA).
 *
 *                 NOTE: examples of routes are { {"SD", "LA"},
 *                                                {"LA", "SJ"},
 *                                                {"SJ", "SF"}
 *                                              }   
 *                       refer to driver.cpp for more examples.  
 *
 * @return       A list of CityNode in the descending order based on the number of their 
 *               reachable cities following the train routes
 
* @see         
*/


bool sortFunction(CityNode city1, CityNode city2){ // set of all posisble pairs which you will comapare while sorting, city1  and city2 can be any 2 values from vector

  if(city1.getReachableCities().size() > city2.getReachableCities().size()){//if the city1's size of reachble cities is greater than city2 return true meaning value goes before city2 in final vector to keep track of the descending order

    return true;

  }
  else if(city1.getReachableCities().size() == city2.getReachableCities().size()){//if city1's size is not larger than city2, but they have equal size

    if(city1.getCity() < city2.getCity()){ // compare the ascii values of the cities name for the tie breaker to sort and return true if ascii value is less than to keep track of ascending alph order

      return true;

    }

    else{

      return false; // else return false, therefore city2 comes before in the alphabet therefore would go before city1

    }
  }
  else{

    return false;// else return false if city2's length is greater than city1 sorting city2 before city1

  }
}

void dfsRecursiveSearch(string current,unordered_map<string, CityNode*> citygraph, unordered_map<string, bool> &visitedCities,  vector<string> &reachableCities){
  if(citygraph.size() == 0){ // base case if the graph is empty return cannot be searched

    return;

  }
  if(visitedCities[current]){// if current is in the visited set return and move to a different Node

    return; 

  }

  visitedCities[current] = true; // if the node passed in, is not in the vector, mark as true meaning the node has been visited, adding it to the set, therefore no duplicates

  reachableCities.push_back(current);// add the starting node to reachable cities because it begins the path

  CityNode* currentNode = citygraph.at(current);//create a new cityNode to keep track of the current city we are going to DFS from our graph

  vector<string> directRoutedCities = currentNode->getDirectRoutedCities(); //since directRoutes were populated in base function, shallow copy the cities into new vector in order to DFS each city within the list

  for(int i = 0; i < directRoutedCities.size(); i++){ // iterate through the list of cities from current node

    dfsRecursiveSearch(directRoutedCities.at(i), citygraph,visitedCities,reachableCities);//recurisvley call DFS on each new visited node, populating the reachable cities from the current parameter node, once all nodes have been visited, now in base function we have the reachable cities for each node

  }
}


vector<CityNode> ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(vector<string> cities, vector<pair<string, string>> trainRoutes) {

unordered_map<string, CityNode*> graph; // graph to populate

unordered_map<string, bool> visitedCities; // empty map to be populated in DFS 

vector<string> reachableCities; // empty vector to be populated in DFS


for(int i = 0; i < cities.size();i++){ // use for loop in order to iterate through all of the cities and make key value pairs to be inserted in the unordered map

  graph.insert(std::make_pair(cities.at(i),new CityNode(cities.at(i)))); // make of a new pair of the city name, and a  new CityNode with the starting city, and insert first pair into the graph

  }

for(int i  = 0; i < trainRoutes.size();i++){ //iterate through trainroutes holding the pairs of adjacent vertices

  pair<string,string> current = trainRoutes.at(i);//to keep track of the current pair, trainRoutes.at(i) would be "name", "name" therefore current gets populated with these values

  CityNode* currentCity = graph.at(current.first);// create new CityNode in order to populate the directRouted Cities(adjacent cities), access the current val in graph

  currentCity->addADirectRoutedCity(current.second);// from this current city after passing into constructor, add the key value pair from trainroutes to the adjacency list for this current node, populating the list

}

for(int i = 0; i < cities.size();i++){ // iterates through each city in vector cities

  visitedCities.clear();// make sure each data structure is empty before recurisve call to ensure correct dfs

  reachableCities.clear();// make sure each data structure is empty before recurisve call to ensure correct dfs


  dfsRecursiveSearch(cities.at(i), graph, visitedCities, reachableCities); // for each city in cities, iterate through cities in order to call the dfs on the current city, populating all reachable cities for cities.at(i)

  CityNode* currentCity = graph.at(cities.at(i)); // create new city node and pass in first city in order to begin populating the reachable cities per each node

  for(int j = 0; j < reachableCities.size();j++){// iterates through each reachable city

    currentCity->addReachableCity(reachableCities.at(j)); //once each value has been trasversed in dfs, use each node visted and populate the new cityNodes reachable cities, which populates for every city once all are passed in

  }

}

vector<CityNode> sorted; // create new vector that will have the cities sorted

int c = 0;//iterative varaible

while(c < cities.size()){ // iterate through sorted populating each city, and its cityNode object inot sorted in order to sort it in ascending alph, descending numerical
  sorted.push_back(*graph.at(cities.at(c)));//use pointer to our graph in order to pass in reference to our sorted vector
  c++;
}

sort(sorted.begin(), sorted.end(), sortFunction);// since each city has an object that needs to be sorted, we use a comparator fucntion, this comapres 2 objects values without overloaded function
                                                //start at the beging node, until end node using the sortFunctions logic to sort each value

  
  for(int i = 0; i < cities.size();i++){
    delete graph.at(cities.at(i)); //  iterate through each value in graph to free memory on the heap
  }

  return sorted; 
}



