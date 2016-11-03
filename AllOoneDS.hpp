#ifndef ALLOONEDS_HPP
#define ALLOONEDS_HPP

#include <unordered_map>
#include <string>

using std::string ;

struct keyNode ;
struct valueNode ;

class AllOne 
{
	public:
    
	/** Initialize the data structure here. */
    AllOne() ;
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) ;
	
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) ;
  
	/** Insert a key node 'curKey' under the value node 'Value' **/
	void InsertKeyNode(int Value, keyNode* curKey) ;

	/** Insert a new value node next/prev to the 'curNode' (determined by the direction) **/
	void InsertValueNode(valueNode* curNode, int direction) ;
	
	/** Construct a first value node (value=1) if needed **/	
	void valueNodeOneConstructor() ; 
	
	/** Check if a value node has no key nodes, destroy it if no key nodes **/
	void EmptyValueNodeChecker(valueNode* emptyNode) ;
	
		
    /** Returns one of the keys with maximal value. */
    string getMaxKey() ;
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() ;
	
private:
	
	valueNode* head ;
	valueNode* tail ;
	std::unordered_map<string, keyNode*> keyDict ;
	std::unordered_map<int, valueNode*>  valueDict ;
	
} ;

#endif //* ALLOONEDS_HPP *//
